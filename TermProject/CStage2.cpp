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
#include "CRenderManager.h"
#include "CGameManager.h"
#include "CSceneManager.h"

CStage2::CStage2()
{
}

CStage2::~CStage2()
{
}

HRESULT CStage2::Initialize()
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
	return NOERROR;
}

GLint CStage2::Update(const GLfloat fTimeDelta)
{
	if (m_pGameMgr->Get_View())
	{
		if (!m_pGameMgr->Get_Obj(OBJ_KEY).empty()) {
			fRotCount -= 90.f / 80.f;
			dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_KEY).front())->Set_Rotate(glm::vec3(0, fRotCount, 0));
		}
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