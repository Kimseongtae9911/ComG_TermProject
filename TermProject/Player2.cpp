#include "stdafx.h"
#include "Player2.h"
#include "CMesh.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"
#include "CSceneManager.h"
#include "CCamera.h"
#include "CObject.h"
#include "CSoundManager.h"
#include "Monster.h"
#include "CPortal.h"

Player2::Player2()
{
}

Player2::~Player2()
{
	Release();
}

HRESULT Player2::Initialize()
{
	CObj::Initialize();
	m_Player = CMesh::Create("../Resource/Player2D/Player2D.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	m_Player->GetScale() = glm::vec3(0.3, 0.3, 0.3);
	m_Player->GetTrans() = glm::vec3(-12.0, 0.0, -0.25);

	CObj::UpdateAABB(m_Player->Get_Matrix(), glm::vec3(2.5f, 3.4f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.4f, 0.0f));
	return NOERROR;
}

GLint Player2::Update(const GLfloat fTimeDelta)
{
	if (VIEW::VIEW_2D == m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_Move() && !m_bPortal) { // 2DPlayer
		for (auto i : m_Player->GetSMESH()) {
			for (size_t j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 1.0;
			}
		}
		if (m_pKeyMgr->KeyCombined(KEY_RIGHT, KEY_SPACE)) {
			if (!m_bJump) {
				//m_pSoundMgr->Play_Sound(L"portal.wav", CSoundManager::PORTAL);
				m_pSoundMgr->Play_Sound(L"jump.wav", CSoundManager::JUMP);
				m_bJump = true;
				m_iJumpdir = 1;
				m_fJumpStart = m_Player->GetPos().y;
			}			
		}
		else if (m_pKeyMgr->KeyCombined(KEY_LEFT, KEY_SPACE)) {
			if (!m_bJump) {
				m_pSoundMgr->Play_Sound(L"jump.wav", CSoundManager::JUMP);
				m_bJump = true;
				m_iJumpdir = 1;
				m_fJumpStart = m_Player->GetPos().y;
			}			
		}
		else if ((m_pKeyMgr->KeyDown(KEY_LEFT) || m_pKeyMgr->KeyPressing(KEY_LEFT)) && (!m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_SPACE))) {
			m_iMoveDir = DIR::LEFT;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(-0.1, 0.0, 0.0));
			}
		}
		else if ((m_pKeyMgr->KeyDown(KEY_RIGHT) || m_pKeyMgr->KeyPressing(KEY_RIGHT)) && (!m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_SPACE))) {
			m_iMoveDir = DIR::RIGHT;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(0.1, 0.0, 0.0));
			}
		}
		else if (m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_LEFT) && !m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			if (!m_bJump) {
				m_pSoundMgr->Play_Sound(L"jump.wav", CSoundManager::JUMP);
				m_bJump = true;
				m_iJumpdir = 1;
				m_fJumpStart = m_Player->GetPos().y;
			}
		}
		else if (m_pKeyMgr->KeyDown(KEY_F5)) {
			m_pGameMgr->Set_DebugMode(!m_pGameMgr->Get_DebugMode());
		}

		if (m_bJump) {
			if (Player2::m_iJumpdir == 1) {
				if (m_pGameMgr->JumpCollide(m_iJumpdir)) {
					m_iJumpdir = -1;
				}
				else {
					m_Player->Move(glm::vec3(0.0, 0.2, 0.0));
					m_fJumpPos += 0.1f;
				}
				if (m_fJumpPos >= 2.0f) {
					m_iJumpdir = -1;
				}
			}
			else {
				if (m_pGameMgr->JumpCollide(m_iJumpdir)) {
					m_iJumpdir = 1;
					m_fJumpPos = 0.0f;
					m_fJumpStart = 0.0f;
					m_bJump = false;
				}
				else {
					m_Player->Move(glm::vec3(0.0, -0.2, 0.0));
					m_fJumpPos -= 0.1f;
				}
				if (m_fJumpPos < 0.0f) {
					m_iJumpdir = 1;
					m_bJump = false;
					m_Player->Move(glm::vec3(0.0, m_fJumpStart - m_Player->GetPos().y, 0.0));
				}
			}
			Get_BB() = { m_Player->GetPos().x - 0.5f, m_Player->GetPos().x + 0.5f, m_Player->GetPos().y + 1.0f, m_Player->GetPos().y };
		}
		if (!m_pGameMgr->JumpCollide(m_iJumpdir) && !m_bJump) {
 			if (m_Player->GetPos().y > 0.01) {
				m_Player->GetPos().y -= 0.2f;
				m_fJumpPos = 0.0f;
				m_fJumpStart = 0.0f;
			}

			if (m_Player->GetPos().y < 0) {
				m_Player->GetPos().y = 0;
				m_fJumpPos = 0.0f;
				m_fJumpStart = 0.0f;
			}
		}
		Get_BB() = { m_Player->GetPos().x - 0.5f, m_Player->GetPos().x + 0.5f, m_Player->GetPos().y + 1.0f, m_Player->GetPos().y };
		m_pRender->Add_RenderObj(RENDER_ID::REDER_NONAL, this);
	}
	else if(VIEW::VIEW_3D == m_pGameMgr->Get_View()){
		for (auto i : m_Player->GetSMESH()) {
			for (size_t j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 0.3f;
			}
		}
		m_pRender->Add_RenderObj(RENDER_ID::REDER_ALPHA, this);
	}
	else {
		m_pRender->Add_RenderObj(RENDER_ID::REDER_NONAL, this);
	}
	if (m_pKeyMgr->KeyDown(KEY_ESCAPE)) {
		exit(0);
	}

	if(VIEW::VIEW_2D == m_pGameMgr->Get_View())
		CollideCheck();

	CObj::UpdateAABB(m_Player->Get_Matrix(), glm::vec3(2.5f, 3.4f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.4f, 0.0f));

	return GLint();
}

GLvoid Player2::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_Player->Render();

	CObj::Render();

	return GLvoid();
}

Player2* Player2::Create()
{
	Player2* pInstance = new Player2;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}

void Player2::PortalInteract()
{
	if (Collide_OBJ()) {
		if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
			m_bPortal = true;
		}
	}
}

void Player2::CollideCheck()
{
	if (Collide_Monster()) {
		CSoundManager::GetInstance()->Play_Sound(L"playerDead.wav", CSoundManager::DEAD);
		m_pGameMgr->Set_PlayerDie(true);
	}

	PortalInteract();
}

bool Player2::Collide_Monster()
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

	return false;
}

bool Player2::Collide_OBJ()
{
	// Key Collide Check
	for (const auto key : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY)) {
		if (m_AABB.Intersects(dynamic_cast<CObject*>(key)->Get_AABB())) {
			m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).erase(find(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).begin(), m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).end(), key));
			return false;
		}
	}

	// Portal Collide Check
	for (const auto portal : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PORTAL)) {
		if (m_AABB.Intersects(dynamic_cast<CPortal*>(portal)->Get_AABB())) {
			return true;
		}
	}

	return false;
}

GLvoid Player2::Release()
{
	SafeDelete(m_Player);
	return GLvoid();
}
