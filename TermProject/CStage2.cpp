#include "stdafx.h"
#include "CStage2.h"
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

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
	Release();
	m_pGameMgr->init();
}

HRESULT CStage2::Initialize()
{
	CScene::Initialize();
	m_pGameMgr->Add_Camera(CCamera::Create(glm::vec3(0.0f, 6.5f, 30.f), glm::vec3(0.f, 6.5f, 0.f), glm::vec3(0.f, 1.f, 0.f)));
	CObj* pObj = nullptr;
	pObj = CBackImage::Create("", "../Resource/UI/Back/backback.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_UI, pObj)))
		return E_FAIL;

	pObj = Player2::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PLAYER1, pObj)))
		return E_FAIL;
	pObj = Player3::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PLAYER2, pObj)))
		return E_FAIL;
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if (i == 0 || i == 14)
			{
				pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
				dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
				pObj->Get_BB() = { -15 + 1.0f * j - 0.5f, -15 + 1.0f * j + 0.5f, 1.0f * i, 1.0f * i - 1.0f };
				if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
					return E_FAIL;
			}
			else
			{
				if (j == 0 || j == 29)
				{
					pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
					dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
					pObj->Get_BB() = { -15 + 1.0f * j - 0.5f, -15 + 1.0f * j + 0.5f, 1.0f * i, 1.0f * i - 1.0f };
					if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
						return E_FAIL;
				}
			}

		}
	}
	for (int i = 3; i < 6; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 6 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		pObj->Get_BB() = { -15 + 1.0f * i - 0.5f, -15 + 1.0f * i + 0.5f, 1.0f * 6, 1.0f * 6 - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
			return E_FAIL;
	}
	for (int i = 1; i < 6; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 5, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		pObj->Get_BB() = { -15 + 1.0f * 5 - 0.5f, -15 + 1.0f * 5 + 0.5f, 1.0f * i, 1.0f * i - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
			return E_FAIL;
	}
	for (int i = 1; i < 10; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 10, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		pObj->Get_BB() = { -15 + 1.0f * 10 - 0.5f, -15 + 1.0f * 10 + 0.5f, 1.0f * i, 1.0f * i - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
			return E_FAIL;

		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 15, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		pObj->Get_BB() = { -15 + 1.0f * 15 - 0.5f, -15 + 1.0f * 15 + 0.5f, 1.0f * i, 1.0f * i - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
			return E_FAIL;
	}
	for (int i = 22; i < 29; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		pObj->Get_BB() = { -15 + 1.0f * i - 0.5f, -15 + 1.0f * i + 0.5f, 1.0f * 10, 1.0f * 10 - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
			return E_FAIL;
	}

	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(-13.0f, 12.0f, 0.0f), { 1.0, 0.0, 0.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_KEY);
	pObj->Get_BB() = { -13.5f, -12.5f, 12.5f, 11.5f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_KEY, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(-3.0f, 1.0f, 0.0f), { 1.0, 0.0, 0.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_KEY);
	pObj->Get_BB() = { -3.5f, -2.5f, 1.5f, 0.5f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_KEY, pObj)))
		return E_FAIL;

	pObj = CPortal::Create(glm::vec3(11.5f, 11.3f, 0.f));
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PORTAL, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 1, 1.0f * 6 - 0.5f, -0.25f), { 1.0, 1.0, 1.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_BOX);
	pObj->Get_BB() = { -15 + 1.0f * 11 - 0.5f, -15 + 1.0f * 1 + 0.5f, 1.0f * 6, 1.0f * 6 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOX, pObj)))
		return E_FAIL;

	pObj = Monster::Create("../Resource/Monster/bee.obj", glm::vec3(0.0f, 1.0f, 0.5f), glm::vec3(0.0002, 0.0002, 0.0002), 1);
	pObj->Set_OBJID(OBJ_ID::OBJ_MONSTER2);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MONSTER2, pObj)))
		return E_FAIL;

	pObj = Monster::Create("../Resource/Monster/bee.obj", glm::vec3(0.0f, 9.0f, 0.5f), glm::vec3(0.0002, 0.0002, 0.0002), 1);
	pObj->Set_OBJID(OBJ_ID::OBJ_MONSTER2);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MONSTER2, pObj)))
		return E_FAIL;
	m_pSoundMgr->Stop_All();
	m_pSoundMgr->Play_BGM(L"Back.mp3");
	m_pSoundMgr->Set_Volume(0.3f, CSoundManager::BGM);

	return NOERROR;
}

GLint CStage2::Update(const GLfloat fTimeDelta)
{
	if (m_pGameMgr->Get_View())
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

	if (m_pGameMgr->Get_DebugMode() && (m_pGameMgr->Get_boolPortal() || m_pKeyMgr->KeyDown(KEY_3)))
	{
		m_pGameMgr->Get_boolPortal() = false;
		m_pSceneMgr->SceneChange(SCENE_ID::SCENE_STAGE3, SCENE_ID::SCENE_STAGE2);
		return 0;
	}

	if (m_pGameMgr->Get_CollideMTP())
	{
		m_pGameMgr->Get_CollideMTP() = false;
		m_pSceneMgr->SceneChange(SCENE_ID::SCENE_LOAD, SCENE_ID::SCENE_STAGE2);
		return 0;
	}


	m_pGameMgr->Update(fTimeDelta);
	return GLint();
}

GLvoid CStage2::Render()
{
	m_pRenderMgr->Render_Object();
	return GLvoid();
}

GLvoid CStage2::Release()
{
	m_pGameMgr->Clear_ObjList();
	return GLvoid();
}

CStage2* CStage2::Create()
{
	CStage2* pInstance = new CStage2();
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
