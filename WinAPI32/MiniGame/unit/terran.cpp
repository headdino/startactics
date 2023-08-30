#include "stdafx.h"
#include "terran.h"

marine::marine()
{
}

marine::~marine()
{
}

void marine::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("marineIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("marineMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("marineDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("marineAtt");


	m_maxHp = 2;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 1;
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
	m_defenceType = DFCTYPE_SM;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

scv::scv()
{
}

scv::~scv()
{
}

void scv::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("scvIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("scvIdle");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("boom");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("scvAtt");


	m_maxHp = 4;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 1;
	m_defence = 0;

	m_moveSpeed = 100.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 0;
	m_Creload = m_reload;


	m_rangeX = 1;
	m_rangeY = 1;
	m_cost = 3;
	m_winPoint = 1;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_SM;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

medic::medic()
{
}

medic::~medic()
{
}

void medic::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("medicIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("medicMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("medicDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("medicAtt");


	m_maxHp = 4;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 1;
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
	m_cost = 3;
	m_winPoint = 1;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_SM;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

firebat::firebat()
{
}

firebat::~firebat()
{
}

void firebat::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("firebatIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("firebatMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("boom");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("firebatAtt");


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


	m_rangeX = 2;
	m_rangeY = 1;
	m_cost = 4;
	m_winPoint = 2;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = true;
	m_defenceType = DFCTYPE_SM;

	m_size = D3DXVECTOR2(20.0f, 20.0f);
}

ghost::ghost()
{
}

ghost::~ghost()
{
}

void ghost::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("ghostIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("ghostMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("ghostDie");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("ghostAtt");


	m_maxHp = 2;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 1;
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
	m_cost = 5;
	m_winPoint = 3;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_SM;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

tankN::tankN()
{
}

tankN::~tankN()
{
}

void tankN::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("tankNIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("tankNMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("boom");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("tankNAtt");


	m_maxHp = 4;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 2;
	m_defence = 1;

	m_moveSpeed = 100.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 0;
	m_Creload = m_reload;

	m_rangeX = 4;
	m_rangeY = 1;
	m_cost = 5;
	m_winPoint = 2;
	m_moveTile = 1;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_LA;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

tankS::tankS()
{
}

tankS::~tankS()
{
}

void tankS::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("tankSIdle");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("ghostMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("boom");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("tankSAtt");


	m_maxHp = 4;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 4;
	m_defence = 1;

	m_moveSpeed = 50.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 2;
	m_Creload = 0;


	m_minRange = 2;
	m_rangeX = 6;
	m_rangeY = 1;
	m_cost = 5;
	m_winPoint = 2;
	m_moveTile = 0;

	m_attackType = ATKTYPE_SPLASH;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_LA;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}

barrigate::barrigate()
{
}

barrigate::~barrigate()
{
}

void barrigate::unitInfo()
{
	m_unitImage[UTST_IDLE] = IMGMANAGER->GetImage("barrigate");
	m_unitImage[UTST_MOVE] = IMGMANAGER->GetImage("ghostMove");
	m_unitImage[UTST_DIE] = IMGMANAGER->GetImage("boom");
	m_unitImage[UTST_ATT] = IMGMANAGER->GetImage("ghostAtt");


	m_maxHp = 8;
	m_hp = m_maxHp;
	m_maxShield = 0;
	m_shield = m_maxShield == 0 ? 0 : m_maxShield;

	m_attackDamage = 1;
	m_defence = 0;

	m_moveSpeed = 120.0f;

	m_frameDelay = 1.0f / 10.0f;
	m_attackDelay = 15.0f;
	m_attackTime = 0.0f;
	m_attackNumber = 1;
	m_reload = 0;
	m_Creload = m_reload;


	m_rangeX = 0;
	m_rangeY = 0;
	m_cost = 2;
	m_winPoint = 0;
	m_moveTile = 0;

	m_attackType = ATKTYPE_N;
	m_isHitAll = false;
	m_defenceType = DFCTYPE_LA;

	m_size = D3DXVECTOR2(60.0f, 60.0f);
}
