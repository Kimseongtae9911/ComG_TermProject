#include "stdafx.h"
#include "Player3.h"
#include "CMesh.h"
#include "CShader.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CSoundManager.h"
#include "CGameManager.h"
#include "CCamera.h"
#include "CObject.h"
#include "Monster.h"
#include "CPortal.h"
#include "CBullet.h"

Player3::Player3()
{
}

Player3::~Player3()
{
	Release();
}

HRESULT Player3::Initialize()
{
	CObj::Initialize();
	m_Player = CMesh::Create("../Resource/Player3D/Player3D.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	m_Player->GetScale() = glm::vec3(0.3, 0.3, 0.3);
	m_Player->GetRotate() = glm::vec3(90.0f, 0.0f, 0.0f);
	m_Player->GetTrans() = glm::vec3(12.0, 1.0, -0.25);
	
	CObj::UpdateAABB(m_Player->Get_Matrix(), glm::vec3(2.5f, 3.4f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.4f, 0.0f));

	return NOERROR;
}

GLint Player3::Update(const GLfloat fTimeDelta)
{
	if (VIEW::VIEW_3D == m_pGameMgr->Get_View() && m_pGameMgr->Get_Camera()->Get_Move() && !m_bPortal)
		KeyboardInput(fTimeDelta);

	if (VIEW::VIEW_3D == m_pGameMgr->Get_View()) {
		m_pRender->Add_RenderObj(RENDER_ID::REDER_NONAL, this);
		CollideCheck();
	}
	else {
		m_pRender->Add_RenderObj(RENDER_ID::REDER_ALPHA, this);
	}

	CObj::UpdateAABB(m_Player->Get_Matrix(), glm::vec3(2.8f, 3.8f, 3.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, -0.2f, 0.4f)); // 위로 갈때 0.2, 아래로 갈때 -0.2
	return GLint();
}

GLvoid Player3::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_Player->Render();
	CObj::Render();

	return GLvoid();
}


void Player3::KeyboardInput(const GLfloat fTimeDelta)
{
	if (m_pKeyMgr->KeyDown(KEY_ESCAPE)) {
		//need to Release Memory
		exit(0);
	}

	if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
		if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
			m_Player->GetRotate() = glm::vec3(90.0f, -45.0f, 0.0f);
			m_iMoveDir = DIR::LEFT;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(-0.07, 0.0, 0.0));
			}

			m_iMoveDir = DIR::DOWN;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(0.0, -0.07, 0.0));
			}
		}
		else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
			m_Player->GetRotate() = glm::vec3(90.0f, -135.0f, 0.0f);
			m_iMoveDir = DIR::UP;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(0.0, 0.07, 0.0));
			}
			m_iMoveDir = DIR::LEFT;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(-0.07, 0.0, 0.0));
			}
		}
		else {
			m_Player->GetRotate() = glm::vec3(90.0f, -90.0f, 0.0f);
			m_iMoveDir = DIR::LEFT;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(-0.1, 0.0, 0.0));
			}
		}
	}
	else if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
		if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
			m_Player->GetRotate() = glm::vec3(90.0f, 45.0f, 0.0f);
			m_iMoveDir = DIR::RIGHT;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(0.07, 0.0, 0.0));
			}
			m_iMoveDir = DIR::DOWN;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(0.0, -0.07, 0.0));
			}
		}
		else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
			m_Player->GetRotate() = glm::vec3(90.0f, 135.0f, 0.0f);
			m_iMoveDir = DIR::RIGHT;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(0.07, 0.0, 0.0));
			}
			m_iMoveDir = DIR::UP;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(0.0, 0.07, 0.0));
			}
		}
		else {
			m_Player->GetRotate() = glm::vec3(90.0f, 90.0f, 0.0f);
			m_iMoveDir = DIR::RIGHT;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(0.1, 0.0, 0.0));
			}
		}
	}
	else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
		m_Player->GetRotate() = glm::vec3(90.0f, 180.0f, 0.0f);
		m_iMoveDir = DIR::UP;
		if (!m_pGameMgr->Collide(m_iMoveDir)) {
			m_Player->Move(glm::vec3(0.0, 0.1, 0.0));
		}
	}
	else if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
		m_Player->GetRotate() = glm::vec3(90.0f, 0.0f, 0.0f);
		m_iMoveDir = DIR::DOWN;
		if (!m_pGameMgr->Collide(m_iMoveDir)) {
			m_Player->Move(glm::vec3(0.0, -0.1, 0.0));
		}
	}

	if (!m_bCollideB) {

	}
	else if (m_bHoldingB) {
		if (m_pKeyMgr->KeyDown(KEY_A)) {
			list<CObj*>::iterator iter_begin;
			list<CObj*>::iterator iter_end;
			iter_begin = m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).begin();
			iter_end = m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX).end();

			for (; iter_begin != iter_end;) {
				switch (m_iMoveDir) {
				case DIR::LEFT:
					m_bHoldingB = false;
					if (dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z > 0.0) {
						dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = m_Player->GetPos().x - 1.5f;
						dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = -0.25;
						glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
						(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
					}
					break;
				case DIR::RIGHT:
					m_bHoldingB = false;
					if (dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z > 0.0) {
						dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().x = m_Player->GetPos().x + 1.5f;
						dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = -0.25;
						glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
						(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
					}
					break;
				case DIR::UP:
					m_bHoldingB = false;
					if (dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z > 0.0) {
						dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = m_Player->GetPos().y + 1.5f;
						dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = -0.25;
						glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
						(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
					}
					break;
				case DIR::DOWN:
					m_bHoldingB = false;
					if (dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z > 0.0) {
						dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().y = m_Player->GetPos().y - 1.5f;
						dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos().z = -0.25;
						glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
						(*iter_begin)->Get_BB() = { temp.x - 0.5f, temp.x + 0.5f, temp.y + 0.5f, temp.y - 0.5f };
					}
					break;
				default:
					break;
				}
				++iter_begin;
			}
		}
	}
	Player3::Get_BB() = { m_Player->GetPos().x - 0.5f, m_Player->GetPos().x + 0.5f, m_Player->GetPos().y + 0.5f, m_Player->GetPos().y - 0.5f };
}

void Player3::PortalInteract()
{
	if (Collide_OBJ()) {
		if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
			m_bPortal = true;
		}
	}
}

void Player3::CollideCheck()
{
	if (Collide_Monster()) {
		CSoundManager::GetInstance()->Play_Sound(L"playerDead.wav", CSoundManager::DEAD);
		m_pGameMgr->Set_PlayerDie(true);
	}

	PortalInteract();
}

bool Player3::Collide_Monster()
{
	// Collide Check with Whale(Ground) Monster
	for (const auto& m : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_MONSTER1)) {
		if (m_AABB.Intersects(dynamic_cast<Monster*>(m)->Get_AABB())) {
			return true;
		}
	}

	// Collide Check with Bee(Flying) Monster
	for (const auto& m : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_MONSTER2)) {
		if (m_AABB.Intersects(dynamic_cast<Monster*>(m)->Get_AABB())) {
			return true;
		}
	}

	// Collide Check with Spike
	for (const auto& spike : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_SPIKE)) {
		if (m_AABB.Intersects(spike->Get_AABB()))
			return true;
	}

	//Bullet Collide Check
	for (const auto bullet : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BULLET)) {
		if (m_AABB.Intersects(dynamic_cast<CBullet*>(bullet)->Get_AABB())) {
			return true;
		}
	}

	return false;
}

bool Player3::Collide_OBJ()
{
	// Portal Collide Check
	for (const auto portal : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PORTAL)) {
		if (m_AABB.Intersects(dynamic_cast<CPortal*>(portal)->Get_AABB())) {
			return true;
		}
	}

	return false;
}

GLvoid Player3::Release()
{
	SafeDelete(m_Player);
	return GLvoid();
}

Player3* Player3::Create()
{
	Player3* pInstance = new Player3;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}