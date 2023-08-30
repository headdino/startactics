#pragma once
#include "GameNode.h"

struct ST_MENU_OBJECT
{
	D3DXVECTOR2 pos;
	D3DXVECTOR2 size;
	bool isTouch;
	bool isClick;

	int frame;
	int frameT;
	string imageName;

	int frame2;
	int frameT2;
	string imageName2;

	float frmaeTime;
	float frameDelay;
};

class Menu : public GameNode
{
private:
	ST_MENU_OBJECT m_exit;
	ST_MENU_OBJECT m_editor;
	ST_MENU_OBJECT m_single;
	ST_MENU_OBJECT m_multi;

	void frameMove();
	void renderText();
public:
	Menu();
	~Menu() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;
};

