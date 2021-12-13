#include "stdafx.h"
#include "Player2.h"
#include "CMesh.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"
#include "CCamera.h"
#include "CObject.h"

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
	return NOERROR;
}

GLint Player2::Update(const GLfloat fTimeDelta)
{
	if (m_pGameMgr->Get_View() && !m_pGameMgr->Get_Camera()->Get_Move() && !m_bPortal) { // 2DPlayer
		for (auto i : m_Player->GetSMESH()) {
			for (int j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 1.0;
			}
		}
		if (m_pKeyMgr->KeyCombined(KEY_RIGHT, KEY_SPACE)) {
			if (!m_bJump) {
				m_bJump = true;
				m_iJumpdir = 1;
				m_fJumpStart = m_Player->GetPos().y;
			}			
		}
		else if (m_pKeyMgr->KeyCombined(KEY_LEFT, KEY_SPACE)) {
			if (!m_bJump) {
				m_bJump = true;
				m_iJumpdir = 1;
				m_fJumpStart = m_Player->GetPos().y;
			}			
		}
		else if ((m_pKeyMgr->KeyDown(KEY_LEFT) || m_pKeyMgr->KeyPressing(KEY_LEFT)) && (!m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_SPACE))) {
			m_iMoveDir = LEFT;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(-0.1, 0.0, 0.0));
			}
		}
		else if ((m_pKeyMgr->KeyDown(KEY_RIGHT) || m_pKeyMgr->KeyPressing(KEY_RIGHT)) && (!m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_SPACE))) {
			m_iMoveDir = RIGHT;
			if (!m_pGameMgr->Collide(m_iMoveDir)) {
				m_Player->Move(glm::vec3(0.1, 0.0, 0.0));
			}
		}
		else if (m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_LEFT) && !m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			if (!m_bJump) {
				m_bJump = true;
				m_iJumpdir = 1;
				m_fJumpStart = m_Player->GetPos().y;
			}
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
			if (Collide_Spike()) {
				cout << "Die" << endl;
			}
			if (m_Player->GetPos().y < 0) {
				m_Player->GetPos().y = 0;
				m_fJumpPos = 0.0f;
				m_fJumpStart = 0.0f;
			}
			//Get_BB() = { m_Player->GetPos().x - 0.5f, m_Player->GetPos().x + 0.5f, m_Player->GetPos().y + 1.0f, m_Player->GetPos().y };
		}
		Get_BB() = { m_Player->GetPos().x - 0.5f, m_Player->GetPos().x + 0.5f, m_Player->GetPos().y + 1.0f, m_Player->GetPos().y };
		m_pRender->Add_RenderObj(REDER_NONAL, this);
	}
	else if(!m_pGameMgr->Get_View()){
		for (auto i : m_Player->GetSMESH()) {
			for (int j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 0.3;
			}
		}
		m_pRender->Add_RenderObj(REDER_ALPHA, this);
	}
	else {
		m_pRender->Add_RenderObj(REDER_NONAL, this);
	}
	if (m_pKeyMgr->KeyDown(KEY_ESCAPE)) {
		//need to Release Memory
		exit(0);
	}
	
	if (Collide_Spike()) {
		cout << "Die" << endl;
	}
	
	return GLint();
}

GLvoid Player2::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_Player->Render();
	return GLvoid();
}

Player2* Player2::Create()
{
	Player2* pInstance = new Player2;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}

bool Player2::Collide_Spike()
{
	list<CObj*>::iterator iter_begin;
	list<CObj*>::iterator iter_end;
	iter_begin = m_pGameMgr->Get_Obj(OBJ_SPIKE).begin();
	iter_end = m_pGameMgr->Get_Obj(OBJ_SPIKE).end();

	for (; iter_begin != iter_end;) {
		glm::vec3 temp = dynamic_cast<CObject*>((*iter_begin))->Get_Rotate()->GetPos();
		BB OBJ_BB = {temp.x - 0.75, temp.x + 0.75, temp.y + 0.5, temp.y - 0.5};
		BB player_BB = Player2::Get_BB();
		if (OBJ_BB.left > player_BB.right || OBJ_BB.right < player_BB.left || OBJ_BB.top < player_BB.bottom || OBJ_BB.bottom > player_BB.top);
		else {			
			return true;
		}

		++iter_begin;
	}
	return false;
}