#pragma once
#include "MiniGame/unit/Unit.h"

class prove : public Unit
{
public:
	prove();
	virtual~prove();
	void unitInfo() override;
};

class zealot : public Unit
{
public:
	zealot();
	virtual~zealot();
	void unitInfo() override;
};

class dragon : public Unit
{
public:
	dragon();
	virtual~dragon();
	void unitInfo() override;
};

class river : public Unit
{
public:
	river();
	virtual~river();
	void unitInfo() override;
};