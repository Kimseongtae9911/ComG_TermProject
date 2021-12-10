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
	m_player = CMesh::Create("../Resource/Player3D/Player3D.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	//m_player->GetScale() = glm::vec3(0.3, 0.3, 0.3);
	//m_player = CMesh::Create("../Resource/cube2.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	
	return NOERROR;
}

GLint Player3::Update(const GLfloat fTimeDelta)
{
	//cout << m_player->GetPos().x << endl;
	//cout << m_player->GetPos().y << endl;
	//cout << m_player->GetPos().z << endl;
	if (!m_bView) { // 3DPlayer
		if (m_pKeyMgr->KeyPressing(KEY_LEFT)) {
			m_player->Move(glm::vec3(-0.1, 0.0, 0.0));
		}
		else if (m_pKeyMgr->KeyPressing(KEY_RIGHT)) {
			m_player->Move(glm::vec3(0.1, 0.0, 0.0));
		}
		else if (m_pKeyMgr->KeyPressing(KEY_UP)) {
			m_player->Move(glm::vec3(0.0, 0.0, -0.1));
		}
		else if (m_pKeyMgr->KeyPressing(KEY_DOWN)) {
			m_player->Move(glm::vec3(0.0, 0.0, 0.1));
		}
		else if (m_pKeyMgr->KeyDown(KEY_A)) {
			//interaction
		}
	}
	
	if (m_pKeyMgr->KeyDown(KEY_F)) {
		m_bView = !m_bView;
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
	m_player->Render();
	return GLvoid();
}


Player3* Player3::Create()
{
	Player3* pInstance = new Player3;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}