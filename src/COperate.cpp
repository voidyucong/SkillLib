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
#include "CScheduleManager.h"

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
    COperate* operate = new COperate();
    operate->targetSearcher_->SetCenter(targetSearcher_->GetCenter());
    operate->targetSearcher_->SetTeams(targetSearcher_->GetTeams());
    operate->targetSearcher_->SetTypes(targetSearcher_->GetTypes());
    operate->targetSearcher_->SetFlags(targetSearcher_->GetFlags());
    operate->targetSearcher_->SetRadius(targetSearcher_->GetRadius());
    return operate;
}

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
#pragma mark COperateAddAbility
// COperateAddAbility
COperateAddAbility::COperateAddAbility()
: abilityName_(0)
{
    
}

COperateAddAbility::~COperateAddAbility() {
    
}

int COperateAddAbility::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CActOnTargets
// CActOnTargets
CActOnTargets::CActOnTargets()
: modelName_(0)
{
    
}

CActOnTargets::~CActOnTargets() {
    
}

int CActOnTargets::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CApplyModifier
// CApplyModifier
CApplyModifier::CApplyModifier()
: CApplyModifier(0)
{
    
}

CApplyModifier::CApplyModifier(std::string modifierName)
: modifierName_(modifierName)
{
    
}

CApplyModifier::~CApplyModifier() {
    
}

int CApplyModifier::Execute(CAbilityEntity* entity, CAbility* ability) {
    auto targets = targetSearcher_->GetTargets(entity, ability);
    auto modifier = ability->GetModifier(modifierName_);
    assert(modifier);
    for (auto target : targets) {
        target->AddModifer(modifier->Clone());
        
        modifier->ExecuteEvent(MODIFIER_EVENT_ON_CREATED, entity, ability);
    }
    
    return 1;
}

#pragma mark -
#pragma mark CAttachEffect
// CAttachEffect
CAttachEffect::CAttachEffect()
: attachType_(0)
{
    
}

CAttachEffect::~CAttachEffect() {
    
}

int CAttachEffect::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CBlink
// CBlink
CBlink::CBlink() {
    
}

CBlink::~CBlink() {
    
}

int CBlink::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CCreateThinker
// CCreateThinker
CCreateThinker::CCreateThinker()
: CCreateThinker(0, -1)
{
}

CCreateThinker::CCreateThinker(float interval, float duration)
: interval_(interval)
, duration_(duration)
{
}

CCreateThinker::~CCreateThinker() {
    CScheduleManager::getInstance()->RemoveSchedule(this);
}

int CCreateThinker::Execute(CAbilityEntity* entity, CAbility* ability) {
    std::cout << "CCreateThinker Execute" << std::endl;
    CScheduleManager::getInstance()->AddSchedule(this, CObject::CALLBACK(&CCreateThinker::Update), interval_);
    return 1;
}

void CCreateThinker::Update(float dt) {
    std::cout << "CCreateThinker update" << std::endl;
}

#pragma mark -
#pragma mark CDamage
// CDamage
CDamage::CDamage()
: damageType_(ABILITY_DAMAGE_TYPE_NONE)
, damage_(0)
, currentHealthPercentBasedDamage_(0)
, maxHealthPercentBasedDamage_(0)
{
    
}

CDamage::~CDamage() {
    
}

int CDamage::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CDelayedAction
// CDelayedAction
CDelayedAction::CDelayedAction()
: delay_(0.f)
, action_(0)
{
    
}

CDelayedAction::~CDelayedAction() {
    
}

int CDelayedAction::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CFireEffect
// CFireEffect
CFireEffect::CFireEffect()
: effectName_("")
, attackType_(0)
{
    
}

CFireEffect::~CFireEffect() {
    
}

int CFireEffect::Execute(CAbilityEntity* entity, CAbility* ability) {
    std::cout << "CFireEffect Execute" << std::endl;
    return 1;
}

#pragma mark -
#pragma mark CFireSound
// CFireSound
CFireSound::CFireSound()
: effectName_("")
{
    
}

CFireSound::~CFireSound() {
    
}

int CFireSound::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CHeal
// CHeal
CHeal::CHeal()
: healAmount_(0)
{
    
}

CHeal::~CHeal() {
    
}

int CHeal::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CKnockback
// CKnockback
CKnockback::CKnockback()
: distance_(0)
, height_(0)
{
    
}
CKnockback::~CKnockback() {
    
}

int CKnockback::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CLevelUpAbility
// CLevelUpAbility
CLevelUpAbility::CLevelUpAbility()
: abilityName_(0)
{
    
}

CLevelUpAbility::~CLevelUpAbility() {
    
}

int CLevelUpAbility::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CLifesteal
// CLifesteal
CLifesteal::CLifesteal()
: lifestealPercent_(0.f)
{
    
}

CLifesteal::~CLifesteal() {
    
}

int CLifesteal::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CLinearProjectile
// CLinearProjectile
CLinearProjectile::CLinearProjectile()
: effectName_(0)
, moveSpeed_(0.f)
, startPosition_(0)
, isProvidesVision_(false)
, visionRadius_ (0.f)
{
    
}

CLinearProjectile::~CLinearProjectile() {
    
}

int CLinearProjectile::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CTrackingProjectile
// CTrackingProjectile
CTrackingProjectile::CTrackingProjectile()
: effectName_(0)
, moveSpeed_(0.f)
, startPosition_(0)
, isProvidesVision_(false)
, visionRadius_ (0.f)
{
    
}

CTrackingProjectile::~CTrackingProjectile() {
    
}

int CTrackingProjectile::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CRandom
// CRandom
CRandom::CRandom()
: chance_(0.f)
, onSuccess_(0)
, onFailed_(0)
{
    
}

CRandom::~CRandom() {
    
}

int CRandom::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CRemoveAbility
// CRemoveAbility
CRemoveAbility::CRemoveAbility()
: abilityName_(0)
{
    
}

CRemoveAbility::~CRemoveAbility() {
    
}

int CRemoveAbility::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CRemoveModifier
// CRemoveModifier
CRemoveModifier::CRemoveModifier()
: modifierName_(0)
{
    
}

CRemoveModifier::~CRemoveModifier() {
    
}

int CRemoveModifier::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CRunScript
// CRunScript
CRunScript::CRunScript()
: scriptFile_(0)
, function_(0)
{
    
}

CRunScript::~CRunScript() {
    
}

int CRunScript::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CSpawnUnit
// CSpawnUnit
CSpawnUnit::CSpawnUnit()
: unitName_(0)
, unitCount_(0)
, unitLimit_(0)
, spawnRadius_(0.f)
, duration_(0.f)
{
    
}

CSpawnUnit::~CSpawnUnit() {
    
}

int CSpawnUnit::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CStun
// CStun
CStun::CStun()
: duration_(0.f)
{
    
}

CStun::~CStun() {
    
}

int CStun::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CSpendMana
// CSpendMana
CSpendMana::CSpendMana()
: mana_(0.f)
{
    
}

CSpendMana::~CSpendMana() {
    
}

int CSpendMana::Execute(CAbilityEntity* entity, CAbility* ability) {
    return 1;
}

#pragma mark -
#pragma mark CLog
// CLog
CLog::CLog() {}
CLog::CLog(std::string text): text_(text) {}
CLog::~CLog() {}

int CLog::Execute(CAbilityEntity* entity, CAbility* ability) {
    std::cout << "Operate:" << text_ << std::endl;
    return 1;
}
