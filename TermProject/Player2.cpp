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
	m_Player->GetTrans() = glm::vec3(-12.0, 0.0f, -0.25);

	for (size_t i = 0; i < m_AABB.GetCornersBox().size(); ++i) {
		m_vecMAABBColor.push_back(glm::vec3(0.f, 1.f, 0.f));
	}

	for (int i = 0; i < 4; ++i) {
		glGenVertexArrays(1, &m_Vao[i]);
		glGenBuffers(2, m_Vbo[i]);

		glBindVertexArray(m_Vao[i]);

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[i][0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_AABB_M[i].GetCornersBox().size(), &m_AABB_M[i].GetCornersBox().front(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[i][1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vecMAABBColor.size(), &m_vecMAABBColor.front(), GL_STATIC_DRAW);
	}

	CObj::UpdateAABB(m_Player->Get_Matrix(), glm::vec3(3.5f, 3.4f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.4f, 0.0f));
	return NOERROR;
}

GLint Player2::Update(const GLfloat fTimeDelta)
{
	if (VIEW::VIEW_2D == m_pGameMgr->Get_View()) {
		m_pRender->Add_RenderObj(RENDER_ID::REDER_NONAL, this);
		CollideCheck();
	}
	else if (VIEW::VIEW_3D == m_pGameMgr->Get_View()) {
		m_pRender->Add_RenderObj(RENDER_ID::REDER_ALPHA, this);
	}
	if (VIEW::VIEW_2D == m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_Move() && !m_bPortal) {		
		KeyboardInput(fTimeDelta);
		JumpProcess(fTimeDelta);
	}

	CObj::UpdateAABB(m_Player->Get_Matrix(), glm::vec3(3.5f, 3.4f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.4f, 0.0f));
	UpdateBB();

	return GLint();
}

GLvoid Player2::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_Player->Render();

	CObj::Render();

	if (m_pGameMgr->Get_DebugMode() && VIEW::VIEW_2D == m_pGameMgr->Get_View()) {
		GLuint program = CShader::GetInstance()->Use_Shader("BoundingBox");

		int viewLoc = glGetUniformLocation(program, "viewTransform");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_pGameMgr->Get_Camera()->Get_View()));

		if (VIEW::VIEW_2D == m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_MovingCam())
		{
			int ProjLoc = glGetUniformLocation(program, "projectionTransform");// 직각
			glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_pGameMgr->Get_Camera()->Get_Ortho()));
		}

		for (int j = 0; j < 4; ++j) {
			GLuint iLocation = glGetUniformLocation(program, "modelTransform");
			glUniformMatrix4fv(iLocation, 1, GL_FALSE, value_ptr(m_AABB_M[j].TransMatrix));

			for (int i = 0; i < 2; ++i)
			{
				glEnableVertexAttribArray(i);
				glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[j][i]);
				glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			}

			glLineWidth(3.0f);

			glDrawArrays(GL_LINE_LOOP, 0, 4);
			glDrawArrays(GL_LINE_LOOP, 4, 4);
			glDrawArrays(GL_LINE_LOOP, 8, 4);
			glDrawArrays(GL_LINE_LOOP, 16, 4);
			glDrawArrays(GL_LINE_LOOP, 20, 4);
			glDrawArrays(GL_LINE_LOOP, 24, 4);


			for (int i = 0; i < 2; ++i)
				glDisableVertexAttribArray(i);
		}
	}

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
	// Jump Input
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
	else if (m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_LEFT) && !m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
		if (!m_bOnAir) {
			m_pSoundMgr->Play_Sound(L"jump.wav", CSoundManager::JUMP);
			m_bOnAir = true;
		}
	} // Left, Right Input
	else if ((m_pKeyMgr->KeyDown(KEY_LEFT) || m_pKeyMgr->KeyPressing(KEY_LEFT)) && (!m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_SPACE))) {
		m_iMoveDir = -1;
		m_Player->Move(glm::vec3(m_iMoveDir * SPEED_2D * fTimeDelta, 0.0, 0.0));
		if (Collide_DIR(DIR::LEFT)) {
			m_Player->Move(glm::vec3(-m_iMoveDir * SPEED_2D * fTimeDelta, 0.0, 0.0));
		}
		Collide_DIR(DIR::DOWN);
	}
	else if (m_pKeyMgr->KeyPressing(KEY_LEFT) && m_pKeyMgr->KeyPressing(KEY_SPACE)) {
		m_iMoveDir = -1;
		m_Player->Move(glm::vec3(m_iMoveDir * SPEED_2D * fTimeDelta, 0.0, 0.0));
		if (Collide_DIR(DIR::LEFT)) {
			m_Player->Move(glm::vec3(-m_iMoveDir * SPEED_2D * fTimeDelta, 0.0, 0.0));
		}
		Collide_DIR(DIR::DOWN);
	}
	else if ((m_pKeyMgr->KeyDown(KEY_RIGHT) || m_pKeyMgr->KeyPressing(KEY_RIGHT)) && (!m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_SPACE))) {
		m_iMoveDir = 1;
		m_Player->Move(glm::vec3(m_iMoveDir * SPEED_2D * fTimeDelta, 0.0, 0.0));
		if (Collide_DIR(DIR::RIGHT)) {
			m_Player->Move(glm::vec3(-m_iMoveDir * SPEED_2D * fTimeDelta, 0.0, 0.0));
		}
		Collide_DIR(DIR::DOWN);
	}
	else if (m_pKeyMgr->KeyPressing(KEY_RIGHT) && m_pKeyMgr->KeyPressing(KEY_SPACE)) {
		m_iMoveDir = 1;
		m_Player->Move(glm::vec3(m_iMoveDir * SPEED_2D * fTimeDelta, 0.0, 0.0));
		if (Collide_DIR(DIR::RIGHT)) {
			m_Player->Move(glm::vec3(-m_iMoveDir * SPEED_2D * fTimeDelta, 0.0, 0.0));
		}
		Collide_DIR(DIR::DOWN);
	}
	else if (m_pKeyMgr->KeyDown(KEY_F5)) {
		m_pGameMgr->Set_DebugMode(!m_pGameMgr->Get_DebugMode());
	}
}

void Player2::JumpProcess(const GLfloat fTimeDelta)
{
	if (m_bOnAir || m_bFalling) {
		m_Player->Move(glm::vec3(0.0f, m_fJumpSpeed * fTimeDelta, 0.0f));
		m_fJumpSpeed -= GRAVITY * fTimeDelta;
		Collide_DIR(DIR::UP);
	}
	
	if ((m_bOnAir && Collide_DIR(DIR::DOWN) && m_fJumpSpeed < 0.f) || (m_bFalling && Collide_DIR(DIR::DOWN))) {
		m_bOnAir = false;
		m_bFalling = false;
		m_fJumpSpeed = JUMP_SPEED;
		m_Player->GetPos() = glm::vec3(m_Player->GetPos().x, m_pCollideObj->Get_AABB().TransCenter.y + m_pCollideObj->Get_AABB().TransExtent.y, m_Player->GetPos().z);
	}
}

void Player2::CollideCheck()
{
	if (Collide_Monster()) {
		CSoundManager::GetInstance()->Play_Sound(L"playerDead.wav", CSoundManager::DEAD);
		m_pGameMgr->Set_PlayerDie(true);
	}

	Collide_OBJ();
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

void Player2::Collide_OBJ()
{
	// Key Collide Check
	for (const auto& key : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY)) {
		if (m_AABB.Intersects(dynamic_cast<CObject*>(key)->Get_AABB())) {
			m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).erase(find(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).begin(), m_pGameMgr->Get_Obj(OBJ_ID::OBJ_KEY).end(), key));
			return;
		}
	}

	// Portal Collide Check
	for (const auto& portal : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PORTAL)) {
		if (m_AABB.Intersects(dynamic_cast<CPortal*>(portal)->Get_AABB())) {
			if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
				m_bPortal = true;
				m_pSoundMgr->Play_Sound(L"portal_in.mp3", CSoundManager::PORTAL);
				return;
			}
		}
	}

	
}

bool Player2::Collide_DIR(const DIR dir)
{
	if (DIR::LEFT == dir) {
		//wall
		for (const auto& wall : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_MAP)) {
			if (m_AABB_M[0].Intersects(dynamic_cast<CObject*>(wall)->Get_AABB())) {
				m_dirCollideDir = DIR::LEFT;
				m_pCollideObj = wall;
				return true;
			}
		}
		// box
		for (const auto& box : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX)) {
			if (m_AABB_M[0].Intersects(box->Get_AABB())) {
				m_dirCollideDir = DIR::LEFT;
				m_pCollideObj = box;
				return true;
			}
		}
	}
	else if (DIR::RIGHT == dir) {
		//wall
		for (const auto& wall : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_MAP)) {
			if (m_AABB_M[2].Intersects(dynamic_cast<CObject*>(wall)->Get_AABB())) {
				m_dirCollideDir = DIR::RIGHT;
				m_pCollideObj = wall;
				return true;
			}
		}
		// box
		for (const auto& box : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX)) {
			if (m_AABB_M[2].Intersects(box->Get_AABB())) {
				m_dirCollideDir = DIR::RIGHT;
				m_pCollideObj = box;
				return true;
			}
		}
	}
	else if (DIR::DOWN == dir) {
		//wall
		for (const auto& wall : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_MAP)) {
			if (m_AABB_M[3].Intersects(dynamic_cast<CObject*>(wall)->Get_AABB())) {
				m_dirCollideDir = DIR::DOWN;
				m_pCollideObj = wall;
				return true;
			}
		}
		// box
		for (const auto& box : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX)) {
			if (m_AABB_M[3].Intersects(box->Get_AABB())) {
				m_dirCollideDir = DIR::DOWN;
				m_pCollideObj = box;
				return true;
			}
		}
		if (!m_bOnAir && !m_bFalling) {
			m_bFalling = true;
			m_fJumpSpeed = 0.0f;
		}

	}
	else if (DIR::UP == dir) {
		//wall
		for (const auto& wall : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_MAP)) {
			if (m_AABB_M[1].Intersects(dynamic_cast<CObject*>(wall)->Get_AABB())) {
				m_dirCollideDir = DIR::UP;
				m_pCollideObj = wall;
				if (m_fJumpSpeed > 0.f)
					m_fJumpSpeed = 0.0f;
				return true;
			}
		}
		// box
		for (const auto& box : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX)) {
			if (m_AABB_M[1].Intersects(box->Get_AABB())) {
				m_dirCollideDir = DIR::UP;
				m_pCollideObj = box;
				if (m_fJumpSpeed > 0.f)
					m_fJumpSpeed = 0.0f;
				return true;
			}
		}
	}

	m_pCollideObj = nullptr;
	m_dirCollideDir = DIR::NONE;

	return false;
}

GLvoid Player2::Release()
{
	SafeDelete(m_Player);
	return GLvoid();
}

GLvoid Player2::UpdateBB()
{
	glm::vec3 T;
	for (int i = 0; i < 4; ++i) {
		switch (i) {
		case 0: // Left
			T = glm::vec3(-0.4f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.4f, 0.0f);
			m_AABB_M[i].Transform(m_Player->Get_Matrix(), glm::vec3(1.0f, 3.4f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), T);
			break;
		case 1: // Top
			T = glm::vec3(0.f, 0.4f, 0.0f) + glm::vec3(0.0f, 0.4f, 0.0f);
			m_AABB_M[i].Transform(m_Player->Get_Matrix(), glm::vec3(3.5f, 1.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), T);
			break;
		case 2: // Right
			T = glm::vec3(0.4f, 0.0f, 0.0f) + glm::vec3(0.0f, 0.4f, 0.0f);
			m_AABB_M[i].Transform(m_Player->Get_Matrix(), glm::vec3(1.0f, 3.4f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), T);
			break;
		case 3: // Bottom
			T = glm::vec3(0.0f, -0.4f, 0.0f) + glm::vec3(0.0f, 0.4f, 0.0f);
			m_AABB_M[i].Transform(m_Player->Get_Matrix(), glm::vec3(3.5f, 1.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), T);
			break;
		}
		
		m_AABB_M[i].Update(m_AABB_M[i].GetCorners()[5], m_AABB_M[i].GetCorners()[3]);
	}

	return GLvoid();
}
