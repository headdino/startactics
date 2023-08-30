#include "stdafx.h"
#include "MainGame.h"
//#include "MiniGame/ImgSort.h"
#include "MiniGame/Scene/Menu.h"
#include "MiniGame/Scene/Loading.h"
#include "MiniGame/Scene/CardDeck.h"
#include "MiniGame/Scene/PlayGame.h"
#include "MiniGame/Scene/TileMapEdit.h"


MainGame::MainGame()
{
}


MainGame::~MainGame()
{
	//싱글톤 해제
	SCENEMANAGER->RealeaseAll();
	SCENEMANAGER->ReleaseSingleton();
	KEYMANAGER->ReleaseSingleton();
	TIMEMANAGER->ReleaseSingleton();
	SOUNDMANAGER->ReleaseSingleton();
	CAMMANAGER->ReleaseSingleton();
	IMGMANAGER->DeleteAll();
	IMGMANAGER->ReleaseSingleton();
	WRITEMANAGER->ReleaseSingleton();

}

HRESULT MainGame::init()
{
	//윈도우가 시작되서 지금까지 흐른 시간을 1/1000초 단위로
	//DWORD형을 리턴하는 함수다
	srand(GetTickCount());
	////////////////////////////////////////////////////

	IMGMANAGER->AddImage("bg_loading", _T("starcraft/background/loading.png"), "PS");
	IMGMANAGER->AddImage("bg_menu", _T("starcraft/background/menu.png"), "PS");
	IMGMANAGER->AddImage("TileSelect", _T("select.bmp"), "PS2");
	IMGMANAGER->AddImage("Tile", _T("starcraft/background/TileMap.bmp"), 1, 5, "PS");
	IMGMANAGER->AddImage("TileList", _T("starcraft/background/TileMap.bmp"), 2, 4, "PS");
	IMGMANAGER->AddImage("TileState", _T("starcraft/background/TileState.png"), 4, 1, "PS");
	IMGMANAGER->AddImage("bg_mapSelect", _T("starcraft/background/mapSelect.png"), "PS");
	IMGMANAGER->AddImage("cusor_normal", _T("starcraft/cusor/cusorNormal.png"), 5, 1, "PS4");
	IMGMANAGER->AddImage("cusor_select_enemy", _T("starcraft/cusor/cusorSelectEnemy.png"), 14, 1, "PS4");
	IMGMANAGER->AddImage("cusor_select_ally", _T("starcraft/cusor/cusorSelectAlly.png"), 14, 1, "PS4");
	IMGMANAGER->AddImage("cusor_select_neutral", _T("starcraft/cusor/cusorSelectNeutral.png"), 14, 1, "PS4");
	IMGMANAGER->AddImage("cusor_drag", _T("starcraft/cusor/cusorDrag.bmp"), "PS4");


	IMGMANAGER->AddImage("uiScreen", _T("starcraft/ui/uiScreen.png"), "PS");
	IMGMANAGER->AddImage("icon_move", _T("starcraft/ui/icon_move.png"), 2, 1, "PS4");
	IMGMANAGER->AddImage("icon_stop", _T("starcraft/ui/icon_stop.png"), 2, 1, "PS4");
	IMGMANAGER->AddImage("icon_attack", _T("starcraft/ui/icon_attack.png"), 2, 1, "PS4");
	IMGMANAGER->AddImage("icon_patrol", _T("starcraft/ui/icon_patrol.png"), 1, 1, "PS4");
	IMGMANAGER->AddImage("icon_hold", _T("starcraft/ui/icon_hold.png"), 1, 1, "PS4");
	IMGMANAGER->AddImage("icon_steam", _T("starcraft/ui/icon_steam.png"), 2, 1, "PS4");

	IMGMANAGER->AddImage("map1", _T("map/map1.png"), "PS");
	IMGMANAGER->GetImage("map1")->Scale(WINSIZEX, WINSIZEY / 2.0f + WINSIZEY / 4.0f);
	IMGMANAGER->GetImage("map1")->Position(WINSIZEX / 2.0f, (WINSIZEY / 2.0f + WINSIZEY / 4.0f) / 2.0f + WINSIZEY / 4.0f);
	IMGMANAGER->AddImage("ui_cardBoard", _T("map/ui_cardboard.png"), "PS");
	IMGMANAGER->GetImage("ui_cardBoard")->Scale(WINSIZEX, WINSIZEY / 2.0f - WINSIZEY / 4.0f);
	IMGMANAGER->GetImage("ui_cardBoard")->Position(WINSIZEX / 2.0f, (WINSIZEY / 2.0f - WINSIZEY / 4.0f) / 2.0f);

	IMGMANAGER->AddImage("ui_number", _T("map/숫자.bmp"), 10, 1, "PS2");

	IMGMANAGER->AddImage("ui_clock", _T("map/ui_clock.png"), "PS2");
	IMGMANAGER->GetImage("ui_clock")->Scale(40, 30);
	IMGMANAGER->GetImage("ui_clock")->Position(133, 60);

	IMGMANAGER->AddImage("ui_turn", _T("map/ui_turn.png"), "PS2");
	IMGMANAGER->GetImage("ui_turn")->Scale(WINSIZEX / 4.0f, WINSIZEY / 2.0f - WINSIZEY / 4.0f + 20.0f);
	IMGMANAGER->GetImage("ui_turn")->Position(WINSIZEX / 8.0f, (WINSIZEY / 2.0f - WINSIZEY / 4.0f) / 2.0f + 20.0f);

	IMGMANAGER->AddImage("map2", _T("map/map2.png"), "PS");
	IMGMANAGER->GetImage("map2")->Scale(WINSIZEX, WINSIZEY / 2.0f + WINSIZEY / 4.0f);
	IMGMANAGER->GetImage("map2")->Position(WINSIZEX / 2.0f, (WINSIZEY / 2.0f + WINSIZEY / 4.0f) / 2.0f + WINSIZEY / 4.0f);

	IMGMANAGER->AddImage("map3", _T("map/map3.png"), "PS");
	IMGMANAGER->GetImage("map3")->Scale(WINSIZEX, WINSIZEY / 2.0f + WINSIZEY / 4.0f);
	IMGMANAGER->GetImage("map3")->Position(WINSIZEX / 2.0f, (WINSIZEY / 2.0f + WINSIZEY / 4.0f) / 2.0f + WINSIZEY / 4.0f);

	IMGMANAGER->AddImage("map4", _T("map/map4.png"), "PS");
	IMGMANAGER->GetImage("map4")->Scale(WINSIZEX, WINSIZEY / 2.0f + WINSIZEY / 4.0f);
	IMGMANAGER->GetImage("map4")->Position(WINSIZEX / 2.0f, (WINSIZEY / 2.0f + WINSIZEY / 4.0f) / 2.0f + WINSIZEY / 4.0f);

	IMGMANAGER->AddImage("map5", _T("map/map5.png"), "PS");
	IMGMANAGER->GetImage("map5")->Scale(WINSIZEX, WINSIZEY / 2.0f + WINSIZEY / 4.0f);
	IMGMANAGER->GetImage("map5")->Position(WINSIZEX / 2.0f, (WINSIZEY / 2.0f + WINSIZEY / 4.0f) / 2.0f + WINSIZEY / 4.0f);

	//덱씬에서 쓰는 배경이미지
	IMGMANAGER->AddImage("bg_deck0", _T("deck/bg0.png"), "PS");
	IMGMANAGER->GetImage("bg_deck0")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_deck0")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

	IMGMANAGER->AddImage("bg_deck1", _T("deck/bg1.png"), "PS");
	IMGMANAGER->GetImage("bg_deck1")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_deck1")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

	IMGMANAGER->AddImage("bg_deck2", _T("deck/bg2.png"), "PS");
	IMGMANAGER->GetImage("bg_deck2")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_deck2")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

	IMGMANAGER->AddImage("bg_deck3", _T("deck/bg3.png"), "PS");
	IMGMANAGER->GetImage("bg_deck3")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_deck3")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

	IMGMANAGER->AddImage("bg_deck4", _T("deck/bg4.png"), "PS");
	IMGMANAGER->GetImage("bg_deck4")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_deck4")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

	IMGMANAGER->AddImage("bg_deck5", _T("deck/bg5.png"), "PS");
	IMGMANAGER->GetImage("bg_deck5")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_deck5")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

	IMGMANAGER->AddImage("bg_deck6", _T("deck/bg6.png"), "PS");
	IMGMANAGER->GetImage("bg_deck6")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_deck6")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

	IMGMANAGER->AddImage("bg_deck7", _T("deck/bg7.png"), "PS");
	IMGMANAGER->GetImage("bg_deck7")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_deck7")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

	IMGMANAGER->AddImage("bg_deck8", _T("deck/bg8.png"), "PS");
	IMGMANAGER->GetImage("bg_deck8")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_deck8")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

	IMGMANAGER->AddImage("bg_deck9", _T("deck/bg9.png"), "PS");
	IMGMANAGER->GetImage("bg_deck9")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_deck9")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);

	IMGMANAGER->AddImage("bg_win", _T("map/bg_win.png"), "PS");
	IMGMANAGER->AddImage("bg_lose", _T("map/bg_lose.png"), "PS");
	IMGMANAGER->GetImage("bg_win")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_win")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);
	IMGMANAGER->GetImage("bg_lose")->Scale(WINSIZEX, WINSIZEY);
	IMGMANAGER->GetImage("bg_lose")->Position(WINSIZEX / 2.0f, WINSIZEY / 2.0f);



	IMGMANAGER->AddImage("ui_move", _T("starcraft/ui/icon_movestop.png"), 4, 1, "PS4");
	IMGMANAGER->GetImage("ui_move")->Scale(20.0f, 20.0f);
	IMGMANAGER->AddImage("ui_guardCard", _T("map/ui_guardCard.png"), "PS");

	IMGMANAGER->AddImage("ui_vp", _T("map/vp.png"), "PS");
	IMGMANAGER->GetImage("ui_vp")->Scale(15.0f, 15.0f);
	IMGMANAGER->AddImage("ui_reload", _T("map/reload.bmp"), "PS2");
	IMGMANAGER->GetImage("ui_reload")->Scale(15.0f, 15.0f);
	IMGMANAGER->AddImage("ui_vpBoard", _T("map/vpBoard.png"), 7, 1, "PS2");
	IMGMANAGER->GetImage("ui_vpBoard")->Scale(150.0f, 100.0f);

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

	//카드들 이미지
	IMGMANAGER->AddImage("card_marine", _T("card/card_marine.png"), "PS");
	IMGMANAGER->AddImage("card_scv", _T("card/card_scv.png"), "PS");
	IMGMANAGER->AddImage("card_Maneuver", _T("card/card_Maneuver.png"), "PS");
	IMGMANAGER->AddImage("card_StimPack", _T("card/card_StimPack.png"), "PS");
	IMGMANAGER->AddImage("card_Field Repair", _T("card/card_Field Repair.png"), "PS");
	IMGMANAGER->AddImage("card_Tank", _T("card/card_Tank.png"), "PS");
	IMGMANAGER->AddImage("card_medic", _T("card/card_medic.png"), "PS");
	IMGMANAGER->AddImage("card_firebat", _T("card/card_firebat.png"), "PS");
	IMGMANAGER->AddImage("card_ghost", _T("card/card_ghost.png"), "PS");
	IMGMANAGER->AddImage("card_SiegeMode", _T("card/card_SiegeMode.png"), "PS");
	IMGMANAGER->AddImage("card_Barrigate", _T("card/card_Barrigate.png"), "PS");
	IMGMANAGER->AddImage("card_Yamato", _T("card/card_Yamato.png"), "PS");

	IMGMANAGER->AddImage("card_drone", _T("card/card_Drone.png"), "PS");
	IMGMANAGER->AddImage("card_zurgling", _T("card/card_Zergling.png"), "PS");
	IMGMANAGER->AddImage("card_hydra", _T("card/card_Hydralisk.png"), "PS");
	//IMGMANAGER->AddImage("card_drone", _T("card/card_.png"), "PS");
	IMGMANAGER->AddImage("card_ultra", _T("card/card_Ultralisk.png"), "PS");

	IMGMANAGER->AddImage("card_prove", _T("card/card_Probe.png"), "PS");
	IMGMANAGER->AddImage("card_zealot", _T("card/card_Zealot.png"), "PS");
	IMGMANAGER->AddImage("card_dragon", _T("card/card_Dragoon.png"), "PS");
	IMGMANAGER->AddImage("card_river", _T("card/card_Reaver.png"), "PS");

	IMGMANAGER->AddImage("card_lurker", _T("card/card_Lurker.png"), "PS");
	IMGMANAGER->AddImage("card_burrow", _T("card/card_Burrow.png"), "PS");
	IMGMANAGER->AddImage("card_bru", _T("card/card_Bru.png"), "PS");
	IMGMANAGER->AddImage("card_makehimdragon", _T("card/card_Makehimdragon.png"), "PS");
	IMGMANAGER->AddImage("card_mindcontrol", _T("card/card_MindControl.png"), "PS");
	IMGMANAGER->AddImage("card_recall", _T("card/card_Recall.png"), "PS");
	IMGMANAGER->AddImage("card_sudden", _T("card/card_Suddenraid.png"), "PS");
	IMGMANAGER->AddImage("card_torasque", _T("card/card_Torasqueroar.png"), "PS");

	//배경음악들 추가
	SOUNDMANAGER->addSound("bgm_win", "sound/bgm/win.wav", false);
	SOUNDMANAGER->addSound("bgm_lose", "sound/bgm/lose.wav", false);

	SOUNDMANAGER->addSound("bgm_menu", "sound/bgm/bgm_menu.wav", true);
	SOUNDMANAGER->addSound("bgm_map0", "sound/bgm/bgm_map0.wav", true);
	SOUNDMANAGER->addSound("bgm_map1", "sound/bgm/bgm_map1.wav", true);
	SOUNDMANAGER->addSound("bgm_map2", "sound/bgm/bgm_map2.wav", true);
	SOUNDMANAGER->addSound("bgm_map3", "sound/bgm/bgm_map3.wav", true);
	SOUNDMANAGER->addSound("bgm_map4", "sound/bgm/bgm_map4.wav", true);

	SOUNDMANAGER->addSound("ef_coin", "sound/effect/Coin.wav", false);
	SOUNDMANAGER->addSound("ef_steampack", "sound/effect/steampack.wav", false);
	SOUNDMANAGER->addSound("ef_build", "sound/effect/build.wav", false);
	SOUNDMANAGER->addSound("ef_reload", "sound/effect/reload.wav", false);
	SOUNDMANAGER->addSound("barrigateDie", "sound/effect/barrigateDie.wav", false);

	SOUNDMANAGER->addSound("kMindcontrol", "sound/effect/kMindcontrol.wav", false);
	SOUNDMANAGER->addSound("makedragon", "sound/effect/makedragon.wav", false);
	SOUNDMANAGER->addSound("maneuver", "sound/effect/maneuver.wav", false);
	SOUNDMANAGER->addSound("mindcontrol", "sound/effect/mindcontrol.wav", false);
	SOUNDMANAGER->addSound("recall", "sound/effect/recall.wav", false);
	SOUNDMANAGER->addSound("repair", "sound/effect/Repair.wav", false);
	SOUNDMANAGER->addSound("sudden", "sound/effect/sudden.wav", false);
	SOUNDMANAGER->addSound("torasque", "sound/effect/torasque.wav", false);
	SOUNDMANAGER->addSound("yamato", "sound/effect/yamato.wav", false);

	SOUNDMANAGER->addSound("marineSet", "sound/unit/marine/marineSet.wav", false);
	SOUNDMANAGER->addSound("marineMove0", "sound/unit/marine/marineMove0.wav", false);
	SOUNDMANAGER->addSound("marineMove1", "sound/unit/marine/marineMove1.wav", false);
	SOUNDMANAGER->addSound("marineMove2", "sound/unit/marine/marineMove2.wav", false);
	SOUNDMANAGER->addSound("marineMove3", "sound/unit/marine/marineMove3.wav", false);
	SOUNDMANAGER->addSound("marineDie", "sound/unit/marine/marineDie.wav", false);
	SOUNDMANAGER->addSound("marineAtt", "sound/unit/marine/marineAtt.wav", false);

	SOUNDMANAGER->addSound("scvSet", "sound/unit/scv/scvSet.wav", false);
	SOUNDMANAGER->addSound("scvMove0", "sound/unit/scv/scvMove0.wav", false);
	SOUNDMANAGER->addSound("scvMove1", "sound/unit/scv/scvMove1.wav", false);
	SOUNDMANAGER->addSound("scvMove2", "sound/unit/scv/scvMove2.wav", false);
	SOUNDMANAGER->addSound("scvMove3", "sound/unit/scv/scvMove3.wav", false);
	SOUNDMANAGER->addSound("scvDie", "sound/unit/scv/scvDie.wav", false);
	SOUNDMANAGER->addSound("scvAtt", "sound/unit/scv/scvAtt.wav", false);

	SOUNDMANAGER->addSound("firebatSet", "sound/unit/firebat/firebatSet.wav", false);
	SOUNDMANAGER->addSound("firebatMove0", "sound/unit/firebat/firebatMove0.wav", false);
	SOUNDMANAGER->addSound("firebatMove1", "sound/unit/firebat/firebatMove1.wav", false);
	SOUNDMANAGER->addSound("firebatMove2", "sound/unit/firebat/firebatMove2.wav", false);
	SOUNDMANAGER->addSound("firebatMove3", "sound/unit/firebat/firebatMove3.wav", false);
	SOUNDMANAGER->addSound("firebatDie", "sound/unit/firebat/firebatDie.wav", false);
	SOUNDMANAGER->addSound("firebatAtt", "sound/unit/firebat/firebatAtt.wav", false);

	SOUNDMANAGER->addSound("medicSet", "sound/unit/medic/medicSet.wav", false);
	SOUNDMANAGER->addSound("medicMove0", "sound/unit/medic/medicMove0.wav", false);
	SOUNDMANAGER->addSound("medicMove1", "sound/unit/medic/medicMove1.wav", false);
	SOUNDMANAGER->addSound("medicMove2", "sound/unit/medic/medicMove2.wav", false);
	SOUNDMANAGER->addSound("medicMove3", "sound/unit/medic/medicMove3.wav", false);
	SOUNDMANAGER->addSound("medicDie", "sound/unit/medic/medicDie.wav", false);
	SOUNDMANAGER->addSound("medicAtt", "sound/unit/medic/medicAtt.wav", false);

	SOUNDMANAGER->addSound("ghostSet", "sound/unit/ghost/ghostSet.wav", false);
	SOUNDMANAGER->addSound("ghostMove0", "sound/unit/ghost/ghostMove0.wav", false);
	SOUNDMANAGER->addSound("ghostMove1", "sound/unit/ghost/ghostMove1.wav", false);
	SOUNDMANAGER->addSound("ghostMove2", "sound/unit/ghost/ghostMove2.wav", false);
	SOUNDMANAGER->addSound("ghostMove3", "sound/unit/ghost/ghostMove3.wav", false);
	SOUNDMANAGER->addSound("ghostDie", "sound/unit/ghost/ghostDie.wav", false);
	SOUNDMANAGER->addSound("ghostAtt", "sound/unit/ghost/ghostAtt.wav", false);

	SOUNDMANAGER->addSound("tankSet", "sound/unit/tank/tankSet.wav", false);
	SOUNDMANAGER->addSound("tankSSet", "sound/unit/tank/tankSSet.wav", false);
	SOUNDMANAGER->addSound("tankMove0", "sound/unit/tank/tankMove0.wav", false);
	SOUNDMANAGER->addSound("tankMove1", "sound/unit/tank/tankMove1.wav", false);
	SOUNDMANAGER->addSound("tankMove2", "sound/unit/tank/tankMove2.wav", false);
	SOUNDMANAGER->addSound("tankMove3", "sound/unit/tank/tankMove3.wav", false);
	SOUNDMANAGER->addSound("tankDie", "sound/unit/tank/tankDie.wav", false);
	SOUNDMANAGER->addSound("tankSAtt", "sound/unit/tank/tankSAtt.wav", false);
	SOUNDMANAGER->addSound("tankNAtt", "sound/unit/tank/tankNAtt.wav", false);

	SOUNDMANAGER->addSound("droneSet", "sound/unit/drone/droneSet.wav", false);
	SOUNDMANAGER->addSound("droneMove0", "sound/unit/drone/droneMove0.wav", false);
	SOUNDMANAGER->addSound("droneMove1", "sound/unit/drone/droneMove1.wav", false);
	SOUNDMANAGER->addSound("droneMove2", "sound/unit/drone/droneMove2.wav", false);
	SOUNDMANAGER->addSound("droneMove3", "sound/unit/drone/droneMove3.wav", false);
	SOUNDMANAGER->addSound("droneDie", "sound/unit/drone/droneDie.wav", false);
	SOUNDMANAGER->addSound("droneAtt", "sound/unit/drone/droneAtt.wav", false);

	SOUNDMANAGER->addSound("zurglingSet", "sound/unit/zurgling/zurglingSet.wav", false);
	SOUNDMANAGER->addSound("zurglingMove0", "sound/unit/zurgling/zurglingMove0.wav", false);
	SOUNDMANAGER->addSound("zurglingMove1", "sound/unit/zurgling/zurglingMove1.wav", false);
	SOUNDMANAGER->addSound("zurglingMove2", "sound/unit/zurgling/zurglingMove2.wav", false);
	SOUNDMANAGER->addSound("zurglingMove3", "sound/unit/zurgling/zurglingMove3.wav", false);
	SOUNDMANAGER->addSound("zurglingDie", "sound/unit/zurgling/zurglingDie.wav", false);
	SOUNDMANAGER->addSound("zurglingAtt", "sound/unit/zurgling/zurglingAtt.wav", false);

	SOUNDMANAGER->addSound("hydraSet", "sound/unit/hydra/hydraSet.wav", false);
	SOUNDMANAGER->addSound("hydraMove0", "sound/unit/hydra/hydraMove0.wav", false);
	SOUNDMANAGER->addSound("hydraMove1", "sound/unit/hydra/hydraMove1.wav", false);
	SOUNDMANAGER->addSound("hydraMove2", "sound/unit/hydra/hydraMove2.wav", false);
	SOUNDMANAGER->addSound("hydraMove3", "sound/unit/hydra/hydraMove3.wav", false);
	SOUNDMANAGER->addSound("hydraDie", "sound/unit/hydra/hydraDie.wav", false);
	SOUNDMANAGER->addSound("hydraAtt", "sound/unit/hydra/hydraAtt.wav", false);

	SOUNDMANAGER->addSound("lurkerSet", "sound/unit/lurker/lurkerSet.wav", false);
	SOUNDMANAGER->addSound("lurkerSet2", "sound/unit/lurker/lurkerSet2.wav", false);
	SOUNDMANAGER->addSound("lurkerMove0", "sound/unit/lurker/lurkerMove0.wav", false);
	SOUNDMANAGER->addSound("lurkerMove1", "sound/unit/lurker/lurkerMove1.wav", false);
	SOUNDMANAGER->addSound("lurkerMove2", "sound/unit/lurker/lurkerMove2.wav", false);
	SOUNDMANAGER->addSound("lurkerMove3", "sound/unit/lurker/lurkerMove3.wav", false);
	SOUNDMANAGER->addSound("lurkerDie", "sound/unit/lurker/lurkerDie.wav", false);
	SOUNDMANAGER->addSound("lurkerAtt", "sound/unit/lurker/lurkerAtt.wav", false);

	SOUNDMANAGER->addSound("ultraSet", "sound/unit/ultra/ultraSet.wav", false);
	SOUNDMANAGER->addSound("ultraMove0", "sound/unit/ultra/ultraMove0.wav", false);
	SOUNDMANAGER->addSound("ultraMove1", "sound/unit/ultra/ultraMove1.wav", false);
	SOUNDMANAGER->addSound("ultraMove2", "sound/unit/ultra/ultraMove2.wav", false);
	SOUNDMANAGER->addSound("ultraMove3", "sound/unit/ultra/ultraMove3.wav", false);
	SOUNDMANAGER->addSound("ultraDie", "sound/unit/ultra/ultraDie.wav", false);
	SOUNDMANAGER->addSound("ultraAtt", "sound/unit/ultra/ultraAtt.wav", false);

	SOUNDMANAGER->addSound("bruSet", "sound/unit/bru/bruSet.wav", false);
	SOUNDMANAGER->addSound("bruMove0", "sound/unit/bru/bruMove0.wav", false);
	SOUNDMANAGER->addSound("bruMove1", "sound/unit/bru/bruMove1.wav", false);
	SOUNDMANAGER->addSound("bruMove2", "sound/unit/bru/bruMove2.wav", false);
	SOUNDMANAGER->addSound("bruMove3", "sound/unit/bru/bruMove3.wav", false);
	SOUNDMANAGER->addSound("bruDie", "sound/unit/bru/bruDie.wav", false);
	SOUNDMANAGER->addSound("bruAtt", "sound/unit/bru/bruAtt.wav", false);

	SOUNDMANAGER->addSound("proveSet", "sound/unit/prove/proveSet.wav", false);
	SOUNDMANAGER->addSound("proveMove0", "sound/unit/prove/proveMove0.wav", false);
	SOUNDMANAGER->addSound("proveMove1", "sound/unit/prove/proveMove1.wav", false);
	SOUNDMANAGER->addSound("proveMove2", "sound/unit/prove/proveMove2.wav", false);
	SOUNDMANAGER->addSound("proveMove3", "sound/unit/prove/proveMove3.wav", false);
	SOUNDMANAGER->addSound("proveDie", "sound/unit/prove/proveDie.wav", false);
	SOUNDMANAGER->addSound("proveAtt", "sound/unit/prove/proveAtt.wav", false);

	SOUNDMANAGER->addSound("zealotSet", "sound/unit/zealot/zealotSet.wav", false);
	SOUNDMANAGER->addSound("zealotMove0", "sound/unit/zealot/zealotMove0.wav", false);
	SOUNDMANAGER->addSound("zealotMove1", "sound/unit/zealot/zealotMove1.wav", false);
	SOUNDMANAGER->addSound("zealotMove2", "sound/unit/zealot/zealotMove2.wav", false);
	SOUNDMANAGER->addSound("zealotMove3", "sound/unit/zealot/zealotMove3.wav", false);
	SOUNDMANAGER->addSound("zealotDie", "sound/unit/zealot/zealotDie.wav", false);
	SOUNDMANAGER->addSound("zealotAtt", "sound/unit/zealot/zealotAtt.wav", false);

	SOUNDMANAGER->addSound("dragonSet", "sound/unit/dragon/dragonSet.wav", false);
	SOUNDMANAGER->addSound("dragonMove0", "sound/unit/dragon/dragonMove0.wav", false);
	SOUNDMANAGER->addSound("dragonMove1", "sound/unit/dragon/dragonMove1.wav", false);
	SOUNDMANAGER->addSound("dragonMove2", "sound/unit/dragon/dragonMove2.wav", false);
	SOUNDMANAGER->addSound("dragonMove3", "sound/unit/dragon/dragonMove3.wav", false);
	SOUNDMANAGER->addSound("dragonDie", "sound/unit/dragon/dragonDie.wav", false);
	SOUNDMANAGER->addSound("dragonAtt", "sound/unit/dragon/dragonAtt.wav", false);

	SOUNDMANAGER->addSound("riverSet", "sound/unit/river/riverSet.wav", false);
	SOUNDMANAGER->addSound("riverMove0", "sound/unit/river/riverMove0.wav", false);
	SOUNDMANAGER->addSound("riverMove1", "sound/unit/river/riverMove1.wav", false);
	SOUNDMANAGER->addSound("riverMove2", "sound/unit/river/riverMove2.wav", false);
	SOUNDMANAGER->addSound("riverMove3", "sound/unit/river/riverMove3.wav", false);
	SOUNDMANAGER->addSound("riverDie", "sound/unit/river/riverDie.wav", false);
	SOUNDMANAGER->addSound("riverAtt", "sound/unit/river/riverAtt.wav", false);

	SCENEMANAGER->AddScene("TileMap", new TileMapEdit);
	SCENEMANAGER->AddScene("Loading", new Loading);
	SCENEMANAGER->AddScene("Menu", new Menu);
	SCENEMANAGER->AddScene("Deck", new CardDeck);
	SCENEMANAGER->AddScene("PlayGame", new PlayGame);
	//SCENEMANAGER->AddScene("ImgSort", new ImgSort);



	char str[128];
	char* str2;
	char* context;
	ifstream in;
	in.open("save/save.txt", ios::in);

	if (in.is_open())
	{
		for (int i = 0; i < STAGEMAX; i++)
		{
			//in >> i >> g_isClear[i];
			in.getline(str, 128);
			str2 = strtok_s(str, ":", &context);
			g_isClear[i] = atoi(context);
		}

		in.getline(str, 128);
		str2 = strtok_s(str, ":", &context);
		g_masterVolume = (float)atof(context);

		in.getline(str, 128);
		str2 = strtok_s(str, ":", &context);
		g_bgVolume = (float)atof(context);

		in.getline(str, 128);
		str2 = strtok_s(str, ":", &context);
		g_extraVolume = (float)atof(context);
	}



	

	SOUNDMANAGER->play("bgm_menu", g_bgVolume * g_masterVolume);
	SCENEMANAGER->ChangeScene("Loading", MENU);

	//현재씬에 접근하려면 GetcurrentScene 호출
	//SCENEMANAGER->GetcurrentScene()->render();


	////////////////////////////////////////////////////
	ImGui::Create(g_hwnd, Device, DeviceContext);
	ImGui::StyleColorsDark();
	return S_OK;
}

void MainGame::release()
{
	////////////////////////////////////////////////////
	
	//씬으로 묶은것은 별도로 SAFE_DELETE 호출 안해도됨

	////////////////////////////////////////////////////
	ImGui::Delete();
}

void MainGame::update()
{
	////////////////////////////////////////////////////
	


	if (KEYMANAGER->isKeyDown('0'))
	{
		g_isDebug = g_isDebug ? false : true;
	}

	//씬별로 하나만 업데이트 한다
	SCENEMANAGER->CurrentSceneUpdate();

	////////////////////////////////////////////////////
	SOUNDMANAGER->Update();
	ImGui::Update();
}

void MainGame::render()
{
	D3DXCOLOR background = D3DXCOLOR(1, 1, 1, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float *)background);
	CAMMANAGER->SetBuffers();
	WRITEMANAGER->GetDc()->BeginDraw();
	TIMEMANAGER->render();
	////////////////////////////////////////////////////
	
	//씬별로 하나만 렌더 한다
	SCENEMANAGER->CurrentSceneRender();


	////////////////////////////////////////////////////
#ifdef _DEBUG
	ImGui::Render();
#endif 
	WRITEMANAGER->GetDc()->EndDraw();
	SwapChain->Present(0, 0);
	
}
