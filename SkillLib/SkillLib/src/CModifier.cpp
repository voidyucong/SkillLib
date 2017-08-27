//
//  CModifier.cpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CModifier.hpp"


CModifier::CModifier()
: isMulti_(true)
, duration_(0)
, isPassive_(false)
, isHidden_(false)
, isBuff_(false)
, isDeBuff_(false)
, isPurgable_(false)
, thinkInterval_(0.f)
, textureName_(NULL)
, effectName_(NULL)
, modelName_(NULL)
{
    
}

CModifier::~CModifier() {
    
}