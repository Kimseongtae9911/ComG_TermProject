#include "stdafx.h"
#include "CShader.h"
#include "Manager.h"
#include "CScene.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"
#include "CSceneManager.h"
#include "CFrameManager.h"
//#include "CSoundManager.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

HRESULT CScene::Initialize()
{
	m_pGameMgr = CGameManager::GetInstance();
	if (!m_pGameMgr) 
		return E_FAIL;
	m_pKeyMgr = CKeyManager::GetInstance();
	if (!m_pKeyMgr) 
		return E_FAIL;
	m_pShader = CShader::GetInstance();
	if (!m_pShader) 
		return E_FAIL;
	m_pSceneMgr = CSceneManager::GetInstance();
	if (!m_pSceneMgr) 
		return E_FAIL;
	m_pFrameMgr = CFrameManager::GetInstance();
	if (!m_pFrameMgr) 
		return E_FAIL;
	m_pRenderMgr = CRenderManager::GetInstance();
	if (!m_pRenderMgr) 
		return E_FAIL;
	//m_pSoundMgr = CSoundManager::GetInstance();
	//if (!m_pSoundMgr)
	//	return E_FAIL;

	return NOERROR;
}

GLint CScene::Update(const GLfloat fTimeDelta)
{
    return GLint();
}

GLvoid CScene::Render()
{
    return GLvoid();
}

GLvoid CScene::Release()
{
    return GLvoid();
}
