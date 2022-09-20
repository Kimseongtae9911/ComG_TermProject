#include "stdafx.h"
#include "CStage1.h"
#include "CScene.h"
#include "Player3.h"
#include "Player2.h"
#include "Monster.h"
#include "CBossMonster.h"
#include "CObject.h"
#include "CCamera.h"
#include "CPortal.h"
#include "CBackImage.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CGameManager.h"
#include "CSceneManager.h"
#include "CSoundManager.h"
#include "CSprite.h"

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
	Release();
	//m_pGameMgr->Delete_Camera();
	//m_pGameMgr->DestroyInstance();
	m_pGameMgr->init();
}

HRESULT CStage1::Initialize()
{
	CScene::Initialize();
	m_pGameMgr->Add_Camera(CCamera::Create(glm::vec3(0.0f, 6.5f, 30.f), glm::vec3(0.f, 6.5f, 0.f), glm::vec3(0.f, 1.f, 0.f)));
	CObj* pObj = nullptr;
	CObj* BlockObj = nullptr;

	pObj = CBackImage::Create("", "../Resource/UI/Back/backback.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_UI, pObj)))
		return E_FAIL;

	//for (int i = 0; i < 15; ++i)
	//{
	//	for (int j = 0; j < 30; ++j)
	//	{
	//		if (i == 0 || i == 14)
	//		{
	//			pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	//			dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	//			pObj->Get_BB() = { -15 + 1.0f * j - 0.5f, -15 + 1.0f * j + 0.5f, 1.0f * i, 1.0f * i - 1.0f };
	//			if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
	//				return E_FAIL;
	//		}
	//		else
	//		{
	//			if (j == 0 || j == 29)
	//			{
	//				pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	//				dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	//				pObj->Get_BB() = { -15 + 1.0f * j - 0.5f, -15 + 1.0f * j + 0.5f, 1.0f * i, 1.0f * i - 1.0f };
	//				if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
	//					return E_FAIL;
	//			}
	//		}

	//	}
	//}
	
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if (i == 0 || i == 14)
			{
				if (!BlockObj)
				{
					BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
				}
				else
				{
					BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj),"../Resource/MapCube/cube3.obj", glm::vec3(-15 + j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
				}
				dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
				if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
					return E_FAIL;
			}
			else
			{
				if (j == 0 || j == 29)
				{
					if (!BlockObj)
					{
						BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
					}
					else
					{
						BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
					}
					dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
					if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
						return E_FAIL;
				}
			}

		}
	}
	//pObj = CObject::Create(pObj,"../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 28, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });

	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 28, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 27, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 26, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 1, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 2, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 3, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 10, 1.0f * 3 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_BOX);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOX, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 15, 1.0f * 5 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_BOX);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOX, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 20, 1.0f * 7 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_BOX);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOX, pObj)))
		return E_FAIL;

	pObj = CPortal::Create(glm::vec3(11.5f, 11.3f, 0.f));
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PORTAL, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(-13.0f, 11.0f, 0.0f), { 1.0, 0.0, 0.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_KEY);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_KEY, pObj)))
		return E_FAIL;

	pObj = Monster::Create("../Resource/Boss/wailmer.obj", glm::vec3(0.0f, 1.5f, -0.25f), glm::vec3(0.3, 0.3, 0.3));
	pObj->Set_OBJID(OBJ_ID::OBJ_MONSTER1);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MONSTER1, pObj)))
		return E_FAIL;

	pObj = Player2::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PLAYER1, pObj)))
		return E_FAIL;

	pObj = Player3::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PLAYER2, pObj)))
		return E_FAIL;


	m_pSoundMgr->Stop_All();
	m_pSoundMgr->Play_BGM(L"Back.mp3");
	m_pSoundMgr->Set_Volume(0.3f, CSoundManager::BGM);
	return NOERROR;
}

GLint CStage1::Update(const GLfloat fTimeDelta)
{
	if (VIEW::VIEW_2D == m_pGameMgr->Get_View())
	{
		if (!m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).empty()) {
			fRotCount -= 90.f / 80.f;
			dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).front())->Set_Rotate(glm::vec3(0, fRotCount, 0));
		}
	}


	if (CScene::SceneChange(SCENE_ID::SCENE_STAGE2, SCENE_ID::SCENE_STAGE1))
		return 0;

	if (CScene::PlayerDieScene(SCENE_ID::SCENE_LOAD, SCENE_ID::SCENE_STAGE1))
		return 0;

	if (CScene::DebugSceneChange(SCENE_ID::SCENE_STAGE1))
		return 0;

	m_pGameMgr->Update(fTimeDelta);

	return GLint();
}

GLvoid CStage1::Render()
{
	m_pRenderMgr->Render_Object();
	return GLvoid();
}

GLvoid CStage1::Release()
{
	m_pGameMgr->Clear_ObjList();
	return GLvoid();
}

CStage1* CStage1::Create()
{
	CStage1* pInstance = new CStage1();
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
