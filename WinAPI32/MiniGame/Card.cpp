#include "stdafx.h"
#include "Card.h"
#include "MiniGame/unit/UnitManager.h"
#include "MiniGame/unit/Unit.h"
#include "MiniGame/map/TileMap.h"
#include "MiniGame/Scene/PlayGame.h"


Card::Card()
{
}


Card::~Card()
{
}

HRESULT Card::init()
{
	m_cardImage = IMGMANAGER->GetImage("card_marine");
	m_pos.x = 200.0f;
	m_pos.y = 100.0f;

	return S_OK;
}

HRESULT Card::init(D3DXVECTOR2 pos)
{
	m_cardImage = nullptr;
	m_type = CARD_NULL;
	m_pos = pos;
	m_isSelect = false;
	m_isUse = false;
	m_isMove = false;
	m_isClickDouble = false;
	m_attribute = CLICK_ONE;
	m_unit = nullptr;
	m_isCrush = false;

	return S_OK;
}

void Card::release()
{
}

void Card::update()
{
	

	if (m_isSelect)
	{
		m_pos.y = 150.0f;
	}
	else
	{
		m_pos.y = 100.0f;
	}

	//if (m_isUse)
	//{
	//	cardUseType();
	//}

	m_rc = RectMakeCenter(m_pos.x, m_pos.y, 150.0f, 150.0f);

}

void Card::render()
{
	if (m_cardImage != nullptr)
	{
		m_cardImage->Position(m_pos);
		m_cardImage->Scale(150.0f, 150.0f);
		m_cardImage->Render();

		//��� ���� ǥ��
		Image* img = IMGMANAGER->GetImage("ui_number");
		img->Scale(40, 30);
		img->GetRefCurrentFrameX() = m_ap;
		img->Position(m_pos.x + 40, m_pos.y + 60);
		img->Render();

		if (m_isSelect)
		{
			RECT rect = { (long)(m_pos.x - 70.0f),
			(long)(WINSIZEY - 110.0f),
			(long)(m_pos.x + 75.0f),
			(long)(WINSIZEY) };
			WRITEMANAGER->RenderText(m_inform, rect, 15, L"�ü�ü", D3DXCOLOR(0, 0, 0, 1));
		}
		else
		{
			RECT rect = { (long)(m_pos.x - 70.0f),
			(long)(WINSIZEY - 60.0f),
			(long)(m_pos.x + 75.0f),
			(long)(WINSIZEY) };
			WRITEMANAGER->RenderText(m_inform, rect, 15, L"�ü�ü", D3DXCOLOR(0, 0, 0, 1));
		}
		
	}
	
}

void Card::selectOnOff()
{

	m_isSelect = m_isSelect ? false : true;

}

bool Card::checkAp(int myap)
{
	if (m_ap > myap) return false;

	return true;
}

void Card::cardType()
{
	switch (m_type)
	{
	case CARD_NULL:
		m_cardImage = nullptr;
		m_ap = NULL;
		m_atk = NULL;
		m_hp = NULL;
		m_range = NULL;
		m_inform = L"";
		break;
	case CARD_MARINE:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_marine");
		m_ap = 3;
		m_atk = 1;
		m_hp = 2;
		m_range = 4;
		m_inform = L"You wanna piece of me, boy?";//\nDamage:" + tempFile + L" Range : ";// +m_range;
		break;
	default:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_marine");
		m_ap = 3;
		m_atk = 1;
		m_hp = 2;
		m_range = 4;
		m_inform = L"You wanna piece of me, boy?";
		break;
	case CARD_SCV:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_scv");
		m_ap = 3;
		m_atk = 1;
		m_hp = 4;
		m_range = 1;
		m_inform = L"�̾�~ �߱��̴�!";
		break;
	case CARD_BARRIGATE:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_Barrigate");
		m_ap = 2;
		m_atk = 1;
		m_hp = 4;
		m_range = 1;
		m_inform = L"SCV�� ������ �ٲߴϴ�.";
		break;
	case CARD_TANK:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_Tank");
		m_ap = 5;
		m_atk = 1;
		m_hp = 1;
		m_range = 0;
		m_inform = L"Ready to roll out!";
		break;
	case CARD_MANEUVER:
		m_attribute = CLICK_TWO;
		m_cardImage = IMGMANAGER->GetImage("card_Maneuver");
		m_ap = 1;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"������ �Ʊ������� �ٸ� �������� �����Դϴ�.";
		break;
	case CARD_FIELD_REPAIR:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_Field Repair");
		m_ap = 3;
		m_atk = 0;
		m_hp = 2;
		m_range = 0;
		m_inform = L"�����̵� ü���� 2 ȸ�������ݴϴ�.";
		break;
	case CARD_STEAMPACK:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_StimPack");
		m_ap = 2;
		m_atk = 1;
		m_hp = 1;
		m_range = 0;
		m_inform = L"������� ��Ⱑ �ּ� �Ǿ��";
		break;
	case CARD_MEDIC:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_medic");
		m_ap = 3;
		m_atk = 1;
		m_hp = 4;
		m_range = 1;
		m_inform = L"�̶����̸���~";
		break;
	case CARD_FIREBAT:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_firebat");
		m_ap = 4;
		m_atk = 2;
		m_hp = 3;
		m_range = 2;
		m_inform = L"Ȯ, �� ���� �������?";
		break;
	case CARD_GHOST:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_ghost");
		m_ap = 5;
		m_atk = 1;
		m_hp = 2;
		m_range = 5;
		m_inform = L"������ ���θ��� �����帱���?";
		break;
	case CARD_SIEGE_MODE:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_SiegeMode");
		m_ap = 5;
		m_atk = 1;
		m_hp = 2;
		m_range = 5;
		m_inform = L"�Ϻδ� ������ �Ϻδ� ������";
		break; 
	case CARD_YAMATO:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_Yamato");
		m_ap = 4;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"������ ���ֿ��� 5�������� �ݴϴ�.";
		break;
	case CARD_DRONE:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_drone");
		m_ap = 2;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"����� ī�島��";
		break;
	case CARD_ZURGLING:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_zurgling");
		m_ap = 2;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"�ֿϿ� ���۸��� �ܵ� 2��!";
		break;
	case CARD_ZURGLING_TOKEN:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_zurgling");
		m_ap = 0;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"��ū���� ������� ���۸��Դϴ�.";
		break;
	case CARD_HYDRA:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_hydra");
		m_ap = 3;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"S������ ���ϰ� �ִ� ���������Դϴ�.";
		break;
	case CARD_LURKER:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_lurker");
		m_ap = 3;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"����� ��Ŀ�� ���Ž�ŵ�ϴ�.";
		break;
	case CARD_BURROW:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_burrow");
		m_ap = 2;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"��Ŀ�� ���ο��ŵ�ϴ�.";
		break;
	case CARD_BRUDLING:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_bru");
		m_ap = 6;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"������ Ÿ�Ͽ� �ִ� ������ ���鸵�� ������ ����ϴ�.";
		break;
	case CARD_ULTRA:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_ultra");
		m_ap = 6;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"���� ������ �Ż��Դϴ�.\n�����ο�!";
		break;
	case CARD_SUDDEN_RAID:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_sudden");
		m_ap = 4;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"Ŭ���� �Ʊ� ������ �ִ� YŸ�Ͽ� ���۸��� ��ȯ�մϴ�.";
		break;
	case CARD_TORASQUE_ROAR:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_torasque");
		m_ap = 4;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"��� �� ������ ������ �ѹ������մϴ�.";
		break;
	case CARD_PROVE:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_prove");
		m_ap = 2;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"���� �����佺 ����Դϴ�.";
		break;
	case CARD_ZEALOT:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_zealot");
		m_ap = 3;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"�� Ÿ�� �Ƶ�!";
		break;
	case CARD_DRAGON:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_dragon");
		m_ap = 4;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"������ ����� �⵿�Ѵٸ� ���?";
		break;
	case CARD_RIVER:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_river");
		m_ap = 6;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"�̷�! �ҹ��̳׿�";
		break;
	case CARD_MIND_CONTROL:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_mindcontrol");
		m_ap = 7;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"������ ������ �� �������� ����ϴ�.";
		break;
	case CARD_MAKE_HIM_DRAGON:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_makehimdragon");
		m_ap = 8;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"�����ϼ� ���� �ڵ��� ��� ��⺴���� ������!";
		break;
	case CARD_RECALL:
		m_attribute = CLICK_ONE;
		m_cardImage = IMGMANAGER->GetImage("card_recall");
		m_ap = 1;
		m_atk = 0;
		m_hp = 0;
		m_range = 0;
		m_inform = L"������ �Ʊ������� ��ȯ��Ű�� AP�� �����޽��ϴ�.";
		break;
	case CARD_END:
		break;
	}
}

void Card::cardUse(int idxx, int idxy)
{
	idxX = idxx;
	idxY = idxy;
	if (m_attribute == CLICK_ONE)
	{
		m_isSelect = false;
		m_isUse = true;
		//cout << "Ŭ�� �ѹ�¥�� ����" << endl;
	}
	else
	{
		//cout << "Ŭ�� �ι�¥���ϱ� �ѹ��� Ŭ�������� ���¸������" << endl;
		m_isClickDouble = true;
	}

}

void Card::cardUseDouble(int idxx, int idxy)
{
	//cout << "Ŭ�� �ι�° ���Ծ��" << endl;
	//cout << idxx << " " << idxy << "  �ι��� Ŭ���� ���� �ε�����" << endl;
	idxX2 = idxx;
	idxY2 = idxy;
	m_isSelect = false;
	m_isUse = true;
	m_isClickDouble = false;
}

void Card::cardUseType()
{
	switch (m_type)
	{
	case CARD_NULL:
		
		break;
	case CARD_MARINE:

		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
			m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_MARINE);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	default:
		m_cardImage = IMGMANAGER->GetImage("card_marine");
		m_ap = 3;
		m_atk = 1;
		m_hp = 2;
		m_range = 4;
		m_inform = L"You wanna piece of me, boy?";
		break;
	case CARD_SCV:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_SCV);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
			m_playGame->drawCard(CARD_BARRIGATE);
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_MEDIC:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_MEDIC);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_FIREBAT:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_FIREBAT);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_GHOST:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_GHOST);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_TANK:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_TANKN);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_MANEUVER:
		//cout << "������ �Ծ��" << endl;
		//ó�� Ŭ���� ������ ����Ÿ���� ����
		//��� idxX,idxY�� ������ ������ �ִ� Ÿ��
		//�ι�° Ŭ���� ������ Ÿ���� ����
		//��� idxX2,idxY2�� ������ Ÿ���̴�.
		//�켱 ������ ������ �������ּҸ� �޾ƿ�
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}
		//�� �� �����ϼ� �ִ� Ÿ������ �Ǻ��غ���.
		//�켱 ���ִ� ���̶� y���� ������ �������ʿ������ ��
		if (idxY == idxY2 ||
			//�Ǵ� �� ��ġ�� ���� ������ ����
			m_tile->CheckTileWall(idxX,idxY2,TILE_WALL) ||
			//�Ǵ� ���� ������
			g_actionPoint < m_ap
			//�Ǵ� ������Ʈ�� ������ �ٵ� �װ� �� ���� ���� ������ ���ܰ� ����
			)
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
			//cout << "�����ϼ� �ִ� Ÿ���� �ƴϰų�" << endl;
			//cout << "���� �����" << endl;
			//cout << idxY << " " << idxY2 << " ù��°�� ������ġ �ι�°�� ������ Y��ġ����" << endl;
			return;
		}

		//�׷��� ���� ���� �˻����ش�.
		//������Ʈ�� ������ �� ���� �� ������ �� ����϶��� ������ ����
		//�������� ���� ����
		if (m_tile->CheckTileObject(idxX, idxY2))
		{
			//cout << "�� Ÿ�Ͽ� ������Ʈ�� �ִ��" << endl;
			//�켱 �� ���⿡ �ִ� �� ������ �����͸� �޾ƿ�
			Unit* tempUnit = m_tile->returnInUnit(idxX, idxY2);

			//�� �༮�� ũ�� ������ �ִ°� ������ 
			//�� �����ϸ� ������ ��Ȳ�̴� ����
			if (m_unit->Getm_defenceType() == DFCTYPE_LA && tempUnit->Getm_defenceType() == DFCTYPE_SM)
			{
				//cout << "ū��տ� �������� �ִ�� ��������" << endl;
				m_isCrush = true;
			}
			else
			{
				m_isUse = false;
				g_mouseState = M_NORMAL;
				//cout << "ū�� �ƴϸ� �������� �������� ���߻���" << endl;

				return;
			}
		}
		//�� ���� �Ȱɸ��� ������Ʈ�� ������
		//�̵������ָ� �ȴ�.
		//cout << "�賭�� �����̾����ϴ� �̵��ص� �����ϴ�" << endl;
		m_unit->moveTileY(idxX, idxY2, m_isCrush);
		SOUNDMANAGER->play("maneuver", g_masterVolume * g_extraVolume);
		m_isUse = false;
		m_isSelect = false;
		g_mouseState = M_NORMAL;
		g_actionPoint -= m_ap;
		m_type = CARD_NULL;
		m_isCrush = false;
		cardType();

		//m_playGame->drawCard(CARD_SCV);

		
		break;
	case CARD_FIELD_REPAIR:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->heal(m_hp);
			SOUNDMANAGER->play("repair", g_masterVolume * g_extraVolume);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_STEAMPACK:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if ((m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_MARINE || 
			m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_FIREBAT )&&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->steampack();
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_BARRIGATE:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_SCV &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_tile->RemoveUnit(idxX, idxY);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_BARIGATE);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_SIEGE_MODE:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_TANKN &&
			m_tile->returnInUnit(idxX,idxY)->Getm_host() == 1 &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_tile->RemoveUnit(idxX, idxY);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX ,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_TANKS);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_YAMATO:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->yamato();
			SOUNDMANAGER->play("yamato", g_masterVolume * g_extraVolume);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_DRONE:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_DRONE);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_ZURGLING:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_ZURGLING);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
			m_playGame->drawCard(CARD_ZURGLING_TOKEN);
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		
		break;
	case CARD_ZURGLING_TOKEN:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_ZURGLING);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_HYDRA:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_HYDRA);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_LURKER:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_HYDRA &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_tile->RemoveUnit(idxX, idxY);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_RULKER);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
			m_playGame->drawCard(CARD_BURROW);
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_BURROW:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->returnInUnit(idxX, idxY)->Getm_unitType() == UTYP_RULKER &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_tile->RemoveUnit(idxX, idxY);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_RULKER_BURROW);
			//m_playGame->drawCard(CARD_UNBURROW);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_BRUDLING:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->changeState(UTST_DIE);
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_BRU);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_ULTRA:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_ULTRA);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_SUDDEN_RAID:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			m_tile->returnInUnit(idxX,idxY)->Getm_host() == 1 &&
			g_actionPoint >= m_ap)
		{
			for (int i = 0; i < 4; i++)
			{
				if (!m_tile->CheckTileObject(idxX, i) &&
					!m_tile->CheckTileWall(idxX, i, TILE_WALL))
				{
					m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						idxX * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						i * m_tile->Getm_TileDesc().TileSizeY),
						1, UTYP_ZURGLING); 
					SOUNDMANAGER->play("sudden", g_masterVolume * g_extraVolume);
				}
			}
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_TORASQUE_ROAR:
		if (g_actionPoint >= m_ap)
		{
			m_unitManager->cardTorasque();
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		
		break;
	case CARD_PROVE:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_PROBE);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_ZEALOT:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_ZEALOT);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_DRAGON:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_DRAGON);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_RIVER:
		if (!m_tile->CheckTileObject(0, idxY) && !m_tile->CheckTileWall(0, idxY, TILE_WALL) &&
			g_actionPoint >= m_ap)
		{
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_RIVER);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_MIND_CONTROL:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			m_tile->returnInUnit(idxX,idxY)->Getm_host() != 1 && 
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->mindControl();
			SOUNDMANAGER->play("mindcontrol", g_masterVolume * g_extraVolume);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}

		break;
	case CARD_MAKE_HIM_DRAGON:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			g_actionPoint >= m_ap)
		{
			m_tile->returnInUnit(idxX, idxY)->changeState(UTST_DIE);
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				idxX * m_tile->Getm_TileDesc().TileSizeX,
				m_tile->Getm_TileDesc().ZeroStartPos.y +
				idxY * m_tile->Getm_TileDesc().TileSizeY),
				1, UTYP_DRAGON);
			SOUNDMANAGER->play("makedragon", g_masterVolume * g_extraVolume);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_RECALL:
		m_unit = m_tile->returnInUnit(idxX, idxY);
		//�ٵ� �� Ÿ�Ͽ� ������ ���ٸ�?
		//�������ش�.
		if (m_unit == nullptr)
		{
			//cout << "�ٵ� ������ ��??" << endl;
			m_isUse = false;
			g_mouseState = M_NORMAL;

			return;
		}

		if (m_tile->CheckTileObject(idxX, idxY) &&
			m_tile->returnInUnit(idxX,idxY)->Getm_host() == 1 &&
			g_actionPoint >= m_ap)
		{
			g_actionPoint += m_tile->returnInUnit(idxX, idxY)->Getm_cost();
			m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
			m_tile->RemoveUnit(idxX, idxY);
			SOUNDMANAGER->play("recall", g_masterVolume * g_extraVolume);
			m_isUse = false;
			m_isSelect = false;
			g_mouseState = M_NORMAL;
			g_actionPoint -= m_ap;
			m_type = CARD_NULL;
			cardType();
		}
		else
		{
			m_isUse = false;
			g_mouseState = M_NORMAL;
		}
		break;
	case CARD_END:
		break;
	}


}
