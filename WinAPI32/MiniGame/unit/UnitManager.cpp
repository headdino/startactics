#include "stdafx.h"
#include "UnitManager.h"
#include "MiniGame/map/TileMap.h"


UnitManager::UnitManager()
{
}


UnitManager::~UnitManager()
{
}

HRESULT UnitManager::init()
{
	m_shieldCount = 0;
	m_UnitArray = new Unit[UNITMAX];
	//for (int i = 0; i < UNITMAX; i++)
	//{
	//	m_Unit[i].init();
	//}

	return S_OK;
}

void UnitManager::release()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		m_UnitArray[i].release();
	}
	SAFE_DELETE_ARRAY(m_UnitArray);
}

void UnitManager::update()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		if (!m_UnitArray[i].Getm_isDead())
		{
			if (m_shieldCount >= 4)
			{
				m_UnitArray[i].naturalShield();
			}
			m_UnitArray[i].update();
		}
		else
			continue;
	}

	if (m_shieldCount >= 4)
		m_shieldCount = 0;

	if (m_isWorkDoneMove)
	{
		for (int i = 0; i < UNITMAX; i++)
		{
			m_UnitArray[i].Setm_isWorkDoneMove(false);
		}
	}

	if (m_isWorkDoneKill)
	{
		for (int i = 0; i < UNITMAX; i++)
		{
			m_UnitArray[i].Setm_isWorkDoneKill(false);
		}
	}

	if (m_isWorkDoneAct)
	{
		for (int i = 0; i < UNITMAX; i++)
		{
			m_UnitArray[i].Setm_isWorkDoneAct(false);
		}
	}

	clickupdate();


}

void UnitManager::render()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		if (!m_UnitArray[i].Getm_isDead())
			m_UnitArray[i].render();
		else
			continue;
	}


}

void UnitManager::actUpdate()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		if (!m_UnitArray[i].Getm_isDead())
		{
			if (!m_UnitArray[i].Getm_isWorkDoneAct())
			{
				m_UnitArray[i].attack();
				break;
			}
		}
		else if (i == UNITMAX - 1)
		{
			m_isWorkDoneAct = true;
		}
	}
}

void UnitManager::killUpdate()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		if (!m_UnitArray[i].Getm_isDead())
		{
			if (!m_UnitArray[i].Getm_isWorkDoneKill())
			{
				m_UnitArray[i].killSelf();
				break;
			}
		}
		else if (i == UNITMAX - 1)
		{
			m_isWorkDoneKill = true;
		}
	}
}

void UnitManager::moveUpdate()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		if (!m_UnitArray[i].Getm_isDead())
		{
			//cout << i << ":" << m_UnitArray[i].Getm_isWorkDoneMove() << "," << m_UnitArray[i].Getm_isGo() << endl;
			if (!m_UnitArray[i].Getm_isWorkDoneMove() && m_UnitArray[i].Getm_isGo())
			{
				m_UnitArray[i].move();
				break;
			}
		}
		else if (i == UNITMAX - 1)
		{
			m_isWorkDoneMove = true;
		}
	}

}

void UnitManager::createUnit(D3DXVECTOR2 pos, int host, UNIT_TYPE type)
{
	Unit* unit = new Unit;

	switch (type)
	{
	case UTYP_MARINE:
		unit = new marine;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("marineSet", g_masterVolume * g_extraVolume);
		//unit->setTile(m_tile);
		break;
	case UTYP_SCV:
		unit = new scv;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("scvSet", g_masterVolume * g_extraVolume);
		//unit->setTile(m_tile);
		break;
	case UTYP_BARIGATE:
		unit = new barrigate;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("ef_build", g_masterVolume * g_extraVolume);
		break;
	case UTYP_TANKN:
		unit = new tankN;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("tankSet", g_masterVolume * g_extraVolume);
		//unit->setTile(m_tile);
		break;
	case UTYP_MEDIC:
		unit = new medic;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("medicSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_FIREBAT:
		unit = new firebat;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("firebatSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_GHOST:
		unit = new ghost;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("ghostSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_TANKS:
		unit = new tankS;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("tankSSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_DRONE:
		unit = new drone;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("droneSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_ZURGLING:
		unit = new zurgling;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("zurglingSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_HYDRA:
		unit = new hydra;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("hydraSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_ULTRA:
		unit = new ultra;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("ultraSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_BRU:
		unit = new bru;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("bruSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_RULKER:
		unit = new lurker;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("lurkerSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_RULKER_BURROW:
		unit = new lurker2;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("lurkerSet2", g_masterVolume * g_extraVolume);
		break;
	case UTYP_PROBE:
		unit = new prove;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("proveSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_ZEALOT:
		unit = new zealot;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("zealotSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_DRAGON:
		unit = new dragon;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("dragonSet", g_masterVolume * g_extraVolume);
		break;
	case UTYP_RIVER:
		unit = new river;
		unit->init(pos, host, type);
		SOUNDMANAGER->play("riverSet", g_masterVolume * g_extraVolume);
		break;
	default:
		break;
	}
	int idxX, idxY;
	if (unit != nullptr)
	{
		unit->setTile(m_tile);
		for (int i = 0; i < UNITMAX; i++)
		{

			if (m_UnitArray[i].Getm_isDead())
			{

				m_UnitArray[i] = (*unit);
				PtinTile(idxX, idxY, m_tile->Getm_TileDesc(), m_UnitArray[i].Getm_pos());
				m_tile->SetUnit(idxX, idxY, &m_UnitArray[i]);
				break;
			}


		}
	}
	else
	{
		return;
	}

}

void UnitManager::clickupdate()
{



	if (KEYMANAGER->isKeyDown('M'))
	{
		createUnit(g_ptMouse, 1, UTYP_MARINE);
	}

	if (KEYMANAGER->isKeyDown('N'))
	{
		createUnit(g_ptMouse, 2, UTYP_MARINE);
	}
	if (KEYMANAGER->isKeyDown('B'))
	{
		createUnit(g_ptMouse, 2, UTYP_TANKN);
	}
	if (KEYMANAGER->isKeyDown('H'))
	{
		createUnit(g_ptMouse, 1, UTYP_TANKS);
	}
	if (KEYMANAGER->isKeyDown('1'))
	{
		createUnit(g_ptMouse, 1, UTYP_RIVER);
	}
	if (KEYMANAGER->isKeyDown('2'))
	{
		createUnit(g_ptMouse, 1, UTYP_RULKER);
	}
	if (KEYMANAGER->isKeyDown('3'))
	{
		createUnit(g_ptMouse, 1, UTYP_RULKER_BURROW);
	}
	if (KEYMANAGER->isKeyDown('4'))
	{
		createUnit(g_ptMouse, 2, UTYP_RULKER_BURROW);
	}



}

void UnitManager::clickUnitStop()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		if (!m_UnitArray[i].Getm_isDead())
		{
			if (PtInRect(m_UnitArray[i].Getm_rc(), g_ptMouse) && m_UnitArray[i].Getm_host() == 1)
			{
				m_UnitArray[i].stopOrMove();
				break;
			}
		}
	}
}

void UnitManager::cardTorasque()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 2)
		{
			m_UnitArray[i].torasque();
		}
		else continue;
	}

}

void UnitManager::AISiege()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 적유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 2)
		{
			//이제 각 마법에 맞는 대상을 찾아준다.
			if (m_UnitArray[i].Getm_unitType() == UTYP_TANKN)
			{
				//m_tile->returnInUnit(idxX, idxY)->Setm_isDead(true);
				//m_tile->RemoveUnit(idxX, idxY);
				//m_unitManager->createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
				//	idxX * m_tile->Getm_TileDesc().TileSizeX,
				//	m_tile->Getm_TileDesc().ZeroStartPos.y +
				//	idxY * m_tile->Getm_TileDesc().TileSizeY),
				//	1, UTYP_TANKS);
				m_UnitArray[i].Setm_isDead(true);
				createUnit(m_UnitArray[i].Getm_pos(), 2, UTYP_TANKS);

				break;
			}
			else continue;
		}
	}

}

void UnitManager::AIManeuver()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 적유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 2)
		{

		}
	}

}

void UnitManager::AIFieldRepair()
{
	int smallHp = INT_MIN;
	int temp = 0;
	int index = 0;
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 적유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 2)
		{
			//최대체력에서 현재체력을 뺀값(피가 얼마나 달았는지)
			//이 값이 크면 그 녀석을 우선으로 치료해준다.
			temp = m_UnitArray[i].Getm_hp();
			if (smallHp < temp && temp != 0)
			{
				smallHp = temp;
				index = i;
			}
		}
	}

	if (smallHp != INT_MIN)
	{
		m_UnitArray[index].heal(2);
		SOUNDMANAGER->play("repair", g_masterVolume * g_extraVolume);
	}


}

void UnitManager::AISteamPack()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 적유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 2)
		{
			//이제 각 마법에 맞는 대상을 찾아준다.
			if (m_UnitArray[i].Getm_unitType() == UTYP_MARINE ||
				m_UnitArray[i].Getm_unitType() == UTYP_FIREBAT)
			{
				m_UnitArray[i].steampack();
				break;
			}
			else continue;
		}
	}
}

void UnitManager::AIYamato()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 플레이어유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 1)
		{
			m_UnitArray[i].yamato();
			break;
		}
	}

}

void UnitManager::AIRulker()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 적유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 2)
		{
			//이제 각 마법에 맞는 대상을 찾아준다.
			if (m_UnitArray[i].Getm_unitType() == UTYP_HYDRA)
			{
				m_UnitArray[i].Setm_isDead(true);
				createUnit(m_UnitArray[i].Getm_pos(), 2, UTYP_RULKER);
				break;
			}
			else continue;
		}
	}
}

void UnitManager::AITorasque()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 플레이어유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 1)
		{
			m_UnitArray[i].torasque();
		}
	}

}

void UnitManager::AIBru()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 플레이어유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 1)
		{
			m_UnitArray[i].changeState(UTST_DIE);
			/*switch (m_UnitArray[i].Getm_unitType())
			{
			case UTYP_MARINE:
				SOUNDMANAGER->play("marineDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_SCV:
				SOUNDMANAGER->play("scvDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_TANKN:

			case UTYP_TANKS:
				SOUNDMANAGER->play("tankDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_VURTURE:
				break;
			case UTYP_MEDIC:
				SOUNDMANAGER->play("medicDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_FIREBAT:
				SOUNDMANAGER->play("firebatDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_GHOST:
				SOUNDMANAGER->play("ghostDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_BARIGATE:
				SOUNDMANAGER->play("barrigateDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_DRONE:
				SOUNDMANAGER->play("droneDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_ZURGLING:
				SOUNDMANAGER->play("zurglingDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_HYDRA:
				SOUNDMANAGER->play("hydraDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_RULKER:
			case UTYP_RULKER_BURROW:
				SOUNDMANAGER->play("lurkerDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_ULTRA:
				SOUNDMANAGER->play("ultraDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_BRU:
				SOUNDMANAGER->play("bruDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_PROBE:
				SOUNDMANAGER->play("proveDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_ZEALOT:
				SOUNDMANAGER->play("zealotDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_DRAGON:
				SOUNDMANAGER->play("dragonDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_RIVER:
				SOUNDMANAGER->play("riverDie", g_masterVolume * g_extraVolume);
				break;
			case UTYP_END:
				break;
			default:
				break;
			}*/
			m_UnitArray[i].Setm_isDead(true);
			createUnit(m_UnitArray[i].Getm_pos(), 2, UTYP_BRU);
			break;
		}
	}

}

void UnitManager::AISudden()
{
	int count = 0;

	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 플레이어유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 2)
		{

			int idxX, idxY;
			PtinTile(idxX, idxY, m_tile->Getm_TileDesc(), m_UnitArray[i].Getm_pos());
			
			

			for (int j = 0; j < 4; j++)
			{
				if (!m_tile->CheckTileObject(idxX, j) &&
					!m_tile->CheckTileWall(idxX, j, TILE_WALL))
				{
					createUnit(D3DXVECTOR2(m_tile->Getm_TileDesc().ZeroStartPos.x +
						idxX * m_tile->Getm_TileDesc().TileSizeX,
						m_tile->Getm_TileDesc().ZeroStartPos.y +
						j * m_tile->Getm_TileDesc().TileSizeY),
						2, UTYP_ZURGLING);
					SOUNDMANAGER->play("sudden", g_masterVolume * g_extraVolume);
				}
				else
				{
					count++;
				}
			}
			if (count == 4)
			{
				count = 0;
				continue;
			}
			break;
			
		}
	}

}

void UnitManager::AIBurrow()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 적유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 2)
		{
			//이제 각 마법에 맞는 대상을 찾아준다.
			if (m_UnitArray[i].Getm_unitType() == UTYP_HYDRA)
			{
				m_UnitArray[i].Setm_isDead(true);
				createUnit(m_UnitArray[i].Getm_pos(), 2, UTYP_RULKER_BURROW);
				break;
			}
			else continue;
		}
	}
}

void UnitManager::AIMakeDragon()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 플레이어유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 1)
		{
			m_UnitArray[i].changeState(UTST_DIE);
			m_UnitArray[i].Setm_isDead(true);
			createUnit(m_UnitArray[i].Getm_pos(), 2, UTYP_DRAGON);
			SOUNDMANAGER->play("makedragon", 0.5f);
			break;
		}
	}
}

void UnitManager::AIMindControl()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 플레이어유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 1)
		{
			m_UnitArray[i].mindControl();
			SOUNDMANAGER->play("mindcontrol", 0.5f);
			break;
		}
	}
}

void UnitManager::AIKMindControl()
{
	for (int i = 0; i < UNITMAX; i++)
	{
		//뒤진게 아니면서 플레이어유닛인 유닛들을 찾아라
		if (!m_UnitArray[i].Getm_isDead() && m_UnitArray[i].Getm_host() == 1)
		{
			m_UnitArray[i].mindControl();
			SOUNDMANAGER->play("kMindcontrol", 0.5f);
			break;
		}
	}
}

void UnitManager::AIRecall()
{
}
