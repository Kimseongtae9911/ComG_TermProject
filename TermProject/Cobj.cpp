#include "stdafx.h"
#include "CObj.h"

#include "CGameManager.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CSceneManager.h"
#include "CShader.h"
#include "CFrameManager.h"
#include "CSoundManager.h"

CObj::CObj()
{
}

CObj::~CObj()
{
}

HRESULT CObj::Initialize()
{
	m_pGameMgr = CGameManager::GetInstance();
	m_pRender = CRenderManager::GetInstance();
	m_pSceneMgr = CSceneManager::GetInstance();
	m_pKeyMgr = CKeyManager::GetInstance();
	m_pShaderLoader = CShader::GetInstance();
	m_pSoundMgr = CSoundManager::GetInstance();

	return NOERROR;
}

GLint CObj::Update(const GLfloat fTimeDelta)
{
	return GLint();
}

GLvoid CObj::Render()
{
	return GLvoid();
}

GLvoid CObj::Release()
{
	return GLvoid();
}
