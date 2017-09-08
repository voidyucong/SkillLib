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
#include "SkillTypes.h"
#include "CObject.hpp"

class CAbilityEntity;

class CTargetSearcher : public CObject {
    struct {
    public:
        TARGET_CENTER center_;
        float radius_;      // 半径
        TARGET_TEAMS teams_;
        TARGET_TYPES types_;
        TARGET_FLAGS flags_;
    };
public:
    CTargetSearcher();
    ~CTargetSearcher();
    
    bool IsHaveTargets(CAbilityEntity* caster);
    std::vector<CAbilityEntity*> GetTargets(CAbilityEntity* caster);
    
    void SetCenter(TARGET_CENTER center) { center_ = center; }
    TARGET_CENTER GetCenter() { return center_; }
    
    void SetRadius(float radius) { radius_ = radius; }
    float GetRadius() { return radius_; }
    
    void SetTeams(TARGET_TEAMS teams) { teams_ = teams; }
    TARGET_TEAMS GetTeams() { return teams_; }
    
    void SetTypes(TARGET_TYPES types) { types_ = types; }
    TARGET_TYPES GetTypes() { return types_; }
    
    void SetFlags(TARGET_FLAGS flags) { flags_ = flags; }
    TARGET_FLAGS GetFlags() { return flags_; }
};

#endif /* CTargetSearcher_hpp */
