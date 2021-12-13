#include "stdafx.h"
#include "CLogo.h"
#include "CRenderManager.h"
#include "CGameManager.h"
#include "CBackImage.h"
#include "CSprite.h"
#include "CSceneManager.h"
#include "CRenderManager.h"

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

	pObj = CBackImage::Create("", "../Resource/UI/Back/title4.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_UI, pObj)))
		return E_FAIL;
	pObj = CSprite::Create(glm::vec3(640.f, 230.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/pressenter.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_UI, pObj)))
		return E_FAIL;
	m_pAni = new CObj * [16];
	m_pAni[0] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading0.png");
	m_pAni[1] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading1.png");
	m_pAni[2] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading2.png");
	m_pAni[3] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading3.png");
	m_pAni[4] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading4.png");
	m_pAni[5] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading5.png");
	m_pAni[6] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading6.png");
	m_pAni[7] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading7.png");
	m_pAni[8] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading8.png");
	m_pAni[9] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading9.png");
	m_pAni[10] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading10.png");
	m_pAni[11] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading11.png");
	m_pAni[12] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading12.png");
	m_pAni[13] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading13.png");
	m_pAni[14] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading14.png");
	m_pAni[15] = CSprite::Create(glm::vec3(640.f, 50.f, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading15.png");
	return NOERROR;
}

GLint CLogo::Update(const GLfloat fTimeDelta)
{
	if (GetAsyncKeyState(VK_RETURN))
	{
		m_pSceneMgr->SceneChange(SCENE_STAGE1);
		return 0;
	}
	fTime += fTimeDelta;
	if (fTime >= 0.05)
	{
		fTime = 0;
		++iAniCounter;
		if (iAniCounter > 15)
			iAniCounter = 0;
	}
	CRenderManager::GetInstance()->Add_RenderObj(REDER_UI, m_pAni[iAniCounter]);
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
