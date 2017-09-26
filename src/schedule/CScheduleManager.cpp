//
//  CScheduleManager.cpp
//  SkillLib
//
//  Created by yucong on 2017/9/4.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "CScheduleManager.h"
#include <vector>
#include "TimeUtil.h"
#include "MathUtil.hpp"

static CScheduleManager* s_pInstance = NULL;

CScheduleManager::CScheduleManager() {
    lastTime_ = SKB::TimeUtil::GetSeconds();
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

void CScheduleManager::Update() {
    double now = SKB::TimeUtil::GetSeconds();
//    std::cout << std::fixed << now << std::endl;
//    std::cout << "lastTime_:" << std::fixed << lastTime_ << " now:" << std::fixed << now << std::endl;
    double deltaTime = now - lastTime_;
    deltaTime = MAX(0, deltaTime);
    std::vector<CObject*> deletions;
    for (auto iter = schedules_.begin(); iter != schedules_.end(); iter++) {
        if (!iter->second->markedDeletion)
            iter->second->schedule->Update(deltaTime);
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
