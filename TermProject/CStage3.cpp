#include "stdafx.h"
#include "CStage3.h"
#include "CScene.h"
#include "CMesh.h"
#include "Player3.h"
#include "Player2.h"
#include "Monster.h"
#include "CBossMonster.h"
#include "CObject.h"
#include "CCamera.h"
#include "CPortal.h"
#include "CBackImage.h"
#include "CRenderManager.h"
#include "CGameManager.h"
#include "CSceneManager.h"
#include "CKeyManager.h"
#include "CSoundManager.h"


CStage3::CStage3()
{
}

CStage3::~CStage3()
{
	m_pGameMgr->init();
	Release();
}

HRESULT CStage3::Initialize()
{
	CScene::Initialize();
	m_pGameMgr->Add_Camera(CCamera::Create(glm::vec3(0.0f, 6.5f, 30.f), glm::vec3(0.f, 6.5f, 0.f), glm::vec3(0.f, 1.f, 0.f)));
	CObj* pObj = nullptr;
	CObj* BlockObj = nullptr;

	pObj = CBackImage::Create("", "../Resource/UI/Back/backback.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_UI, pObj)))
		return E_FAIL;

	pObj = Player2::Create();
	dynamic_cast<Player2*>(pObj)->GetP()->GetPos() = { -12.0, 6.0, -0.25 };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PLAYER1, pObj)))
		return E_FAIL;
	pObj = Player3::Create();
	dynamic_cast<Player3*>(pObj)->Get_pMesh()->GetPos() = { 12.0, 7.0, -0.25 };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PLAYER2, pObj)))
		return E_FAIL;
	//for (int i = 0; i < 15; ++i)
	//{
	//	for (int j = 0; j < 30; ++j)
	//	{
	//		if (i == 0 || i == 14)
	//		{
	//			pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	//			dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	//			if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
	//				return E_FAIL;
	//		}
	//		else
	//		{
	//			if (j == 0 || j == 29)
	//			{
	//				pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	//				dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
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
					BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
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

	for (int i = 13; i > 9; --i) {
		//pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 11, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		//dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		//if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		//	return E_FAIL;
		if (!BlockObj)
		{
			BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 11, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		else
		{
			BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 11, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
			return E_FAIL;


		//pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 18, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		//dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		//if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		//	return E_FAIL;

		if (!BlockObj)
		{
			BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 18, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		else
		{
			BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 18, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
			return E_FAIL;
	}
	for (int i = 1; i < 11; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 6 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
			return E_FAIL;

		if (!BlockObj)
		{
			BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 6 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		else
		{
			BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 6 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
			return E_FAIL;
	}
	for (int i = 28; i > 18; --i) {
		//pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 6 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		//dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		//if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		//	return E_FAIL;

		if (!BlockObj)
		{
			BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 6 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		else
		{
			BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 6 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
			return E_FAIL;
	}

	for (int i = 6; i > 3; --i) {
		//pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 10, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		//dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		//if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		//	return E_FAIL;

		if (!BlockObj)
		{
			BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 10, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		else
		{
			BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 10, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
			return E_FAIL;

		//pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 19, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		//dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		//if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		//	return E_FAIL;

		if (!BlockObj)
		{
			BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 19, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		else
		{
			BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 19, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
			return E_FAIL;
	}
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 8, 1.0f * 1 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 21, 1.0f * 1 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 15, 1.0f * 10 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_BOX);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOX, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 17, 1.0f * 10 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_BOX);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOX, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 13.5, 1.0f * 10 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_BOX);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOX, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 12, 1.0f * 10 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_BOX);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOX, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(-14.0f, 0.0f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_KEY);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_KEY, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(13.0f, 0.0f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_KEY);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_KEY, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(0.0f, 12.0f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_KEY);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_KEY, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/Spike/spike.obj", glm::vec3(0.0f, 0.1f, -0.1f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_SPIKE);
	dynamic_cast<CObject*>(pObj)->Get_Mesh()->GetScale() = { 0.03f, 0.03f, 0.03f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_SPIKE, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Spike/spike.obj", glm::vec3(-1.5f, 0.1f, -0.1f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_SPIKE);
	dynamic_cast<CObject*>(pObj)->Get_Mesh()->GetScale() = { 0.03f, 0.03f, 0.03f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_SPIKE, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Spike/spike.obj", glm::vec3(1.5f, 0.1f, -0.1f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_SPIKE);
	dynamic_cast<CObject*>(pObj)->Get_Mesh()->GetScale() = { 0.03f, 0.03f, 0.03f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_SPIKE, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Spike/spike.obj", glm::vec3(3.0f, 0.1f, -0.1f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_SPIKE);
	dynamic_cast<CObject*>(pObj)->Get_Mesh()->GetScale() = { 0.03f, 0.03f, 0.03f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_SPIKE, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Spike/spike.obj", glm::vec3(-3.0f, 0.1f, -0.1f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_SPIKE);
	dynamic_cast<CObject*>(pObj)->Get_Mesh()->GetScale() = { 0.03f, 0.03f, 0.03f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_SPIKE, pObj)))
		return E_FAIL;

	pObj = Monster::Create("../Resource/Boss/wailmer.obj", glm::vec3(-13.0f, 0.6f, -0.25f), glm::vec3(0.3, 0.3, 0.3));
	pObj->UpdateAABB(dynamic_cast<Monster*>(pObj)->Get_Mesh()->Get_Matrix(), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	pObj->Set_OBJID(OBJ_ID::OBJ_MONSTER1);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MONSTER1, pObj)))
		return E_FAIL;

	pObj = Monster::Create("../Resource/Boss/wailmer.obj", glm::vec3(12.0f, 0.6f, -0.25f), glm::vec3(0.3, 0.3, 0.3));
	pObj->UpdateAABB(dynamic_cast<Monster*>(pObj)->Get_Mesh()->Get_Matrix(), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	pObj->Set_OBJID(OBJ_ID::OBJ_MONSTER1);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MONSTER1, pObj)))
		return E_FAIL;

	pObj = Monster::Create("../Resource/Boss/wailmer.obj", glm::vec3(-2.5f, 11.0f, -0.25f), glm::vec3(0.3, 0.3, 0.3));
	pObj->UpdateAABB(dynamic_cast<Monster*>(pObj)->Get_Mesh()->Get_Matrix(), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f));
	pObj->Set_OBJID(OBJ_ID::OBJ_MONSTER1);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MONSTER1, pObj)))
		return E_FAIL;

	pObj = CPortal::Create(glm::vec3(11.5f, 11.3f, 0.f));
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PORTAL, pObj)))
		return E_FAIL;
	m_pSoundMgr->Stop_All();
	m_pSoundMgr->Play_BGM(L"Back.mp3");
	m_pSoundMgr->Set_Volume(0.3f, CSoundManager::BGM);

	return NOERROR;
}

GLint CStage3::Update(const GLfloat fTimeDelta)
{
	if (VIEW::VIEW_2D == m_pGameMgr->Get_View())
	{
		if (!m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).empty()) {
			fRotCount -= 90.f / 80.f;
			list<CObj*>::iterator iter_begin = m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).begin();
			list<CObj*>::iterator iter_end = m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).end();
			for (; iter_begin != iter_end;) {
				dynamic_cast<CObject*>((*iter_begin))->Set_Rotate(glm::vec3(0, fRotCount, 0));
				++iter_begin;
			}
		}
	}

	if (CScene::SceneChange(SCENE_ID::SCENE_STAGE4, SCENE_ID::SCENE_STAGE3))
		return 0;

	if (CScene::PlayerDieScene(SCENE_ID::SCENE_LOAD, SCENE_ID::SCENE_STAGE3))
		return 0;

	if (CScene::DebugSceneChange(SCENE_ID::SCENE_STAGE3))
		return 0;

	m_pGameMgr->Update(fTimeDelta);
	return GLint();
}

GLvoid CStage3::Render()
{
	m_pRenderMgr->Render_Object();
	return GLvoid();
}

GLvoid CStage3::Release()
{
	m_pGameMgr->Clear_ObjList();
	return GLvoid();
}

CStage3* CStage3::Create()
{
	CStage3* pInstance = new CStage3();
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}
