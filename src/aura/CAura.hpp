//
//  CAura.hpp
//  SkillLib
//
//  Created by yucong on 2017/10/12.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CAura_hpp
#define CAura_hpp

#include <iostream>
#include <set>
#include "CObject.hpp"

class CAbilityValue;
class CAbility;
class CAbilityEntity;
class CTargetSearchType;

class CAura : public CObject {
public:
    CAura();
    CAura(std::string modifierName, float duration, const CVector& position, float radius, CTargetSearchType* targetType);
    ~CAura();
    
    void Update(float dt);
    void Activate();
    void Destroy();
    
    void SetCaster(CAbilityEntity* caster) { caster_ = caster; }
    void SetAbility(CAbility* ability) { ability_ = ability; }
private:
    std::string modifierName_;
    float duration_;
    CVector position_;
    float radius_;
    CTargetSearchType* targetType_;
    
    double endTime_;
    CAbilityEntity* caster_;
    CAbility* ability_;
    std::set<CAbilityEntity*> targets_;
};

#endif /* CAura_hpp */
