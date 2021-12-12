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
#include "CRenderManager.h"
#include "CGameManager.h"


CStage1::CStage1()
{
}

CStage1::~CStage1()
{
}

HRESULT CStage1::Initialize()
{
	CScene::Initialize();
	m_pGameMgr->Add_Camera(CCamera::Create(glm::vec3(0.0f, 6.5f, 30.f), glm::vec3(0.f, 6.5f, 0.f), glm::vec3(0.f, 1.f, 0.f)));
	CObj* pObj = nullptr;
	pObj = CPortal::Create("../Resource/UI/portal/portal.png", glm::vec3(100.f, 150.f, 0.f), glm::vec3(1.f));
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
				pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 0.5f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
				if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
					return E_FAIL;
			}
			else
			{
				if (j == 0 || j == 29)
				{
					pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 0.5f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
					if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
						return E_FAIL;
				}
			}

		}
	}
	
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 28, 1.0f * 10 - 0.5f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 27, 1.0f * 10 - 0.5f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 26, 1.0f * 10 - 0.5f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/Cube/TestCube.obj", glm::vec3(-15 + 1.0f * 10, 1.0f * 5 - 0.5f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_BOX, pObj)))
		return E_FAIL;


	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(0.0f + 5.0f, 6.5f + 5.0f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_KEY, pObj)))
		return E_FAIL;

	pObj = Monster::Create("../Resource/Monster/podoboo.obj", glm::vec3(0.0f, 0.6f, -0.25f), glm::vec3(0.03, 0.03, 0.03), 0);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MONSTER1, pObj)))
		return E_FAIL;

	pObj = Monster::Create("../Resource/Monster/bee.obj", glm::vec3(0.0f, 10.0f, -0.25f), glm::vec3(0.0002, 0.0002, 0.0002), 1);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MONSTER2, pObj)))
		return E_FAIL;

	pObj = CBossMonster::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MONSTER2, pObj)))
		return E_FAIL;
}

GLint CStage1::Update(const GLfloat fTimeDelta)
{
	m_pGameMgr->Update(fTimeDelta);

	if (!bMove && m_pGameMgr->Get_View() == false)
	{
		//fRotCount += 90.f / 80.f;
		fRotCount = 90.f;
		dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_KEY).front())->Set_Rotate(glm::vec3 (fRotCount, 0, 0));
		//dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_KEY).front())->Get_Rotate()->
	}
	else if (m_pGameMgr->Get_View())
	{
		++iRotCount;
		fRotCount -= 90.f / 80.f;
		dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_KEY).front())->Set_Rotate(glm::vec3(0, fRotCount, 0));
	}
	
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
