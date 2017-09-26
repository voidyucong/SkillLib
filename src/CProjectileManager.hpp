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

class CAbilibyEntity;
class CProjectile;
class CLinearProjectile;
class CTrackingProjectile;
class CLinearProjectileData;
class CTrackingProjectileData;

class CProjectileManager {
public:
    static CLinearProjectile* CreateLinearProjectile(CLinearProjectileData* data);
    static CTrackingProjectile* CreateTrackingProjectile(CTrackingProjectileData* data);
    
private:
    std::map<int, CProjectile*> cache_;
};

#endif /* CProjectileManager_hpp */
