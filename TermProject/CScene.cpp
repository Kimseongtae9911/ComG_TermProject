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
