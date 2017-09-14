//
//  CTargetSearcher.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/6.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CTargetSearcher_hpp
#define CTargetSearcher_hpp

#include <iostream>
#include <vector>
#include "SkillTypes.h"
#include "CObject.hpp"

class CAbilityEntity;
class CAbilityValue;
class CAbility;

class CTargetSearcher : public CObject {
    struct {
        TARGET_CENTER center_;
        TARGET_TEAMS teams_;
        TARGET_TYPES types_;
        TARGET_FLAGS flags_;
        CAbilityValue* radius_;      // 半径，默认NULL
    };
public:
    CTargetSearcher();
    ~CTargetSearcher();
    
    bool IsHaveTargets(CAbilityEntity* caster, CAbility* ability);
    std::vector<CAbilityEntity*> GetTargets(CAbilityEntity* caster, CAbility* ability);
    
    void SetCenter(TARGET_CENTER center) { center_ = center; }
    TARGET_CENTER GetCenter() { return center_; }
    
    void SetRadius(CAbilityValue* radius) { if (radius_) { delete radius_; radius_ = 0; } radius_ = radius; }
    CAbilityValue* GetRadius() { return radius_; }
    
    void SetTeams(TARGET_TEAMS teams) { teams_ = teams; }
    TARGET_TEAMS GetTeams() { return teams_; }
    
    void SetTypes(TARGET_TYPES types) { types_ = types; }
    TARGET_TYPES GetTypes() { return types_; }
    
    void SetFlags(TARGET_FLAGS flags) { flags_ = flags; }
    TARGET_FLAGS GetFlags() { return flags_; }
    
private:
    std::vector<CAbilityEntity*> targets_;
};

#endif /* CTargetSearcher_hpp */
