#pragma once
#include "MiniGame/unit/Unit.h"

class marine : public Unit
{
public:
	marine();
	virtual~marine();
	void unitInfo() override;
};

class scv : public Unit
{
public:
	scv();
	virtual~scv();
	void unitInfo() override;
};

class medic : public Unit
{
public:
	medic();
	virtual~medic();
	void unitInfo() override;
};

class firebat : public Unit
{
public:
	firebat();
	virtual~firebat();
	void unitInfo() override;
};

class ghost : public Unit
{
public:
	ghost();
	virtual~ghost();
	void unitInfo() override;
};

class tankN : public Unit
{
public:
	tankN();
	virtual~tankN();
	void unitInfo() override;
};

class tankS : public Unit
{
public:
	tankS();
	virtual~tankS();
	void unitInfo() override;
};

class barrigate : public Unit
{
public:
	barrigate();
	virtual~barrigate();
	void unitInfo() override;
};
