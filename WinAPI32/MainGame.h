#pragma once
#include "GameNode.h"

class MainGame :public GameNode
{
private:



public:
	MainGame();
	~MainGame() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

};

