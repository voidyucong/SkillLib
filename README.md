# SkillLib
CSkill {
	uint abilityBehavior; // 技能行为 可以无目标攻击|忽略后摇
	uint abilityDamageType;  // 伤害类型 物理|魔法|纯粹
	uint abilityMaxLevel;  // 最大等级
	const char* abilityTextureName;  // 技能图标
	std::vector<float> abilityCooldown;  // "140.0 120.0 100.0"  //技能cd 
	std::vector<float> abilityDuration;  // "3.0 3.0 3.0"   //持续时间
	std::vector<float> abilityChannelTime;  // "2.0 2.0 2.0"   //引导时间，或者叫吟唱
	std::vector<float> abilityCastPoint;  // "0.0 0.0 0.0 0.0"   //施法前摇
	std::vector<float> abilityManaCost;  // "175 250 325"   //技能魔法消耗

	std::map<const char*, CSpecial*> specials;
}

CSpecial {
	CSpecial (int);
	CSpecial (float);
	CSpecial (const char*);
	CSpecial (vector<CSpecial>);
}

CModifier {
	const char* name;
	unit attributes;	// 属性	忽视无敌，可叠加，无，正常
	float duration;  // 持续时间
	EffectAttachType	follow_origin, follow_overhead, follow_chest, follow_head, start_at_customorigin, world_origin
	特效附着点类型	原点，头顶，胸膛，头部，自定义原点，世界原点
	EffectName	StringValue
	特效名称	字符串(路径+特效名)
	IsBuff	BooleanValue
	是否增益魔法	布尔值（1为增益魔法）
	IsDebuff	BooleanValue
	是否减益魔法	布尔值（1为减益魔法）
	IsHidden	BooleanValue
	是否隐藏	布尔值（1为隐藏）
	IsPurgable	BooleanValue
	能否被驱散	布尔值（1为可被驱散）
	OverrideAnimation	ACT_DOTA_ATTACK, ACT_DOTA_CAST_ABILITY_1 (2, 3, 4, 5, 6), ACT_DOTA_DISABLED, ACT_DOTA_SPAWN, ACT_DOTA_TELEPORT, ACT_DOTA_VICTORY
	覆盖模型动作	攻击动作，技能释放动作(1~6)，受伤动作，出生动作，回程动作，胜利动作
	Passive	BooleanValue
	被动	布尔值（1为被动技能，会自动添加该Modifiers）
	TextureName	StringValue
	图标名称	字符串
	ThinkInterval	FloatValue
	Think间隔	浮点值
}

CModifierEvent {
	unit eventType;  // MODIFIER_EVENT_INTERVAL  MODIFIER_EVENT_ONATTACK
	std::vector<COperate*> operates;
}

CModifierProperty {
	std::vector<uint> properties;
}

CModifierState {
	
}

CPreCache {
	unit cacheType;
	const char* path;
}

CEvent {
	unit eventType;  // EVENT_SPELL_START
	std::vector<COperate*> operates;
}

COperate {
	
}