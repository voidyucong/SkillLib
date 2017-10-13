//
//  CScheduleManager.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/4.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CScheduleManager_hpp
#define CScheduleManager_hpp

#include <iostream>
#include <map>
#include <vector>
#include "CSchedule.h"

struct ScheduleNode {
    ScheduleNode(): markedDeletion(false), interval(0.f), elapsed(0.f), target(0) {}
    ~ScheduleNode() {  }
    
    void Update(float dt) {
        elapsed += dt;
        if (elapsed >= interval) {
            if (target && callback) {
                (target->*callback)(dt);
            }
            elapsed = 0.f;
        }
    }
    bool markedDeletion;    // 标记移除
    float interval;
    float elapsed;
    CObject* target;
    CObject::CALLBACK callback;
};

class CScheduleManager {
public:
    CScheduleManager();
    ~CScheduleManager();
    
    static CScheduleManager* getInstance();
    
    void Update();
    
    void AddSchedule(CObject* target, CObject::CALLBACK callback, float interval);
    void RemoveSchedule(CObject* target);
private:
    std::map<unsigned, std::vector<ScheduleNode*>> schedules_;
    double lastTime_;
};


#endif /* CScheduleManager_hpp */
