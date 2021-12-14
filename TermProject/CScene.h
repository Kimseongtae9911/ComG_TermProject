#pragma once

class CKeyManager;
class CGameManager;
class CShader;
class CSceneManager;
class CFrameManager;
class CRenderManager;
//class CSoundManager;
class CScene
{
public:
	CScene();
	virtual ~CScene();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

protected:
	CKeyManager* m_pKeyMgr = nullptr;
	CGameManager* m_pGameMgr = nullptr;
	CShader* m_pShader = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CFrameManager* m_pFrameMgr = nullptr;
	CRenderManager* m_pRenderMgr = nullptr;
	//CSoundManager* m_pSoundMgr = nullptr;

protected:
	GLvoid Release();
};

