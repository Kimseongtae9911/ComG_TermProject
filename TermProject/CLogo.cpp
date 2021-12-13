#include "stdafx.h"
#include "CLogo.h"
#include "CRenderManager.h"
#include "CGameManager.h"
#include "CBackImage.h"
#include "CSceneManager.h"


CLogo::CLogo()
{
}

CLogo::~CLogo()
{
}

HRESULT CLogo::Initialize()
{
	CScene::Initialize();
	//m_pGameMgr->Add_Camera(CCamera::Create(glm::vec3(0.0f, 6.5f, 30.f), glm::vec3(0.f, 6.5f, 0.f), glm::vec3(0.f, 1.f, 0.f)));
	CObj* pObj = nullptr;

	pObj = CBackImage::Create("", "../Resource/UI/Back/title4.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_UI, pObj)))
		return E_FAIL;
	return NOERROR;
}

GLint CLogo::Update(const GLfloat fTimeDelta)
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		m_pSceneMgr->SceneChange(SCENE_STAGE1);
		return 0;
	}
	m_pGameMgr->Update(fTimeDelta);
	return GLint();
}

GLvoid CLogo::Render()
{
	m_pRenderMgr->Render_Object();
	return GLvoid();
}

GLvoid CLogo::Release()
{
	m_pGameMgr->Clear_ObjList();
	return GLvoid();
}

CLogo* CLogo::Create()
{
	CLogo* pInstance = new CLogo();
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
