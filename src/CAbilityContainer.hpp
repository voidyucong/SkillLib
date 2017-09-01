//
//  CAbilityContainer.hpp
//  SkillLib
//
//  Created by yucong on 2017/8/31.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CAbilityContainer_hpp
#define CAbilityContainer_hpp

#include <stdio.h>
#include <vector>

class CAbility;

class CAbilityContainer {
public:
    CAbilityContainer();
    ~CAbilityContainer();
    
    void SetAbility(CAbility* ability, int index);
    CAbility* GetAbility(int index);
    
    void SetAbilityLayout(unsigned layout) { abilityLayout_ = layout; }
    unsigned int GetAbilityLayout() { return abilityLayout_; }
    
private:
    unsigned int abilityLayout_;    // 技能槽数量
    std::vector<CAbility*> abilities_;
};

#endif /* CAbilityContainer_hpp */
