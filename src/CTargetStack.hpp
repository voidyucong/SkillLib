//
//  CTargetStack.hpp
//  SkillLib
//
//  Created by yucong on 2017/9/20.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CTargetStack_hpp
#define CTargetStack_hpp

#include <iostream>
#include <vector>
#include <assert.h>
#include "CObject.hpp"


class CTargetStackItem {
public:
    CTargetStackItem() {}
    CTargetStackItem(TARGET_LIST& value) { targets_ = value; }
    ~CTargetStackItem() { targets_.clear(); }
    TARGET_LIST& GetTargets() { return targets_; }
    void ClearTargets() { targets_.clear(); }
    size_t Size() { return targets_.size(); }
private:
    TARGET_LIST targets_;
};

//
// 目标栈
// 存储当前节点的目标序列和指向父节点的指针
class CTargetStack {
public:
    CTargetStack(): parent_(0), self_(0) {}
    ~CTargetStack() {
        DestroySelf();
    }
    void SetParent(CTargetStack* item) {
        if (!parent_) parent_ = item;
        // 设置的父节点每次必须是一样的
        assert(parent_ == item);
    }
    void SetSelf(CTargetStackItem* item) { self_ = item; }
    CTargetStack* GetParent() { return parent_; }
    CTargetStackItem* GetSelf() { return self_; }
    CTargetStackItem* GetValid() {
        if (self_) return self_;
        if (parent_) return parent_->GetValid();
        assert(false);
    }
    void DestroyParent() {
        if (parent_) {
            delete parent_;
            parent_ = 0;
        }
    }
    void DestroySelf() {
        if (self_) {
            delete self_;
            self_ = 0;
        }
    }
private:
    CTargetStack* parent_;
    CTargetStackItem* self_;
};

#endif /* CTargetStack_hpp */
