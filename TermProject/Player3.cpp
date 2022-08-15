#include "stdafx.h"
#include "Player3.h"
#include "CMesh.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"
#include "CCamera.h"
#include "CObject.h"

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
	
	
	return NOERROR;
}

GLint Player3::Update(const GLfloat fTimeDelta)
{
	if (!m_pGameMgr->Get_View() && m_pGameMgr->Get_Camera()->Get_Move() && !m_bPortal) { // 3DPlayer
		for (auto i : m_Player->GetSMESH()) {
			for (size_t j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 1.0;
			}
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
			if (m_pKeyMgr->KeyDown(KEY_A)) {
				if (m_bIn_Portal) {
					m_bPortal = true;
				}
			}
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
		Player3::Get_BB() = { m_Player->GetPos().x - 0.5f, m_Player->GetPos().x + 0.5f, m_Player->GetPos().y + 0.5f, m_Player->GetPos().y - 0.5f};
		m_pRender->Add_RenderObj(RENDER_ID::REDER_NONAL, this);
	}
	else if (m_pGameMgr->Get_View()){
		for (auto i : m_Player->GetSMESH()) {
			for (size_t j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 0.3f;
			}
		}
		Player3::Get_BB() = { m_Player->GetPos().x - 0.5f, m_Player->GetPos().x + 0.5f, m_Player->GetPos().y + 0.5f, m_Player->GetPos().y - 0.5f };
		m_pRender->Add_RenderObj(RENDER_ID::REDER_ALPHA, this);
	}
	else {
		m_pRender->Add_RenderObj(RENDER_ID::REDER_NONAL, this);
	}
	if (m_pKeyMgr->KeyDown(KEY_ESCAPE)) {
		//need to Release Memory
		exit(0);
	}
	return GLint();
}

GLvoid Player3::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_Player->Render();
	return GLvoid();
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