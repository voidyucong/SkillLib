//
//  CLinearProjectile.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/22.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CLinearProjectile_hpp
#define CLinearProjectile_hpp

#include <iostream>
#include <map>
#include "CProjectile.hpp"

class CAbility;
class CAbilityEntity;
class CAbilityValue;
class CTargetSearchType;

class CLinearProjectileData {
public:
    CLinearProjectileData() {}
    ~CLinearProjectileData() {}
    
    void SetEffectName(std::string name) { effectName_ = name; }
    void SetMoveSpeed(CAbilityValue* value) { moveSpeed_ = value; }
    void SetStartRadius(CAbilityValue* value) { startRadius_ = value; }
    void SetEndRadius(CAbilityValue* value) { endRadius_ = value; }
    void SetLength(CAbilityValue* value) { length_ = value; }
    void SetWidth(CAbilityValue* value) { width_ = value; }
    void SetAttachType(MODIFIER_EFFECT_ATTACH_TYPE value) { attachType_ = value; }
    void SetIsDeleteOnHit(bool value) { isDeleteOnHit_ = value; }
    void SetIsProvidesVision(bool value) { isProvidesVision_ = value; }
    void SetVisionRadius(CAbilityValue* value) { visionRadius_ = value; }
    void SetDirection(CVector direction) { direction_ = direction; }
    void SetTargetType(CTargetSearchType* targetType) { targetType_ = targetType; }
    void SetCaster(CAbilityEntity* caster) { caster_ = caster; }
    void SetAbility(CAbility* ability) { ability_ = ability; }
    void SetCastPosition(const CVector& castPosition) { castPosition_ = castPosition; }
    
    std::string GetEffectName() { return effectName_; }
    CAbilityValue* GetMoveSpeed() { return moveSpeed_; }
    CAbilityValue* GetStartRadius() { return startRadius_; }
    CAbilityValue* GetEndRadius() { return endRadius_; }
    CAbilityValue* GetLength() { return length_; }
    CAbilityValue* GetWidth() { return width_; }
    MODIFIER_EFFECT_ATTACH_TYPE GetAttachType() { return attachType_; }
    bool GetIsDeleteOnHit() { return isDeleteOnHit_; }
    bool GetIsProvidesVision() { return isProvidesVision_; }
    CAbilityValue* GetVisionRadius() { return visionRadius_; }
    const CVector& GetDirection() { return direction_; }
    CTargetSearchType* GetTargetType() { return targetType_; }
    CAbilityEntity* GetCaster() { return caster_; }
    CAbility* GetAbility() { return ability_; }
    const CVector& GetCastPosition() { return castPosition_; }
private:
    std::string effectName_;
    CAbilityValue* moveSpeed_;  // pixel/frame
    CAbilityValue* startRadius_;    //
    CAbilityValue* endRadius_;
    CAbilityValue* length_;         // 长度
    CAbilityValue* width_;          // 宽度
    MODIFIER_EFFECT_ATTACH_TYPE attachType_;
    bool isDeleteOnHit_;        // 碰到目标后是否删除
    bool isProvidesVision_;     // 是否提供视野
    CAbilityValue* visionRadius_;        // 视野范围
    CTargetSearchType* targetType_;
    CAbilityEntity* caster_;
    CAbility* ability_;
    CVector direction_;         // 释放方向
    CVector castPosition_;      // 释放位置
};


class CLinearProjectile : public CProjectile {
public:
    CLinearProjectile();
    CLinearProjectile(CLinearProjectileData* data);
    ~CLinearProjectile();
    void Update(float dt);
    void Execute();
    CLinearProjectileData* GetData() { return data_; }
private:
    CLinearProjectileData* data_;
    double castTimestamp_;      // 释放时间
    std::map<CAbilityEntity*, int> hitTargets_;
};

#endif /* CLinearProjectile_hpp */
