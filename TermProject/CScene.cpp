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
#include "CSoundManager.h"
#include "CPortal.h"


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
	m_pSoundMgr = CSoundManager::GetInstance();
	if (!m_pSoundMgr)
		return E_FAIL;



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

bool CScene::SceneChange(SCENE_ID next, SCENE_ID cur)
{
	if (dynamic_cast<CPortal*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PORTAL).front())->Get_NextStage())
	{
		m_pSceneMgr->SceneChange(next, cur);
		return true;
	}

	return false;
}

bool CScene::PlayerDieScene(SCENE_ID next, SCENE_ID cur)
{
	if (m_pGameMgr->Get_PlayerDie())
	{
		m_pGameMgr->Set_PlayerDie(false);
		m_pSceneMgr->Set_Life(m_pSceneMgr->Get_Life() - 1);
		m_pSceneMgr->SceneChange(next, cur);

		return true;
	}

	return false;
}

bool CScene::DebugSceneChange(SCENE_ID cur)
{
	if (m_pGameMgr->Get_DebugMode())
	{
		if (m_pKeyMgr->KeyDown(KEY_1)) {
			m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE2, cur);
			return true;
		}
		else if (m_pKeyMgr->KeyDown(KEY_2)) {
			m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE2, cur);
			return true;
		}
		else if (m_pKeyMgr->KeyDown(KEY_3)) {
			m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE3, cur);
			return true;
		}
		else if (m_pKeyMgr->KeyDown(KEY_4)) {
			m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE4, cur);
			return true;
		}
		else if (m_pKeyMgr->KeyDown(KEY_5)) {
			m_pSceneMgr->SceneChange(SCENE_ID::SCENE_END, cur);
			return true;
		}
	}

	return false;
}

GLvoid CScene::Release()
{
    return GLvoid();
}
