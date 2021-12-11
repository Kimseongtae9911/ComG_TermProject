#include "stdafx.h"
#include "Player3.h"
#include "CMesh.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"

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
	m_Player->Move(glm::vec3(12.0, 0.0, 0.0));
	
	return NOERROR;
}

GLint Player3::Update(const GLfloat fTimeDelta)
{
	if (!m_pGameMgr->Get_View()) { // 3DPlayer
		for (auto i : m_Player->GetSMESH()) {
			for (int j = 0; j < i->color.size(); ++j) {
				i->color[j][3] = 1.0;
			}
		}
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			m_Player->Move(glm::vec3(-0.1, 0.0, 0.0));
		}
		else if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			m_Player->Move(glm::vec3(0.1, 0.0, 0.0));
		}
		else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
			m_Player->Move(glm::vec3(0.0, 0.0, -0.1));
		}
		else if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
			m_Player->Move(glm::vec3(0.0, 0.0, 0.1));
		}
		else if (m_pKeyMgr->KeyDown(KEY_A)) {
			//interaction
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