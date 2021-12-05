#pragma once
#include"Manager.h"

class CObj
{
public:
	CObj();
	~CObj();

public:
	virtual HRESULT Initialize();
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

protected:
	CRenderManager* m_pRender = nullptr;
	CKeyManager* m_pKeyMgr = nullptr;
	CGameManager* m_pGameMgr = nullptr;
	CSceneManager* m_pSceneMgr = nullptr;
	CShader* m_pShaderLoader = nullptr;

protected:
	GLvoid Release();
};

