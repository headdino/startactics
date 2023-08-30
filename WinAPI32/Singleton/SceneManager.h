#pragma once
#include "SingletonBase.h"
//게임노드 전방선언
class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<string, GameNode*> m_ScenList;
	typedef map<string, GameNode*>::iterator m_ScenListIter;

	GameNode*			currentScene = nullptr;	//현재 씬
	m_ScenList			sceneList;	//씬 목록


public:
	SceneManager() {};
	~SceneManager() {};

	//씬 == 게임노드 (게임노드를 상속받는 전부가 씬이 될수가 있다)


	//전체 씬 삭제
	void RealeaseAll();
	//현재 씬 호출
	void CurrentSceneUpdate();
	void CurrentSceneRender();
	
	//씬추가
	GameNode* AddScene(string name, GameNode* scene);
	//씬변경
	HRESULT ChangeScene(string name);
	HRESULT ChangeScene(string name, LOADING_PAGE what);
	//현재씬 받아오기
	MAKEGET(GameNode*, currentScene);

};
