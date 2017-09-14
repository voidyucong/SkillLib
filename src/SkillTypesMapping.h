//
//  SkillTypesMapping.h
//  SkillLib
//
//  Created by yucong on 2017/9/12.
//  Copyright © 2017年 yucong. All rights reserved.
//

#ifndef SkillTypesMapping_h
#define SkillTypesMapping_h

#include <map>

namespace SKB {
    std::map<std::string, int> g_skillTypeMapping = {
        // 技能行为
        {"ABILITY_BEHAVIOR_HIDDEN",               1 << 0}, //这个技能是单位所拥有的技能，但是不会在HUD上显示。
        {"ABILITY_BEHAVIOR_PASSIVE",              1 << 1}, //这个技能是一个被动技能，不能被使用，但是会在HUD上显示。
        {"ABILITY_BEHAVIOR_NO_TARGET",            1 << 2}, //不需要指定目标就能释放的技能，当按下技能按钮的时候，这个技能就会被释放。
        {"ABILITY_BEHAVIOR_UNIT_TARGET",          1 << 3}, //技能需要指定一个目标来释放。
        {"ABILITY_BEHAVIOR_POINT",                1 << 4}, //技能将会在鼠标指定的位置释放（如果鼠标指向了一个单位，会在单位所在的位置释放）。
        {"ABILITY_BEHAVIOR_AOE",                  1 << 5}, //这个技能将会显示技能释放的范围"ABILITY_BEHAVIOR_POINT类的技能，但是会显示一个范围。"
        {"ABILITY_BEHAVIOR_NOT_LEARNABLE",        1 << 6}, //这个技能将能被释放，或者拥有对应的释放机制，但是不能被学习。（一般是用在类似炸弹人的引爆炸弹技能）。
        {"ABILITY_BEHAVIOR_CHANNELLED",           1 << 7}, //持续性施法技能，如果施法者移动或者被沉默，这个技能将会被中断。
        {"ABILITY_BEHAVIOR_ITEM",                 1 << 8}, //这个技能绑定了一个物品。
        {"ABILITY_BEHAVIOR_TOGGLE",               1 << 9}, //切换类技能。
        {"ABILITY_BEHAVIOR_DIRECTIONAL",          1 << 10}, //这个技能是一个从英雄出发的方向性技能，比如米拉娜的月之神剑或者屠夫的肉钩。
        {"ABILITY_BEHAVIOR_IMMEDIATE",            1 << 11}, //这个技能将会被立即释放，不会进入操作序列。
        {"ABILITY_BEHAVIOR_AUTOCAST",             1 << 12}, //这个技能可以被自动释放。
        {"ABILITY_BEHAVIOR_NOASSIST",             1 << 13}, //这个技能将不会有辅助网格。
        {"ABILITY_BEHAVIOR_AURA",                 1 << 14}, //这个技能是一个光环技能，Not really used other than to tag the ability as such.
        {"ABILITY_BEHAVIOR_ORB",                  1 << 15}, //这个技能是一个法球技能，不能对魔法免疫目标生效，
        {"ABILITY_BEHAVIOR_DONT_RESUME_MOVEMENT", 1 << 16}, //这个技能在释放完成之后不会继续之前的移动操作，只能和无目标或者立即释放类技能配合使用。
        {"ABILITY_BEHAVIOR_ROOT_DISABLES",        1 << 17}, //这个技能在单位被定身的时候无法使用。
        {"ABILITY_BEHAVIOR_UNRESTRICTED",         1 << 18}, //这个技能在释放指令被限制的时候也能被使用。
        {"ABILITY_BEHAVIOR_IGNORE_PSEUDO_QUEUE",  1 << 19}, //这个技能在被眩晕，施法和被强制攻击的时候也能使用，只能和自"ABILITY_BEHAVIOR_AUTOCAST配合使用。"
        {"ABILITY_BEHAVIOR_IGNORE_CHANNEL",       1 << 20}, //这个技能即使施法被中断也能继续释放。
        {"ABILITY_BEHAVIOR_DONT_ALERT_TARGET",    1 << 21}, //这个技能在指定敌人释放的时候将不会惊醒他们。
        {"ABILITY_BEHAVIOR_DONT_RESUME_ATTACK",   1 << 22}, //这个技能在释放完成之后，将不会恢复对之前目标的自动攻击，只能配合无目标，非立即释放类和指定单位目标类技能使用。
        {"ABILITY_BEHAVIOR_NORMAL_WHEN_STOLEN",   1 << 23}, //这个技能在被偷取之后，依然使用之前的施法前摇。
        {"ABILITY_BEHAVIOR_IGNORE_BACKSWING",     1 << 24}, //这个技能将会无视施法后摇。
        
        // 技能事件
        {"EVENT_TYPE_ON_SPELL_START",           1},               // 当技能施法开始
        {"EVENT_TYPE_ON_TOGGLE_ON",             2},                 // 当切换为开启状态
        {"EVENT_TYPE_ON_TOGGLE_OFF",            3},                // 当切换为关闭状态
        {"EVENT_TYPE_ON_CHANNEL_FINISH",        4},            // 当持续性施法完成
        {"EVENT_TYPE_ON_CHANNEL_INTERRUPTED",   5},       // 当持续性施法被中断
        {"EVENT_TYPE_ON_CHANNEL_SUCCESS",       6},           // 当持续性施法成功
        {"EVENT_TYPE_ON_DEATH",                 7},                     // 当拥有者死亡
        {"EVENT_TYPE_ON_SPAWNED",               8},                   // 当拥有者出生
        {"EVENT_TYPE_ON_PROJECTILE_HIT",        9},            // 当弹道粒子特效命中单位
        {"EVENT_TYPE_ON_PROJECTILE_FINISH",     10},        // 当弹道粒子特效结束
        
        {"MODIFIER_EVENT_ON_CREATED", 1},              // 创建时
        {"MODIFIER_EVENT_ON_DESTROY", 2},              // 销毁时
        {"MODIFIER_EVENT_ON_ATTACK", 3},               // 攻击时
        {"MODIFIER_EVENT_ON_ATTACKED", 4},             // 被攻击时
        {"MODIFIER_EVENT_ON_ATTACK_LADNED", 5},        // 攻击到时
        {"MODIFIER_EVENT_ON_ATTACK_FAILED", 6},        // 攻击单位丢失时
        {"MODIFIER_EVENT_ON_ATTACK_ALLIED", 7},        // 攻击同盟时
        {"MODIFIER_EVENT_ON_DEAL_DAMAGE", 8},          // 施加伤害时
        {"MODIFIER_EVENT_ON_TAKE_DAMAGE", 9},          // 收到伤害时
        {"MODIFIER_EVENT_ON_DEATH", 10},                // 死亡时
        {"MODIFIER_EVENT_ON_KILL", 11},                 // 杀死任意单位时
        {"MODIFIER_EVENT_ON_KILL_HERO", 12},            // 杀死英雄时
        {"MODIFIER_EVENT_ON_RESPAWN", 13},              // 重生时
        {"MODIFIER_EVENT_ON_ORB", 14},                  // 创建法球
        {"MODIFIER_EVENT_ON_ORB_FIRE", 15},             // 法球发射时
        {"MODIFIER_EVENT_ON_ORB_IMPACT", 16},           // 法球命中目标时
        {"MODIFIER_EVENT_ON_ABILITY_START", 17},        // 施法开始时
        {"MODIFIER_EVENT_ON_ABILITY_EXECUTED", 18},     // 施法结束时
        {"MODIFIER_EVENT_ON_HEAL_RECEIVED", 19},        // 受到治疗时
        {"MODIFIER_EVENT_ON_HEALTH_GAINED", 20},        // 主动获得生命值时
        {"MODIFIER_EVENT_ON_MANA_GAINED", 21},          // 主动获得魔法值时
        {"MODIFIER_EVENT_ON_MANA_SPENT", 22},           // 消耗魔法值时
        {"MODIFIER_EVENT_ON_ENTITY_MOVED", 23},         // 移动时
        {"MODIFIER_EVENT_ON_TELEPORTED", 24},           // 传送结束时
        {"MODIFIER_EVENT_ON_TELEPORTING", 25},          // 传送开始时
        {"MODIFIER_EVENT_ON_PROJECTILE_DODGE", 26},     // 躲避投射物时
        {"MODIFIER_EVENT_ON_INTERVAL", 27},             // 定时器
        
        // 特效附着点类型
        {"MODIFIER_EFFECT_ATTACH_TYPE_ORIGIN", 1},     //  原点
        {"MODIFIER_EFFECT_ATTACH_TYPE_HEAD", 2},       //  头顶
        
        // 伤害类型
        {"ABILITY_DAMAGE_TYPE_NONE", 1},
        {"ABILITY_DAMAGE_TYPE_PHYSICAL", 2},           // 物理伤害
        {"ABILITY_DAMAGE_TYPE_MAGICAL", 3},            // 法术伤害
        {"ABILITY_DAMAGE_TYPE_PURE", 4},               // 纯粹伤害
        
        //
        //
        {"TARGET_CENTER_CASTER", 1},       // 施法者(单体、群体)
        {"TARGET_CENTER_TARGET", 2},       // 目标（单体、群体）
        {"TARGET_CENTER_POINT", 3},        // 点（单体、群体）
        {"TARGET_CENTER_ATTACKER", 4},     // 攻击者（单体、群体）
        {"TARGET_CENTER_PROJECTILE", 5},   // 抛射物（群体）
        {"TARGET_CENTER_UNIT", 6},         // 单位（单体、群体）
        
        {"TARGET_TEAM_BOTH", 1},           // 全部
        {"TARGET_TEAM_ENEMY", 2},          // 敌方
        {"TARGET_TEAM_FRIENDLY", 3},       // 友方
        {"TARGET_TEAM_NONE", 4},           // 无
        
        {"TARGET_TYPE_ALL", 1},
        {"TARGET_TYPE_HERO", 2},           // 英雄
        {"TARGET_TYPE_BASIC", 3},          // 基本单位, 包括召唤单位
        {"TARGET_TYPE_MECHANICAL", 4},     // 机械
        {"TARGET_TYPE_BUILDING", 5},       // 建筑
        {"TARGET_TYPE_CREEP", 6},          // 野怪
        {"TARGET_TYPE_NONE", 7},           //    没有
        
        {"TARGET_FLAG_NONE", 1},           //  缺省默认值
        {"TARGET_FLAG_DEAD", 2},           //  死亡单位忽略
        {"TARGET_FLAG_NO_INVIS", 3},       // 不可见单位
        {"TARGET_FLAG_MAGIC_IMMUNE_ENEMIES", 4},       // 魔法免疫的敌人单位
        {"TARGET_FLAG_NOT_MAGIC_IMMUNE_ALLIES", 5},    // 魔法免疫的友军
        {"TARGET_FLAG_NOT_ATTACK_IMMUNE", 6},          // 攻击免疫单位
        {"TARGET_FLAG_OUT_OF_WORLD", 7},               // 离开游戏的单位
        
        {"ENTITY_ATTRIBUTE_STRENGTH", 1},             // 力量
        {"ENTITY_ATTRIBUTE_STRENGTH_GAIN", 2},        // 力量成长
        {"ENTITY_ATTRIBUTE_INTELLIGENCE", 3},         // 智力
        {"ENTITY_ATTRIBUTE_INTELLIGENCE_GAIN", 4},    // 智力成长
        {"ENTITY_ATTRIBUTE_AGILITY", 5},              // 敏捷
        {"ENTITY_ATTRIBUTE_AGILITY_GAIN", 6},         // 敏捷成长
        {"ENTITY_ATTRIBUTE_HP", 7},                   // 生命上限
        {"ENTITY_ATTRIBUTE_HP_GAIN", 8},              // 生命上限成长
        {"ENTITY_ATTRIBUTE_HP_REGEN", 9},             // 生命回复速度
        {"ENTITY_ATTRIBUTE_MANA", 10},
        {"ENTITY_ATTRIBUTE_MANA_GAIN", 11},
        {"ENTITY_ATTRIBUTE_MANA_REGEN", 12},
        {"ENTITY_ATTRIBUTE_DAMAGE", 13},
        {"ENTITY_ATTRIBUTE_DAMAGE_GAIN", 14},
        {"ENTITY_ATTRIBUTE_ARMOR", 15},                // 护甲
        {"ENTITY_ATTRIBUTE_ARMOR_GAIN", 16},
        {"ENTITY_ATTRIBUTE_MAGIC_RESIST", 17},         // 魔抗
        {"ENTITY_ATTRIBUTE_MAGIC_RESIST_GAIN", 18},
        
        {"ENTITY_ATTRIBUTE_MOVE_SPEED", 1},            // 移动速度
        {"ENTITY_ATTRIBUTE_MOVE_SPEED_GAIN", 2},
        
        {"ENTITY_ATTRIBUTE_DAMAGE_MIN", 1},
        {"ENTITY_ATTRIBUTE_DAMAGE_MAX", 2},
        {"ENTITY_ATTRIBUTE_ATTACK_RATE", 3},           //
        {"ENTITY_ATTRIBUTE_ATTACK_POINT", 4},          //
        {"ENTITY_ATTRIBUTE_ATTACK_RANGE", 5},          //
        {"ENTITY_ATTRIBUTE_ATTACK_RANGE_BUFFER", 6},   //
        
        {"ENTITY_ATTRIBUTE_PROJECTILE_SPEED", 1},      // 投射物速度
        
        {"ENTITY_ATTRIBUTE_VISION_RANGE", 1},          // 视野范围
        
        // 属性变化
        {"MODIFIER_ATTRIBUTE_COOLDOWN_GAIN_PERCENT", 1},       // 冷却加成百分比，例10s冷却，加成10%，冷却9s
        {"MODIFIER_ATTRIBUTE_COOLDOWN_GAIN", 2},               // 冷却加成秒数
        {"MODIFIER_ATTRIBUTE_MANACOST_GAIN_PERCENT", 3},       // 法术消耗加成百分比
        {"MODIFIER_ATTRIBUTE_CRYSTALCOST_GAIN_PERCENT", 4},    // 晶石消耗加成百分比
        {"MODIFIER_ATTRIBUTE_HPCOST_GAIN_PERCENT", 5},
        {"MODIFIER_ATTRIBUTE_DURATION_GAIN_PERCENT", 6},       // 持续时间加成百分比
        {"MODIFIER_ATTRIBUTE_DURATION_GAIN", 7},               // 持续时间加成
        {"MODIFIER_ATTRIBUTE_ARMOR_BONUS", 8},                 // 增加护甲
        
        // 主属性类型
        {"ENTITY_ATTRIBUTE_PRIMARY_STRENGTH", 1},    // 物理
        {"ENTITY_ATTRIBUTE_PRIMARY_MAGIC", 2},       // 魔法
        
        // 移动能力
        {"ENTITY_MOVEMENT_CAPABILITY_NONE", 1},      // 不能移动
        {"ENTITY_MOVEMENT_CAPABILITY_GROUND", 2},    // 地面
        {"ENTITY_MOVEMENT_CAPABILITY_FLY", 3},       // 飞行
        
        // 攻击能力
        {"ENTITY_ATTACK_CAPABILITY_NONE", 1},        // 不能攻击
        {"ENTITY_ATTACK_CAPABILITY_MELEE", 3},       // 近战
        {"ENTITY_ATTACK_CAPABILITY_RANGED", 4},      // 远程
        
        // 实体类型
        {"ENTITY_TYPE_HERO", 2},       // 英雄
        {"ENTITY_TYPE_BASIC", 3},          // 基本单位, 包括召唤单位
        {"ENTITY_TYPE_MECHANICAL", 4},     // 机械
        {"ENTITY_TYPE_BUILDING", 5},       // 建筑
        {"ENTITY_TYPE_CREEP", 6},          // 野怪
    };
    
}
#endif /* SkillTypesMapping_h */
