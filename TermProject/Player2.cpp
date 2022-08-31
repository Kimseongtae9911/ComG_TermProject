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
#include "CBullet.h"

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
	m_fJumpSpeed = JUMP_SPEED;

	CObj::UpdateAABB(m_Player->Get_Matrix(), glm::vec3(2.5f, 3.4f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.4f, 0.0f));
	return NOERROR;
}

GLint Player2::Update(const GLfloat fTimeDelta)
{
	if (VIEW::VIEW_2D == m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_Move() && !m_bPortal) {		
		KeyboardInput(fTimeDelta);
		JumpProcess(fTimeDelta);
	}

	if (VIEW::VIEW_2D == m_pGameMgr->Get_View()) {
		m_pRender->Add_RenderObj(RENDER_ID::REDER_NONAL, this);
		CollideCheck();
	}
	else if (VIEW::VIEW_3D == m_pGameMgr->Get_View()) {
		m_pRender->Add_RenderObj(RENDER_ID::REDER_ALPHA, this);
	}

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

void Player2::KeyboardInput(const GLfloat fTimeDelta)
{
	if (m_pKeyMgr->KeyCombined(KEY_RIGHT, KEY_SPACE)) {
		if (!m_bOnAir) {
			m_pSoundMgr->Play_Sound(L"jump.wav", CSoundManager::JUMP);
			m_bOnAir = true;
		}
	}
	else if (m_pKeyMgr->KeyCombined(KEY_LEFT, KEY_SPACE)) {
		if (!m_bOnAir) {
			m_pSoundMgr->Play_Sound(L"jump.wav", CSoundManager::JUMP);
			m_bOnAir = true;
		}
	}
	else if ((m_pKeyMgr->KeyDown(KEY_LEFT) || m_pKeyMgr->KeyPressing(KEY_LEFT)) && (!m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_SPACE))) {
		m_dirMoveDir = DIR::LEFT;
		m_iMoveDir = -1;
		if (!m_pGameMgr->Collide(m_dirMoveDir)) {
			m_Player->Move(glm::vec3(m_iMoveDir * SPEED_2D, 0.0, 0.0));
		}
	}
	else if ((m_pKeyMgr->KeyDown(KEY_RIGHT) || m_pKeyMgr->KeyPressing(KEY_RIGHT)) && (!m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_SPACE))) {
		m_dirMoveDir = DIR::RIGHT;
		m_iMoveDir = 1;
		if (!m_pGameMgr->Collide(m_dirMoveDir)) {
			m_Player->Move(glm::vec3(m_iMoveDir * SPEED_2D, 0.0, 0.0));
		}
	}
	else if (m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_LEFT) && !m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
		if (!m_bOnAir) {
			m_pSoundMgr->Play_Sound(L"jump.wav", CSoundManager::JUMP);
			m_bOnAir = true;
		}
	}
	else if (m_pKeyMgr->KeyPressing(KEY_LEFT) && m_pKeyMgr->KeyPressing(KEY_SPACE)) {
		m_dirMoveDir = DIR::LEFT;
		m_iMoveDir = -1;
		if (!m_pGameMgr->Collide(m_dirMoveDir)) {
			m_Player->Move(glm::vec3(m_iMoveDir * SPEED_2D, 0.0, 0.0));
		}
	}
	else if (m_pKeyMgr->KeyPressing(KEY_RIGHT) && m_pKeyMgr->KeyPressing(KEY_SPACE)) {
		m_dirMoveDir = DIR::RIGHT;
		m_iMoveDir = 1;
		if (!m_pGameMgr->Collide(m_dirMoveDir)) {
			m_Player->Move(glm::vec3(m_iMoveDir * SPEED_2D, 0.0, 0.0));
		}
	}
	else if (m_pKeyMgr->KeyDown(KEY_F5)) {
		m_pGameMgr->Set_DebugMode(!m_pGameMgr->Get_DebugMode());
	}

	if (m_pKeyMgr->KeyDown(KEY_ESCAPE)) {
		exit(0);
	}
}

void Player2::JumpProcess(const GLfloat fTimeDelta)
{
	if (m_bOnAir) {
		m_Player->Move(glm::vec3(0.0f, m_fJumpSpeed * fTimeDelta, 0.0f));
		if (m_fJumpSpeed > 0.0f)
			m_fJumpSpeed -= GRAVITY;
		else {
			m_fJumpSpeed -= GRAVITY;
		}
	}
	if (m_bOnAir && m_AABB.CollideDir == DIR::DOWN) {
		m_bOnAir = false;
		m_Player->Move(glm::vec3(0.0f, -m_fJumpSpeed * fTimeDelta + (dynamic_cast<CObject*>(m_pCollideObj)->Get_AABB().TransCenter.y + dynamic_cast<CObject*>(m_pCollideObj)->Get_AABB().TransExtent.y) - (m_AABB.TransCenter.y - m_AABB.TransExtent.y), 0.0f));
		m_fJumpSpeed = JUMP_SPEED;
		m_AABB.CollideDir = DIR::NONE;
	}
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

	//Bullet Collide Check
	for (const auto bullet : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BULLET)) {
		if (m_AABB.Intersects(dynamic_cast<CBullet*>(bullet)->Get_AABB())) {
			return true;
		}
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

	// Map(wall) Collide Check
	for (const auto wall : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_MAP)) {
		if (m_AABB.Intersects(dynamic_cast<CObject*>(wall)->Get_AABB())) {
			m_pCollideObj = wall;
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
