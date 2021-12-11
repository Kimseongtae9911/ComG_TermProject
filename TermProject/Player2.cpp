#include "stdafx.h"
#include "Player2.h"
#include "CMesh.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"
#include "CCamera.h"

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
	//m_Player = CMesh::Create("../Resource/Monster/podoboo.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	m_Player->GetScale() = glm::vec3(0.3, 0.3, 0.3);
	m_Player->GetTrans() = glm::vec3(-12.0, 0.0, 0.0);
	return NOERROR;
}

GLint Player2::Update(const GLfloat fTimeDelta)
{
	if (m_pGameMgr->Get_View()) { // 2DPlayer
		for (auto i : m_Player->GetSMESH()) {
			for (int j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 1.0;
			}
		}
		if (m_pKeyMgr->KeyCombined(KEY_RIGHT, KEY_SPACE)) {
			if (!Player2::m_bJump) {
				Player2::m_bJump = true;
				Player2::m_iJumpdir = 1;
				Player2::m_fJumpStart = m_Player->GetPos().y;
			}
			m_Player->Move(glm::vec3(0.1, 0.0, 0.0));
		}
		if (m_pKeyMgr->KeyCombined(KEY_LEFT, KEY_SPACE)) {
			if (!Player2::m_bJump) {
				Player2::m_bJump = true;
				Player2::m_iJumpdir = 1;
				Player2::m_fJumpStart = m_Player->GetPos().y;
			}
			m_Player->Move(glm::vec3(-0.1, 0.0, 0.0));
		}
		else if ((m_pKeyMgr->KeyDown(KEY_LEFT) || m_pKeyMgr->KeyPressing(KEY_LEFT)) && (!m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_SPACE))) {
			m_Player->Move(glm::vec3(-0.1, 0.0, 0.0));
		}
		else if ((m_pKeyMgr->KeyDown(KEY_RIGHT) || m_pKeyMgr->KeyPressing(KEY_RIGHT)) && (!m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_SPACE))) {
			m_Player->Move(glm::vec3(0.1, 0.0, 0.0));
		}
		else if (m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyPressing(KEY_LEFT) && !m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			if (!Player2::m_bJump) {
				Player2::m_bJump = true;
				Player2::m_iJumpdir = 1;
				Player2::m_fJumpStart = m_Player->GetPos().y;
			}
		}
		else if (m_pKeyMgr->KeyDown(KEY_A)) {

		}
	}
	else {
		for (auto i : m_Player->GetSMESH()) {
			for (int j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 0.1;
			}
		}
	}
	if (m_pKeyMgr->KeyDown(KEY_ESCAPE)) {
		//need to Release Memory
		exit(0);
	}
	if (Player2::m_bJump) {
		if (Player2::m_iJumpdir == 1) {
			m_Player->Move(glm::vec3(0.0, 0.2, 0.0));

			Player2::m_fJumpPos += 0.1f;
			if (m_fJumpPos >= 2.0f) {
				Player2::m_iJumpdir = -1;
			}
		}
		else {
			m_Player->Move(glm::vec3(0.0, -0.2, 0.0));

			Player2::m_fJumpPos -= 0.1f;
			if (m_fJumpPos <= 0.0f) {
				Player2::m_iJumpdir = 1;
				Player2::m_bJump = false;
				m_Player->Move(glm::vec3(0.0, Player2::m_fJumpStart - m_Player->GetPos().y, 0.0));
			}
		}
	}

	m_pRender-> Add_RenderObj(REDER_NONAL, this);
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