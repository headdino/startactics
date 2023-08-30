#pragma once
#include "GameNode.h"

class CardDeck : public GameNode
{
private:
	int m_randBg;

	int m_totalCard;

	ST_Card* m_card;

private:
	bool m_isCardDown = false;
	bool show_another_window = false;
	bool goMenu = false;
	bool m_isInDeck = true;
	
public:
	CardDeck();
	~CardDeck() override;
	HRESULT init() override;
	void release() override;
	void update() override;
	void render() override;

	void Save(char* fileName);
	void Load(char* fileName);
};

