#include "CScene.h"

CScene::CScene()
{
}

CScene::~CScene()
{
}

HRESULT CScene::Initialize()
{
	m_pGameMgr = CGameManager::GetInstance();
	m_pKeyMgr = CKeyManager::GetInstance();
	m_pShader = CShader::GetInstance();
	m_pScenceMgr = CSceneManager::GetInstance();
	m_pFrameMgr = CFrameManager::GetInstance();
	m_pRenderMgr = CRenderManager::GetInstance();

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
