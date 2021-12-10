#include "stdafx.h"
#include "CMainGame.h"

#include "CShader.h"
#include "CGameManager.h"
#include "CRenderManager.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include"CFrameManager.h"

CMainGame::CMainGame()
{
}

CMainGame::~CMainGame()
{
}

HRESULT CMainGame::Initialize()
{
	/*if (FAILED(Initialize_Manager()))
		return E_FAIL;*/
	if (FAILED(Initialize_Shader()))
		return E_FAIL;

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);



	CSceneManager::GetInstance()->SceneChange(SCENE_STAGE1);

	return NOERROR;
}

GLint CMainGame::Update(const GLfloat fTimeDelta)
{
	CSceneManager::GetInstance()->Update(fTimeDelta);
	return GLint();
}

GLvoid CMainGame::Render()
{
	CSceneManager::GetInstance()->Render();
	return GLvoid();
}

HRESULT CMainGame::Initialize_Manager()
{

	return NOERROR;
}

HRESULT CMainGame::Initialize_Shader()
{
	if (FAILED(CShader::GetInstance()->Add_Shader("Default", "vertex.glsl", "fragment.glsl")))
		return E_FAIL;
	return NOERROR;
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
}