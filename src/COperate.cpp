//
//  COperate.cpp
//  SkillLib
//
//  Created by yucong on 17/8/27.
//  Copyright © 2017年 yucong. All rights reserved.
//

#include "COperate.hpp"
#include <iostream>


// COperate
COperate::COperate() {
    
}

COperate::~COperate() {
    
}

int COperate::Execute() {
    return 1;
}

#pragma mark -
#pragma mark COperateAddAbility
// COperateAddAbility
COperateAddAbility::COperateAddAbility()
: abilityName_(0)
{
    
}

COperateAddAbility::~COperateAddAbility() {
    
}

int COperateAddAbility::Execute() {
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

int CActOnTargets::Execute() {
    return 1;
}

#pragma mark -
#pragma mark CApplyModifier
// CApplyModifier
CApplyModifier::CApplyModifier()
: modifierName_(0)
{
    
}

CApplyModifier::~CApplyModifier() {
    
}

int CApplyModifier::Execute() {
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

int CAttachEffect::Execute() {
    return 1;
}

#pragma mark -
#pragma mark CBlink
// CBlink
CBlink::CBlink() {
    
}

CBlink::~CBlink() {
    
}

int CBlink::Execute() {
    return 1;
}

#pragma mark -
#pragma mark CCreateThinker
// CCreateThinker
CCreateThinker::CCreateThinker()
: interval_(0)
{
}

CCreateThinker::CCreateThinker(float interval)
: interval_(interval)
{
}

CCreateThinker::~CCreateThinker() {
    
}

int CCreateThinker::Execute() {
    std::cout << "CCreateThinker Execute" << std::endl;
    return 1;
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

int CDamage::Execute() {
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

int CDelayedAction::Execute() {
    return 1;
}

#pragma mark -
#pragma mark CFireEffect
// CFireEffect
CFireEffect::CFireEffect()
: effectName_(0)
, attackType_(0)
{
    
}

CFireEffect::~CFireEffect() {
    
}

int CFireEffect::Execute() {
    std::cout << "CFireEffect Execute" << std::endl;
    return 1;
}

#pragma mark -
#pragma mark CFireSound
// CFireSound
CFireSound::CFireSound()
: effectName_(0)
{
    
}

CFireSound::~CFireSound() {
    
}

int CFireSound::Execute() {
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

int CHeal::Execute() {
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

int CKnockback::Execute() {
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

int CLevelUpAbility::Execute() {
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

int CLifesteal::Execute() {
    return 1;
}

#pragma mark -
#pragma mark CLinearProjectile
// CLinearProjectile
CLinearProjectile::CLinearProjectile()
: effectName_(0)
, moveSpeed_(0.f)
, startPosition_(0)
, targetType_(0)
, isProvidesVision_(false)
, visionRadius_ (0.f)
{
    
}

CLinearProjectile::~CLinearProjectile() {
    
}

int CLinearProjectile::Execute() {
    return 1;
}

#pragma mark -
#pragma mark CTrackingProjectile
// CTrackingProjectile
CTrackingProjectile::CTrackingProjectile()
: effectName_(0)
, moveSpeed_(0.f)
, startPosition_(0)
, targetType_(0)
, isProvidesVision_(false)
, visionRadius_ (0.f)
{
    
}

CTrackingProjectile::~CTrackingProjectile() {
    
}

int CTrackingProjectile::Execute() {
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

int CRandom::Execute() {
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

int CRemoveAbility::Execute() {
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

int CRemoveModifier::Execute() {
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

int CRunScript::Execute() {
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

int CSpawnUnit::Execute() {
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

int CStun::Execute() {
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

int CSpendMana::Execute() {
    return 1;
}
