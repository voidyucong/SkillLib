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

unsigned HashInt(const char* str)
{
    if(!*str) return 0;
    unsigned int hash = 1315423911;
    while (unsigned int ch = (unsigned int)*str++)
        hash ^= ((hash << 5) + ch + (hash >> 2));
    return hash;
}
#define HASH_TARGET(obj) (HashInt((const char*)&obj) % 16)

static CScheduleManager* s_pInstance = NULL;

CScheduleManager::CScheduleManager() {
    lastTime_ = SKB::TimeUtil::GetSeconds();
}

CScheduleManager::~CScheduleManager() {
    for (auto iter = schedules_.begin(); iter != schedules_.end(); iter++) {
        for (auto node : iter->second)
            delete node;
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
    for (auto iter = schedules_.begin(); iter != schedules_.end(); ++iter) {
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end();) {
            auto node = *iter2;
            if (!node) continue;
            if (!node->markedDeletion) {
                node->Update(deltaTime);
                ++iter2;
            }
            else {
                iter2 = iter->second.erase(iter2);
                node = 0;
            }
        }
    }
    lastTime_ = now;
    
//    for (auto obj : deletions) schedules_.erase(schedules_.find(obj));
}

void CScheduleManager::AddSchedule(CObject* target, CObject::CALLBACK callback, float interval) {
    unsigned hash = HASH_TARGET(target);
    if (schedules_.find(hash) == schedules_.end()) {
        schedules_[hash] = {};
    }
    for (auto node : schedules_[hash]) {
        if (node->callback == callback) {
            node->interval = interval;
            return;
        }
    }
    
    ScheduleNode* node = new ScheduleNode();
    node->target = target;
    node->callback = callback;
    node->interval = interval;
    node->markedDeletion = false;
    schedules_[hash].push_back(node);
}

void CScheduleManager::RemoveSchedule(CObject* target) {
    unsigned hash = HASH_TARGET(target);
    if (schedules_.find(hash) != schedules_.end()) {
        auto nodes = schedules_[hash];
        for (auto node : nodes) {
            if (node->target == target)
                node->markedDeletion = true;
        }
    }
}
