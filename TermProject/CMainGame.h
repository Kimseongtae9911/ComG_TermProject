#pragma once
#include "Manager.h"

class CMainGame
{
public:
	CMainGame();
	~CMainGame();

public:
	HRESULT Initialize();
	GLint Update(const GLfloat fTimeDelta);
	GLvoid Render();

private:
	HRESULT Initialize_Manager();
	HRESULT Initialize_Shader();

private:
	CRenderManager* m_pRenderMgr = nullptr;
	CKeyManager* m_pKeyMgr = nullptr;
	CGameManager* m_pGameMgr = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CShader* m_pShaderLoader = nullptr;
	CFrameManager* m_pFrameMgr = nullptr;

private:
	GLvoid Release();

public:
	static CMainGame* Create();
};
