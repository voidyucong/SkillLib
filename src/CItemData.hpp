//
//  CItemData.hpp
//  SkillLib
//
//  Created by yucong on 2017/10/17.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CItemData_hpp
#define CItemData_hpp

#include <iostream>
#include <vector>
#include "CObject.hpp"
#include "SkillTypes.h"

class CItemData {
public:
    CItemData() {}
    ~CItemData() {}
    
    void SetId(int64_t value) { id_ = value; }
    void SetCost(int8_t value) { cost_ = value; }
    void SetShopFlags(ITEM_TYPE value) { shopFlags_ = value; }
    void SetQuality(ITEM_QUALITY value) { quality_ = value; }
    void AddRequirements(int64_t value) { requirements_.push_back(value); }
    void AddDefaultModifiers(std::string value) { defaultModifiers_.push_back(value); }
    
    int64_t GetId() { return id_; }
    int8_t GetCost() { return cost_; }
    ITEM_TYPE GetShopFlags() { return shopFlags_; }
    ITEM_QUALITY GetQuality() { return quality_; }
    const std::vector<int64_t>& GetRequirements() { return requirements_; }
    const std::vector<std::string>& GetDefaultModifiers() { return defaultModifiers_; }

private:
    int64_t id_;
    int8_t cost_;
    ITEM_TYPE shopFlags_;
    ITEM_QUALITY quality_;
    std::vector<int64_t> requirements_;
    std::vector<std::string> defaultModifiers_;
};

#endif /* CItemData_hpp */
