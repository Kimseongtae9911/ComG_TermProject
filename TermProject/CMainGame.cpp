#include "stdafx.h"
#include "CMainGame.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
}

HRESULT CMainGame::Initialize()
{
	if (FAILED(Initialize_Manager()))
		return E_FAIL;
	if (FAILED(Initialize_Shader()))
		return E_FAIL;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	m_pSceneMgr->SceneChange(SCENE_LOGO);

	return NOERROR;
}

GLint CMainGame::Update(const GLfloat fTimeDelta)
{
	m_pSceneMgr->Update(fTimeDelta);
	return GLint();
}

GLvoid CMainGame::Render()
{
	m_pSceneMgr->Render();
	return GLvoid();
}

HRESULT CMainGame::Initialize_Manager()
{
	m_pGameMgr = CGameManager::GetInstance();
	if (!m_pGameMgr)
		return E_FAIL;
	m_pRenderMgr = CRenderManager::GetInstance();
	if (!m_pRenderMgr)
		return E_FAIL;
	m_pSceneMgr = CSceneManager::GetInstance();
	if (!m_pSceneMgr)
		return E_FAIL;
	m_pKeyMgr = CKeyManager::GetInstance();
	if (!m_pKeyMgr)
		return E_FAIL;
	m_pShaderLoader = CShader::GetInstance();
	if (!m_pShaderLoader)
		return E_FAIL;
	m_pFrameMgr = CFrameManager::GetInstance();
	if (!m_pFrameMgr)
		return E_FAIL;


	return NOERROR;
}

HRESULT CMainGame::Initialize_Shader()
{
	if (FAILED(m_pShaderLoader->Add_Shader("Default", "vertex.glsl", "fragment.glsl")))
		return E_FAIL;
	return E_NOTIMPL;
}

GLvoid CMainGame::Release()
{
	return GLvoid();
}

CMainGame* CMainGame::Create()
{
	CMainGame* pInstance = new CMainGame;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
