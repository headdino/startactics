#include "stdafx.h"
#include "Loading.h"

//스태틱 멤버는 클래스 밖에서 초기화
int Loading::LoadingNum = 0;

Loading::Loading()
{
}


Loading::~Loading()
{
}

HRESULT Loading::init()
{
	return S_OK;
}

void Loading::release()
{
}

void Loading::update()
{
	//메인게임 이닛 호출이 다 완료된후 시점이라
	//업데이트에 호출
	thread t[10];
	//Image* bg;

	//스레드를 한 포문에 여러개 넣으면 안된다.

	////for (int i = 0; i < 10; i++)
	////{
	////	t[i] = thread(funcLoadMenu,i*10, i*10+10, 4, 9,"bg_exit");
	////	t[i] = thread(funcLoadMenu,i*10, i*10+10, 2, 9,"bg_exiton");
	////	t[i] = thread(funcLoadMenu,i*10, i*10+10, 4, 9,"bg_multi");
	////	t[i] = thread(funcLoadMenu,i*10, i*10+10, 1, 9,"bg_multion");
	////	t[i] = thread(funcLoadMenu,i*10, i*10+10, 8, 4,"bg_editor");
	////	t[i] = thread(funcLoadMenu,i*10, i*10+10, 1, 9,"bg_editoron");
	////	t[i] = thread(funcLoadMenu,i*10, i*10+10, 3, 4,"bg_single");
	////	t[i] = thread(funcLoadMenu,i*10, i*10+10, 5, 9,"bg_singleon");
	////	//t[i] = thread([&]() {ImageExit(); });
	//}


	switch (m_loading)
	{
		//메뉴를 로딩할때
	case MENU:
		for (int i = 0; i < 10; i++)
		{
			t[i] = thread(funcLoadMenu, i * 10, i * 10 + 10, 4, 9, "bg_exit");
		}

		for (int i = 0; i < 10; i++)
		{
			t[i].join();
		}

		for (int i = 0; i < 10; i++)
		{
			t[i] = thread(funcLoadMenu, i * 10, i * 10 + 10, 2, 9, "bg_exiton");
		}

		for (int i = 0; i < 10; i++)
		{
			t[i].join();
		}

		for (int i = 0; i < 10; i++)
		{
			t[i] = thread(funcLoadMenu, i * 10, i * 10 + 10, 4, 9, "bg_multi");
		}

		for (int i = 0; i < 10; i++)
		{
			t[i].join();
		}

		for (int i = 0; i < 10; i++)
		{
			t[i] = thread(funcLoadMenu, i * 10, i * 10 + 10, 1, 9, "bg_multion");
		}

		for (int i = 0; i < 10; i++)
		{
			t[i].join();
		}

		for (int i = 0; i < 10; i++)
		{
			t[i] = thread(funcLoadMenu, i * 10, i * 10 + 10, 8, 4, "bg_editor");
		}

		for (int i = 0; i < 10; i++)
		{
			t[i].join();
		}

		for (int i = 0; i < 10; i++)
		{
			t[i] = thread(funcLoadMenu, i * 10, i * 10 + 10, 1, 9, "bg_editoron");
		}

		for (int i = 0; i < 10; i++)
		{
			t[i].join();
		}

		for (int i = 0; i < 10; i++)
		{
			t[i] = thread(funcLoadMenu, i * 10, i * 10 + 10, 3, 4, "bg_single");
		}

		for (int i = 0; i < 10; i++)
		{
			t[i].join();
		}

		for (int i = 0; i < 10; i++)
		{
			t[i] = thread(funcLoadMenu, i * 10, i * 10 + 10, 5, 9, "bg_singleon");
		}



		//ImageExit();

		for (int i = 0; i < 10; i++)
		{
			t[i].join();
		}

		g_ptCam.x = 0;
		g_ptCam.y = 0;
		//로딩의 업데이트는 한번만 호출되도록 로딩이 끝난후 다른씬으로 전환
		SCENEMANAGER->ChangeScene("Menu");
		//SCENEMANAGER->ChangeScene("TileMap");
		SCENEMANAGER->GetcurrentScene()->update();

		break;
	case PLAY_GAME:

		/*for (int i = 0; i < 10; i++)
		{
			t[i] = thread(funcLoadPlayGame, i * 10, i * 10 + 10, 4, 9, "bg_exit");
		}

		for (int i = 0; i < 10; i++)
		{
			t[i].join();
		}*/
		/*bg = IMGMANAGER->GetImage("bg_mapSelect");
		bg->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
		bg->Scale(WINSIZEX, WINSIZEY);
		bg->Render();*/
		//unitImage();
		heroImage();

		//로딩의 업데이트는 한번만 호출되도록 로딩이 끝난후 다른씬으로 전환
		SCENEMANAGER->ChangeScene("PlayGame");
		SCENEMANAGER->GetcurrentScene()->update();


		break;
	case DECK:



		g_ptCam.x = 0;
		g_ptCam.y = 0;
		SCENEMANAGER->ChangeScene("Deck");  
		SCENEMANAGER->GetcurrentScene()->update();
		break;
	default:
		break;
	}

}

void Loading::render()
{
}

void Loading::unitImage()
{
	IMGMANAGER->AddImage("marineIdle", _T("starcraft/unit/marine/marineIdle.png"), 1, 8, "PS4");
	IMGMANAGER->AddImage("marineMove", _T("starcraft/unit/marine/marineMove.png"), 9, 8, "PS4");
	IMGMANAGER->AddImage("marineDie", _T("starcraft/unit/marine/marineDie.png"), 8, 1, "PS4");
	IMGMANAGER->AddImage("marineAtt", _T("starcraft/unit/marine/marineAtt.png"), 3, 8, "PS4");


	IMGMANAGER->AddImage("greenTarget", _T("starcraft/ui/greenTarget.bmp"), "PS4");

	IMGMANAGER->AddImage("boom", _T("starcraft/unit/mecaDie.png"), 3, 1, "PS4");

	IMGMANAGER->AddImage("scvIdle", _T("starcraft/unit/scv/scvIdle.png"), 1, 2, "PS4");
	IMGMANAGER->AddImage("scvAtt", _T("starcraft/unit/scv/scvAtt.png"), 4, 2, "PS4");

	IMGMANAGER->AddImage("medicIdle", _T("starcraft/unit/medic/medicIdle.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("medicAtt", _T("starcraft/unit/medic/medicAtt.png"), 6, 2, "PS4");
	IMGMANAGER->AddImage("medicDie", _T("starcraft/unit/medic/medicDie.png"), 8, 1, "PS4");
	IMGMANAGER->AddImage("medicMove", _T("starcraft/unit/medic/medicMove.png"), 7, 2, "PS4");

	IMGMANAGER->AddImage("firebatIdle", _T("starcraft/unit/firebat/firebatIdle.png"), 1, 2, "PS4");
	IMGMANAGER->AddImage("firebatAtt", _T("starcraft/unit/firebat/firebatAtt.png"), 4, 2, "PS4");
	IMGMANAGER->AddImage("firebatMove", _T("starcraft/unit/firebat/firebatMove.png"), 8, 2, "PS4");

	IMGMANAGER->AddImage("ghostIdle", _T("starcraft/unit/ghost/ghostIdle.png"), 1, 2, "PS4");
	IMGMANAGER->AddImage("ghostMove", _T("starcraft/unit/ghost/ghostMove.png"), 9, 2, "PS4");
	IMGMANAGER->AddImage("ghostAtt", _T("starcraft/unit/ghost/ghostAtt.png"), 4, 2, "PS4");
	IMGMANAGER->AddImage("ghostDie", _T("starcraft/unit/ghost/ghostDie.png"), 8, 1, "PS4");


	IMGMANAGER->AddImage("tankNMove", _T("starcraft/unit/tank/tankMove.png"), 3, 2, "PS4");
	IMGMANAGER->AddImage("tankNIdle", _T("starcraft/unit/tank/tankIdle.png"), 1, 2, "PS4");
	IMGMANAGER->AddImage("tankNAtt", _T("starcraft/unit/tank/tankAtt.png"), 5, 2, "PS4");
	IMGMANAGER->AddImage("tankTrans", _T("starcraft/unit/tank/tankTrans.png"), 6, 2, "PS4");

	IMGMANAGER->AddImage("tankSIdle", _T("starcraft/unit/tank/tankSIdle.png"), 1, 2, "PS4");
	IMGMANAGER->AddImage("tankSAtt", _T("starcraft/unit/tank/tankSAtt.png"), 5, 2, "PS4");

	IMGMANAGER->AddImage("barrigate", _T("starcraft/unit/barrigate.png"), "PS4");

	IMGMANAGER->AddImage("droneIdle", _T("starcraft/unit/drone/droneIdle.png"), 7, 2, "PS4");
	IMGMANAGER->AddImage("droneMove", _T("starcraft/unit/drone/droneMove.png"), 6, 2, "PS4");
	IMGMANAGER->AddImage("droneAtt", _T("starcraft/unit/drone/droneAtt.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("droneDie", _T("starcraft/unit/drone/droneDie.png"), 8, 1, "PS4");

	IMGMANAGER->AddImage("zurglingIdle", _T("starcraft/unit/zurgling/zurglingIdle.png"), 6, 2, "PS4");
	IMGMANAGER->AddImage("zurglingMove", _T("starcraft/unit/zurgling/zurglingMove.png"), 9, 2, "PS4");
	IMGMANAGER->AddImage("zurglingAtt", _T("starcraft/unit/zurgling/zurglingAtt.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("zurglingDie", _T("starcraft/unit/zurgling/zurglingDie.png"), 7, 1, "PS4");

	//일단 보류
	//프레임수도 고쳐야돰
	IMGMANAGER->AddImage("lurkerIdle", _T("starcraft/unit/lurker/lurkerIdle.png"), 6, 2, "PS4");
	IMGMANAGER->AddImage("lurkerMove", _T("starcraft/unit/lurker/lurkerMove.png"), 5, 2, "PS4");
	//IMGMANAGER->AddImage("lurkerAtt", _T("starcraft/unit/lurker/lurkerAtt.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("lurkerDie", _T("starcraft/unit/lurker/lurkerDie.png"), 9, 1, "PS4");

	IMGMANAGER->AddImage("lurker2Idle", _T("starcraft/unit/lurker/lurker2Idle.png"), 1, 2, "PS4");
	IMGMANAGER->AddImage("lurker2Att", _T("starcraft/unit/lurker/lurker2Att.png"), 6, 2, "PS4");

	IMGMANAGER->AddImage("hydraIdle", _T("starcraft/unit/hydra/hydraIdle.png"), 6, 2, "PS4");
	IMGMANAGER->AddImage("hydraMove", _T("starcraft/unit/hydra/hydraMove.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("hydraAtt", _T("starcraft/unit/hydra/hydraAtt.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("hydraDie", _T("starcraft/unit/hydra/hydraDie.png"), 8, 1, "PS4");

	IMGMANAGER->AddImage("ultraIdle", _T("starcraft/unit/ultra/ultraIdle.png"), 6, 2, "PS4");
	IMGMANAGER->AddImage("ultraMove", _T("starcraft/unit/ultra/ultraMove.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("ultraAtt", _T("starcraft/unit/ultra/ultraAtt.png"), 10, 2, "PS4");
	IMGMANAGER->AddImage("ultraDie", _T("starcraft/unit/ultra/ultraDie.png"), 10, 1, "PS4");

	IMGMANAGER->AddImage("bruIdle", _T("starcraft/unit/bru/bruIdle.png"), 9, 2, "PS4");
	IMGMANAGER->AddImage("bruMove", _T("starcraft/unit/bru/bruMove.png"), 7, 2, "PS4");
	IMGMANAGER->AddImage("bruAtt", _T("starcraft/unit/bru/bruAtt.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("bruDie", _T("starcraft/unit/bru/bruDie.png"), 5, 1, "PS4");

	IMGMANAGER->AddImage("proveIdle", _T("starcraft/unit/prove/proveIdle.png"), 9, 2, "PS4");
	IMGMANAGER->AddImage("proveMove", _T("starcraft/unit/prove/proveMove.png"), 6, 2, "PS4");
	IMGMANAGER->AddImage("proveAtt", _T("starcraft/unit/prove/proveAtt.png"), 8, 2, "PS4");
	//메카 다이로 프로브 다이 대체
	//IMGMANAGER->AddImage("proveDie", _T("starcraft/unit/prove/proveDie.png"), 5, 1, "PS4");

	IMGMANAGER->AddImage("zealotIdle", _T("starcraft/unit/zealot/zealotIdle.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("zealotMove", _T("starcraft/unit/zealot/zealotMove.png"), 6, 2, "PS4");
	IMGMANAGER->AddImage("zealotAtt", _T("starcraft/unit/zealot/zealotAtt.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("zealotDie", _T("starcraft/unit/zealot/zealotDie.png"), 7, 1, "PS4");

	IMGMANAGER->AddImage("dragonIdle", _T("starcraft/unit/dragoon/dragonIdle.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("dragonMove", _T("starcraft/unit/dragoon/dragonMove.png"), 9, 2, "PS4");
	IMGMANAGER->AddImage("dragonAtt", _T("starcraft/unit/dragoon/dragonAtt.png"), 9, 2, "PS4");
	IMGMANAGER->AddImage("dragonDie", _T("starcraft/unit/dragoon/dragonDie.png"), 7, 1, "PS4");

	IMGMANAGER->AddImage("riverIdle", _T("starcraft/unit/river/riverIdle.png"), 8, 2, "PS4");
	IMGMANAGER->AddImage("riverMove", _T("starcraft/unit/river/riverMove.png"), 6, 2, "PS4");
	IMGMANAGER->AddImage("riverAtt", _T("starcraft/unit/river/riverAtt.png"), 6, 2, "PS4");
	//메카 다이로 리버 다이 대체
	//IMGMANAGER->AddImage("riverDie", _T("starcraft/unit/dragoon/dragoonDie.png"), 7, 1, "PS4");

}

void Loading::heroImage()
{
	IMGMANAGER->AddImage("h_jim", _T("hero/hero_jim.png"), 10, 1, "PS");
	IMGMANAGER->AddImage("h_meng", _T("hero/hero_meng.png"), 9, 1, "PS");
	IMGMANAGER->AddImage("h_ke", _T("hero/hero_ke.png"), 10, 1, "PS");
	IMGMANAGER->AddImage("h_over", _T("hero/hero_over.png"), 15, 1, "PS");
	IMGMANAGER->AddImage("h_arta", _T("hero/hero_arta.png"), 10, 1, "PS");
	IMGMANAGER->AddImage("h_du", _T("hero/hero_du.png"), 10, 1, "PS");


}
