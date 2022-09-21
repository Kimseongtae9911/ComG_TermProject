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
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_UI, pObj)))
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

	//m_pBox = new CObj;
	//m_pBox = CSprite::Create(glm::vec3(600, 50, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/boxblank.png");

	m_pLifeWord = new CObj;
	m_pLifeWord = CSprite::Create(glm::vec3(100, 50, 0.f), glm::vec3(1.f), "", "../Resource/UI/Back/LifeWord.png");
	
	m_pLifePlayer1 = new CObj;
	m_pLifePlayer1 = CSprite::Create(glm::vec3(250, 50, 0.f), glm::vec3(1.5f), "", "../Resource/UI/Back/LifePlayer.png");
	m_pLifePlayer2 = new CObj;
	m_pLifePlayer2 = CSprite::Create(glm::vec3(320, 50, 0.f), glm::vec3(1.5f), "", "../Resource/UI/Back/LifePlayer.png");
	m_pLifePlayer3 = new CObj;
	m_pLifePlayer3 = CSprite::Create(glm::vec3(390, 50, 0.f), glm::vec3(1.5f), "", "../Resource/UI/Back/LifePlayer.png");
	m_pLifePlayer4 = new CObj;
	m_pLifePlayer4 = CSprite::Create(glm::vec3(460, 50, 0.f), glm::vec3(1.5f), "", "../Resource/UI/Back/LifePlayer.png");
	m_pLifePlayer5 = new CObj;
	m_pLifePlayer5 = CSprite::Create(glm::vec3(530, 50, 0.f), glm::vec3(1.5f), "", "../Resource/UI/Back/LifePlayer.png");

	m_iLife = m_pSceneMgr->Get_Life();
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
	if (fNextScene >= 5.0)
	{
		fNextScene = 0;
		switch (m_pSceneMgr->Get_SceneChangeCount())
		{
		case 2:
			m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE1, SCENE_ID::SCENE_LOAD);
			break;
		case 3:
			m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE2, SCENE_ID::SCENE_LOAD);
			break;
		case 4:
			m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE3, SCENE_ID::SCENE_LOAD);
			break;
		case 5:
			m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE4, SCENE_ID::SCENE_LOAD);
			break;
		default:
			break;
		}
		
		return 0;
	}
	CRenderManager::GetInstance()->Add_RenderObj(RENDER_ID::REDER_UI, m_pAni[iAniCounter]);
	CRenderManager::GetInstance()->Add_RenderObj(RENDER_ID::REDER_UI, m_pLifeWord);

	switch (m_iLife)
	{
	case 5:
		CRenderManager::GetInstance()->Add_RenderObj(RENDER_ID::REDER_UI, m_pLifePlayer5);
	case 4:
		CRenderManager::GetInstance()->Add_RenderObj(RENDER_ID::REDER_UI, m_pLifePlayer4);
	case 3:
		CRenderManager::GetInstance()->Add_RenderObj(RENDER_ID::REDER_UI, m_pLifePlayer3);
	case 2:
		CRenderManager::GetInstance()->Add_RenderObj(RENDER_ID::REDER_UI, m_pLifePlayer2);
	case 1:
		CRenderManager::GetInstance()->Add_RenderObj(RENDER_ID::REDER_UI, m_pLifePlayer1);
		break;
	default:
		break;
	}

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
