#include "stdafx.h"
#include "SceneManager.h"
#include "GameNode.h"

void SceneManager::RealeaseAll()
{
	//�ݺ��ڸ� ���Ͽ� ���� ���鼭 �ϳ��� ����
	m_ScenListIter iter = sceneList.begin();
	for (iter; iter != sceneList.end();)
	{
		if (iter->second != nullptr)
		{
			//������� �����ɶ��� ������ ȣ��� ����
			if (iter->second == currentScene) iter->second->release();
			SAFE_DELETE(iter->second);
			iter = sceneList.erase(iter);
		}
		else
		{
			iter++;
		}
	}
	sceneList.clear();
}

void SceneManager::CurrentSceneUpdate()
{
	if (currentScene)currentScene->update();
}

void SceneManager::CurrentSceneRender()
{
	if (currentScene)currentScene->render();
}

GameNode * SceneManager::AddScene(string name, GameNode * scene)
{
	if (!scene) return nullptr;

	sceneList.insert(make_pair(name, scene));

	return scene;
}

HRESULT SceneManager::ChangeScene(string name)
{
	m_ScenListIter iter = sceneList.find(name);

	//��ã��
	if (iter == sceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������̶� ������ E_FAIL
	if(iter->second == currentScene) return E_FAIL;

	//������� ������ �ʰ� ã������ ���� �����Ѵٸ� init ȣ��
	if (SUCCEEDED(iter->second->init()))
	{
		//���� �ٲٱ��� ���� �����Ѵٸ� ������ ȣ��
		if (currentScene) currentScene->release();
		currentScene = iter->second;

		return S_OK;

	}
	//���ӳ�带 ��ӹ޴� �ش���� ���ϰ��� S_OK�� �ƴҰ��
	else
	{
		return E_FAIL;
	}
	return E_FAIL;
}


HRESULT SceneManager::ChangeScene(string name, LOADING_PAGE what)
{
	m_ScenListIter iter = sceneList.find(name);

	//��ã��
	if (iter == sceneList.end()) return E_FAIL;

	//�ٲٷ��� ���� ������̶� ������ E_FAIL
	if (iter->second == currentScene) return E_FAIL;

	//������� ������ �ʰ� ã������ ���� �����Ѵٸ� init ȣ��
	if (SUCCEEDED(iter->second->init()))
	{
		//���� �ٲٱ��� ���� �����Ѵٸ� ������ ȣ��
		if (currentScene) currentScene->release();
		currentScene = iter->second;
		currentScene->LoadingWhat(what);

		return S_OK;

	}
	//���ӳ�带 ��ӹ޴� �ش���� ���ϰ��� S_OK�� �ƴҰ��
	else
	{
		return E_FAIL;
	}
	return E_FAIL;
}
