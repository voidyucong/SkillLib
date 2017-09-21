//
//  CTargetSearchType.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/6.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CTargetSearchType_hpp
#define CTargetSearchType_hpp

#include <iostream>
#include <vector>
#include "SkillTypes.h"
#include "CObject.hpp"

class CAbilityEntity;
class CAbilityValue;
class CAbility;
class COpRunScript;
class CTargetSets;

class CTargetSearchType : public CObject {
    struct {
        TARGET_CENTER single_;      // 单体，只在radius_=NULL时有效
        TARGET_CENTER center_;      // 中心点
        TARGET_TEAMS teams_;        // 队伍
        TARGET_TYPES types_;        // 实体类型
        TARGET_FLAGS flags_;        //
        CAbilityValue* radius_;     // 半径，默认NULL单体
        CAbilityValue* maxTargets_; // 最大目标数
    };
public:
    CTargetSearchType(): center_(TARGET_CENTER_CASTER), teams_(TARGET_TEAM_NONE), types_(TARGET_TYPE_NONE), flags_(TARGET_FLAG_NONE), radius_(0), maxTargets_(0)
    {}
    ~CTargetSearchType() { targets_.clear(); }
    
    
    //------------------------------------
    void SetSingle(TARGET_CENTER single) { single_ = single; }
    TARGET_CENTER GetSingle() { return single_; }
    
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
    
    void SetMaxTargets(CAbilityValue* max) { maxTargets_ = max; }
    CAbilityValue* GetMaxTargets() { return maxTargets_; }
    
private:
    std::vector<CAbilityEntity*> targets_;
};

#endif /* CTargetSearchType_hpp */
