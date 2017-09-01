//
//  CTargetType.hpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CTargetType_hpp
#define CTargetType_hpp

#include "SkillTypes.h"

class CTargetType {
public:
    CTargetType(): center_(TARGET_CENTER_POINT), teams_(TARGET_TEAM_BOTH), types_(TARGET_TYPE_ALL), flags_(TARGET_FLAG_NONE) {}
    CTargetType(TARGET_CENTER center): center_(center), teams_(TARGET_TEAM_BOTH), types_(TARGET_TYPE_ALL), flags_(TARGET_FLAG_NONE) {}
    ~CTargetType() {}
    
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
private:
    TARGET_CENTER center_;
    float radius_;      // 半径
    TARGET_TEAMS teams_;
    TARGET_TYPES types_;
    TARGET_FLAGS flags_;
};

#endif /* CTargetType_hpp */
