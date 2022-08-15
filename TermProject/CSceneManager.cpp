#include "stdafx.h"
#include "CSceneManager.h"
#include "CScene.h"
#include "CLogo.h"
#include "CStage1.h"
#include "CStage2.h"
#include "CStage3.h"
#include "CStage4.h"
#include "CEnding.h"
#include "CLoad.h"

IMPLEMENT_SINGLETON(CSceneManager)

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
}

HRESULT CSceneManager::SceneChange(SCENE_ID eID, SCENE_ID MyID)
{
	if (eID < MyID)
	{
		iScene = static_cast<int>(MyID);
	}
	m_eCurrScene = eID;

	if (m_ePreScene != m_eCurrScene)
	{
		SafeDelete(m_pScene);

		switch (m_eCurrScene)
		{
		case SCENE_ID::SCENE_LOGO:
			m_pScene = CLogo::Create();
			break;
		case SCENE_ID::SCENE_STAGE1:
			m_pScene = CStage1::Create();
			break;
		case SCENE_ID::SCENE_STAGE2:
			m_pScene = CStage2::Create();
			break;
		case SCENE_ID::SCENE_STAGE3:
			m_pScene = CStage3::Create();
			break;
		case SCENE_ID::SCENE_STAGE4:
			m_pScene = CStage4::Create();
			break;
		case SCENE_ID::SCENE_END:
			m_pScene = CEnding::Create();
			break;
		case SCENE_ID::SCENE_LOAD:
			m_pScene = CLoad::Create();
			break;
		default:
			break;
		}

		if (!m_pScene)
			return E_FAIL;

		m_ePreScene = m_eCurrScene;
	}

	return NOERROR;
}

HRESULT CSceneManager::Change_NextScene()
{
	m_eNextScene = SCENE_ID(static_cast<int>(m_ePreScene) + 1);
	return NOERROR;
}

HRESULT CSceneManager::Change_LastScene()
{
	m_eNextScene = SCENE_ID::SCENE_END;
	return NOERROR;
}

HRESULT CSceneManager::Change_GameOverScene()
{
	m_eNextScene = SCENE_ID::SCENE_GAMEOVER;
	return NOERROR;
}

GLint CSceneManager::Update(const GLfloat fTimeDelta)
{
	return m_pScene->Update(fTimeDelta);
}

GLvoid CSceneManager::Render()
{
	return m_pScene->Render();
}

void CSceneManager::Release()
{
	SafeDelete(m_pScene);
}
