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
	UpdateBB();
	return GLint();
}

GLvoid Player3::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_Player->Render();
	CObj::Render();

	if (m_pGameMgr->Get_DebugMode() && VIEW::VIEW_3D == m_pGameMgr->Get_View()) {
		GLuint program = CShader::GetInstance()->Use_Shader("BoundingBox");

		int viewLoc = glGetUniformLocation(program, "viewTransform");
		glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_pGameMgr->Get_Camera()->Get_View()));

		if (VIEW::VIEW_2D == m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_MovingCam())
		{
			int ProjLoc = glGetUniformLocation(program, "projectionTransform");// 직각
			glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_pGameMgr->Get_Camera()->Get_Ortho()));
		}

		for (int j = 0; j < 1; ++j) {
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


void Player3::KeyboardInput(const GLfloat fTimeDelta)
{
	if (m_pKeyMgr->KeyDown(KEY_ESCAPE)) {
		//need to Release Memory
		exit(0);
	}

	if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
		if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
			m_Player->GetRotate() = glm::vec3(90.0f, -45.0f, 0.0f);
			//Left
			m_Player->Move(glm::vec3(-SPEED_3D_DI * fTimeDelta, 0.0, 0.0));
			if (Collide_OBJ()) {
				m_Player->Move(glm::vec3(SPEED_3D_DI * fTimeDelta, 0.0, 0.0));
			}
			if (m_bCollideB && !Collide_OBJ())
				dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(-SPEED_3D_DI * fTimeDelta, 0.0, 0.0));

			//Down
			m_Player->Move(glm::vec3(0.0, -SPEED_3D_DI * fTimeDelta, 0.0));
			if (Collide_OBJ()) {
				m_Player->Move(glm::vec3(0.0, SPEED_3D_DI * fTimeDelta, 0.0));
			}
			if (m_bCollideB && !Collide_OBJ())
				dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(0.0, -SPEED_3D_DI * fTimeDelta, 0.0));
		}
		else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
			m_Player->GetRotate() = glm::vec3(90.0f, -135.0f, 0.0f);
			//Left
			m_Player->Move(glm::vec3(-SPEED_3D_DI * fTimeDelta, 0.0, 0.0));
			if (Collide_OBJ()) {
				m_Player->Move(glm::vec3(SPEED_3D_DI * fTimeDelta, 0.0, 0.0));
			}
			if (m_bCollideB && !Collide_OBJ())
				dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(-SPEED_3D_DI * fTimeDelta, 0.0, 0.0));

			//Up
			m_Player->Move(glm::vec3(0.0, SPEED_3D_DI * fTimeDelta, 0.0));
			if (Collide_OBJ()) {
				m_Player->Move(glm::vec3(0.0, -SPEED_3D_DI * fTimeDelta, 0.0));
			}
			if (m_bCollideB && !Collide_OBJ())
				dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(0.0, SPEED_3D_DI * fTimeDelta, 0.0));
		}
		else {
			m_Player->GetRotate() = glm::vec3(90.0f, -90.0f, 0.0f);
			//Left
			m_Player->Move(glm::vec3(-SPEED_3D * fTimeDelta, 0.0, 0.0));
			if (Collide_OBJ()) {
				m_Player->Move(glm::vec3(SPEED_3D * fTimeDelta, 0.0, 0.0));
			}
			if (m_bCollideB && !Collide_OBJ())
				dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(-SPEED_3D * fTimeDelta, 0.0, 0.0));
		}
	}
	else if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
		if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
			m_Player->GetRotate() = glm::vec3(90.0f, 45.0f, 0.0f);
			//Right
			m_Player->Move(glm::vec3(SPEED_3D_DI * fTimeDelta, 0.0, 0.0));
			if (Collide_OBJ()) {
				m_Player->Move(glm::vec3(-SPEED_3D_DI * fTimeDelta, 0.0, 0.0));
			}
			if (m_bCollideB && !Collide_OBJ())
				dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(SPEED_3D_DI * fTimeDelta, 0.0, 0.0));

			//Down
			m_Player->Move(glm::vec3(0.0, -SPEED_3D_DI * fTimeDelta, 0.0));
			if (Collide_OBJ()) {
				m_Player->Move(glm::vec3(0.0, SPEED_3D_DI * fTimeDelta, 0.0));
			}
			if (m_bCollideB && !Collide_OBJ())
				dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(0.0, -SPEED_3D_DI * fTimeDelta, 0.0));
		}
		else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
			m_Player->GetRotate() = glm::vec3(90.0f, 135.0f, 0.0f);
			//Right
			m_Player->Move(glm::vec3(SPEED_3D_DI * fTimeDelta, 0.0, 0.0));
			if (Collide_OBJ()) {
				m_Player->Move(glm::vec3(-SPEED_3D_DI * fTimeDelta, 0.0, 0.0));
			}
			if (m_bCollideB && !Collide_OBJ())
				dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(SPEED_3D_DI * fTimeDelta, 0.0, 0.0));

			//Up
			m_Player->Move(glm::vec3(0.0, SPEED_3D_DI * fTimeDelta, 0.0));
			if (Collide_OBJ()) {
				m_Player->Move(glm::vec3(0.0, -SPEED_3D_DI * fTimeDelta, 0.0));
			}
			if (m_bCollideB && !Collide_OBJ())
				dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(0.0, SPEED_3D_DI * fTimeDelta, 0.0));
		}
		else {
			//Right
			m_Player->GetRotate() = glm::vec3(90.0f, 90.0f, 0.0f);
			m_Player->Move(glm::vec3(SPEED_3D * fTimeDelta, 0.0, 0.0));
			if (Collide_OBJ()) {
				m_Player->Move(glm::vec3(-SPEED_3D * fTimeDelta, 0.0, 0.0));
			}
			if (m_bCollideB && !Collide_OBJ())
				dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(SPEED_3D * fTimeDelta, 0.0, 0.0));
		}
	}
	else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
		m_Player->GetRotate() = glm::vec3(90.0f, 180.0f, 0.0f);
		//Up
		m_Player->Move(glm::vec3(0.0, SPEED_3D * fTimeDelta, 0.0));
		if (Collide_OBJ()) {
			m_Player->Move(glm::vec3(0.0, -SPEED_3D * fTimeDelta, 0.0));
		}
		if (m_bCollideB && !Collide_OBJ())
			dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(0.0, SPEED_3D * fTimeDelta, 0.0));
	}
	else if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
		m_Player->GetRotate() = glm::vec3(90.0f, 0.0f, 0.0f);
		//Down
		m_Player->Move(glm::vec3(0.0, -SPEED_3D * fTimeDelta, 0.0));
		if (Collide_OBJ()) {
			m_Player->Move(glm::vec3(0.0, SPEED_3D * fTimeDelta, 0.0));
		}
		if (m_bCollideB && !Collide_OBJ())
			dynamic_cast<CObject*>(m_pCollideObj)->Get_Mesh()->Move(glm::vec3(0.0, -SPEED_3D * fTimeDelta, 0.0));
	}
	else if (m_pKeyMgr->KeyDown(KEY_F5)) {
		m_pGameMgr->Set_DebugMode(!m_pGameMgr->Get_DebugMode());
	}

	if (m_bHoldingB) {
		/*if (m_pKeyMgr->KeyDown(KEY_A)) {
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
		}*/
	}
}

void Player3::CollideCheck()
{
	if (Collide_Monster()) {
		CSoundManager::GetInstance()->Play_Sound(L"playerDead.wav", CSoundManager::DEAD);
		m_pGameMgr->Set_PlayerDie(true);
	}

	Collide_OBJ();
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
			if (CKeyManager::GetInstance()->KeyDown(KEY_A)) {
				m_bPortal = true;
				return false;
			}
		}
	}

	// wall
	for (const auto& wall : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_MAP)) {
		if (m_AABB_M[0].Intersects(dynamic_cast<CObject*>(wall)->Get_AABB())) {
			m_pCollideObj = wall;
			return true;
		}
	}
	// box
	for (const auto& box : m_pGameMgr->Get_Obj(OBJ_ID::OBJ_BOX)) {
		if (m_AABB_M[0].Intersects(box->Get_AABB())) {
			m_pCollideObj = box;
			m_bCollideB = true;
			return false;
		}
	}

	m_pCollideObj = nullptr;
	m_bCollideB = false;

	return false;
}

GLvoid Player3::Release()
{
	SafeDelete(m_Player);
	return GLvoid();
}

GLvoid Player3::UpdateBB()
{
	glm::vec3 T;
	for (int i = 0; i < 1; ++i) {
		switch (i) {
		case 0:
			T = glm::vec3(0.0f, 0.5f, 0.8f);
			m_AABB_M[i].Transform2(m_Player->Get_Matrix(), glm::vec3(4.0f, 3.0f, 2.5f), glm::vec3(0.0f, 0.0f, 0.0f), T);
			break;
		}

		m_AABB_M[i].Update(m_AABB_M[i].GetCorners()[5], m_AABB_M[i].GetCorners()[3]);
	}

	return GLvoid();
}

Player3* Player3::Create()
{
	Player3* pInstance = new Player3;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}