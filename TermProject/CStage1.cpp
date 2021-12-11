#include "stdafx.h"
#include "CStage1.h"
#include "CScene.h"
#include "Player3.h"
#include "Player2.h"
#include "Monster.h"
#include "CObject.h"
#include "CCamera.h"
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
				pObj = CObject::Create("../Resource/MapCube/Cube.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 0.5f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
				if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
					return E_FAIL;
			}
			else
			{
				if (j == 0 || j == 29)
				{
					pObj = CObject::Create("../Resource/MapCube/Cube.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 0.5f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
					if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
						return E_FAIL;
				}
			}

		}
	}
	
	pObj = CObject::Create("../Resource/MapCube/Cube.obj", glm::vec3(-15 + 1.0f * 28, 1.0f * 10 - 0.5f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/Cube.obj", glm::vec3(-15 + 1.0f * 27, 1.0f * 10 - 0.5f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;
	pObj = CObject::Create("../Resource/MapCube/Cube.obj", glm::vec3(-15 + 1.0f * 26, 1.0f * 10 - 0.5f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
		return E_FAIL;

	//pObj = CObject::Create("../Resource/Key/Key.obj", glm::vec3(0.0f + 5.0f, 6.5f + 5.0f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(0.0f + 5.0f, 6.5f + 5.0f, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_KEY, pObj)))
		return E_FAIL;

	pObj = Monster::Create(glm::vec3(-15 + 1.0f * 15, 1.0f * 1 - 0.5f, 0.0f));
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MONSTER, pObj)))
		return E_FAIL;

	return NOERROR;
}

GLint CStage1::Update(const GLfloat fTimeDelta)
{
	m_pGameMgr->Update(fTimeDelta);

	if (!bMove && m_pGameMgr->Get_View() == false)
	{
		++iRotCount;
		//m_pMonster->GetRotate().x += 90.f / 80.f;
		fRotCount += 90.f / 80.f;
		dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_KEY).front())->Set_Rotate(glm::vec3 (fRotCount,0,0));
		//dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_KEY).front())->Get_Rotate();
		if (fRotCount >= 90)
		{
			iRotCount = 0;
			bMove = !bMove;
		}
	}
	else if (bMove && m_pGameMgr->Get_View())
	{
		++iRotCount;
		//m_pMonster->GetRotate().x -= 90.f / 80.f;
		fRotCount -= 90.f / 80.f;
		dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_KEY).front())->Set_Rotate(glm::vec3(fRotCount, 0, 0));
		if (fRotCount <= 0)
		{
			iRotCount = 0;
			bMove = !bMove;
		}
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
