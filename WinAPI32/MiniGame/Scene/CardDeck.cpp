#include "stdafx.h"
#include "CardDeck.h"


CardDeck::CardDeck()
{
}


CardDeck::~CardDeck()
{
}

HRESULT CardDeck::init()
{

	m_randBg = GetFromIntTo(0, 9);

	m_card = new ST_Card[CARD_KIND];

	for (int i = 0; i < CARD_KIND; i++)
	{
		m_card[i].name = "";
		m_card[i].count = 0;
		m_card[i].isCollect = false;
	}

	m_card[0].name = "Marine";
	m_card[1].name = "SCV";
	m_card[2].name = "FireBat";
	m_card[3].name = "Ghost";
	m_card[4].name = "Medic";
	//m_card[5].name = "Vulture";
	m_card[6].name = "Tank";

	m_card[0].isCollect = true;
	m_card[1].isCollect = true;
	m_card[2].isCollect = true;
	m_card[3].isCollect = true;
	m_card[4].isCollect = true;
	//m_card[5].isCollect = true;
	m_card[6].isCollect = true;

	m_card[7].name = "Drone";
	m_card[8].name = "Zurgling";
	m_card[9].name = "Hydra";
	m_card[10].name = "Ultra";

	if (g_isClear[2])
	{
		m_card[7].isCollect = true;
		m_card[8].isCollect = true;
		m_card[9].isCollect = true;
		m_card[10].isCollect = true;
	}

	m_card[11].name = "Probe";
	m_card[12].name = "Zealot";
	m_card[13].name = "Dragon";
	m_card[14].name = "River";

	if (g_isClear[3])
	{
		m_card[11].isCollect = true;
		m_card[12].isCollect = true;
		m_card[13].isCollect = true;
		m_card[14].isCollect = true;
	}

	m_card[15].name = "Maneuver";
	m_card[16].name = "Field repair";
	m_card[17].name = "SteamPack";
	m_card[18].name = "Siege Mode";
	//m_card[19].name = "Speed Up";
	//m_card[20].name = "Defensive Matrix";
	m_card[21].name = "Yamato"; 

	m_card[15].isCollect = true;
	m_card[16].isCollect = true;
	m_card[17].isCollect = true;
	m_card[18].isCollect = true;
	//m_card[19].isCollect = true;
	//m_card[20].isCollect = true;
	m_card[21].isCollect = true;


	m_card[22].name = "Torasque Roar";
	m_card[23].name = "Sudden Raid"; 
	m_card[24].name = "Lurker";
	m_card[25].name = "Brudling";

	if (g_isClear[2])
	{
		m_card[22].isCollect = true;
		m_card[23].isCollect = true;
		m_card[24].isCollect = true;
		m_card[25].isCollect = true;
	}


	m_card[26].name = "Make Him Dragon";
	m_card[27].name = "MindControl";
	m_card[28].name = "Recall";

	if (g_isClear[3])
	{
		m_card[26].isCollect = true;
		m_card[27].isCollect = true;
		m_card[28].isCollect = true;
	}



	m_totalCard = 0;

	goMenu = false;
	show_another_window = true;
	return S_OK;
}

void CardDeck::release()
{
	SAFE_DELETE_ARRAY(m_card);
}

void CardDeck::update()
{
	if (goMenu)
	{
		SCENEMANAGER->ChangeScene("Loading", MENU);
	}

	if (KEYMANAGER->isKeyDown(VK_RBUTTON))
	{
		m_isInDeck = m_isInDeck ? false : true;
	}
}

void CardDeck::render()
{
	Image* img;

	string str = "bg_deck" + to_string(m_randBg);
	
	img = IMGMANAGER->GetImage(str);
	img->Render();

	ImGui::Checkbox("SaveLoad", &show_another_window);
	ImGui::Checkbox("inCard", &m_isInDeck);

	if (ImGui::TreeNode("Card"))
	{
		ImGui::Text("Add or Remove Card");
		ImGui::Columns(1, "mycolumns3", false);  // 3-ways, no border
		ImGui::Separator();
		for (int n = 0; n < CARD_KIND; n++)
		{
			if (m_card[n].name == "") continue;
			if (!m_card[n].isCollect) continue;
			char label[64];
			sprintf_s(label, "Card : %s  Count : %d", m_card[n].name.c_str(),m_card[n].count);
			if (ImGui::Selectable(label))
			{
				if (m_isInDeck)
				{
					if (m_card[n].count < 4)
					{
						m_card[n].count++;
						m_totalCard++;
					}
				}
				else
				{
					if (m_card[n].count > 0)
					{
						m_card[n].count--;
						m_totalCard--;
					}
				}
				
				
			}
			//if (ImGui::Button(label, ImVec2(-FLT_MIN,0.0f))) {}
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
		ImGui::Separator();

		ImGui::TreePop();
	}

	if (ImGui::Button("Go to Menu"))
	goMenu = true;

	if (show_another_window)
	{



		ImGui::Begin("Save&Load&ShowDeck", &show_another_window);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		/*ImGui::InputInt("TileMaxX", &m_TileDesc.TileMaxX, 1, 0);
		ImGui::InputInt("TileMaxY", &m_TileDesc.TileMaxY, 1, 0);*/

		if (ImGui::SliderFloat("Master Volume", &g_masterVolume, 0.0f, 1.0f))
		{
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
		if (ImGui::SliderFloat("BackGround Volume", &g_bgVolume, 0.0f, 1.0f))
		{
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
		if (ImGui::SliderFloat("Extra Volume", &g_extraVolume, 0.0f, 1.0f))
		{
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
		
		SOUNDMANAGER->Volume("bgm_menu", g_bgVolume * g_masterVolume);

		static char fileName[64] = ""; ImGui::InputText("fileName", fileName, 64);
		if (ImGui::Button("Save"))
		{
			if (m_totalCard == 20)
			{
				Save(fileName);
			}
			else if (m_totalCard < 20)
			{
				m_isCardDown = true;
			}
			else if (m_totalCard > 20)
			{
				m_isCardDown = true;
			}

		}

		if (ImGui::Button("Load"))
		{
			Load(fileName);
		}

		ImGui::Text("Your Card");
		ImGui::Columns(1, "mycolumns3", false);  // 3-ways, no border
		ImGui::Separator();
		for (int n = 0; n < CARD_KIND; n++)
		{
			char label[64];
			if (m_card[n].count > 0)
			{
				sprintf_s(label, "Card : %s  Count : %d", m_card[n].name.c_str(), m_card[n].count);
				ImGui::Selectable(label);
			}
			
			ImGui::NextColumn();
		}
		ImGui::Columns(1);
		ImGui::Separator();
		char label2[32];
		sprintf_s(label2,"Total Crads : %d", m_totalCard);
		ImGui::Text(label2);

		
		ImGui::End();
	}

	if (m_isCardDown)
	{
		ImGui::Begin("Caution", &m_isCardDown);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		//ImGui::Text("덱에 카드가 20장보다 적어서 저장에 실패했습니다.");
		ImGui::Text("Must Card in deck 20");
		if (ImGui::Button("Close Me"))
			m_isCardDown = false;
		ImGui::End();
	}




}

void CardDeck::Save(char* fileName)
{
	//wstring tempFile(fileName,&fileName[sizeof(fileName)]);
	wstring tempFile(fileName, &fileName[64]);
	//wstring str = L"deck/" + tempFile + L".txt";
	wstring str = L"deck/";
	wstring strEnd = str + tempFile;
	//str = str + L".txt";
	ofstream out;

	//ofstream out;
	char cstr[128];

	//out.open(str, ios::out | ios::trunc);
	out.open(strEnd, ios::out | ios::trunc);

	if (out.is_open())
	{
		out << m_totalCard << endl;
		for (int i = 0; i < CARD_KIND; i++)
		{
			
			if (m_card[i].name == "") continue;
			sprintf_s(cstr, "%d cardCount : %d",i, m_card[i].count);
			out << cstr << endl;
			//out << i << " " << g_isClear[i] << endl;
		}

	}
	out.flush();
	out.close();

	//out.open(str, ios::out | ios::trunc);
	/*out.open(strEnd, ios::out | ios::trunc);

	if (out.is_open())
	{
		out << m_totalCard << endl;
		for (int i = 0; i < CARD_KIND; i++)
		{
			if (m_card[i].name == "") continue;
			out << m_card[i].count << " " << m_card[i].name << endl;
		}
		
	}*/
	//out.flush();
	//out.close();

}

void CardDeck::Load(char * fileName)
{
	//wstring tempFile(fileName, &fileName[sizeof(fileName)]);
	wstring tempFile(fileName, &fileName[64]);
	//wstring str = L"deck/" + tempFile + L".txt";
	wstring str = L"deck/";
	wstring strEnd = str + tempFile;
	//str = str + L".txt";
	//ifstream in;

	char cstr[128];
	char* cstr2;
	char* context;
	ifstream in;
	in.open(strEnd, ios::in);

	if (in.is_open())
	{
		in >> m_totalCard;

		for (int i = 0; i < CARD_KIND; i++)
		{
			//in >> i >> g_isClear[i];
			in.getline(cstr, 128);
			if (m_card[i].name == "") continue;
			cstr2 = strtok_s(cstr, ":", &context);
			m_card[i].count = atoi(context);
		}

	}

	/*in.open(strEnd, ios::in);

	if (in.is_open())
	{
		in >> m_totalCard;
		for (int i = 0; i < CARD_KIND; i++)
		{
			if (m_card[i].name == "") continue;
			in >> m_card[i].count >> m_card[i].name;
		}
		
	}*/

}

