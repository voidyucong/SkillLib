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

// COperate
COperate::COperate()
{
    targetSearcher_ = new CTargetSearcher();
}

COperate::~COperate() {
    delete targetSearcher_;
    targetSearcher_ = 0;
}

int COperate::Execute(CAbilityEntity* entity, CAbility* ability) {
    
    return 1;
}

void COperate::Update(float dt) {
    
}

COperate* COperate::Clone() {
    COperate* operate = CreateCloneInstance();
    operate->targetSearcher_->SetCenter(targetSearcher_->GetCenter());
    operate->targetSearcher_->SetTeams(targetSearcher_->GetTeams());
    operate->targetSearcher_->SetTypes(targetSearcher_->GetTypes());
    operate->targetSearcher_->SetFlags(targetSearcher_->GetFlags());
    operate->targetSearcher_->SetRadius(targetSearcher_->GetRadius());
    CloneProperties(operate);
    return operate;
}

COperate* COperate::CreateCloneInstance() {
    return new COperate();
}

void COperate::CloneProperties(COperate* operate) {
    
}

void COperate::SetSingle(TARGET_CENTER single) { targetSearcher_->SetSingle(single); }
TARGET_CENTER COperate::GetSingle() { return targetSearcher_->GetSingle(); }
void COperate::SetCenter(TARGET_CENTER center) { targetSearcher_->SetCenter(center); }
TARGET_CENTER COperate::GetCenter() { return targetSearcher_->GetCenter(); }
void COperate::SetRadius(CAbilityValue* radius) { targetSearcher_->SetRadius(radius); }
CAbilityValue* COperate::GetRadius() { return targetSearcher_->GetRadius(); }
void COperate::SetTeams(TARGET_TEAMS teams) { targetSearcher_->SetTeams(teams); }
TARGET_TEAMS COperate::GetTeams() { return targetSearcher_->GetTeams(); }
void COperate::SetTypes(TARGET_TYPES types) { targetSearcher_->SetTypes(types); }
TARGET_TYPES COperate::GetTypes() { return targetSearcher_->GetTypes(); }
void COperate::SetFlags(TARGET_FLAGS flags) { targetSearcher_->SetFlags(flags); }
TARGET_FLAGS COperate::GetFlags() { return targetSearcher_->GetFlags(); }

#pragma mark -
#pragma mark COpAddAbility
// COpAddAbility
COpAddAbility::COpAddAbility()
: abilityName_(0)
{
    
}

COpAddAbility::~COpAddAbility() {
    
}

int COpAddAbility::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpActOnTargets::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpApplyModifier::Execute(CAbilityEntity* entity, CAbility* ability) {
    auto targets = targetSearcher_->GetTargets(entity);
    auto modifierData = ability->GetModifierData(modifierName_);
    assert(modifierData);
    for (auto target : targets) {
        CModifier* modifier = new CModifier();
        target->AddModifer(modifier);
        modifier->SetModifierData(modifierData->Clone());
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

int COpAttachEffect::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark COpBlink
// COpBlink
COpBlink::COpBlink() {
    
}

COpBlink::~COpBlink() {
    
}

int COpBlink::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpCreateThinker::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpDamage::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpDelayedAction::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpFireEffect::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpFireSound::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark COpHeal
// COpHeal
COpHeal::COpHeal()
: COpHeal(0)
{
    
}

COpHeal::COpHeal(float amount)
: healAmount_(amount)
{
    
}

COpHeal::~COpHeal() {
    
}

int COpHeal::Execute(CAbilityEntity* entity, CAbility* ability) {
    std::cout << "Heal " << healAmount_ << std::endl;
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

int COpKnockback::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpLevelUpAbility::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpLifesteal::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark COpLinearProjectile
// COpLinearProjectile
COpLinearProjectile::COpLinearProjectile()
: effectName_(0)
, moveSpeed_(0.f)
, startPosition_(0)
, isProvidesVision_(false)
, visionRadius_ (0.f)
{
    
}

COpLinearProjectile::~COpLinearProjectile() {
    
}

int COpLinearProjectile::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpTrackingProjectile::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpRandom::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpRemoveAbility::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpRemoveModifier::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpRunScript::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpSpawnUnit::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpStun::Execute(CAbilityEntity* entity, CAbility* ability) {
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

int COpSpendMana::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark COpLog
// COpLog
COpLog::COpLog() {}
COpLog::COpLog(std::string text): text_(text) {}
COpLog::~COpLog() {}

int COpLog::Execute(CAbilityEntity* entity, CAbility* ability) {
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
