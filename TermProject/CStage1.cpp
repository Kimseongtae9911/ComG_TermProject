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

	pObj = CBackImage::Create("", "../Resource/UI/Back/backback.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_UI, pObj)))
		return E_FAIL;

	pObj = Player2::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_PLAYER1, pObj)))
		return E_FAIL;
	pObj = Player3::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_PLAYER2, pObj)))
		return E_FAIL;
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if (i == 0 || i == 14)
			{
				pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
				pObj->Get_BB() = { -15 + 1.0f * j - 0.5f, -15 + 1.0f * j + 0.5f, 1.0f * i, 1.0f * i - 1.0f };
				if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
					return E_FAIL;
			}
			else
			{
				if (j == 0 || j == 29)
				{
					pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
					pObj->Get_BB() = { -15 + 1.0f * j - 0.5f, -15 + 1.0f * j + 0.5f, 1.0f * i, 1.0f * i - 1.0f };
					if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
						return E_FAIL;
				}
			}

		}
	}
	//pObj = CObject::Create(pObj,"../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 28, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });

	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 28, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	pObj->Get_BB() = { -15 + 1.0f * 28 - 0.5f, -15 + 1.0f * 28 + 0.5f, 1.0f * 10, 1.0f * 10 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 27, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	pObj->Get_BB() = { -15 + 1.0f * 27 - 0.5f, -15 + 1.0f * 27 + 0.5f, 1.0f * 10, 1.0f * 10 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 26, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	pObj->Get_BB() = { -15 + 1.0f * 26 - 0.5f, -15 + 1.0f * 26 + 0.5f, 1.0f * 10, 1.0f * 10 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 1, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	pObj->Get_BB() = { -15 + 1.0f * 1 - 0.5f, -15 + 1.0f * 1 + 0.5f, 1.0f * 10, 1.0f * 10 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 2, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	pObj->Get_BB() = { -15 + 1.0f * 2 - 0.5f, -15 + 1.0f * 2 + 0.5f, 1.0f * 10, 1.0f * 10 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 3, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	pObj->Get_BB() = { -15 + 1.0f * 3 - 0.5f, -15 + 1.0f * 3 + 0.5f, 1.0f * 10, 1.0f * 10 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 10, 1.0f * 3 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	pObj->Get_BB() = { -15 + 1.0f * 10 - 0.5f, -15 + 1.0f * 10 + 0.5f, 1.0f * 3, 1.0f * 3 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_BOX, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 15, 1.0f * 5 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	pObj->Get_BB() = { -15 + 1.0f * 15 - 0.5f, -15 + 1.0f * 15 + 0.5f, 1.0f * 5, 1.0f * 5 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_BOX, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 20, 1.0f * 7 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	pObj->Get_BB() = { -15 + 1.0f * 20 - 0.5f, -15 + 1.0f * 20 + 0.5f, 1.0f * 7, 1.0f * 7 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_BOX, pObj)))
		return E_FAIL;



	pObj = CPortal::Create(glm::vec3(11.5f, 11.3f, 0.f));
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_PORTAL, pObj)))
		return E_FAIL;



	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(-13.0f, 11.0f, 0.0f), { 1.0, 0.0, 0.0, 1.0 });
	pObj->Get_BB() = {-13.5f, -12.5f, 11.5f, 10.5f};
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_KEY, pObj)))
		return E_FAIL;

	pObj = Monster::Create("../Resource/Boss/wailmer.obj", glm::vec3(0.0f, 1.5f, -0.25f), glm::vec3(0.3, 0.3, 0.3), 0);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MONSTER1, pObj)))
		return E_FAIL;

	//pObj = CBossMonster::Create();
	//if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MONSTER2, pObj)))
	//	return E_FAIL;
	return NOERROR;
}

GLint CStage1::Update(const GLfloat fTimeDelta)
{
	if (m_pGameMgr->Get_View())
	{
		if (!m_pGameMgr->Get_Obj(OBJ_KEY).empty()) {
			fRotCount -= 90.f / 80.f;
				dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_KEY).front())->Set_Rotate(glm::vec3(0, fRotCount, 0));
		}
	}
	if (m_pGameMgr->Get_boolPortal() || m_pKeyMgr->KeyDown(KEY_2))
	{
		m_pGameMgr->Get_boolPortal() = false;
		m_pSceneMgr->SceneChange(SCENE_STAGE2,SCENE_STAGE1);
		return 0;
	}
	if (m_pGameMgr->Get_CollideMTP())
	{
		m_pGameMgr->Get_CollideMTP() = false;
		m_pSceneMgr->SceneChange(SCENE_LOAD, SCENE_STAGE1);
		return 0;
	}
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
