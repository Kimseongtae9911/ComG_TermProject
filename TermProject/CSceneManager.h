#pragma once

class CScene;
class CSceneManager
{
	DECLARE_SINGLETON(CSceneManager)

private:
	CSceneManager();
	~CSceneManager();

public:
	SCENE_ID& Get_NextScene() { return m_eNextScene; }
	int& Get_SceneChangeCount() { return iScene; };
	int Get_Life() { return iLife; };
	void Set_Life(int life) { iLife = life; };

public:
	HRESULT SceneChange(SCENE_ID eID, SCENE_ID MyID);
	HRESULT Change_NextScene();
	HRESULT Change_LastScene();
	HRESULT Change_GameOverScene();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	void Release();
	int iScene = 2;
	int iLife = 5;

private:
	SCENE_ID m_ePreScene =  SCENE_ID::SCENE_END;
	SCENE_ID m_eCurrScene = SCENE_ID::SCENE_END;
	SCENE_ID m_eNextScene = SCENE_ID::SCENE_END;
	CScene* m_pScene = nullptr;
};

