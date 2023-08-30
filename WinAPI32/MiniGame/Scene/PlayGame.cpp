#include "stdafx.h"
#include "PlayGame.h"

PlayGame::PlayGame()
{
}


PlayGame::~PlayGame()
{
}

HRESULT PlayGame::init()
{
	mapIndex = 0;
	m_isMapSelect = true;
	m_isInGame = false;
	m_isText = true;
	goMenu = false;

	g_actionPoint = 3.0f;
	m_turnMoneyBase = 1.5f;
	m_turnMoney = 1.0f;
	m_turnTime = 0.0f;
	m_turn = T_PLAY;
	m_angle = 0.0f;

	m_tile = new TileMap;
	m_tile->init();

	m_unitManager = new UnitManager;
	m_unitManager->init();
	m_unitManager->setTile(m_tile);

	m_card = new Card[CARDMAX];
	for (int i = 0; i < CARDMAX; i++)
	{
		m_card[i].init(D3DXVECTOR2(i * 190.0f + 420.0f, 100));
		m_card[i].SetUnitManager(m_unitManager);
		m_card[i].SetTileMap(m_tile);
		m_card[i].SetPlayGame(this);
	}

	m_deck = new ST_Card[CARD_KIND];

	for (int i = 0; i < CARD_KIND; i++)
	{
		m_deck[i].name = "";
		m_deck[i].count = 0;
	}

	m_deck[0].name = "Marine";
	m_deck[0].count = 4;
	m_deck[1].name = "SCV";
	m_deck[1].count = 2;
	m_deck[2].name = "Tank";
	m_deck[2].count = 2;
	m_deck[3].name = "Maneuver";
	m_deck[3].count = 4;
	m_deck[4].name = "Field repair";
	m_deck[4].count = 1;
	m_deck[5].name = "SteamPack";
	m_deck[5].count = 4;
	m_deck[6].name = "Siege Mode";
	m_deck[6].count = 2;
	m_deck[7].name = "Medic";
	m_deck[7].count = 1;

	m_totalCard = 20;

	int j = 0;

	for (int i = 0; i < CARD_KIND; i++)
	{
		while (1)
		{
			if (m_deck[i].count <= 0) break;
			if (j == 20) break;

			m_deck[i].count--;

			m_cardName[j] = m_deck[i].name;
			++j;
			
		}
		
		
	}

	m_guardImage = IMGMANAGER->GetImage("ui_guardCard");
	m_guardPos.x = 1250.0f;
	m_guardPos.y = 200.0f;
	m_guardSize.x = 100.0f;
	m_guardSize.y = 100.0f;
	m_guardImage->Scale(m_guardSize);
	m_guardImage->Position(m_guardPos);
	m_guardRc = RectMakeCenter(m_guardPos.x, m_guardPos.y, m_guardSize.x, m_guardSize.y);

	g_losePoint = 0;
	g_winPoint = 0;

	m_textFrame = 0;
	m_frameHero = 0;
	m_whoHero = 0;
	m_frameTime = 0.0f;
	m_HeroImg[0] = IMGMANAGER->GetImage("h_jim");
	m_HeroImg[1] = IMGMANAGER->GetImage("h_meng");
	m_HeroImg[2] = IMGMANAGER->GetImage("h_ke");
	m_HeroImg[3] = IMGMANAGER->GetImage("h_over");
	m_HeroImg[4] = IMGMANAGER->GetImage("h_arta");
	m_HeroImg[5] = IMGMANAGER->GetImage("h_du");

	m_aiUTime = 0.0f;
	m_aiMTime = 0.0f;
	m_aiUDelay = 0.0f;
	m_aiMDelay = 0.0f;


	return S_OK;
}

void PlayGame::release()
{
	SAFE_DELETE(m_tile);
	SAFE_DELETE(m_unitManager);
	SAFE_DELETE_ARRAY(m_card);
}

void PlayGame::update()
{



	if (m_isMapSelect)
	{

		if (goMenu)
			SCENEMANAGER->ChangeScene("Loading", MENU);
	}
	else
	{
		//게임 중일때만 업데이트 돌림
		if (m_isInGame)
		{
			clickUpdate();
			turn();
			m_tile->update();
			m_unitManager->update();
			AI();

			//int count = 0;
			for (int i = 0; i < CARDMAX; i++)
			{
				m_card[i].update();

				/*if (m_card[i].Getm_isSelect())
				{
					count++;
				}*/
			}

			/*if (count > 1)
			{
				for (int i = 0; i < CARDMAX; i++)
				{
					m_card[i].Setm_isSelect(false);
				}
			}*/

			if (g_winPoint >= 6)
			{
				g_winPoint = 6;
				m_isInGame = false;
				switch (mapIndex)
				{
				case 0:
					SOUNDMANAGER->stop("bgm_map0");
					break;
				case 1:
					SOUNDMANAGER->stop("bgm_map1");
					break;
				case 2:
					SOUNDMANAGER->stop("bgm_map2");
					break;
				case 3:
					SOUNDMANAGER->stop("bgm_map3");
					break;
				case 4:
					SOUNDMANAGER->stop("bgm_map4");
					break;
				}
				SOUNDMANAGER->play("bgm_win", g_masterVolume * g_bgVolume);

				for (int i = 0; i < STAGEMAX; i++)
				{
					if (i == mapIndex) g_isClear[i] = true;
				}

				ofstream out;
				char str[128];

				//out.open(str, ios::out | ios::trunc);
				out.open("save/save.txt", ios::out | ios::trunc);

				if (out.is_open())
				{
					for (int i = 0; i < STAGEMAX; i++)
					{
						sprintf_s(str, "g_isClear[%d] : %d", i, g_isClear[i]);
						out << str << endl;
						//out << i << " " << g_isClear[i] << endl;
					}
					sprintf_s(str, "Master Volume : %f", g_masterVolume);
					out << str << endl;
					sprintf_s(str, "BackGround Volume : %f", g_bgVolume);
					out << str << endl;
					sprintf_s(str, "Extra Volume : %f", g_extraVolume);
					out << str << endl;

				}
				out.flush();
				out.close();

			}
			if (g_losePoint >= 6)
			{
				g_losePoint = 6;
				m_isInGame = false;
				switch (mapIndex)
				{
				case 0:
					SOUNDMANAGER->stop("bgm_map0");
					break;
				case 1:
					SOUNDMANAGER->stop("bgm_map1");
					break;
				case 2:
					SOUNDMANAGER->stop("bgm_map2");
					break;
				case 3:
					SOUNDMANAGER->stop("bgm_map3");
					break;
				case 4:
					SOUNDMANAGER->stop("bgm_map4");
					break;
				}
				SOUNDMANAGER->play("bgm_lose",g_masterVolume * g_bgVolume);
			}
		}
		else
		{
			if (m_isText)
			{

				if (KEYMANAGER->isKeyDown(VK_RIGHT))
				{
					m_textFrame++;
				}
				if (KEYMANAGER->isKeyDown(VK_LEFT))
				{
					m_textFrame--;
				}
				if (KEYMANAGER->isKeyDown(VK_UP))
				{
					m_textFrame = 50;
				}

				if (m_frameTime >= 0.35f)
				{
					m_frameTime = 0.0f;
					m_frameHero++;
					if (m_frameHero >= static_cast<int>(m_HeroImg[m_whoHero]->GetRefmaxFrameX()))
					{
						m_frameHero = 0;
					}
				}
				else
				{
					m_frameTime += g_ETime;
				}

			}
			else
			{
				if (KEYMANAGER->isKeyDown(VK_SPACE))
				{
					init();
					SOUNDMANAGER->resume("bgm_menu");
					//g_losePoint = 6;
					//m_isInGame = false;

				}
			}


			
		}
		
	}
	


}

void PlayGame::render()
{
	
	if (m_isMapSelect)
	{
		if (ImGui::TreeNode("MapSelect"))
		{

			ImGui::Text("Map");
			ImGui::Columns(3, "mycolumns3", false);  // 3-ways, no border
			ImGui::Separator();
			for (int n = 0; n < 5; n++)
			{
				char label[32];
				sprintf_s(label, "MAP %d", n);
				if (ImGui::Selectable(label))
				{
					mapIndex = n;
				}
				//if (ImGui::Button(label, ImVec2(-FLT_MIN,0.0f))) {}
				ImGui::NextColumn();
			}
			


			ImGui::Columns(1);
			ImGui::Separator();

			ImGui::TreePop();
		}

		static char fileName[64] = ""; ImGui::InputText("DeckName", fileName, 64);

		if (ImGui::Button("Load"))
		{
			wstring tempFile(fileName, &fileName[64]);
			wstring str = L"deck/" + tempFile + L".txt";
			//str = str + L".txt";
			ifstream in;

			in.open(str, ios::in);

			if (in.is_open())
			{
				in >> m_totalCard;
				for (int i = 0; i < CARD_KIND; i++)
				{
					in >> m_deck[i].count >> m_deck[i].name;
				}

			}

			int j = 0;

			for (int i = 0; i < CARD_KIND; i++)
			{
				while (1)
				{
					if (m_deck[i].count <= 0) break;
					if (j == 20) break;

					m_deck[i].count--;

					m_cardName[j] = m_deck[i].name;
					++j;

				}
			}
		}

		if (ImGui::Button("START"))
		{
			m_tile->Load(mapIndex);
			SOUNDMANAGER->pause("bgm_menu");
			if (mapIndex == 0)
			{
				m_deck[0].count = 6;
				m_deck[3].count = 14;
				
				SOUNDMANAGER->play("bgm_map0", g_masterVolume * g_bgVolume);
			}
			switch (mapIndex)
			{
			case 1:
				//맹스크
				m_aiUDelay = 15.0f;
				m_aiMDelay = 20.0f;
				SOUNDMANAGER->play("bgm_map1", g_masterVolume * g_bgVolume);
				break;
			case 2:
				//오버마인드
				m_aiUDelay = 14.0f;
				m_aiMDelay = 19.0f;
				SOUNDMANAGER->play("bgm_map2", g_masterVolume * g_bgVolume);
				break;
			case 3:
				//아르타니스
				m_aiUDelay = 16.0f;
				m_aiMDelay = 22.0f;
				SOUNDMANAGER->play("bgm_map3", g_masterVolume * g_bgVolume);
				break;
			case 4:
				//케리건
				m_aiUDelay = 12.45f;
				m_aiMDelay = 18.6f;
				SOUNDMANAGER->play("bgm_map4", g_masterVolume * g_bgVolume);
				break;
			}
			int j = 0;

			for (int i = 0; i < CARD_KIND; i++)
			{
				while (1)
				{
					if (m_deck[i].count <= 0) break;
					if (j == 20) break;

					m_deck[i].count--;

					m_cardName[j] = m_deck[i].name;
					++j;

				}


			}
			m_isMapSelect = false;
			//m_isInGame = true;
			drawCard();
			drawCard();
			drawCard();
		}

		if (ImGui::Button("Go to Menu"))
			goMenu = true;


		Image* bg = IMGMANAGER->GetImage("bg_mapSelect");
		bg->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		bg->Scale(WINSIZEX, WINSIZEY);
		bg->Render();
	}
	else
	{
		Image* img = IMGMANAGER->GetImage("ui_turn");
		if (m_isInGame)
		{

			m_tile->render();
			img->Render();


			renderText();

			//40,30 SCALE
			img = IMGMANAGER->GetImage("ui_clock");
			img->Position(133, 60);
			//img->SetParent(img->GetRT());
			//img->Rotate2(0.0f, 0.0f, m_angle);
			img->Rotate(0.0f, 0.0f, m_angle);

			img->Render();

			m_unitManager->render();

			for (int i = 0; i < CARDMAX; i++)
			{
				m_card[i].render();
			}

			m_guardImage->Render();

			//점수판 (플레이어꺼부터)
			img = IMGMANAGER->GetImage("ui_vpBoard");
			img->Position(75.0f, WINSIZEY - 50.0f);
			img->GetRefCurrentFrameX() = g_winPoint;
			img->Render();

			//점수판 (적꺼까지)
			img = IMGMANAGER->GetImage("ui_vpBoard");
			img->Position(WINSIZEX - 75.0f, WINSIZEY - 50.0f);
			img->GetRefCurrentFrameX() = g_losePoint;
			img->Render();

		}
		
		else if (!m_isInGame)
		{
			if (m_isText)
			{
				m_tile->render();

				m_HeroImg[m_whoHero]->Position(400.0f, 400.0f);
				m_HeroImg[m_whoHero]->Scale(100.0f, 100.0f);
				m_HeroImg[m_whoHero]->GetRefCurrentFrameX() = m_frameHero;
				m_HeroImg[m_whoHero]->Render();

				heroText();
				
				
			}
			else
			{
				//짐 렌더
				if (g_losePoint == 6)
				{
					img = IMGMANAGER->GetImage("bg_lose");
					img->Render();
					
				}
				//이김 렌더
				else if (g_winPoint == 6)
				{
					img = IMGMANAGER->GetImage("bg_win");
					img->Render();
				
				}
			}
			
		}
	}

}

void PlayGame::turn()
{
	if (m_angle > PI * 2) m_angle -= PI * 2;
	else if (m_angle < 0) m_angle += PI * 2;

	if (m_turn == T_PLAY)
	{
		if (KEYMANAGER->isKeyDown('Q'))
		{
			if (PtInRect(m_guardRc, g_ptMouse))
			{
				guardCard();
			}
		}

		for (int i = 0; i < CARDMAX; i++)
		{
			if (m_card[i].Getm_isUse())
			{
				m_card[i].cardUseType();
			}
		}

		if (m_turnTime >= 5.0f)
		{
			g_actionPoint += m_turnMoney + m_turnMoneyBase;
			m_turn = T_ACT;
			m_turnTime = 0;
			drawCard();
		}
		else
		{
			m_turnTime += g_ETime;
			m_angle -= (PI / 5.0f) * g_ETime;
		}
	}

	if (m_turn == T_ACT)
	{
		m_angle = PI;
		//액트관련된 업데이트
		if (!m_unitManager->Getm_isWorkDoneAct())
		{
			m_unitManager->actUpdate();
		}
		else
		{
			//액트관련 업데이트를 더 해줄것이 없다면
			if (m_turnTime >= 2.0f)
			{
				m_turn = T_KILL;
				m_turnTime = 0;
				m_unitManager->Setm_isWorkDoneAct(false);
			}
			else
			{
				m_turnTime += g_ETime;
			}
		}
	
		
	}
	if (m_turn == T_KILL)
	{
		m_angle = PI - PI / 4;
		//킬 관련된 업데이트
		if (!m_unitManager->Getm_isWorkDoneKill())
		{
			m_unitManager->killUpdate();
		}
		else
		{
			//킬관련 업데이트를 더 해줄것이 없다면
			if (m_turnTime >= 2.0f)
			{
				m_turn = T_MOVE;
				m_turnTime = 0;
				m_unitManager->Setm_isWorkDoneKill(false);
			}
			else
			{
				m_turnTime += g_ETime;
			}
		}
		
	}
	if (m_turn == T_MOVE)
	{
		m_angle = PI - PI / 2;
		//움직임 관련된 업데이트
		if (!m_unitManager->Getm_isWorkDoneMove())
		{
			m_unitManager->moveUpdate();
		}
		//움직임 업데이트를 더 해줄것이 없다면
		else
		{
			if (m_turnTime >= 2.0f)
			{
				m_angle = 0.0f;
				m_turn = T_PLAY;
				m_unitManager->GetRefm_shieldCount()++;
				m_turnTime = 0;
				m_unitManager->Setm_isWorkDoneMove(false);
			}
			else
			{
				m_turnTime += g_ETime;
			}
		}
		
	}


}

void PlayGame::drawCard()
{
	//한장씩 자신이 가진 타입을 다음 카드에게 넘겨줌
	//마지막 카드는 넘겨줄 다음 카드가 없으니 제외
	/*for (int i = CARDMAX - 2; i > 0; i--)
	{
		m_card[i].Getm_nextCard()->Setm_type(m_card[i].Getm_type());
	}*/
	CARD_TYPE temp;

	cardMove();

	


	int n = GetInt(20);
	

	if (m_cardName[n] == "Marine")
	{
		temp = CARD_MARINE;
	}
	else if (m_cardName[n] == "SCV")
	{
		temp = CARD_SCV;
	}
	else if (m_cardName[n] == "Maneuver")
	{
		temp = CARD_MANEUVER;
	}
	else if (m_cardName[n] == "SteamPack")
	{
		temp = CARD_STEAMPACK;
	}
	else if (m_cardName[n] == "Field repair")
	{
		temp = CARD_FIELD_REPAIR;
	}
	else if (m_cardName[n] == "Tank")
	{
		temp = CARD_TANK;
	}
	else if (m_cardName[n] == "Medic")
	{
		temp = CARD_MEDIC;
	}
	else if (m_cardName[n] == "Ghost")
	{
		temp = CARD_GHOST;
	}
	else if (m_cardName[n] == "FireBat")
	{
		temp = CARD_FIREBAT;
	}
	else if (m_cardName[n] == "Siege Mode")
	{
		temp = CARD_SIEGE_MODE;
	}
	else if (m_cardName[n] == "Yamato")
	{
		temp = CARD_YAMATO;
	}
	else if (m_cardName[n] == "Drone")
	{
		temp = CARD_DRONE;
	}
	else if (m_cardName[n] == "Zurgling")
	{
		temp = CARD_ZURGLING;
	}
	else if (m_cardName[n] == "Hydra")
	{
		temp = CARD_HYDRA;
	}
	else if (m_cardName[n] == "Ultra")
	{
		temp = CARD_ULTRA;
	}
	else if (m_cardName[n] == "Lurker")
	{
		temp = CARD_LURKER;
	}
	else if (m_cardName[n] == "Probe")
	{
		temp = CARD_PROVE;
	}
	else if (m_cardName[n] == "Zealot")
	{
		temp = CARD_ZEALOT;
	}
	else if (m_cardName[n] == "Dragon")
	{
		temp = CARD_DRAGON;
	}
	else if (m_cardName[n] == "River")
	{
		temp = CARD_RIVER;
	}
	else if (m_cardName[n] == "Torasque Roar")
	{
		temp = CARD_TORASQUE_ROAR;
	}
	else if (m_cardName[n] == "Sudden Raid")
	{
		temp = CARD_SUDDEN_RAID;
	}
	else if (m_cardName[n] == "Brudling")
	{
		temp = CARD_BRUDLING;
	}
	else if (m_cardName[n] == "Make Him Dragon")
	{
		temp = CARD_MAKE_HIM_DRAGON;
	}
	else if (m_cardName[n] == "MindControl")
	{
		temp = CARD_MIND_CONTROL;
	}
	else if (m_cardName[n] == "Recall")
	{
		temp = CARD_RECALL;
	}
	else
	{
		if (n % 2 == 0) temp = CARD_MARINE;
		else temp = CARD_SCV;
	}

	m_card[0].Setm_type(temp);
	m_card[0].cardType();

	//지금 필요한것 카드이름이 담긴 배열
	//0~19까지 20개
	//랜덤숫자를 받아서 그 숫자에 담긴 이름에 맞춰서
	//0번카드에 타입을 넣어줌

}

void PlayGame::drawCard(CARD_TYPE type)
{
	cardMove();

	m_card[0].Setm_type(type);
	m_card[0].cardType();

}

void PlayGame::guardCard()
{
	if (g_actionPoint >= 1 && m_card[CARDMAX-1].Getm_type() != CARD_NULL)
	{
		g_actionPoint--;

		CARD_TYPE temp = m_card[CARDMAX - 1].Getm_type();
		//CARD_TYPE temp2;

		cardMove();
		/*for (int i = CARDMAX - 1; i > 0; i--)
		{
			if (m_card[i - 1].Getm_type() != CARD_NULL)
			{
				temp2 = m_card[i - 1].Getm_type();
				m_card[i - 1].Setm_type(CARD_NULL);
				m_card[i - 1].cardType();
				m_card[i].Setm_type(temp2);
				m_card[i].cardType();
				m_card[i].Setm_isSelect(m_card[i - 1].Getm_isSelect());
				m_card[i - 1].Setm_isSelect(false);
			}
		}*/

		m_card[0].Setm_type(temp);
		m_card[0].cardType();
	}
	
}

void PlayGame::cardMove()
{
	CARD_TYPE temp;

	for (int i = CARDMAX - 1; i > 0; i--)
	{
		if (m_card[i - 1].Getm_type() == CARD_NULL)
		{
			m_card[i].Setm_isMove(false);
		}
		else
		{
			m_card[i].Setm_isMove(true);
		}
	}

	if (m_card[0].Getm_type() != CARD_NULL)
	{
		m_card[0].Setm_isMove(true);
	}
	

	for (int i = CARDMAX - 1; i > 0; i--)
	{
		if (m_card[i].Getm_isMove() && m_card[i-1].Getm_isMove())
		{
			temp = m_card[i - 1].Getm_type();
			m_card[i - 1].Setm_type(CARD_NULL);
			m_card[i - 1].cardType();
			m_card[i].Setm_type(temp);
			m_card[i].cardType();
			m_card[i].Setm_isSelect(m_card[i - 1].Getm_isSelect());
			m_card[i - 1].Setm_isSelect(false);
		}
		
	}
}

void PlayGame::clickUpdate()
{
	int idxx, idxy;

	//cout << g_mouseState << endl;
	//테란 유닛 랜덤 드로우
	if (KEYMANAGER->isKeyDown('Q'))
	{
		int rdint = GetInt(6);
		CARD_TYPE crdtp;
		switch (rdint)
		{
		case 0:
			crdtp = CARD_MARINE;
			break;
		case 1:
			crdtp = CARD_SCV;
			break;
		case 2:
			crdtp = CARD_FIREBAT;
			break;
		case 3:
			crdtp = CARD_MEDIC;
			break;
		case 4:
			crdtp = CARD_GHOST;
			break;
		case 5:
			crdtp = CARD_TANK;
			break;
		
		}

		drawCard(crdtp);

		
	}
	//저그 유닛 랜덤 드로우
	if (KEYMANAGER->isKeyDown('W'))
	{
		int rdint = GetInt(4);
		CARD_TYPE crdtp;
		switch (rdint)
		{
		case 0:
			crdtp = CARD_DRONE;
			break;
		case 1:
			crdtp = CARD_ZURGLING;
			break;
		case 2:
			crdtp = CARD_HYDRA;
			break;
		case 3:
			crdtp = CARD_ULTRA;
			break;
		}

		drawCard(crdtp);


	}
	//플토 유닛 랜덤 드로우
	if (KEYMANAGER->isKeyDown('E'))
	{
		int rdint = GetInt(4);
		CARD_TYPE crdtp;
		switch (rdint)
		{
		case 0:
			crdtp = CARD_PROVE;
			break;
		case 1:
			crdtp = CARD_ZEALOT;
			break;
		case 2:
			crdtp = CARD_DRAGON;
			break;
		case 3:
			crdtp = CARD_RIVER;
			break;
		}

		drawCard(crdtp);


	}
	//테란 매직 랜덤 드로우
	if (KEYMANAGER->isKeyDown('A'))
	{
		int rdint = GetInt(5);
		CARD_TYPE crdtp;
		switch (rdint)
		{
		case 0:
			crdtp = CARD_MANEUVER;
			break;
		case 1:
			crdtp = CARD_FIELD_REPAIR;
			break;
		case 2:
			crdtp = CARD_STEAMPACK;
			break;
		case 3:
			crdtp = CARD_SIEGE_MODE;
			break;
		case 4:
			crdtp = CARD_YAMATO;
			break;
		}

		drawCard(crdtp);


	}
	//저그 매직 랜덤 드로우
	if (KEYMANAGER->isKeyDown('S'))
	{
		int rdint = GetInt(4);
		CARD_TYPE crdtp;
		switch (rdint)
		{
		case 0:
			crdtp = CARD_SUDDEN_RAID;
			break;
		case 1:
			crdtp = CARD_LURKER;
			break;
		case 2:
			crdtp = CARD_TORASQUE_ROAR;
			break;
		case 3:
			crdtp = CARD_BRUDLING;
			break;
		}

		drawCard(crdtp);


	}
	//플토 매직 랜덤 드로우
	if (KEYMANAGER->isKeyDown('D'))
	{
		int rdint = GetInt(3);
		CARD_TYPE crdtp;
		switch (rdint)
		{
		case 0:
			crdtp = CARD_MAKE_HIM_DRAGON;
			break;
		case 1:
			crdtp = CARD_MIND_CONTROL;
			break;
		case 2:
			crdtp = CARD_RECALL;
			break;
		}

		drawCard(crdtp);


	}

	if (KEYMANAGER->isKeyDown('X'))
	{
		drawCard(CARD_SIEGE_MODE);
	}

	if (KEYMANAGER->isKeyDown('C'))
	{
		g_actionPoint++;
	}

	if (KEYMANAGER->isKeyDown('6'))
	{
		//init();
		g_winPoint = 6;
		m_isInGame = false;
		switch (mapIndex)
		{
		case 0:
			SOUNDMANAGER->stop("bgm_map0");
			break;
		case 1:
			SOUNDMANAGER->stop("bgm_map1");
			break;
		case 2:
			SOUNDMANAGER->stop("bgm_map2");
			break;
		case 3:
			SOUNDMANAGER->stop("bgm_map3");
			break;
		case 4:
			SOUNDMANAGER->stop("bgm_map4");
			break;
		}
	}

	if (KEYMANAGER->isKeyDown('7'))
	{
		//init();
		g_losePoint = 6;
		m_isInGame = false;
		switch (mapIndex)
		{
		case 0:
			SOUNDMANAGER->stop("bgm_map0");
			break;
		case 1:
			SOUNDMANAGER->stop("bgm_map1");
			break;
		case 2:
			SOUNDMANAGER->stop("bgm_map2");
			break;
		case 3:
			SOUNDMANAGER->stop("bgm_map3");
			break;
		case 4:
			SOUNDMANAGER->stop("bgm_map4");
			break;
		}
	}

	if (KEYMANAGER->isKeyDown(VK_LBUTTON))
	{
		
		//카드 클릭
		for (int i = 0; i < CARDMAX; i++)
		{
			if (g_mouseState == M_SELECT)
			{
				if (m_card[i].Getm_isSelect() && PtinTile(idxx,idxy,m_tile->Getm_TileDesc(),g_ptMouse))
				{
					if (!m_card[i].Getm_isClickDouble())
					{
						m_card[i].cardUse(idxx, idxy);
					}
					else
					{
						m_card[i].cardUseDouble(idxx, idxy);
					}
					
					//cout << "카드 사용 들어옴" << endl;
				}
			}

			if (PtInRect(m_card[i].Getm_rc(), g_ptMouse) &&
				m_card[i].Getm_type() != CARD_NULL)
			{
				if (m_card[i].checkAp(static_cast<int>(g_actionPoint)))
				{
					//cout << i << " 번째 카드클릭됨" << endl;
					m_card[i].selectOnOff();
					g_mouseState = M_SELECT;
					break;
				}
			}

		
		}
		
		//내 유닛 클릭해서 움직이는지 아닌지 정해주는거
		//m_unitManager->clickUnitStop();
		


	}

	//우클릭하면 카드선택 다 취소해줌
	if (KEYMANAGER->isKeyDown(VK_RBUTTON))
	{
		for (int i = 0; i < CARDMAX; i++)
		{
			m_card[i].Setm_isSelect(false);
		}
		g_mouseState = M_NORMAL;
	}

	if (KEYMANAGER->isKeyUp(VK_LBUTTON) && g_mouseState == M_NORMAL)
	{
		//내 유닛 클릭해서 움직이는지 아닌지 정해주는거
		m_unitManager->clickUnitStop();
	}

	
}

void PlayGame::renderText()
{
	if (g_actionPoint >= 30.0f) g_actionPoint = 30.0f;

	int one = (int)g_actionPoint;
	 one = one % 10;
	int ten = (int)g_actionPoint;
	 ten = ten % 100 / 10;

	Image* img = IMGMANAGER->GetImage("ui_number");
	img->Scale(40, 30);
	img->GetRefCurrentFrameX() = one;
	img->Position(180.0f, 160.0f);
	img->Render();

	img->GetRefCurrentFrameX() = ten;
	img->Position(140.0f, 160.0f);
	img->Render();




	string strnum = to_string_with_precision(m_turnMoneyBase, 3);
	wstring wstrnum;
	wstrnum.assign(strnum.begin(), strnum.end());
	
	_tstring str = _T("+") + wstrnum + _T(" (base)");
	
	RECT rect = { 100,565,200,585 };
	WRITEMANAGER->RenderText(str, rect, 15, L"궁서체", D3DXCOLOR(0, 0, 0, 1));

	str = _T("ㅡㅡㅡㅡㅡㅡ");
	rect = { 100,575,200,595 };
	WRITEMANAGER->RenderText(str, rect, 15, L"궁서체", D3DXCOLOR(0, 0, 0, 1));


	strnum = to_string_with_precision(m_turnMoney, 3);
	wstrnum;
	wstrnum.assign(strnum.begin(), strnum.end());

	str = _T("+") + wstrnum + _T(" AP/turn");

	rect = { 100,585,200,605 };
	WRITEMANAGER->RenderText(str, rect, 15, L"궁서체", D3DXCOLOR(0, 0, 0, 1));






}

void PlayGame::heroText()
{
	RECT rect = { 500,200,1200,500 };

	Rect* rc = IMGMANAGER->Getrect();

	rc->SetisFill(true);
	rc->Position(850.0f, 350.0f);
	rc->Scale(700.0f, 300.0f);
	rc->Color(1.0f, 1.0f, 1.0f);
	rc->Render();

	_tstring str = _T("");

	//맵에 따라서 대사가 달리지므로
	//맵 종류마다 스위치문으로 들어간뒤
	switch (mapIndex)
	{
	case 0:
		if (m_textFrame < 0) m_textFrame = 0;
		if (m_textFrame > 6)
		{
			m_isText = false;
			m_isInGame = true;
		}
		//현재 대사 프레임에 맞춰서 대사를 바꿔준다.
		switch (m_textFrame)
		{
		case 0:
			m_whoHero = 0;
			str = _T("아 반갑습니다. 사령관님.");
			break;
		case 1:
			m_whoHero = 0;
			str = _T("저희의 전장이 조금 바뀌었습니다.\n그에 관해 잠깐 설명드리겠습니다.");
			break;
		case 2:
			m_whoHero = 0;
			str = _T("가운데 있는 타일에서 대원들이\n전투를 벌이는 전장입니다.");
			break;
		case 3:
			m_whoHero = 0;
			str = _T("하단에 공간에서 카드로 대원들을\n소환할수있습니다.");
			break;
		case 4:
			m_whoHero = 0;
			str = _T("시간이 지나면 대원들은 스스로\n적을 공격하고 이동을 합니다.\n사령관님은 PLAY턴에 대원들을\n지원할 수 있습니다.");
			break;
		case 5:
			m_whoHero = 0;
			str = _T("무사히 대원들을 타일끝까지 이동시킨다면 대원들마다 가진 승리포인트를 얻게됩니다.\n이 승리 포인트를 6개 먼저\n모은쪽이 승리합니다.");
			break;
		case 6:
			m_whoHero = 0;
			str = _T("자세한것은 직접 전장에서 배우시면\n금방 배우실겁니다. 시작하시죠");
			break;
		}
		break;
	case 1:
		if (m_textFrame < 0) m_textFrame = 0;
		if (m_textFrame > 3)
		{
			m_isText = false;
			m_isInGame = true;
		}
		//현재 대사 프레임에 맞춰서 대사를 바꿔준다.
		switch (m_textFrame)
		{
		case 0:
			m_whoHero = 1;
			str = _T("정말 잘 해주었네 제군.\n하지만 아직 끝이 아니라는 걸 명심하게");
			break;
		case 1:
			m_whoHero = 0;
			str = _T("지옥에나 떨어져!");
			break;
		case 2:
			m_whoHero = 1;
			str = _T("넌 돌이킬 수 없는 실수를 하는거다.\n날 배반할 생각은 꿈에도 하지도 마라");
			break;
		case 3:
			m_whoHero = 0;
			str = _T("지옥에나 가 우린 간다.");
			break;
		}
		break;
	case 2:
		if (m_textFrame < 0) m_textFrame = 0;
		if (m_textFrame > 6)
		{
			m_isText = false;
			m_isInGame = true;
		}
		//현재 대사 프레임에 맞춰서 대사를 바꿔준다.
		switch (m_textFrame)
		{
		case 0:
			m_whoHero = 3;
			str = _T("일어나라, 내 딸아.\n일어나라..케리건..");
			break;
		case 1:
			m_whoHero = 0;
			str = _T("오버마인드, 이 나쁜 자식! 그러지 마!");
			break;
		case 2:
			m_whoHero = 2;
			str = _T("당신의 의지에 따라, 아버지,\n저는 당신을 섬깁니다...");
			break;
		case 3:
			m_whoHero = 2;
			str = _T("오버마인드에 저항하는 모든 자들에게\n군단의 분노를 안기겠습니다.");
			break;
		case 4:
			m_whoHero = 0;
			str = _T("맙소사..케리건,\n놈들이 당신에게 무슨 짓을 한 거야?");
			break;
		case 5:
			m_whoHero = 2;
			str = _T("가 짐. 어서");
			break;
		case 6:
			m_whoHero = 0;
			str = _T("조그만 기다려 달링! 금방 구해줄께");
			break;
		}
		break;
	case 3:
		if (m_textFrame < 0) m_textFrame = 0;
		if (m_textFrame > 3)
		{
			m_isText = false;
			m_isInGame = true;
		}
		//현재 대사 프레임에 맞춰서 대사를 바꿔준다.
		switch (m_textFrame)
		{
		case 0:
			m_whoHero = 4;
			str = _T("앤 타로 태사다르\n용감한 레이너여 이성을 찾으시오!\n케리건은 변했소.");
			break;
		case 1:
			m_whoHero = 4;
			str = _T("더 이상 테란이 아닌 추악한 저그입니다.");
			break;
		case 2:
			m_whoHero = 0;
			str = _T("미안 외계인친구\n내게 그녀는 그녀일뿐이야");
			break;
		case 3:
			m_whoHero = 0;
			str = _T("아무도 내게서 그녀를 빼았지못해");
			break;
		}
		break;
	case 4:
		if (m_textFrame < 0) m_textFrame = 0;
		if (m_textFrame > 20)
		{
			m_isText = false;
			m_isInGame = true;
		}
		//현재 대사 프레임에 맞춰서 대사를 바꿔준다.
		switch (m_textFrame)
		{
		case 0:
			m_whoHero = 0;
			str = _T("사라..이제 당신과 나 둘뿐이야");
			break;
		case 1:
			m_whoHero = 2;
			str = _T("지미..");
			break;
		case 2:
			m_whoHero = 2;
			str = _T("미안해...푹");
			break;
		case 3:
			m_whoHero = 0;
			str = _T("커헉..사라..");
			break;
		case 4:
			m_whoHero = 1;
			str = _T("이런 부부싸움중이셨나?\n내가 좀 안 좋은 때 나타난건가?");
			break;
		case 5:
			m_whoHero = 2;
			str = _T("전혀 아니야,\n어디에서 새로운 병력을 긁어모은거지?\n 또 누굴 그렇게 희생시키려고");
			break;
		case 6:
			m_whoHero = 1;
			str = _T("여기저기 부탁을 하고 양해를 좀 구했지.");
			break;
		case 7:
			m_whoHero = 1;
			str = _T("얼마나 많은 자들이\n널 죽이고 싶어하는지 알면\n꽤 놀랄거다.");
			break;
		case 8:
			m_whoHero = 2;
			str = _T("네 새친구들을 실망시켜서 미안하다.\n아크튜러스.");
			break;
		case 9:
			m_whoHero = 2;
			str = _T("네놈과 네놈친구들의 소원은\n이루어지지 않을테니 말이야");
			break;
		case 10:
			m_whoHero = 4;
			str = _T("케리건, 여기는 아르타니스다.\n형제들과 함께 네 손에 죽어간 짐.. \n그리고 모든 프로토스의 죽음을\n복수하러 왔다!");
			break;
		case 11:
			m_whoHero = 4;
			str = _T("우주 주민들에게 저지른 죄악의 대가를\n치러야 할 시간이다!");
			break;
		case 12:
			m_whoHero = 1;
			str = _T("하하하..프로토스도 뛰어들었군!\n다음은 누구일지 맞춰 볼 생각이 있느냐?");
			break;
		case 13:
			m_whoHero = 2;
			str = _T("맞출것도 없지\n듀갈과 UED가 길들인 저그겠지");
			break;
		case 14:
			m_whoHero = 5;
			str = _T("그렇다 케리건 여기는 듀갈 제독이다.\n병력을 포기하고 항복해라.\n항복하면 목숨은 살려주마.");
			break;
		case 15:
			m_whoHero = 2;
			str = _T("오, 너무 힘든 제안이야, 제독.\n잠깐 생각할 시간을 줄 수 있겠어?");
			break;
		case 16:
			m_whoHero = 2;
			str = _T("항복을 하느니 차라리\n남은 네 병력을 모두 학살하고\n네가 고통속에 죽어가는 꼴을 보고 싶은데 그게 어떻겠어?");
			break;
		case 17:
			m_whoHero = 5;
			str = _T("나를 너무 과소평가하는군 꼬마 아가씨");
			break;
		case 18:
			m_whoHero = 2;
			str = _T("그런 것 같지는 않아, 제독.\n이제는.. 내가 사실상\n이 우주의 여왕이거든");
			break;
		case 19:
			m_whoHero = 2;
			str = _T("그리고 너희 보잘것 없는 병사와\n우주선들이 내 앞길을\n가로막고 있을 뿐이라고");
			break;
		case 20:
			m_whoHero = 5;
			str = _T("그렇다면 해 보자고");
			break;
		}
		break;
	}
	

	WRITEMANAGER->RenderText(str, rect, 35, L"궁서체", D3DXCOLOR(0, 0, 0, 1));


}

void PlayGame::AI()
{
	switch (mapIndex)
	{
	case 0:
		break;
	case 1:
		//멩스크 패턴

		if (m_aiUTime >= m_aiUDelay && m_turn == T_PLAY)
		{
			m_aiUTime = 0.0f;
			int y = GetInt(4);
			int unit = GetInt(10);
			if (unit == 0 || unit == 1) unit = 0;
			else if (unit == 2) unit = 1;
			else if (unit == 3 || unit == 4 || unit == 5)unit = 2;
			else if (unit == 6) unit = 3;
			else if (unit == 7 || unit == 8 || unit == 9) unit = 4;
			switch (unit)
			{
			case 0:
				/*for (int i = 0; i < 4; i++)
				{
					if (!m_tile->CheckTileObject(8, i))
					{
						
						break;
					}
				}*/
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_MARINE);
				}
				
				
				break;
			case 1:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_FIREBAT);
				}
				break;
			case 2:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_GHOST);
				}
				break;
			case 3:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_MEDIC);
				}
				break;
			case 4:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_TANKN);
				}
				break;
			}
		}
		else
		{
			m_aiUTime += g_ETime;
		}

		if (m_aiMTime >= m_aiMDelay && m_turn == T_PLAY)
		{
			m_aiMTime = 0.0f;
			int magic = GetInt(10);
			if (magic == 0 || magic == 1) magic = 0;
			else if (magic == 2 || magic == 3) magic = 1;
			else if (magic == 5 || magic == 4)magic = 2;
			else if (magic == 6 || magic == 7) magic = 3;
			else if (magic == 8 || magic == 9) magic = 4;
			switch (magic)
			{
			case 0:
				//시즈모드
				m_unitManager->AISiege();
				//cout << "AI시즈모드" << endl;
				break;
			case 1:
				//이동
				/*m_unitManager->AIManeuver();
				cout << "AI이동" << endl;*/
				m_unitManager->AIYamato();
				break;
			case 2:
				//치료
				m_unitManager->AIFieldRepair();
				//cout << "AI치료" << endl;
				break;
			case 3:
				//스팀팩
				m_unitManager->AISteamPack();
				//cout << "AI스팀팩" << endl;
				break;
			case 4:
				//야마토포
				m_unitManager->AIYamato();
				//cout << "AI야마토" << endl;
				break;
			}
		//시즈모드 2
		//이동 2
		//치료 2
		//스팀팩 2
		//야마토포 2
		}
		else
		{
			m_aiMTime += g_ETime;
		}

		break;
	case 2:
		//오버마인드 패턴
		if (m_aiUTime >= m_aiUDelay && m_turn == T_PLAY)
		{
			m_aiUTime = 0.0f;
			int y = GetInt(4);
			int unit = GetInt(12);
			if (unit == 0 || unit == 1 || unit == 2) unit = 0;
			else if (unit == 3 || unit == 4 || unit == 5 || unit == 6) unit = 1;
			else if (unit == 7 || unit == 8 || unit == 9)unit = 2;
			else if (unit == 10 || unit == 11) unit = 3;
			switch (unit)
			{
			case 0:
				
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_DRONE);
				}


				break;
			case 1:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_ZURGLING);
				}
				break;
			case 2:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_HYDRA);
				}
				break;
			case 3:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_ULTRA);
				}
				break;
			}
		}
		else
		{
			m_aiUTime += g_ETime;
		}

		if (m_aiMTime >= m_aiMDelay && m_turn == T_PLAY)
		{
			m_aiMTime = 0.0f;
			int magic = GetInt(8);
			if (magic == 0 || magic == 1) magic = 0;
			else if (magic == 2 || magic == 3 || magic == 4) magic = 1;
			else if (magic == 5 || magic == 6 || magic == 7)magic = 2;
			switch (magic)
			{
			case 0:
				//시즈모드
				m_unitManager->AIRulker();
				//cout << "AI시즈모드" << endl;
				break;
			case 1:
				//이동
				/*m_unitManager->AIManeuver();
				cout << "AI이동" << endl;*/
				m_unitManager->AITorasque();
				break;
			case 2:
				//치료
				m_unitManager->AIBru();
				//cout << "AI치료" << endl;
				break;
			}
		}
		else
		{
			m_aiMTime += g_ETime;
		}
		break;
	case 3:
		//아르타니스 패턴
		if (m_aiUTime >= m_aiUDelay && m_turn == T_PLAY)
		{
			m_aiUTime = 0.0f;
			int y = GetInt(4);
			int unit = GetInt(10);
			if (unit == 0 || unit == 1) unit = 0;
			else if (unit == 2 || unit == 3 || unit == 4 || unit == 5) unit = 1;
			else if (unit == 6 || unit == 7)unit = 2;
			else if (unit == 8 || unit == 9) unit = 3;
			switch (unit)
			{
			case 0:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_PROBE);
				}


				break;
			case 1:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_ZEALOT);
				}
				break;
			case 2:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_DRAGON);
				}
				break;
			case 3:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_RIVER);
				}
				break;
			}
		}
		else
		{
			m_aiUTime += g_ETime;
		}

		if (m_aiMTime >= m_aiMDelay && m_turn == T_PLAY)
		{
			m_aiMTime = 0.0f;
			int magic = GetInt(8);
			if (magic == 0 || magic == 1) magic = 0;
			else if (magic == 2 || magic == 3 || magic == 4) magic = 1;
			else if (magic == 5)magic = 2;
			else if (magic == 6 || magic == 7) magic = 3;
			switch (magic)
			{
			case 0:
				//시즈모드
				m_unitManager->AIFieldRepair();
				//cout << "AI시즈모드" << endl;
				break;
			case 1:
				//이동
				/*m_unitManager->AIManeuver();
				cout << "AI이동" << endl;*/
				m_unitManager->AIMakeDragon();
				break;
			case 2:
				//치료
				m_unitManager->AIMindControl();
				//cout << "AI치료" << endl;
				break;
			case 3:
				//스팀팩
				m_unitManager->AIRecall();
				//cout << "AI스팀팩" << endl;
				break;
			}
			//시즈모드 2
			//이동 2
			//치료 2
			//스팀팩 2
			//야마토포 2
		}
		else
		{
			m_aiMTime += g_ETime;
		}
		break;
	case 4:
		//케리건 패턴
		if (m_aiUTime >= m_aiUDelay && m_turn == T_PLAY)
		{
			m_aiUTime = 0.0f;
			int y = GetInt(4);
			int unit = GetInt(8);
			if (unit == 0 || unit == 1) unit = 0;
			else if (unit == 2 || unit == 3 || unit == 4) unit = 1;
			else if (unit == 5 || unit == 6 || unit == 7)unit = 2;
			switch (unit)
			{
			case 0:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_ZURGLING);
					m_aiUTime += m_aiUDelay / 2.0f;
				}


				break;
			case 1:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_HYDRA);
				}
				break;
			case 2:
				if (!m_tile->CheckTileObject(8, y))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						8 * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						y * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_ULTRA);
				}
				break;
			}
		}
		else
		{
			m_aiUTime += g_ETime;
		}

		if (m_aiMTime >= m_aiMDelay && m_turn == T_PLAY)
		{
			m_aiMTime = 0.0f;
			int magic = GetInt(15); 
			if (magic == 0 || magic == 1 || magic == 2) magic = 0;
			else if (magic == 3 || magic == 4) magic = 1;
			else if (magic == 5 || magic == 6)magic = 2;
			else if (magic == 7 || magic == 8 || magic == 9) magic = 3;
			else if (magic == 10 || magic == 11) magic = 4;
			else if (magic == 12 || magic == 13 || magic == 14) magic = 5;
			//magic = 3;
			switch (magic)
			{
			case 0:
				//시즈모드
				m_unitManager->AIRulker();
				//cout << "AI시즈모드" << endl;
				break;
			case 1:
				//이동
				/*m_unitManager->AIManeuver();
				cout << "AI이동" << endl;*/
				m_unitManager->AITorasque();
				break;
			case 2:
				//치료
				m_unitManager->AIBru();
				//cout << "AI치료" << endl;
				break;
			case 3:
				//스팀팩
				m_unitManager->AISudden();
				//cout << "AI스팀팩" << endl;
				break;
			case 4:
				//야마토포
				m_unitManager->AIKMindControl();
				//cout << "AI야마토" << endl;
				break;
			case 5:
				m_unitManager->AIBurrow();
				break;
			}
			//시즈모드 2
			//이동 2
			//치료 2
			//스팀팩 2
			//야마토포 2
		}
		else
		{
			m_aiMTime += g_ETime;
		}
		break;
	}

	
}
