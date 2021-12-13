#include "stdafx.h"
#include "CLoad.h"
#include "CSprite.h"
#include "CBackImage.h"
#include "CGameManager.h"
#include "CSceneManager.h"
#include "CRenderManager.h"

CLoad::CLoad()
{
}

CLoad::~CLoad()
{
	//Release();
	//SafeDelete(m_pAni);
}

HRESULT CLoad::Initialize()
{
	CScene::Initialize();
	CObj* pObj = CBackImage::Create("", "../Resource/UI/Back/backload.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_UI, pObj)))
		return E_FAIL;
	m_pAni = new CObj * [16];
	float x = 1200.f;
	float y = 50.f;
	m_pAni[0] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading0.png");
	m_pAni[1] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading1.png");
	m_pAni[2] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading2.png");
	m_pAni[3] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading3.png");
	m_pAni[4] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading4.png");
	m_pAni[5] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading5.png");
	m_pAni[6] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading6.png");
	m_pAni[7] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading7.png");
	m_pAni[8] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading8.png");
	m_pAni[9] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading9.png");
	m_pAni[10] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading10.png");
	m_pAni[11] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading11.png");
	m_pAni[12] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading12.png");
	m_pAni[13] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading13.png");
	m_pAni[14] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading14.png");
	m_pAni[15] = CSprite::Create(glm::vec3(x, y, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/loading15.png");
	return NOERROR;
}

GLint CLoad::Update(const GLfloat fTimeDelta)
{
	fTime += fTimeDelta;
	fNextScene += fTimeDelta;
	if (fTime >= 0.05)
	{
		fTime = 0;
		++iAniCounter;
		if (iAniCounter > 15)
			iAniCounter = 0;
	}
	if (fNextScene >= 2.5)
	{
		fNextScene = 0;
		m_pSceneMgr->SceneChange(SCENE_STAGE1);
		return 0;
	}
	CRenderManager::GetInstance()->Add_RenderObj(REDER_UI, m_pAni[iAniCounter]);
	m_pGameMgr->Update(fTimeDelta);
	return GLint();
}

GLvoid CLoad::Render()
{
	m_pRenderMgr->Render_Object();
	return GLvoid();
}

GLvoid CLoad::Release()
{
	m_pGameMgr->Clear_ObjList();
	return GLvoid();
}

CLoad* CLoad::Create()
{
	CLoad* pInstance = new CLoad();
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
