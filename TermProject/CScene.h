#pragma once

class CKeyManager;
class CGameManager;
class CShader;
class CSceneManager;
class CFrameManager;
class CRenderManager;
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
	CSceneManager* m_pScenceMgr = nullptr;
	CFrameManager* m_pFrameMgr = nullptr;
	CRenderManager* m_pRenderMgr = nullptr;

protected:
	GLvoid Release();
};

