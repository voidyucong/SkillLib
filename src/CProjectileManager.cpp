//
//  CProjectileManager.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/22.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CProjectileManager.hpp"
#include "CLinearProjectile.hpp"
#include "CTrackingProjectile.hpp"
#include "CAbility.hpp"
#include "CAbilityEntity.hpp"
#include "CTargetSearchType.hpp"

CLinearProjectile* CProjectileManager::CreateLinearProjectile(CLinearProjectileData* data,
                                                              CAbilityEntity* caster,
                                                              CAbility* ability,
                                                              const CVector& direction,
                                                              const CVector& castPosition,
                                                              CTargetSearchType* targetType)
{
    CLinearProjectile* projectile = new CLinearProjectile(data);
    projectile->SetCaster(caster);
    projectile->SetAbility(ability);
    projectile->SetDirection(direction);
    projectile->SetCastPosition(castPosition);
    projectile->SetTargetType(targetType);
//    projectile->Execute();
    return projectile;
}

CTrackingProjectile* CProjectileManager::CreateTrackingProjectile(CTrackingProjectileData* data,
                                                                  CAbilityEntity* caster,
                                                                  CAbility* ability,
                                                                  CAbilityEntity* target,
                                                                  const CVector& castPosition)
{
    CTrackingProjectile* projectile = new CTrackingProjectile(data);
    projectile->SetCaster(caster);
    projectile->SetTarget(target);
    projectile->SetAbility(ability);
    projectile->SetCastPosition(castPosition);
    return projectile;
}
