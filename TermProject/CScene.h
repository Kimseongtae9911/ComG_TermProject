#pragma once
#include "CGameManager.h"
#include "CKeyManager.h"
#include "CShader.h"

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

protected:
	GLvoid Release();
};

