//
//  CMaster.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/29.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CMaster_hpp
#define CMaster_hpp

#include <iostream>
#include "CObject.hpp"
#include "SkillTypes.h"

class CAbility;
class CAbilityEntity;

class CMaster {
public:
    static void ApplyDamage(CAbilityEntity* victim,
                            CAbilityEntity* attacker,
                            float damage,
                            ABILITY_DAMAGE_TYPE type,
                            long damgeFlags,
                            CAbility* ability = NULL);
    
    static void ApplyHealth(CAbilityEntity* target,
                            CAbilityEntity* source,
                            float value);
};

#endif /* CMaster_hpp */
