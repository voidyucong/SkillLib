//
//  CTargetType.hpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef CTargetType_hpp
#define CTargetType_hpp

enum TARGET_CENTER {
    TARGET_CENTER_CASTER,       // 施法者
    TARGET_CENTER_TARGET,       // 目标
    TARGET_CENTER_POINT,        // 点
    TARGET_CENTER_ATTACKER,     // 攻击者
    TARGET_CENTER_PROJECTILE,   // 抛射物
};

enum TARGET_TEAMS {
    TARGET_TEAM_BOTH,           // 全部
    TARGET_TEAM_ENEMY,          // 敌方
    TARGET_TEAM_FRIENDLY,       // 友方
    TARGET_TEAM_NONE,           // 无
};

enum TARGET_TYPES {
    TARGET_TYPE_ALL,
    TARGET_TYPE_HERO,           // 英雄
    TARGET_TYPE_BASIC,          // 基本单位, 包括召唤单位
    TARGET_TYPE_MECHANICAL,     // 机械
    TARGET_TYPE_BUILDING,       // 建筑
    TARGET_TYPE_CREEP,          // 野怪
    TARGET_TYPE_NONE,           //	没有
};

enum TARGET_FLAGS {
    TARGET_FLAG_NONE,           //  缺省默认值
    TARGET_FLAG_DEAD,           //  死亡单位忽略
    TARGET_FLAG_NO_INVIS,       // 不可见单位
    TARGET_FLAG_MAGIC_IMMUNE_ENEMIES,       // 魔法免疫的敌人单位
    TARGET_FLAG_NOT_MAGIC_IMMUNE_ALLIES,    // 魔法免疫的友军
    TARGET_FLAG_NOT_ATTACK_IMMUNE,          // 攻击免疫单位
    TARGET_FLAG_OUT_OF_WORLD,               // 离开游戏的单位
};

class CTargetType {
public:
    CTargetType();
    ~CTargetType();
private:
    TARGET_CENTER center_;
    float radius_;      // 半径
    TARGET_TEAMS teams_;
    TARGET_TYPES types_;
    TARGET_FLAGS flags_;
};

#endif /* CTargetType_hpp */
