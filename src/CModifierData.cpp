//
//  CModifierData.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/14.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CModifierData.hpp"
#include "CModifierEvent.hpp"
#include "COperate.hpp"

CModifierData* CModifierData::Clone() {
    CModifierData* modifier = new CModifierData();
    modifier->isMulti_ = isMulti_;      // 是否可叠加
    modifier->maxMulti_ = maxMulti_;    // 最高叠加层数
    modifier->duration_ = duration_;    // 持续时间
    modifier->isPassive_ = isPassive_;    // 是否被动
    modifier->isHidden_ = isHidden_;     // 是否隐藏图标
    modifier->isBuff_ = isBuff_;       // 是否正面buff
    modifier->isDebuff_ = isDebuff_;     // 是否负面buff
    modifier->isPurgable_ = isPurgable_;   // 是否可被清除
    modifier->thinkInterval_ = thinkInterval_;       // 间隔
    modifier->textureName_ = textureName_;   // 图标名称
    modifier->effectName_ = effectName_;    // 特效名
    modifier->modelName_ = modelName_;     // 模型名，默认空
    modifier->name_ = name_;
    
    // 事件集合
    for (auto iter = events_.begin(); iter != events_.end(); ++iter) {
        modifier->SetModifierEvent(iter->first, iter->second->Clone());
    }
    // 操作集合
    for (auto iter = operators_.begin(); iter != operators_.end(); ++iter) {
        modifier->AddOperate((*iter)->Clone());
    }
    
    modifier->properties_ = properties_;
    
    return modifier;
}
