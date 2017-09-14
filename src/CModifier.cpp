//
//  CModifier.cpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CModifier.h"
#include "CModifierEvent.hpp"
#include "COperate.hpp"
#include "CAbility.hpp"
#include "CAbilityEntity.hpp"

CModifier::CModifier()
{
    
}

CModifier::~CModifier() {
    for (auto iter = base.events_.begin(); iter != base.events_.end(); iter++) {
        delete iter->second;
    }
    base.events_.clear();
    for (auto operate : base.operators_) {
        delete operate;
        operate = NULL;
    }
    base.operators_.clear();
}

void CModifier::Destroy() {
    delete this;
}

void CModifier::SetModifierEvent(MODIFIER_EVENT_TYPE type, CModifierEvent* event) {
    base.events_[type] = event;
}

int CModifier::ExecuteEvent(MODIFIER_EVENT_TYPE type, CAbilityEntity *entity, CAbility *ability) {
    CModifierEvent* event = this->GetModifierEvent(type);
    if (event) {
        return event->Execute(entity, ability);
    }
    return 0;
}

void CModifier::ExecuteOperate(CAbilityEntity* entity, CAbility* ability) {
    for (COperate* operate : base.operators_) {
        operate->Execute(entity, ability);
    }
}

CModifier* CModifier::Clone() {
    CModifier* modifier = new CModifier();
    modifier->base.isMulti_ = base.isMulti_;      // 是否可叠加
    modifier->base.maxMulti_ = base.maxMulti_;    // 最高叠加层数
    modifier->base.duration_ = base.duration_;    // 持续时间
    modifier->base.isPassive_ = base.isPassive_;    // 是否被动
    modifier->base.isHidden_ = base.isHidden_;     // 是否隐藏图标
    modifier->base.isBuff_ = base.isBuff_;       // 是否正面buff
    modifier->base.isDebuff_ = base.isDebuff_;     // 是否负面buff
    modifier->base.isPurgable_ = base.isPurgable_;   // 是否可被清除
    modifier->base.thinkInterval_ = base.thinkInterval_;       // 间隔
    modifier->base.textureName_ = base.textureName_;   // 图标名称
    modifier->base.effectName_ = base.effectName_;    // 特效名
    modifier->base.modelName_ = base.modelName_;     // 模型名，默认空
    modifier->base.name_ = base.name_;
    
    // 事件集合
    for (auto iter = base.events_.begin(); iter != base.events_.end(); ++iter) {
        modifier->SetModifierEvent(iter->first, iter->second->Clone());
    }
    // 操作集合
    for (auto iter = base.operators_.begin(); iter != base.operators_.end(); ++iter) {
        modifier->AddOperate((*iter)->Clone());
    }
    
    modifier->base.properties_ = base.properties_;
    
    return modifier;
}
