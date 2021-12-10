#include "stdafx.h"
#include "CStage1.h"
#include "CScene.h"
#include "Player3.h"
#include "Player2.h"
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
	m_pGameMgr->Add_Camera(CCamera::Create(glm::vec3(0.0f, 0.f, 30.f), glm::vec3(0.f, 0.0f, 0.f), glm::vec3(0.f, 1.f, 0.f)));
	CObj* pObj = nullptr;
	pObj = Player2::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_PLAYER1, pObj)))
		return E_FAIL;
	pObj = Player3::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_PLAYER2, pObj)))
		return E_FAIL;
	for (int i = 0; i < 10; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (i == 0 || i == 9)
			{
				pObj = CObject::Create("../Resource/MapCube/Cube.obj", glm::vec3(-10 + 1.0f * j, 1.0f * i, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
				if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
					return E_FAIL;
			}
			else
			{
				if (j == 0 || j == 19)
				{
					pObj = CObject::Create("../Resource/MapCube/Cube.obj", glm::vec3(-10 + 1.0f * j, 1.0f * i, 0.0f), { 1.0, 1.0, 1.0, 1.0 });
					if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
						return E_FAIL;
				}
			}

		}
	}

	return NOERROR;
}

GLint CStage1::Update(const GLfloat fTimeDelta)
{
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
