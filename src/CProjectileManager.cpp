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

CLinearProjectile* CProjectileManager::CreateLinearProjectile(CLinearProjectileData* data) {
    CLinearProjectile* projectile = new CLinearProjectile();
    projectile->Execute();
    return projectile;
}

CTrackingProjectile* CProjectileManager::CreateTrackingProjectile(CTrackingProjectileData* data) {
    CTrackingProjectile* projectile = new CTrackingProjectile();
    
    return projectile;
}
