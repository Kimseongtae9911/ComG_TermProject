#include "stdafx.h"
#include "Player3.h"
#include "CMesh.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"
#include "CCamera.h"

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
	m_Player->GetTrans() = glm::vec3(12.0, 1.5, -0.25);
	
	
	return NOERROR;
}

GLint Player3::Update(const GLfloat fTimeDelta)
{
	if (!m_pGameMgr->Get_View() && m_pGameMgr->Get_Camera()->Get_Move()) { // 3DPlayer
		for (auto i : m_Player->GetSMESH()) {
			for (int j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 1.0;
			}
		}
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
				m_Player->GetRotate() = glm::vec3(90.0f, -45.0f, 0.0f);
				m_Player->Move(glm::vec3(-0.07, -0.07, 0.0));
			}
			else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
				m_Player->GetRotate() = glm::vec3(90.0f, -135.0f, 0.0f);
				m_Player->Move(glm::vec3(-0.07, 0.07, 0.0));
			}
			else {
				m_Player->GetRotate() = glm::vec3(90.0f, -90.0f, 0.0f);
				m_Player->Move(glm::vec3(-0.1, 0.0, 0.0));
			}
		}
		else if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
				m_Player->GetRotate() = glm::vec3(90.0f, 45.0f, 0.0f);
				m_Player->Move(glm::vec3(0.07, -0.07, 0.0));
			}
			else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
				m_Player->GetRotate() = glm::vec3(90.0f, 135.0f, 0.0f);
				m_Player->Move(glm::vec3(0.07, 0.07, 0.0));
			}
			else {
				m_Player->GetRotate() = glm::vec3(90.0f, 90.0f, 0.0f);
				m_Player->Move(glm::vec3(0.1, 0.0, 0.0));
			}
		}
		else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
			m_Player->GetRotate() = glm::vec3(90.0f, 180.0f, 0.0f);
			m_Player->Move(glm::vec3(0.0, 0.1, 0.0));
		}
		else if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
			m_Player->GetRotate() = glm::vec3(90.0f, 0.0f, 0.0f);
			m_Player->Move(glm::vec3(0.0, -0.1, 0.0));
		}
		else if (m_pKeyMgr->KeyDown(KEY_A)) {
			//interaction
		}
		Player3::Get_BB() = { m_Player->GetPos().x - 0.5f, m_Player->GetPos().x + 0.5f, m_Player->GetPos().y, m_Player->GetPos().y - 1.0f };
	}
	else if (m_pGameMgr->Get_View()){
		for (auto i : m_Player->GetSMESH()) {
			for (int j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 0.1;
			}
		}
		Player3::Get_BB() = { m_Player->GetPos().x - 0.5f, m_Player->GetPos().x + 0.5f, m_Player->GetPos().y, m_Player->GetPos().y - 1.0f };
	}
	if (m_pKeyMgr->KeyDown(KEY_ESCAPE)) {
		//need to Release Memory
		exit(0);
	}
	m_pRender->Add_RenderObj(REDER_NONAL, this);
	return GLint();
}

GLvoid Player3::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_Player->Render();
	return GLvoid();
}


Player3* Player3::Create()
{
	Player3* pInstance = new Player3;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}