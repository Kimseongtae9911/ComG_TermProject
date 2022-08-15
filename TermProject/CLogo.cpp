#include "stdafx.h"
#include "CLogo.h"
#include "CRenderManager.h"
#include "CGameManager.h"
#include "CBackImage.h"
#include "CSprite.h"
#include "CSceneManager.h"
#include "CRenderManager.h"
#include "CKeyManager.h"
#include "CSoundManager.h"

CLogo::CLogo()
{
}

CLogo::~CLogo()
{
	Release();
}

HRESULT CLogo::Initialize()
{
	CScene::Initialize();
	//m_pGameMgr->Add_Camera(CCamera::Create(glm::vec3(0.0f, 6.5f, 30.f), glm::vec3(0.f, 6.5f, 0.f), glm::vec3(0.f, 1.f, 0.f)));
	CObj* pObj = nullptr;

	pObj = CBackImage::Create("", "../Resource/UI/Back/background.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_UI, pObj)))
		return E_FAIL;
	pObj = CSprite::Create(glm::vec3(1040.f, 100.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/pressenter.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_UI, pObj)))
		return E_FAIL;
	m_pSoundMgr->Play_BGM(L"Ending.mp3");
	m_pSoundMgr->Set_Volume(0.3f, CSoundManager::BGM);

	return NOERROR;
}

GLint CLogo::Update(const GLfloat fTimeDelta)
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		m_pSceneMgr->SceneChange(SCENE_ID::SCENE_LOAD, SCENE_ID::SCENE_LOGO);
		return 0;
	}
	else if (m_pKeyMgr->KeyDown(KEY_2))
	{
		m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE2, SCENE_ID::SCENE_LOGO);
		return 0;
	}
	else if (m_pKeyMgr->KeyDown(KEY_3))
	{
		m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE3, SCENE_ID::SCENE_LOGO);
		return 0;
	}
	else if (m_pKeyMgr->KeyDown(KEY_4))
	{
		m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE4, SCENE_ID::SCENE_LOGO);
		return 0;
	}
	else if (m_pKeyMgr->KeyDown(KEY_5))
	{
		m_pSceneMgr->SceneChange(SCENE_ID::SCENE_END, SCENE_ID::SCENE_LOGO);
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
