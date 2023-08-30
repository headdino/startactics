#pragma once
#include "MiniGame/unit/Unit.h"

class drone : public Unit
{
public:
	drone();
	virtual~drone();
	void unitInfo() override;
};

class zurgling : public Unit
{
public:
	zurgling();
	virtual~zurgling();
	void unitInfo() override;
};

class hydra : public Unit
{
public:
	hydra();
	virtual~hydra();
	void unitInfo() override;
};

class bru : public Unit
{
public:
	bru();
	virtual~bru();
	void unitInfo() override;
};

class ultra : public Unit
{
public:
	ultra();
	virtual~ultra();
	void unitInfo() override;
};

class lurker : public Unit
{
public:
	lurker();
	virtual~lurker();
	void unitInfo() override;
};

class lurker2 : public Unit
{
public:
	lurker2();
	virtual~lurker2();
	void unitInfo() override;
};