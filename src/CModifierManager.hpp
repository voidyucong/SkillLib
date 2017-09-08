//
//  CModifierManager.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/8.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CModifierManager_hpp
#define CModifierManager_hpp

#include <iostream>
#inclu

class CModifierManager {
public:
    CModifierManager();
    ~CModifierManager();
    
    static CModifierManager* getInstance();
    
    void update(float dt);
    
private:
    
};

#endif /* CModifierManager_hpp */
