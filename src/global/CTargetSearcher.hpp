//
//  CTargetSearcher.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/19.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CTargetSearcher_hpp
#define CTargetSearcher_hpp

#include <iostream>
#include <vector>
#include "CObject.hpp"
#include "SkillTypes.h"

class CAbility;
class CAbilityEntity;
class CAbilityValue;
class CTargetStack;
class CTargetSearchType;

class CTargetSearcher : public CObject {
public:
    static void HandleTargetStack(CAbilityEntity* caster,
                                  CAbility* ability,
                                  CTargetStack* stack,
                                  CTargetSearchType* type);
    
    // 用于ability目标查找
    static bool FindAbilityTargets(std::vector<CAbilityEntity*>& ret,
                                   CAbilityEntity* caster,
                                   const CVector& center,
                                   const CAbilityValue* radius,
                                   TARGET_TEAMS teams,
                                   TARGET_TYPES types,
                                   TARGET_FLAGS flags,
                                   long behavior,
                                   CAbilityValue* maxTargets);
    
    // 用于modifier、operate目标查找
    static bool FindModifierTargets(std::vector<CAbilityEntity*>& ret,
                                    CAbilityEntity* caster,
                                    const CVector& center,
                                    const CAbilityValue* radius,
                                    TARGET_TEAMS teams,
                                    TARGET_TYPES types,
                                    TARGET_FLAGS flags,
                                    CAbilityValue* maxTargets);
    
    // 是否使用父节点的目标栈
    static bool IsUseParent(const CAbilityValue* radius);
                                    
    // 搜索范围内符合条件的entity
    static bool FindEntitesInRadius(std::vector<CAbilityEntity*>& ret,
                                    CAbilityEntity* caster,
                                    const CCircle& circle,
                                    TARGET_TEAMS teams,
                                    TARGET_TYPES types,
                                    TARGET_FLAGS flags,
                                    int maxTargets = 0);
    
    // 搜索线段内符合条件的entity
    static bool FindEntitesInLine(std::vector<CAbilityEntity*>& ret,
                                  CAbilityEntity* caster,
                                  const CVector& startPosition,
                                  const CVector& endPosition,
                                  float width,
                                  float radian,
                                  TARGET_TEAMS teams,
                                  TARGET_TYPES types,
                                  TARGET_FLAGS flags,
                                  int maxTargets = 0);
    
    // 查找复合条件的所有entity
    static bool FindEntites(std::vector<CAbilityEntity*>& ret,
                            CAbilityEntity* caster,
                            TARGET_TEAMS teams,
                            TARGET_TYPES types,
                            TARGET_FLAGS flags);
    
    // 检测vec中的entity与指定线段是否存在碰撞
    static bool CollisionLine(TARGET_LIST& vec,
                              CAbilityEntity* caster,
                              const CVector& startPosition,
                              const CVector& endPosition,
                              float width,
                              float radian,
                              int maxTargets);
    
    // 检测vec中的entity与指定范围是否存在碰撞
    static bool CollisionCircle(TARGET_LIST& vec,
                                CAbilityEntity* caster,
                                const CCircle& circle,
                                int maxTargets);
    
    static bool CollisionPoint(TARGET_LIST& vec,
                               CAbilityEntity* caster,
                               const CVector& point,
                               int maxTargets);
    
    static bool IsPointInLine(const CVector& point, const CVector& lt, const CVector& lb, const CVector& rt, const CVector& rb);
};

#endif /* CTargetSearcher_hpp */
