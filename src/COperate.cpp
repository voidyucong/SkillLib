//
//  COperate.cpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "COperate.hpp"
#include <iostream>
#include <assert.h>
#include "CAbility.hpp"
#include "CAbilityEntity.hpp"
#include "CModifier.h"
#include "CModifierData.hpp"
#include "CScheduleManager.h"
#include "CRunScprite.hpp"
#include "CTargetStack.hpp"
#include "CTargetSearcher.hpp"
#include "CAbilityValue.hpp"

// COperate
COperate::COperate()
{
    targetSearchType_ = new CTargetSearchType();
    targetStack_ = new CTargetStack();
}

COperate::~COperate() {
    delete targetSearchType_;
    targetSearchType_ = 0;
}

int COperate::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    targetStack_->SetParent(parentStack);
    CTargetSearcher::HandleTargetStack(entity, ability, targetStack_, targetSearchType_);
    return 1;
}

void COperate::Update(float dt) {
    
}

COperate* COperate::Clone() {
    COperate* operate = CreateCloneInstance();
    operate->targetSearchType_->SetCenter(targetSearchType_->GetCenter());
    operate->targetSearchType_->SetTeams(targetSearchType_->GetTeams());
    operate->targetSearchType_->SetTypes(targetSearchType_->GetTypes());
    operate->targetSearchType_->SetFlags(targetSearchType_->GetFlags());
    operate->targetSearchType_->SetRadius(targetSearchType_->GetRadius());
    CloneProperties(operate);
    return operate;
}

COperate* COperate::CreateCloneInstance() {
    return new COperate();
}

void COperate::CloneProperties(COperate* operate) {
    
}

void COperate::SetSingle(TARGET_CENTER single) { targetSearchType_->SetSingle(single); }
TARGET_CENTER COperate::GetSingle() { return targetSearchType_->GetSingle(); }
void COperate::SetCenter(TARGET_CENTER center) { targetSearchType_->SetCenter(center); }
TARGET_CENTER COperate::GetCenter() { return targetSearchType_->GetCenter(); }
void COperate::SetRadius(CAbilityValue* radius) { targetSearchType_->SetRadius(radius); }
CAbilityValue* COperate::GetRadius() { return targetSearchType_->GetRadius(); }
void COperate::SetTeams(TARGET_TEAMS teams) { targetSearchType_->SetTeams(teams); }
TARGET_TEAMS COperate::GetTeams() { return targetSearchType_->GetTeams(); }
void COperate::SetTypes(TARGET_TYPES types) { targetSearchType_->SetTypes(types); }
TARGET_TYPES COperate::GetTypes() { return targetSearchType_->GetTypes(); }
void COperate::SetFlags(TARGET_FLAGS flags) { targetSearchType_->SetFlags(flags); }
TARGET_FLAGS COperate::GetFlags() { return targetSearchType_->GetFlags(); }
void COperate::SetMaxTargets(CAbilityValue* max) { targetSearchType_->SetMaxTargets(max); }
CAbilityValue* COperate::GetMaxTargets() { return targetSearchType_->GetMaxTargets(); }

void COperate::SetParentTargets(CTargetStack* parent) {
    targetStack_->SetParent(parent);
}

void COperate::SetSelfTargets(TARGET_LIST targets) {
    targetStack_->SetSelf(new CTargetStackItem(targets));
}


#pragma mark -
#pragma mark COpAddAbility
// COpAddAbility
COpAddAbility::COpAddAbility()
: abilityName_(0)
{
    
}

COpAddAbility::~COpAddAbility() {
    
}

int COpAddAbility::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpActOnTargets
// COpActOnTargets
COpActOnTargets::COpActOnTargets()
: modelName_(0)
{
    
}

COpActOnTargets::~COpActOnTargets() {
    
}

int COpActOnTargets::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpApplyModifier
// COpApplyModifier
COpApplyModifier::COpApplyModifier()
: COpApplyModifier(0)
{
    
}

COpApplyModifier::COpApplyModifier(std::string modifierName)
: modifierName_(modifierName)
{
    
}

COpApplyModifier::~COpApplyModifier() {
    
}

int COpApplyModifier::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    COperate::Execute(entity, ability, parentStack);
    auto modifierData = ability->GetModifierData(modifierName_);
    assert(modifierData);
    for (auto target : targetStack_->GetValid()->GetTargets()) {
        CModifier* modifier = new CModifier();
        modifier->SetModifierData(modifierData->Clone());
        modifier->GetTargetStack()->SetParent(parentStack);
        target->AddModifer(modifier);
        modifier->Activate(entity, ability);
    }
    
    return 1;
}

#pragma mark -
#pragma mark COpAttachEffect
// COpAttachEffect
COpAttachEffect::COpAttachEffect()
: attachType_(0)
{
    
}

COpAttachEffect::~COpAttachEffect() {
    
}

int COpAttachEffect::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpBlink
// COpBlink
COpBlink::COpBlink() {
    
}

COpBlink::~COpBlink() {
    
}

int COpBlink::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpCreateThinker
// COpCreateThinker
COpCreateThinker::COpCreateThinker()
: COpCreateThinker(0, -1)
{
}

COpCreateThinker::COpCreateThinker(float interval, float duration)
: interval_(interval)
, duration_(duration)
{
}

COpCreateThinker::~COpCreateThinker() {
    CScheduleManager::getInstance()->RemoveSchedule(this);
}

int COpCreateThinker::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    std::cout << "COpCreateThinker Execute" << std::endl;
    CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&COpCreateThinker::Update), interval_);
    return 1;
}

void COpCreateThinker::Update(float dt) {
    std::cout << "COpCreateThinker Update" << std::endl;
}

#pragma mark -
#pragma mark COpDamage
// COpDamage
COpDamage::COpDamage()
: damageType_(ABILITY_DAMAGE_TYPE_NONE)
, damage_(0)
, currentHealthPercentBasedDamage_(0)
, maxHealthPercentBasedDamage_(0)
{
    
}

COpDamage::~COpDamage() {
    
}

int COpDamage::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpDelayedAction
// COpDelayedAction
COpDelayedAction::COpDelayedAction()
: delay_(0.f)
, action_(0)
{
    
}

COpDelayedAction::~COpDelayedAction() {
    
}

int COpDelayedAction::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpFireEffect
// COpFireEffect
COpFireEffect::COpFireEffect()
: effectName_("")
, attackType_(0)
{
    
}

COpFireEffect::~COpFireEffect() {
    
}

int COpFireEffect::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    std::cout << "COpFireEffect Execute" << std::endl;
    return 1;
}

#pragma mark -
#pragma mark COpFireSound
// COpFireSound
COpFireSound::COpFireSound()
: effectName_("")
{
    
}

COpFireSound::~COpFireSound() {
    
}

int COpFireSound::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpHeal
// COpHeal
COpHeal::COpHeal()
: COpHeal(0)
{
    
}

COpHeal::COpHeal(CAbilityValue* amount)
: healAmount_(amount)
{
    
}

COpHeal::~COpHeal() {
    
}

int COpHeal::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    COperate::Execute(entity, ability, parentStack);
    auto targets = targetStack_->GetValid()->GetTargets();
    for (auto target : targets) {
        std::cout << "Heal " << target << " " << healAmount_->GetArrayValueByIndex(ability->GetLevel() - 1)->GetValue<float>() << std::endl;
    }
    
    return 1;
}

COperate* COpHeal::CreateCloneInstance() {
    return new COpHeal();
}

void COpHeal::CloneProperties(COperate* operate) {
    COpHeal* op = dynamic_cast<COpHeal*>(operate);
    op->SetHealAmount(healAmount_);
}

#pragma mark -
#pragma mark COpKnockback
// COpKnockback
COpKnockback::COpKnockback()
: distance_(0)
, height_(0)
{
    
}
COpKnockback::~COpKnockback() {
    
}

int COpKnockback::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpLevelUpAbility
// COpLevelUpAbility
COpLevelUpAbility::COpLevelUpAbility()
: abilityName_(0)
{
    
}

COpLevelUpAbility::~COpLevelUpAbility() {
    
}

int COpLevelUpAbility::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpLifesteal
// COpLifesteal
COpLifesteal::COpLifesteal()
: lifestealPercent_(0.f)
{
    
}

COpLifesteal::~COpLifesteal() {
    
}

int COpLifesteal::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpLinearProjectile
// COpLinearProjectile
COpLinearProjectile::COpLinearProjectile()
: effectName_(0)
, moveSpeed_(0)
, startRadius_(0)
, endRadius_(0)
, distance_(0)
, isProvidesVision_(false)
, visionRadius_ (0)
{
    
}

COpLinearProjectile::~COpLinearProjectile() {
    
}

int COpLinearProjectile::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpTrackingProjectile
// COpTrackingProjectile
COpTrackingProjectile::COpTrackingProjectile()
: effectName_(0)
, moveSpeed_(0.f)
, startPosition_(0)
, isProvidesVision_(false)
, visionRadius_ (0.f)
{
    
}

COpTrackingProjectile::~COpTrackingProjectile() {
    
}

int COpTrackingProjectile::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpRandom
// COpRandom
COpRandom::COpRandom()
: chance_(0.f)
, onSuccess_(0)
, onFailed_(0)
{
    
}

COpRandom::~COpRandom() {
    
}

int COpRandom::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpRemoveAbility
// COpRemoveAbility
COpRemoveAbility::COpRemoveAbility()
: abilityName_(0)
{
    
}

COpRemoveAbility::~COpRemoveAbility() {
    
}

int COpRemoveAbility::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpRemoveModifier
// COpRemoveModifier
COpRemoveModifier::COpRemoveModifier()
: modifierName_(0)
{
    
}

COpRemoveModifier::~COpRemoveModifier() {
    
}

int COpRemoveModifier::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpRunScript
// COpRunScript
COpRunScript::COpRunScript()
: scriptFile_(0)
, function_(0)
{
    
}

COpRunScript::~COpRunScript() {
    
}

int COpRunScript::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpSpawnUnit
// COpSpawnUnit
COpSpawnUnit::COpSpawnUnit()
: unitName_(0)
, unitCount_(0)
, unitLimit_(0)
, spawnRadius_(0.f)
, duration_(0.f)
{
    
}

COpSpawnUnit::~COpSpawnUnit() {
    
}

int COpSpawnUnit::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpStun
// COpStun
COpStun::COpStun()
: duration_(0.f)
{
    
}

COpStun::~COpStun() {
    
}

int COpStun::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpSpendMana
// COpSpendMana
COpSpendMana::COpSpendMana()
: mana_(0.f)
{
    
}

COpSpendMana::~COpSpendMana() {
    
}

int COpSpendMana::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    return 1;
}

#pragma mark -
#pragma mark COpLog
// COpLog
COpLog::COpLog() {}
COpLog::COpLog(std::string text): text_(text) {}
COpLog::~COpLog() {}

int COpLog::Execute(CAbilityEntity* entity, CAbility* ability, CTargetStack* parentStack) {
    std::cout << "Operate:" << text_ << std::endl;
    return 1;
}

COperate* COpLog::CreateCloneInstance() {
    return new COpLog();
}
void COpLog::CloneProperties(COperate* operate) {
    COpLog* log = dynamic_cast<COpLog*>(operate);
    log->SetText(text_);
    
}
