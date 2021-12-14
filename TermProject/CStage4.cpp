#include "stdafx.h"
#include "CStage4.h"
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

CStage4::CStage4()
{
}

CStage4::~CStage4()
{
	Release();
}

HRESULT CStage4::Initialize()
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

	for (int i = 3; i < 8; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 4 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		pObj->Get_BB() = { -15 + 1.0f * i - 0.5f, -15 + 1.0f * i + 0.5f, 1.0f * 4, 1.0f * 4 - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
			return E_FAIL;
	}

	for (int i = 6; i < 11; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 7 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		pObj->Get_BB() = { -15 + 1.0f * i - 0.5f, -15 + 1.0f * i + 0.5f, 1.0f * 7, 1.0f * 7 - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
			return E_FAIL;
	}

	for (int i = 3; i < 8; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		pObj->Get_BB() = { -15 + 1.0f * i - 0.5f, -15 + 1.0f * i + 0.5f, 1.0f * 10, 1.0f * 10 - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MAP, pObj)))
			return E_FAIL;
	}

	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(-11.0f, 11.0f, 0.0f), { 1.0, 0.0, 0.0, 1.0 });
	pObj->Get_BB() = { -11.5f, -10.5f, 11.5f, 10.5f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_KEY, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 15, 1.0f * 1 - 0.5f, -0.25f), { 0.0, 0.0, 1.0, 0.1 });
	pObj->Get_BB() = { -15 + 1.0f * 15 - 0.5f, -15 + 1.0f * 15 + 0.5f, 1.0f * 1, 1.0f * 1 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_BOX, pObj)))
		return E_FAIL;

	pObj = CBossMonster::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_BOSS, pObj)))
		return E_FAIL;

	return NOERROR;
}

GLint CStage4::Update(const GLfloat fTimeDelta)
{
	if (m_pGameMgr->Get_View())
	{
		if (!m_pGameMgr->Get_Obj(OBJ_KEY).empty()) {
			fRotCount -= 90.f / 80.f;
			list<CObj*>::iterator iter_begin = m_pGameMgr->Get_Obj(OBJ_KEY).begin();
			list<CObj*>::iterator iter_end = m_pGameMgr->Get_Obj(OBJ_KEY).end();
			for (; iter_begin != iter_end;) {
				dynamic_cast<CObject*>((*iter_begin))->Set_Rotate(glm::vec3(0, fRotCount, 0));
				++iter_begin;
			}
		}
		if (dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_BOX).front())->Get_Rotate()->GetPos().y > 0.5) {
			dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_BOX).front())->Get_Rotate()->GetPos().y -= 0.1;
			if (dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_BOX).front())->Get_Rotate()->GetPos().y < 0.5) {
				dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_BOX).front())->Get_Rotate()->GetPos().y = 0.5;
			}
		}
		BB BOX_BB = dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_BOX).front())->Get_BB();
		/*BB Boss_BB = dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_MONSTER2).front())->Get_BB();*/
		BB Boss_BB = {1.0f, 9.0f, 8.5f, -0.5f };
		if (Boss_BB.left > BOX_BB.right || Boss_BB.right < BOX_BB.left || Boss_BB.top < BOX_BB.bottom || Boss_BB.bottom > BOX_BB.top);
		else {
			cout << "보스몬스터 생명 감소" << endl;
			cout << "초기화" << endl;
		}
	}
	if (m_pGameMgr->Get_Obj(OBJ_KEY).empty()) {
		for (auto i : dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_BOX).front())->Get_Rotate()->GetSMESH()) {
			for (int j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 1.0;
			}
		}
	}


	m_pGameMgr->Update(fTimeDelta);
	return GLint();
}

GLvoid CStage4::Render()
{
	m_pRenderMgr->Render_Object();
	return GLvoid();
}

GLvoid CStage4::Release()
{
	m_pGameMgr->Clear_ObjList();
	return GLvoid();
}

CStage4* CStage4::Create()
{
	CStage4* pInstance = new CStage4();
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
