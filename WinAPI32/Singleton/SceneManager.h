#pragma once
#include "SingletonBase.h"
//���ӳ�� ���漱��
class GameNode;

class SceneManager : public SingletonBase<SceneManager>
{
private:
	typedef map<string, GameNode*> m_ScenList;
	typedef map<string, GameNode*>::iterator m_ScenListIter;

	GameNode*			currentScene = nullptr;	//���� ��
	m_ScenList			sceneList;	//�� ���


public:
	SceneManager() {};
	~SceneManager() {};

	//�� == ���ӳ�� (���ӳ�带 ��ӹ޴� ���ΰ� ���� �ɼ��� �ִ�)


	//��ü �� ����
	void RealeaseAll();
	//���� �� ȣ��
	void CurrentSceneUpdate();
	void CurrentSceneRender();
	
	//���߰�
	GameNode* AddScene(string name, GameNode* scene);
	//������
	HRESULT ChangeScene(string name);
	HRESULT ChangeScene(string name, LOADING_PAGE what);
	//����� �޾ƿ���
	MAKEGET(GameNode*, currentScene);

};
