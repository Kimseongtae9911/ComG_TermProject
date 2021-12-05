#include "CSceneManager.h"
#include "CScene.h"



IMPLEMENT_SINGLETON(CSceneManager)

CSceneManager::CSceneManager()
{
}

CSceneManager::~CSceneManager()
{
}

HRESULT CSceneManager::SceneChange(SCENE_ID eID)
{
	m_eCurrScene = eID;

	if (m_ePreScene != m_eCurrScene)
	{
		SafeDelete(m_pScene);

		switch (m_eCurrScene)
		{
		case SCENE_LOGO:
			//m_pScene = CScene_Logo::Create();
			break;
		case SCENE_STAGE1:
			//m_pScene = CScene_Stage1::Create();
			break;
		case SCENE_STAGE2:
			//m_pScene = CScene_Stage2::Create();
			break;
		case SCENE_END:
			//m_pScene = CScene_End::Create();
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
	m_eNextScene = SCENE_ID(m_ePreScene + 1);
	return NOERROR;
}

HRESULT CSceneManager::Change_LastScene()
{
	m_eNextScene = SCENE_ID(SCENE_END);
	return NOERROR;
}

HRESULT CSceneManager::Change_GameOverScene()
{
	m_eNextScene = SCENE_ID(SCENE_GAMEOVER);
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
