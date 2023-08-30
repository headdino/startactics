#include "stdafx.h"
#include "protoss.h"

prove::prove()
{
}

prove::~prove()
{
}

void prove::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("proveIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("proveMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("boom");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("proveAtt");


	m_maxHp = 2;
	m_hp = m_maxHp;
	m_maxShield = 2;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 1;
	m_defence = 0;

	m_moveSpeed = 80.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 0;
	m_Creload = 0;


	m_minRange = 0;
	m_rangeX = 2;
	m_rangeY = 1;
	m_cost = 2;
	m_winPoint = 2;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_ME;

	m_size = D3DXVECTOR2(30.0f, 30.0f);
}

zealot::zealot()
{
}

zealot::~zealot()
{
}

void zealot::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("zealotIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("zealotMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("zealotDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("zealotAtt");


	m_maxHp = 3;
	m_hp = m_maxHp;
	m_maxShield = 2;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 2;
	m_defence = 0;

	m_moveSpeed = 120.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 2;
	m_reload = 0;
	m_Creload = 0;


	m_minRange = 0;
	m_rangeX = 1;
	m_rangeY = 1;
	m_cost = 3;
	m_winPoint = 2;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_ME;

	m_size = D3DXVECTOR2(80.0f, 80.0f);
}

dragon::dragon()
{
}

dragon::~dragon()
{
}

void dragon::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("dragonIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("dragonMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("dragonDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("dragonAtt");


	m_maxHp = 4;
	m_hp = m_maxHp;
	m_maxShield = 4;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 2;
	m_defence = 1;

	m_moveSpeed = 90.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 1;
	m_Creload = 0;


	m_minRange = 0;
	m_rangeX = 4;
	m_rangeY = 1;
	m_cost = 4;
	m_winPoint = 2;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_ME;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

river::river()
{
}

river::~river()
{
}

void river::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("riverIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("riverMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("boom");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("riverAtt");


	m_maxHp = 2;
	m_hp = m_maxHp;
	m_maxShield = 4;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 4;
	m_defence = 0;

	m_moveSpeed = 70.0f;

	m_frameDelay = 2.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 2;
	m_Creload = m_reload;


	m_minRange = 2;
	m_rangeX = 5;
	m_rangeY = 1;
	m_cost = 6;
	m_winPoint = 3;
	m_moveTile = 1;

	m_attackType = ATKTYPE_SPLASH;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_LA;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}
