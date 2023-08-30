#include "stdafx.h"
#include "zerg.h"

drone::drone()
{
}

drone::~drone()
{
}

void drone::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("droneIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("droneMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("droneDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("droneAtt");


	m_maxHp = 2;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 1;
	m_defence = 0;

	m_moveSpeed = 80.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 0;
	m_Creload = m_reload;


	m_rangeX = 2;
	m_rangeY = 1;
	m_cost = 2;
	m_winPoint = 2;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_SM;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

zurgling::zurgling()
{
}

zurgling::~zurgling()
{
}

void zurgling::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("zurglingIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("zurglingMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("zurglingDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("zurglingAtt");


	m_maxHp = 2;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 2;
	m_defence = 0;

	m_moveSpeed = 120.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 2;
	m_reload = 0;
	m_Creload = m_reload;


	m_rangeX = 1;
	m_rangeY = 1;
	m_cost = 2;
	m_winPoint = 1;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_SM;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

hydra::hydra()
{
}

hydra::~hydra()
{
}

void hydra::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("hydraIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("hydraMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("hydraDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("hydraAtt");


	m_maxHp = 3;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 2;
	m_defence = 0;

	m_moveSpeed = 120.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 0;
	m_Creload = m_reload;


	m_rangeX = 3;
	m_rangeY = 1;
	m_cost = 3;
	m_winPoint = 2;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_ME;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

bru::bru()
{
}

bru::~bru()
{
}

void bru::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("bruIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("bruMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("bruDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("bruAtt");


	m_maxHp = 1;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 3;
	m_defence = 0;

	m_moveSpeed = 120.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 0;
	m_Creload = m_reload;


	m_rangeX = 1;
	m_rangeY = 1;
	m_cost = 2;
	m_winPoint = 0;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_SM;

	m_size = D3DXVECTOR2(40.0f, 40.0f);
}

ultra::ultra()
{
}

ultra::~ultra()
{
}

void ultra::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("ultraIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("ultraMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("ultraDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("ultraAtt");


	m_maxHp = 6;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 3;
	m_defence = 1;

	m_moveSpeed = 120.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 0;
	m_Creload = m_reload;


	m_rangeX = 2;
	m_rangeY = 1;
	m_cost = 6;
	m_winPoint = 2;
	m_moveTile = 1;

	m_attackType = ATKTYPE_SPLASH;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_LA;

	m_size = D3DXVECTOR2(90.0f, 90.0f);
}

lurker::lurker()
{
}

lurker::~lurker()
{
}

void lurker::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("lurkerIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("lurkerMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("lurkerDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("lurkerIdle");


	m_maxHp = 5;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 0;
	m_defence = 0;

	m_moveSpeed = 120.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 0;
	m_Creload = m_reload;


	m_rangeX = 0;
	m_rangeY = 1;
	m_cost = 3;
	m_winPoint = 2;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_LA;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

lurker2::lurker2()
{
}

lurker2::~lurker2()
{
}

void lurker2::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("lurker2Idle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("hydraMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("lurkerDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("lurker2Att");


	m_maxHp = 5;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 3;
	m_defence = 0;

	m_moveSpeed = 120.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 1;
	m_Creload = m_reload;


	m_rangeX = 5;
	m_rangeY = 1;
	m_cost = 3;
	m_winPoint = 2;
	m_moveTile = 0;

	m_attackType = ATKTYPE_N;
	m_isHitAll = true;
	m_defenceType = DFCTYPE_LA;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}
