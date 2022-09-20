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
	CObj* BlockObj = nullptr;
	pObj = CBackImage::Create("", "../Resource/UI/Back/backback.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_UI, pObj)))
		return E_FAIL;

	pObj = Player2::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PLAYER1, pObj)))
		return E_FAIL;
	pObj = Player3::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PLAYER2, pObj)))
		return E_FAIL;
	/*for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 30; ++j)
		{
			if (i == 0 || i == 14)
			{
				pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
				dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
				if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
					return E_FAIL;
			}
			else
			{
				if (j == 0 || j == 29)
				{
					pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * j, 1.0f * i - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
					dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
					if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
						return E_FAIL;
				}
			}

		}
	}*/

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

	for (int i = 4; i < 8; ++i) {
		/*pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 4 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
			return E_FAIL;*/

		if (!BlockObj)
		{
			BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 4 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		else
		{
			BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 4 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
			return E_FAIL;
	}

	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f, 1.0f * 2 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;

	for (int i = 6; i < 11; ++i) {
		//pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 7 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		//dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		//if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		//	return E_FAIL;

		if (!BlockObj)
		{
			BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 7 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		else
		{
			BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 7 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
			return E_FAIL;
	}

	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 5, 1.0f * 6 - 1.0f, 0.0f), {0.6, 0.6, 0.6, 1.0});
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;

	for (int i = 3; i < 8; ++i) {
		//pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		//dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		//if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		//	return E_FAIL;

		if (!BlockObj)
		{
			BlockObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		else
		{
			BlockObj = CObject::Create(dynamic_cast<CObject*>(BlockObj), "../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * i, 1.0f * 10 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
		}
		dynamic_cast<CObject*>(BlockObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, BlockObj)))
			return E_FAIL;
	}

	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 11, 1.0f * 9 - 1.0f, 0.0f), { 0.6, 0.6, 0.6, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MAP, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(-11.0f, 11.0f, 0.0f), { 1.0, 0.0, 0.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_KEY);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_KEY, pObj)))
		return E_FAIL;

	pObj = CObject::Create("../Resource/MapCube/cube3.obj", glm::vec3(-15 + 1.0f * 15, 1.0f * 1 - 0.5f, -0.25f), { 0.0, 0.0, 1.0, 0.1 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_MAP);	// OBJID for AABB
	m_pBox = pObj;
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOX, pObj)))
		return E_FAIL;

	pObj = CBossMonster::Create();
	m_pBoss = dynamic_cast<CBossMonster*>(pObj);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BOSS, pObj)))
		return E_FAIL;

	m_pSoundMgr->Stop_All();
	m_pSoundMgr->Play_BGM(L"Back.mp3");
	m_pSoundMgr->Set_Volume(0.3f, CSoundManager::BGM);

	return NOERROR;
}

GLint CStage4::Update(const GLfloat fTimeDelta)
{
	if (VIEW::VIEW_2D == m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_Move())
	{
		if (!m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).empty()) {
			fRotCount -= 90.f / 80.f;
			for (auto& iter_begin : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY)) 
				dynamic_cast<CObject*>((iter_begin))->Set_Rotate(glm::vec3(0, fRotCount, 0));
		}

		if (m_pBox) {
			if (dynamic_cast<CObject*>(m_pBox)->Get_Mesh()->GetPos().y > 0.5f) {
				dynamic_cast<CObject*>(m_pBox)->Get_Mesh()->GetPos().y -= 0.1f;
				if (dynamic_cast<CObject*>(m_pBox)->Get_Mesh()->GetPos().y < 0.0f) {
					dynamic_cast<CObject*>(m_pBox)->Get_Mesh()->GetPos().y = 0.0f;
				}
			}
		}
		// Box and Boss Collide Check
		if (m_pBoss->Get_AABB().Intersects(m_pBox->Get_AABB())) {
			if (m_pBoss->GetLife() > 0) {
				m_pBoss->SetLife((m_pBoss->GetLife() - 1));
				if (m_pBoss->GetLife() == 0) {
					CObj* pObj = CPortal::Create(glm::vec3(0.0f, 3.0f, 0.f));
					if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_PORTAL, pObj)))
						return E_FAIL;
					m_pBoss->Get_Mesh()->GetPos() = { -50.0, 0.0, 0.0 };
					m_pBoss->SetBullet(false);
					if (!m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).empty()) {
						dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->SetHoldingB(false);
						dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->SetCollideB(true);
					}
				}
				// Reset Stage
				else
					Reset();
			}
		}
	}

	// Box appears if keys are gone
	if (m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).empty()) {
		for (auto i : dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Mesh()->GetSMESH()) {
			for (size_t j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 1.0;
			}
		}
	}
	else {
		for (auto i : dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Mesh()->GetSMESH()) {
			for (size_t j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 0.1f;
			}
		}
	}

	if (!m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PORTAL).empty()) {
		if (CScene::SceneChange(SCENE_ID::SCENE_END, SCENE_ID::SCENE_STAGE4))
			return 0;
	}

	if (CScene::PlayerDieScene(SCENE_ID::SCENE_LOAD, SCENE_ID::SCENE_STAGE4))
		return 0;

	if (CScene::DebugSceneChange(SCENE_ID::SCENE_STAGE4))
		return 0;
	
	m_pGameMgr->Update(fTimeDelta);
	return GLint();
}

GLvoid CStage4::Render()
{
	m_pRenderMgr->Render_Object();
	return GLvoid();
}

GLvoid CStage4::Reset()
{
	CObj* pObj = CObject::Create("../Resource/Key1/Key.obj", glm::vec3(-11.0f, 11.0f, 0.0f), { 1.0, 0.0, 0.0, 1.0 });
	dynamic_cast<CObject*>(pObj)->Set_OBJID(OBJ_ID::OBJ_KEY);
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_KEY, pObj)))
		return;

	if (!m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER1).empty()) {
		dynamic_cast<Player2*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER1).front())->GetP()->GetPos() = { -12.0, 0.0, -0.25 };
		dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_pMesh()->GetPos() = { 12.0, 1.0, -0.25 };
		dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_pMesh()->GetRotate() = { 90.0f, 0.0f, 0.0f };
		dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->SetHoldingB(false);
		dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->SetCollideB(false);
	}
	dynamic_cast<CObject*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).front())->Get_Mesh()->GetPos() = { -15 + 1.0f * 15, 1.0f * 1 - 0.5f, -0.25f };
	dynamic_cast<CObject*>(m_pBox)->Get_Mesh()->GetPos() = { -15 + 1.0f * 15, 1.0f * 1 - 0.5f, -0.25f };
	m_pBoss->Get_Mesh()->GetPos() = { 5.0f, 0.0f, 0.0f };
	m_pBoss->Get_Mesh()->GetRotate().y = -20.0f;
	
	// Bullet Reset
	if (!m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BULLET).empty()) {
		for (auto& bullet : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BULLET))
			dynamic_cast<CBullet*>(bullet)->Get_Mesh()->GetPos().x += 14.0f;
	}

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
