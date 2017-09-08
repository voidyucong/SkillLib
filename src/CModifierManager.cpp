//
//  CModifierManager.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/8.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CModifierManager.hpp"

static CModifierManager* s_pInstance = NULL;

CModifierManager::CModifierManager() {
    
}

CModifierManager::~CModifierManager() {
    
}

CModifierManager* CModifierManager::getInstance() {
    if (!s_pInstance) {
        s_pInstance = new CModifierManager();
    }
    return s_pInstance;
}

void CModifierManager::update(float dt) {
    
}
