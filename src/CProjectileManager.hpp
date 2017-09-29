//
//  CProjectileManager.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/22.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CProjectileManager_hpp
#define CProjectileManager_hpp

#include <iostream>
#include <map>
#include "CObject.hpp"

class CAbility;
class CAbilityEntity;
class CProjectile;
class CLinearProjectile;
class CTrackingProjectile;
class CLinearProjectileData;
class CTrackingProjectileData;
class CTargetSearchType;

class CProjectileManager {
public:
    static CLinearProjectile* CreateLinearProjectile(CLinearProjectileData* data,
                                                     CAbilityEntity* caster,
                                                     CAbility* ability,
                                                     const CVector& direction,
                                                     const CVector& castPosition,
                                                     CTargetSearchType* targetType);
    static CTrackingProjectile* CreateTrackingProjectile(CTrackingProjectileData* data,
                                                         CAbilityEntity* caster,
                                                         CAbility* ability,
                                                         CAbilityEntity* target,
                                                         const CVector& castPosition);
    
private:
    std::map<int, CProjectile*> cache_;
};

#endif /* CProjectileManager_hpp */
