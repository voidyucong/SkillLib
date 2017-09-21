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


void Local_FilterType(TARGET_LIST& ret, CAbilityEntity* caster, TARGET_TYPES type) {
    if (type == TARGET_TYPE_ALL || type == TARGET_TYPE_NONE) return;
    for (auto iter = ret.begin(); iter != ret.end();) {
        auto target = *iter;
        if ((int)type != (int)target->GetType())
            ret.erase(iter);
        else
            ++iter;
    }
}

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
        auto item = new CTargetStackItem();
        stack->SetSelf(item);
        // 筛选
        for (auto iter = list.begin(); iter != list.end(); ++iter) {
            auto target = *iter;
            if (type->GetTeams() == TARGET_TEAM_BOTH || type->GetTeams() == TARGET_TEAM_NONE) {
                item->GetTargets().push_back(target);
            }
            else if (type->GetTeams() == TARGET_TEAM_FRIENDLY && target->GetTeamId() == caster->GetTeamId()) {
                item->GetTargets().push_back(target);
            }
            else if (type->GetTeams() == TARGET_TEAM_ENEMY && target->GetTeamId() != caster->GetTeamId()) {
                item->GetTargets().push_back(target);
            }
            
        }
        
        if (type->GetTypes() != TARGET_TYPE_ALL && type->GetTypes() != TARGET_TYPE_NONE) {
            for (auto iter = item->GetTargets().begin(); iter != item->GetTargets().end();) {
                auto target = *iter;
                if ((int)type->GetTypes() == (int)target->GetType())
                    item->GetTargets().erase(iter);
                else
                    ++iter;
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
                                caster->GetPosition(),
                                radius->GetValue<float>(),
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
                                caster->GetPosition(),
                                radius->GetValue<float>(),
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
                            caster->GetPosition(),
                            radius->GetValue<float>(),
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
                                          const CVector& center,
                                          float radius,
                                          TARGET_TEAMS teams,
                                          TARGET_TYPES types,
                                          TARGET_FLAGS flags,
                                          int maxTargets)
{
    // 选择队伍
    switch (teams) {
        case TARGET_TEAM_BOTH: ret = CAbilityEntityManager::getInstance()->GetAllEntity(); break;
        case TARGET_TEAM_FRIENDLY: ret = CAbilityEntityManager::getInstance()->GetTeam(caster->GetTeamId()); break;
        case TARGET_TEAM_ENEMY: ret = CAbilityEntityManager::getInstance()->GetOtherTeam(caster->GetTeamId()); break;
        case TARGET_TEAM_NONE: return false;
    }
    // types
    if (types != TARGET_TYPE_ALL && types != TARGET_TYPE_NONE) {
        for (auto iter = ret.begin(); iter != ret.end();) {
            auto target = *iter;
            if ((int)types != (int)target->GetType())
                ret.erase(iter);
            else
                ++iter;
        }
    }
    
    // flags
    
    // radius == -1 代表全屏
    if (radius <= -1) {
        return ret.size() > 0;
    }
    // 选择范围内的
    for (auto iter = ret.begin(); iter != ret.end();) {
        auto target = *iter;
        if (!IsPointInCircle(target->GetPosition(), center, radius))
            ret.erase(iter);
        else
            ++iter;
    }
    
    if (maxTargets > 0 && ret.size() > maxTargets) {
        int count = maxTargets;
        for (auto iter = ret.begin(); iter != ret.end();) {
            ret.erase(iter);
            --count;
            if (count == 0) break;
        }
    }
    
    return ret.size() > 0;
}

bool CTargetSearcher::FindEntitesInLine(std::vector<CAbilityEntity*>& ret,
                                        CAbilityEntity* caster,
                                        const CVector& starPosition,
                                        const CVector& endPosition,
                                        float width,
                                        TARGET_TEAMS teams,
                                        TARGET_TYPES types,
                                        TARGET_FLAGS flags)
{
    // 选择队伍
    switch (teams) {
        case TARGET_TEAM_BOTH: ret = CAbilityEntityManager::getInstance()->GetAllEntity(); break;
        case TARGET_TEAM_FRIENDLY: ret = CAbilityEntityManager::getInstance()->GetTeam(caster->GetTeamId()); break;
        case TARGET_TEAM_ENEMY: ret = CAbilityEntityManager::getInstance()->GetOtherTeam(caster->GetTeamId()); break;
        case TARGET_TEAM_NONE: return false;
    }
    // types
    for (auto iter = ret.begin(); iter != ret.end();) {
        auto target = *iter;
        if ((int)types != (int)target->GetType())
            ret.erase(iter);
        else
            ++iter;
    }
    // flags
    
    // 选择范围内的
    for (auto iter = ret.begin(); iter != ret.end();) {
        auto target = *iter;
        
        if (!IsPointInLine(target->GetPosition(), CLine()))
            ret.erase(iter);
        else
            ++iter;
    }
    return ret.size() > 0;
}

bool CTargetSearcher::IsPointInCircle(const CVector& point, const CVector& center, float radius) {
    return center.GetDistance(point) <= radius;
}

bool CTargetSearcher::IsPointInLine(const CVector& point, const CLine& rect) {
    return rect.containsPoint(point);
}
