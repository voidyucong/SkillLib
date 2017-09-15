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
#include "CSchedule.h"

struct ScheduleNode {
    ScheduleNode(): schedule(0), markedDeletion(false) {}
    ~ScheduleNode() { delete schedule; }
    CSchedule* schedule;
    bool markedDeletion;    // 标记移除
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
    std::map<CObject*, ScheduleNode*> schedules_;
    double lastTime_;
};


#endif /* CScheduleManager_hpp */
