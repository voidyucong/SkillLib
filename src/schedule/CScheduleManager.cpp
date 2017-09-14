//
//  CScheduleManager.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/4.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CScheduleManager.h"
#include <vector>
extern "C" {
#include "TimeUtil.h"
}

#define MAX(x,y) (((x) < (y)) ? (y) : (x))

static CScheduleManager* s_pInstance = NULL;

CScheduleManager::CScheduleManager() {
    lastTime_ = SKB::GetSeconds();
}

CScheduleManager::~CScheduleManager() {
    for (auto iter = schedules_.begin(); iter != schedules_.end(); iter++) {
        delete iter->second;
    }
}

CScheduleManager* CScheduleManager::getInstance() {
    if (s_pInstance == NULL) {
        s_pInstance = new CScheduleManager();
    }
    return s_pInstance;
}

void CScheduleManager::update() {
    double now = SKB::GetSeconds();
    float deltaTime = now - lastTime_;
    deltaTime = MAX(0, deltaTime);
    std::vector<CObject*> deletions;
    for (auto iter = schedules_.begin(); iter != schedules_.end(); iter++) {
        if (!iter->second->markedDeletion)
            iter->second->schedule->update(deltaTime);
        else
            deletions.push_back(iter->first);
    }
    lastTime_ = now;
    
    for (auto obj : deletions) schedules_.erase(schedules_.find(obj));
}

void CScheduleManager::AddSchedule(CObject* target, CObject::CALLBACK callback, float interval) {
    ScheduleNode* node = new ScheduleNode();
    node->schedule = new CSchedule(target, callback, interval);
    node->markedDeletion = false;
    schedules_[target] = node;
}

void CScheduleManager::RemoveSchedule(CObject* target) {
    if (schedules_.find(target) != schedules_.end()) {
        auto node = schedules_[target];
        node->markedDeletion = true;
    }
}
