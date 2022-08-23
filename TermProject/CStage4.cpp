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
#include "CKeyManager.h"
#include "CSoundManager.h"
#include "CBullet.h"

CStage4::CStage4()
{
}

CStage4::~CStage4()
{
	m_pGameMgr->init();
	Release();
}

HRESULT CStage4::Initialize()
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

	for (int i = 3; i < 8; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 4 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		pObj->Get_BB() = { -15 + 1.0f * i - 0.5f, -15 + 1.0f * i + 0.5f, 1.0f * 4, 1.0f * 4 - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
			return E_FAIL;
	}

	for (int i = 6; i < 11; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 7 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		pObj->Get_BB() = { -15 + 1.0f * i - 0.5f, -15 + 1.0f * i + 0.5f, 1.0f * 7, 1.0f * 7 - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
			return E_FAIL;
	}

	for (int i = 3; i < 8; ++i) {
		pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		pObj->Get_BB() = { -15 + 1.0f * i - 0.5f, -15 + 1.0f * i + 0.5f, 1.0f * 10, 1.0f * 10 - 1.0f };
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
			return E_FAIL;
	}

	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(-11.0f, 11.0f, 0.0f), { 1.0, 0.0, 0.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_KEY);
	pObj->Get_BB() = { -11.5f, -10.5f, 11.5f, 10.5f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_KEY, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 15, 1.0f * 1 - 0.5f, -0.25f), { 0.0, 0.0, 1.0, 0.1 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);	// OBJID for AABB
	pObj->Get_BB() = { -15 + 1.0f * 15 - 0.5f, -15 + 1.0f * 15 + 0.5f, 1.0f * 1, 1.0f * 1 - 1.0f };
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOX, pObj)))
		return E_FAIL;

	pObj = CBossMonster::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOSS, pObj)))
		return E_FAIL;

	m_pSoundMgr->Stop_All();
	m_pSoundMgr->Play_BGM(L"Back.mp3");
	m_pSoundMgr->Set_Volume(0.3f, CSoundManager::BGM);

	return NOERROR;
}

GLint CStage4::Update(const GLfloat fTimeDelta)
{
	if (m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_Move())
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
		if (dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Rotate()->GetPos().y > 0.5f) {
			dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Rotate()->GetPos().y -= 0.1f;
			if (dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Rotate()->GetPos().y < 0.0f) {
				dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Rotate()->GetPos().y = 0.0f;
			}
		}
		BB BOX_BB = dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_BB();
		/*BB Boss_BB = dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_MONSTER2).front())->Get_BB();*/
		BB Boss_BB = {1.0f, 9.0f, 8.5f, -0.5f };
		glm::vec3 temp = dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Rotate()->GetPos();
		dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y, temp.y - 1.0f };

		if (Boss_BB.left > BOX_BB.right || Boss_BB.right < BOX_BB.left || Boss_BB.top < BOX_BB.bottom || Boss_BB.bottom > BOX_BB.top);
		else {

			if (dynamic_cast<CBossMonster*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOSS).front())->GetLife() > 0) {
				dynamic_cast<CBossMonster*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOSS).front())->GetLife() -= 1;
				if (dynamic_cast<CBossMonster*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOSS).front())->GetLife() == 0) {
					CObj* pObj = CPortal::Create(glm::vec3(0.0f, 3.0f, 0.f));
					if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PORTAL, pObj)))
						return E_FAIL;
					dynamic_cast<CBossMonster*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOSS).front())->Get_Pmesh()->GetPos() = { -50.0, 0.0, 0.0 };
					dynamic_cast<CBossMonster*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOSS).front())->GetBullet() = false;
					dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_HoldingB() = false;
					dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_CollideB() = true;
				}
				else {
					CObj* pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(-11.0f, 11.0f, 0.0f), { 1.0, 0.0, 0.0, 1.0 });
					pObj->Get_BB() = { -11.5f, -10.5f, 11.5f, 10.5f };
					if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_KEY, pObj)))
						return E_FAIL;
					dynamic_cast<Player2*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER1).front())->GetP()->GetPos() = { -12.0, 0.0, -0.25 };
					dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_pMesh()->GetPos() = { 12.0, 1.0, -0.25 };
					dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_pMesh()->GetRotate() = { 90.0f, 0.0f, 0.0f };
					dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_HoldingB() = false;
					dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_CollideB() = true;
					dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Rotate()->GetPos() = { -15 + 1.0f * 15, 1.0f * 1 - 0.5f, -0.25f };
					temp = dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Rotate()->GetPos();
					dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y, temp.y - 1.0f };
					dynamic_cast<CBossMonster*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOSS).front())->Get_Pmesh()->GetPos() = { 5.0, 0.0, 0.0 };
					dynamic_cast<CBossMonster*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOSS).front())->Get_Pmesh()->GetRotate().y = -20.0f;
					if (!m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BULLET).empty()) {
						for (list<CObj*>::iterator iter_bullet = m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BULLET).begin(); iter_bullet != m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BULLET).end() && m_pGameMgr->Get_View(); ++iter_bullet) // ����
						{
							dynamic_cast<CBullet*>((*iter_bullet))->Get_Mesh()->GetPos().x += 14.0f;
						}
					}
				}
			}
			
			
		}
	}
	if (m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).empty()) {
		for (auto i : dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Rotate()->GetSMESH()) {
			for (size_t j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 1.0;
			}
		}
	}
	else {
		for (auto i : dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Rotate()->GetSMESH()) {
			for (size_t j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 0.1f;
			}
		}
	}

	if (m_pGameMgr->Get_boolPortal() || m_pKeyMgr->KeyDown(KEY_5))
	{
		m_pGameMgr->Get_boolPortal() = false;
		m_pSceneMgr->SceneChange(SCENE_ID::SCENE_END, SCENE_ID::SCENE_STAGE4);
		return 0;
	}
	if (m_pGameMgr->Get_CollideMTP() || dynamic_cast<Player2*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER1).front())->Get_Die())
	{
		m_pGameMgr->Get_CollideMTP() = false;
		m_pSceneMgr->SceneChange(SCENE_ID::SCENE_LOAD, SCENE_ID::SCENE_STAGE4);
		return 0;
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
