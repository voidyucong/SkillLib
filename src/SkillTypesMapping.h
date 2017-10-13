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
    static std::map<std::string, int> s_skillTypeMapping = {
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
        {"MODIFIER_EVENT_ON_ATTACK_LANDED", 5},        // 攻击到时
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
        {"TARGET_CENTER_NONE", 7},
        
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
        {"ENTITY_ATTRIBUTE_CUR_HP", 8},
        {"ENTITY_ATTRIBUTE_HP_GAIN", 9},              // 生命上限成长
        {"ENTITY_ATTRIBUTE_HP_REGEN", 10},             // 生命回复速度
        {"ENTITY_ATTRIBUTE_MANA", 11},
        {"ENTITY_ATTRIBUTE_CUR_MANA", 12},
        {"ENTITY_ATTRIBUTE_MANA_GAIN", 13},
        {"ENTITY_ATTRIBUTE_MANA_REGEN", 14},
        {"ENTITY_ATTRIBUTE_MANA_STARTING", 15},
        {"ENTITY_ATTRIBUTE_DAMAGE", 16},
        {"ENTITY_ATTRIBUTE_DAMAGE_GAIN", 17},
        {"ENTITY_ATTRIBUTE_ARMOR", 18},                // 护甲
        {"ENTITY_ATTRIBUTE_ARMOR_GAIN", 19},
        {"ENTITY_ATTRIBUTE_MAGIC_RESIST", 20},         // 魔抗
        {"ENTITY_ATTRIBUTE_MAGIC_RESIST_GAIN", 21},
        {"ENTITY_ATTRIBUTE_MOVE_SPEED", 22},            // 移动速度
        {"ENTITY_ATTRIBUTE_MOVE_SPEED_GAIN", 23},
        {"ENTITY_ATTRIBUTE_XP_GAIN", 24},
        {"ENTITY_ATTRIBUTE_DAMAGE_MIN", 25},
        {"ENTITY_ATTRIBUTE_DAMAGE_MAX", 26},
        {"ENTITY_ATTRIBUTE_ATTACK_RATE", 27},           //
        {"ENTITY_ATTRIBUTE_ATTACK_POINT", 28},          //
        {"ENTITY_ATTRIBUTE_ATTACK_RANGE", 29},          //
        {"ENTITY_ATTRIBUTE_ATTACK_ACQUISITION_RANGE", 30},
        {"ENTITY_ATTRIBUTE_ATTACK_RANGE_BUFFER", 31},   //
        {"ENTITY_ATTRIBUTE_PROJECTILE_SPEED", 32},      // 投射物速度
        {"ENTITY_ATTRIBUTE_VISION_RANGE", 33},          // 视野范围
        {"ENTITY_ATTRIBUTE_ARMOR_SHIELD", 34},          // 物理护盾
        {"ENTITY_ATTRIBUTE_SPELL_SHIELD", 35},          // 魔法护盾
        
        
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
        
        // state
        {"MODIFIER_STATE_ATTACK_IMMUNE", 1},	//攻击免疫状态
        {"MODIFIER_STATE_BLIND", 2},	//致盲状态？无法物理攻击？
        {"MODIFIER_STATE_BLOCK_DISABLED", 3},	//禁用伤害减免？
        {"MODIFIER_STATE_CANNOT_MISS", 4},	//不能闪避？
        {"MODIFIER_STATE_COMMAND_RESTRICTED", 5},	//禁魔状态
        {"MODIFIER_STATE_DISARMED", 6},	//缴械状态
        {"MODIFIER_STATE_DOMINATED", 7},	//支配状态？
        {"MODIFIER_STATE_EVADE_DISABLED", 8},	//禁用躲避？
        {"MODIFIER_STATE_FLYING", 9},	//飞行状态
        {"MODIFIER_STATE_FROZEN", 10},	//冷冻状态
        {"MODIFIER_STATE_HEXED", 11},	//妖术状态
        {"MODIFIER_STATE_INVISIBLE", 12},	//隐身状态
        {"MODIFIER_STATE_INVULNERABLE", 13},	//无敌状态
        {"MODIFIER_STATE_LOW_ATTACK_PRIORITY", 14},	//低的攻击优先级
        {"MODIFIER_STATE_MAGIC_IMMUNE", 15},	//魔法免疫状态
        {"MODIFIER_STATE_MUTED", 16},	//禁用物品状态
        {"MODIFIER_STATE_NIGHTMARED", 17},	//催眠状态
        {"MODIFIER_STATE_NO_HEALTH_BAR", 18},	//没有生命条
        {"MODIFIER_STATE_NO_TEAM_MOVE_TO", 19},	//没有移动到队伍状态
        {"MODIFIER_STATE_NO_TEAM_SELECT", 20},	//没有选择队伍状态
        {"MODIFIER_STATE_NOT_ON_MINIMAP", 21},	//不在小地图状态
        {"MODIFIER_STATE_NOT_ON_MINIMAP_FOR_ENEMIES", 22},	//敌人不在小地图状态
        {"MODIFIER_STATE_NO_UNIT_COLLISION", 23},	//没有单位碰撞状态
        {"MODIFIER_STATE_OUT_OF_GAME", 24},	//离开游戏状态
        {"MODIFIER_STATE_PASSIVES_DISABLED", 25},	//禁用被动技能状态
        {"MODIFIER_STATE_PROVIDES_VISION", 26},	//提供视野状态
        {"MODIFIER_STATE_ROOTED", 27},	//被缠绕状态
        {"MODIFIER_STATE_SILENCED", 28},	//沉默状态
        {"MODIFIER_STATE_SOFT_DISARMED", 29},	//软解除武装状态
        {"MODIFIER_STATE_SPECIALLY_DENIABLE", 30},	//*暂无说明*
        {"MODIFIER_STATE_STUNNED", 31},	//眩晕状态
        {"MODIFIER_STATE_UNSELECTABLE", 32},	//无法选取状态
        
        // property
        {"MODIFIER_PROPERTY_ABSOLUTE_NO_DAMAGE_MAGICAL", 1},		//所有魔法攻击无效
        {"MODIFIER_PROPERTY_ABSOLUTE_NO_DAMAGE_PHYSICAL", 2},		//所有物理攻击无效
        {"MODIFIER_PROPERTY_ABSOLUTE_NO_DAMAGE_PURE", 3},		//所有神圣伤害无效
        {"MODIFIER_PROPERTY_ABSORB_SPELL", 4},		//偷取法术？
        {"MODIFIER_PROPERTY_ATTACK_RANGE_BONUS", 5},		//修改攻击范围
        {"MODIFIER_PROPERTY_ATTACK_RANGE_BONUS_UNIQUE", 6},		//攻击距离增益（不叠加）
        {"MODIFIER_PROPERTY_ATTACKSPEED_BONUS_CONSTANT", 7},		//修改攻击速度
        {"MODIFIER_PROPERTY_BASEATTACK_BONUSDAMAGE", 8},		//修改基础攻击力
        {"MODIFIER_PROPERTY_BASE_ATTACK_TIME_CONSTANT", 9},		//设定基础攻击间隔
        {"MODIFIER_PROPERTY_BASEDAMAGEOUTGOING_PERCENTAGE", 10},		//修改基础攻击伤害
        {"MODIFIER_PROPERTY_BASE_MANA_REGEN", 11},		//修改基础魔法回复数值，对百分比回魔有影响
        {"MODIFIER_PROPERTY_BONUS_DAY_VISION", 12},		//修改白天的视野距离
        {"MODIFIER_PROPERTY_BONUS_NIGHT_VISION", 13},		//修改夜间的视野距离
        {"MODIFIER_PROPERTY_BONUS_VISION_PERCENTAGE", 14},		//按百分比修改视野距离
        {"MODIFIER_PROPERTY_CAST_RANGE_BONUS", 15},		//施法距离增益
        {"MODIFIER_PROPERTY_CHANGE_ABILITY_VALUE", 16},		//改变技能数值
        {"MODIFIER_PROPERTY_COOLDOWN_PERCENTAGE_STACKING", 17},		//冷却时间百分比堆叠
        {"MODIFIER_PROPERTY_COOLDOWN_REDUCTION_CONSTANT", 18},		//减少冷却时间
        {"MODIFIER_PROPERTY_DAMAGEOUTGOING_PERCENTAGE", 19},		//按百分比修改攻击力，负数降低攻击，正数提高攻击
        {"MODIFIER_PROPERTY_DEATHGOLDCOST", 20},		//修改死亡损失的金钱
        {"MODIFIER_PROPERTY_DISABLE_AUTOATTACK", 21},		//禁止自动攻击
        {"MODIFIER_PROPERTY_DISABLE_HEALING", 22},		//禁止生命回复(1为禁止)
        {"MODIFIER_PROPERTY_DISABLE_TURNING", 23},		//禁止转身
        {"MODIFIER_PROPERTY_EVASION_CONSTANT", 24},		//闪避
        {"MODIFIER_PROPERTY_HEALTH_BONUS", 25},		//修改目前血量
        {"MODIFIER_PROPERTY_HEALTH_REGEN_CONSTANT", 26},		//固定的生命回复数值
        {"MODIFIER_PROPERTY_HEALTH_REGEN_PERCENTAGE", 27},		//根据装备带来的最大血量所产生的血量回复数值
        {"MODIFIER_PROPERTY_HEALTH_REGEN_ADDITION_PERCENT", 28},        //生命回复百分比，负数降级，正数提高
        {"MODIFIER_PROPERTY_IGNORE_CAST_ANGLE", 29},		//忽略施法角度
        {"MODIFIER_PROPERTY_INCOMING_DAMAGE_PERCENTAGE", 30},		//按百分比修改受到的所有伤害，负数降低伤害，正数加深伤害
        {"MODIFIER_PROPERTY_INCOMING_PHYSICAL_DAMAGE_CONSTANT", 31},		//所受物理伤害数值（数值物理伤害减免/增加）
        {"MODIFIER_PROPERTY_INCOMING_PHYSICAL_DAMAGE_PERCENTAGE", 32},		//按百分比修改受到的物理伤害，负数降低伤害，正数加深伤害
        {"MODIFIER_PROPERTY_INCOMING_SPELL_DAMAGE_CONSTANT", 33},		//按百分比修改受到的技能伤害，负数降低伤害，正数加深伤害
        {"MODIFIER_PROPERTY_INVISIBILITY_LEVEL", 34},		//隐身等级？
        {"MODIFIER_PROPERTY_IS_ILLUSION", 35},		//是否为某个单位的幻象
        {"MODIFIER_PROPERTY_PHYSICAL_ARMOR_BONUS", 36},                 //增加护甲
        {"MODIFIER_PROPERTY_PHYSICAL_ARMOR_BONUS_UNIQUE", 37},          //增加护甲，不可叠加
        {"MODIFIER_PROPERTY_PHYSICAL_ARMOR_SHIELD_BONUS", 38},        //物理护盾加成
        {"MODIFIER_PROPERTY_PHYSICAL_ATTACK_RELIEF_BONUS", 39},       //物理免伤加成
        {"MODIFIER_PROPERTY_PHYSICAL_ATTACK_RELIEF_PERCENT_BONUS", 40},       //物理免伤百分比加成
        {"MODIFIER_PROPERTY_PHYSICAL_ATTACK_LIFESTEAL_BONUS", 41},    //物理吸血加成
        {"MODIFIER_PROPERTY_PHYSICAL_ATTACK_LIFESTEAL_PERCENT_BONUS", 42},    //物理吸血百分比加成
        {"MODIFIER_PROPERTY_PHYSICAL_ATTACK_PENETRATE_BONUS", 43},    //物理穿透加成
        {"MODIFIER_PROPERTY_PHYSICAL_ATTACK_PENETRATE_PERCENT_BONUS", 44},    //物理穿透百分比加成
        {"MODIFIER_PROPERTY_MAGICAL_RESISTANCE_BONUS", 45},             //法术抗性，可以累加
        {"MODIFIER_PROPERTY_MAGICAL_RESISTANCE_ITEM_UNIQUE", 46},       //法术抗性，不可以累加
        {"MODIFIER_PROPERTY_MAGICAL_ARMOR_SHIELD_BONUS", 47},         //法术护盾加成
        {"MODIFIER_PROPERTY_MAGICAL_ATTACK_RELIEF_BONUS", 48},       //法术免伤加成
        {"MODIFIER_PROPERTY_MAGICAL_ATTACK_RELIEF_PERCENT_BONUS", 49},       //法术免伤百分比加成
        {"MODIFIER_PROPERTY_MAGICAL_ATTACK_LIFESTEAL_BONUS", 50},    //法术吸血加成
        {"MODIFIER_PROPERTY_MAGICAL_ATTACK_LIFESTEAL_PERCENT_BONUS", 51},    //法术吸血百分比加成
        {"MODIFIER_PROPERTY_MAGICAL_ATTACK_PENETRATE_BONUS", 52},    //法术穿透加成
        {"MODIFIER_PROPERTY_MAGICAL_ATTACK_PENETRATE_PERCENT_BONUS", 53},    //法术穿透百分比加成
        {"MODIFIER_PROPERTY_MANA_BONUS", 54},		//修改目前魔法量
        {"MODIFIER_PROPERTY_MANA_REGEN_CONSTANT", 55},		//修改基础魔法回复数值，对百分比回魔没有影响
        {"MODIFIER_PROPERTY_MANA_REGEN_CONSTANT_UNIQUE", 56},		//修改基础魔法回复数值，对百分比回魔没有影响，且 不可累积
        {"MODIFIER_PROPERTY_MANA_REGEN_PERCENTAGE", 57},		//修改基础魔法回复数值
        {"MODIFIER_PROPERTY_MANA_REGEN_TOTAL_PERCENTAGE", 58},		//修改所有魔法回复数值
        {"MODIFIER_PROPERTY_MAX_ATTACK_RANGE", 59},		//最大攻击距离增益
        {"MODIFIER_PROPERTY_MIN_HEALTH", 60},		//血量在设定值以下是不能杀死（斧王的斩杀依然有效）
        {"MODIFIER_PROPERTY_MISS_PERCENTAGE", 61},		//增加miss的几率
        {"MODIFIER_PROPERTY_MODEL_CHANGE", 62},		//设定模型
        {"MODIFIER_PROPERTY_MODEL_SCALE", 63},		//设定模型大小
        {"MODIFIER_PROPERTY_MOVESPEED_ABSOLUTE", 64},		//设置移动速度
        {"MODIFIER_PROPERTY_MOVESPEED_BASE_OVERRIDE", 65},		//设定基础移动速度
        {"MODIFIER_PROPERTY_MOVESPEED_BONUS_CONSTANT", 66},		//增加移动速度数值
        {"MODIFIER_PROPERTY_MOVESPEED_BONUS_PERCENTAGE", 67},		//百分比增加移动速度，自身不叠加
        {"MODIFIER_PROPERTY_MOVESPEED_BONUS_PERCENTAGE_UNIQUE", 68},		//独立百分比增加移动速度，不叠加
        {"MODIFIER_PROPERTY_MOVESPEED_BONUS_UNIQUE", 69},		//增加移动速度数值，不叠加，物品版本
        {"MODIFIER_PROPERTY_MOVESPEED_LIMIT", 70},		//限制移动速度
        {"MODIFIER_PROPERTY_MOVESPEED_MAX", 71},		//设置最大移动速度
        {"MODIFIER_PROPERTY_NEGATIVE_EVASION_CONSTANT", 72},		//降低闪避概率
        {"MODIFIER_PROPERTY_OVERRIDE_ANIMATION", 73},		//强制播放模型动作
        {"MODIFIER_PROPERTY_OVERRIDE_ANIMATION_RATE", 74},		//设置播放模型动作快慢
        {"MODIFIER_PROPERTY_OVERRIDE_ANIMATION_WEIGHT", 75},		//强制播放模型动作_重？
        {"MODIFIER_PROPERTY_OVERRIDE_ATTACK_MAGICAL", 76},		//魔法攻击
        {"MODIFIER_PROPERTY_PERSISTENT_INVISIBILITY", 77},		//永久性隐身
        {"MODIFIER_PROPERTY_POST_ATTACK", 78},		//增加攻击力？
        {"MODIFIER_PROPERTY_PREATTACK_BONUS_DAMAGE", 79},		//修改附加攻击力
        {"MODIFIER_PROPERTY_PREATTACK_BONUS_DAMAGE_POST_CRIT", 80},		//以增加伤害的方式修改伤害值，不计入暴击计算
        {"MODIFIER_PROPERTY_PREATTACK_CRITICALSTRIKE", 81},		//致命一击
        {"MODIFIER_PROPERTY_PROCATTACK_BONUS_DAMAGE_COMPOSITE", 82},		//修改在普通攻击后计算的神圣伤害
        {"MODIFIER_PROPERTY_PROCATTACK_BONUS_DAMAGE_MAGICAL", 83},		//修改在普通攻击后计算的魔法伤害
        {"MODIFIER_PROPERTY_PROCATTACK_BONUS_DAMAGE_PHYSICAL", 84},		//修改在普通攻击后计算的物理伤害
        {"MODIFIER_PROPERTY_PROCATTACK_BONUS_DAMAGE_PURE", 85},		//修改在普通攻击后计算的神圣伤害
        {"MODIFIER_PROPERTY_PROCATTACK_FEEDBACK", 86},		//法力燃烧？
        {"MODIFIER_PROPERTY_PROVIDES_FOW_POSITION", 87},	//暂无说明*
        {"MODIFIER_PROPERTY_REINCARNATION", 88},		//不朽之守护或者是骷髅王的大招？
        {"MODIFIER_PROPERTY_RESPAWNTIME", 89},		//修改重生时间
        {"MODIFIER_PROPERTY_RESPAWNTIME_PERCENTAGE", 90},		//百分比修改重生时间
        {"MODIFIER_PROPERTY_RESPAWNTIME_STACKING", 91},		//累积重生时间
        {"MODIFIER_PROPERTY_STATS_AGILITY_BONUS", 92},		//修改敏捷
        {"MODIFIER_PROPERTY_STATS_INTELLECT_BONUS", 93},		//修改智力
        {"MODIFIER_PROPERTY_STATS_STRENGTH_BONUS", 94},		//修改力量
        {"MODIFIER_PROPERTY_SUPER_ILLUSION_WITH_ULTIMATE", 95},		//VS A杖大招的那个幻象
        {"MODIFIER_PROPERTY_TOOLTIP", 96},		//可被用于任何提示， 比如臂章的血量移除
        {"MODIFIER_PROPERTY_TOTAL_CONSTANT_BLOCK", 97},		//减免所有来源的伤害
        {"MODIFIER_PROPERTY_TOTAL_CONSTANT_BLOCK_UNAVOIDABLE_PRE_ARMOR", 98},		//对于自动攻击的伤害减免
        {"MODIFIER_PROPERTY_TOTALDAMAGEOUTGOING_PERCENTAGE", 99},		//失效，不工作
        {"MODIFIER_PROPERTY_TRANSLATE_ACTIVITY_MODIFIERS", 100},		//动作修改？
        {"MODIFIER_PROPERTY_TRANSLATE_ATTACK_SOUND", 101},		//攻击音效修改？
        {"MODIFIER_PROPERTY_TURN_RATE_PERCENTAGE", 102},		//百分比修改转向速度
    };
 
    static int GetEnumByString(std::string name) {
        return s_skillTypeMapping[name];
    }
}
#endif /* SkillTypesMapping_h */
