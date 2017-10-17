//
//  CTargetSearcher.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/19.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CTargetSearcher.hpp"
#include "CAbilityEntity.hpp"
#include "CAbilityEntityManager.hpp"
#include "CAbilityValue.hpp"
#include "CTargetStack.hpp"
#include "MathUtil.hpp"

void Local_FilterType(TARGET_LIST& ret, CAbilityEntity* caster, TARGET_TYPES type) {
    if (type == TARGET_TYPE_ALL || type == TARGET_TYPE_NONE) return;
    for (auto iter = ret.begin(); iter != ret.end();) {
        auto target = *iter;
        if ((int)type != (int)target->GetType())
            iter = ret.erase(iter);
        else
            ++iter;
    }
}

// 筛选距离目标点最近的xx个目标
void Local_FilterMaxTargets(TARGET_LIST& ret, const CVector& pivot, float maxTargets) {
    if (maxTargets > 0 && maxTargets < ret.size()) {
        // 筛选距离最近的几个
        std::sort(ret.begin(), ret.end(), [&](CAbilityEntity* entity1, CAbilityEntity* entity2) {
            return entity1->GetPosition().GetDistance(pivot) < entity2->GetPosition().GetDistance(pivot);
        });
        ret.erase(ret.begin() + maxTargets, ret.end());
    }
}

// 处理目标栈
// 判断使用父节点的目标栈还是自己的
// 如果使用父节点的需要判断目标栈是否存在，然后根据条件筛选
// 如果使用自己的则直接查找
void CTargetSearcher::HandleTargetStack(CAbilityEntity* caster,
                                        CAbility* ability,
                                        CTargetStack* stack,
                                        CTargetSearchType* type)
{
    // 如果使用父节点的目标，需要判断父节点的目标是否存在
    if (CTargetSearcher::IsUseParent(type->GetRadius())) {
        assert(stack->GetParent());
        assert(stack->GetParent()->GetValid());
        auto list = stack->GetValid()->GetTargets();
        stack->DestroySelf();
        stack->ConstructSelf();
        // 单体
        if (type->GetSingle() != TARGET_CENTER_NONE) {
            // 释放者
            if (type->GetSingle() == TARGET_CENTER_CASTER) {
                stack->PushSelf(caster);
            }
            // 目标者
            else if (type->GetSingle() == TARGET_CENTER_TARGET) {
                assert(stack->GetParent()->GetValid()->GetTargets().size() <= 1);
                if (stack->GetParent()->GetValid()->GetTargets().size() > 0) {
                    stack->PushSelf(stack->GetParent()->GetValid()->GetTargets()[0]);
                }
            }
            // 攻击者
            else if (type->GetSingle() == TARGET_CENTER_ATTACKER) {
                stack->PushSelf(caster->GetAttacker());
            }
        }
        else {
            // 筛选
            for (auto iter = list.begin(); iter != list.end(); ++iter) {
                auto target = *iter;
                if (type->GetTeams() == TARGET_TEAM_BOTH || type->GetTeams() == TARGET_TEAM_NONE) {
                    stack->PushSelf(target);
                }
                else if (type->GetTeams() == TARGET_TEAM_FRIENDLY && target->GetTeamId() == caster->GetTeamId()) {
                    stack->PushSelf(target);
                }
                else if (type->GetTeams() == TARGET_TEAM_ENEMY && target->GetTeamId() != caster->GetTeamId()) {
                    stack->PushSelf(target);
                }
                
            }
            
            if (type->GetTypes() != TARGET_TYPE_ALL && type->GetTypes() != TARGET_TYPE_NONE) {
                for (auto iter = stack->GetSelf()->GetTargets().begin(); iter != stack->GetSelf()->GetTargets().end();) {
                    auto target = *iter;
                    if ((int)type->GetTypes() != (int)target->GetType())
                        iter = stack->EraseSelf(iter);
                    else
                        ++iter;
                }
            }
        }
    }
    // 使用自己的目标
    else {
        if (!stack->GetSelf()) {
            stack->SetSelf(new CTargetStackItem());
        }
        CTargetStackItem* item = stack->GetSelf();
        item->ClearTargets();
        CTargetSearcher::FindModifierTargets(item->GetTargets(),
                                             caster,
                                             caster->GetPosition(),
                                             type->GetRadius() ? type->GetRadius()->GetArrayValueByIndex(ability->GetLevel() - 1) : NULL,
                                             type->GetTeams(),
                                             type->GetTypes(),
                                             type->GetFlags(),
                                             type->GetMaxTargets() ? type->GetMaxTargets()->GetArrayValueByIndex(ability->GetLevel() - 1) : NULL);
    }
}

//Ability
//  无目标：
//      1.无目标也可以释放，有目标对目标释放，Behavior包含ABILITY_BEHAVIOR_NO_TARGET、Behavior包含ABILITY_BEHAVIOR_POINT（例如扁鹊1、2技能），radius存在；
//      2.有无目标都照常释放，Behavior包含ABILITY_BEHAVIOR_NO_TARGET（例如狄仁杰2技能），radius存在；
//      3.对自己释放，radius为空；
//  有目标：
//      1.范围内有目标才能释放，Behavior包含ABILITY_BEHAVIOR_UNIT_TARGET，radius存在；
bool CTargetSearcher::FindAbilityTargets(std::vector<CAbilityEntity*>& ret,
                                         CAbilityEntity* caster,
                                         const CVector& center,
                                         const CAbilityValue* radius,
                                         TARGET_TEAMS teams,
                                         TARGET_TYPES types,
                                         TARGET_FLAGS flags,
                                         long behavior,
                                         CAbilityValue* maxTargets)
{
    if (behavior & ABILITY_BEHAVIOR_NO_TARGET) {
        // 对自己释放
        if (!radius) {
            ret.push_back(caster);
            return ret.size() > 0;
        }
        // radius == -1 全屏
        if (radius->GetValue<float>() > 0) {
            FindEntitesInRadius(ret,
                                caster,
                                CCircle(caster->GetPosition(), radius->GetValue<float>()),
                                teams,
                                types,
                                flags,
                                maxTargets ? maxTargets->GetValue<float>() : 0);
        }
    }
    else if (behavior & ABILITY_BEHAVIOR_UNIT_TARGET) {
        if (radius && radius->GetValue<float>() > 0) {
            FindEntitesInRadius(ret,
                                caster,
                                CCircle(caster->GetPosition(), radius->GetValue<float>()),
                                teams,
                                types,
                                flags,
                                maxTargets ? maxTargets->GetValue<float>() : 0);
        }
    }
    
    return ret.size() > 0;
}

//Modifier
//  从父节点的目标中获取：
//      1.radius不存在
//  查找自己的目标：
//      1.radius存在
bool CTargetSearcher::FindModifierTargets(std::vector<CAbilityEntity*>& ret,
                                          CAbilityEntity* caster,
                                          const CVector& center,
                                          const CAbilityValue* radius,
                                          TARGET_TEAMS teams,
                                          TARGET_TYPES types,
                                          TARGET_FLAGS flags,
                                          CAbilityValue* maxTargets)
{
    std::cout << radius->GetValue<float>() << (radius->GetValue<float>() > 0) << std::endl;
    if (radius && radius->GetValue<float>() > 0) {
        FindEntitesInRadius(ret,
                            caster,
                            CCircle(caster->GetPosition(), radius->GetValue<float>()),
                            teams,
                            types,
                            flags,
                            maxTargets ? maxTargets->GetValue<float>() : 0);
    }
    return ret.size() > 0;
}

// 使用自己的查找器还是父节点的
bool CTargetSearcher::IsUseParent(const CAbilityValue* radius) {
    return radius == NULL;
}

bool CTargetSearcher::FindEntitesInRadius(std::vector<CAbilityEntity*>& ret,
                                          CAbilityEntity* caster,
                                          const CCircle& circle,
                                          TARGET_TEAMS teams,
                                          TARGET_TYPES types,
                                          TARGET_FLAGS flags,
                                          int maxTargets)
{
    FindEntites(ret, caster, teams, types, flags);
    
    // radius == -1 代表全屏
    if (circle.GetRadius() <= -1) {
        return ret.size() > 0;
    }
    // 选择范围内的
    for (auto iter = ret.begin(); iter != ret.end();) {
        auto target = *iter;
        if (!circle.IntersectsPoint(target->GetPosition()))
            iter = ret.erase(iter);
        else
            ++iter;
    }
    
    Local_FilterMaxTargets(ret, circle.GetCenter(), maxTargets);
    
    return ret.size() > 0;
}

bool CTargetSearcher::FindEntitesInLine(std::vector<CAbilityEntity*>& ret,
                                        CAbilityEntity* caster,
                                        const CVector& startPosition,
                                        const CVector& endPosition,
                                        float width,
                                        float radian,
                                        TARGET_TEAMS teams,
                                        TARGET_TYPES types,
                                        TARGET_FLAGS flags,
                                        int maxTargets)
{
    FindEntites(ret, caster, teams, types, flags);
    
    // 构建矩形线段
    CVector lt(startPosition.GetX(), startPosition.GetY() + width / 2);
    CVector lb(startPosition.GetX(), startPosition.GetY() - width / 2);
    CVector rt(endPosition.GetX(), endPosition.GetY() + width / 2);
    CVector rb(endPosition.GetX(), endPosition.GetY() - width / 2);
//    lt = lt.rotateByAngle(startPosition, radian);
//    lb = lb.rotateByAngle(startPosition, radian);
//    rt = rt.rotateByAngle(startPosition, radian);
//    rb = rb.rotateByAngle(startPosition, radian);
    
    // 选择范围内的
    for (auto iter = ret.begin(); iter != ret.end();) {
        auto target = *iter;
        CVector pos = target->GetPosition().rotateByAngle(startPosition, -radian);
        if (!IsPointInLine(target->GetPosition(), lt, lb, rt, rb))
            iter = ret.erase(iter);
        else
            ++iter;
    }
    CVector centerLine(CVector((endPosition.GetX()-startPosition.GetX()) / 2, (endPosition.GetY()-startPosition.GetY())).rotateByAngle(startPosition, radian));
    Local_FilterMaxTargets(ret, centerLine, maxTargets);
    return ret.size() > 0;
}

bool CTargetSearcher::FindEntites(std::vector<CAbilityEntity*>& ret,
                                  CAbilityEntity* caster,
                                  TARGET_TEAMS teams,
                                  TARGET_TYPES types,
                                  TARGET_FLAGS flags)
{
    // 选择队伍
    switch (teams) {
        case TARGET_TEAM_BOTH: CAbilityEntityManager::getInstance()->GetAllEntity(ret); break;
        case TARGET_TEAM_FRIENDLY: ret = CAbilityEntityManager::getInstance()->GetTeam(caster->GetTeamId()); break;
        case TARGET_TEAM_ENEMY: ret = CAbilityEntityManager::getInstance()->GetOtherTeam(caster->GetTeamId()); break;
        case TARGET_TEAM_NONE: return false;
    }
    // types
    for (auto iter = ret.begin(); iter != ret.end();) {
        auto target = *iter;
        if ((int)types != (int)target->GetType())
            iter = ret.erase(iter);
        else
            ++iter;
    }
    // flags
    
    return ret.size() > 0;
}

bool CTargetSearcher::CollisionLine(TARGET_LIST& vec,
                                     CAbilityEntity* caster,
                                     const CVector& startPosition,
                                     const CVector& endPosition,
                                     float width,
                                     float radian,
                                     int maxTargets)
{
    CRect rect(endPosition.GetX() - startPosition.GetX(), width, startPosition.GetX(), startPosition.GetY() - width/2);
    
    for (auto iter = vec.begin(); iter != vec.end();) {
        auto target = *iter;
        CVector lt(target->GetPosition().GetX() - target->GetSize().width/2, target->GetPosition().GetY() + target->GetSize().height);
        CVector lb(target->GetPosition().GetX() - target->GetSize().width/2, target->GetPosition().GetY());
        CVector rt(target->GetPosition().GetX() + target->GetSize().width/2, target->GetPosition().GetY() + target->GetSize().height);
        CVector rb(target->GetPosition().GetX() + target->GetSize().width/2, target->GetPosition().GetY());
        if (rect.ContainsPoint(lt) || rect.ContainsPoint(lb) || rect.ContainsPoint(rt) || rect.ContainsPoint(rb))
            ++iter;
        else
            iter = vec.erase(iter);
    }
    CVector centerLine(CVector((endPosition.GetX()-startPosition.GetX()) / 2, (endPosition.GetY()-startPosition.GetY())).rotateByAngle(startPosition, radian));
    Local_FilterMaxTargets(vec, centerLine, maxTargets);
    
    return vec.size() > 0;
}

// 判断矩形和圆形是否相交
bool CTargetSearcher::CollisionCircle(TARGET_LIST& vec,
                                       CAbilityEntity* caster,
                                       const CCircle& circle,
                                       int maxTargets)
{
    for (auto iter = vec.begin(); iter != vec.end();) {
        auto target = *iter;
        CRect rect(target->GetSize().width,
                   target->GetSize().height,
                   target->GetPosition().GetX() - target->GetSize().width/2,
                   target->GetPosition().GetY());
        if (circle.IntersectsRect(rect))
            ++iter;
        else
            iter = vec.erase(iter);
    }
    Local_FilterMaxTargets(vec, circle.GetCenter(), maxTargets);
    
    return vec.size() > 0;
}

bool CTargetSearcher::CollisionPoint(TARGET_LIST& vec,
                                      CAbilityEntity* caster,
                                      const CVector& point,
                                      int maxTargets)
{
    return vec.size() > 0;
}

// 判断点与其他四个角的面积与矩形面积是否相等
bool CTargetSearcher::IsPointInLine(const CVector& point, const CVector& lt, const CVector& lb, const CVector& rt, const CVector& rb) {
//    printf("%f-%f %f-%f %f-%f %f-%f\n", lt.GetX(), lt.GetY(), lb.GetX(), lb.GetY(), rt.GetX(), rt.GetY(), rb.GetX(), rb.GetY());
//    printf("%f-%f\n", point.GetX(), point.GetY());
    float area = fabsf(lt.GetY() - lb.GetY()) * fabsf(rt.GetX() - lt.GetX());
    float sumarea = SKB::MathUtil::TriangleArea(lt, lb, point) +
                    SKB::MathUtil::TriangleArea(lb, rb, point) +
                    SKB::MathUtil::TriangleArea(rb, rt, point) +
                    SKB::MathUtil::TriangleArea(lt, rt, point);
//    printf("area:%f total:%f\n", area, SKB::MathUtil::TriangleArea(lt, lb, point) +
//           SKB::MathUtil::TriangleArea(lb, rb, point) +
//           SKB::MathUtil::TriangleArea(rb, rt, point) +
//           SKB::MathUtil::TriangleArea(lt, rt, point));
    return fabsf(area - sumarea) < 1;
}
