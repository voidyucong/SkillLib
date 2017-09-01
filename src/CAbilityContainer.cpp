//
//  CAbilityContainer.cpp
//  SkillLib
//
//  Created by yucong on 2017/8/31.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CAbilityContainer.hpp"
#include <assert.h>
#include "CAbility.hpp"

CAbilityContainer::CAbilityContainer() {
    
}

CAbilityContainer::~CAbilityContainer() {
    for (auto a : abilities_) {
        delete a;
        a = 0;
    }
}

void CAbilityContainer::SetAbility(CAbility* ability, int index) {
    assert(index >= 0);
//    abilities_[index] = ability;
    abilities_.insert(abilities_.begin(), ability);
}

CAbility* CAbilityContainer::GetAbility(int index) {
    assert(index >= 0);
    return abilities_[index];
}
