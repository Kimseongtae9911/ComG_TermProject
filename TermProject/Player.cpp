#include "stdafx.h"
#include "Player.h"
#include "CMesh.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"

Player::Player()
{
}

Player::~Player()
{
	Release();
}

HRESULT Player::Initialize()
{
	CObj::Initialize();
	//m_player = CMesh::Create("../Resource/Ghost/ghost.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	//m_player = CMesh::Create("../Resource/blinky/blinky.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	m_player = CMesh::Create("../Resource/test/test.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	//m_player = CMesh::Create("../Resource/test/test.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	//m_player_3D = CMesh::Create("Player_3D", { 1.0, 1.0, 1.0, m_fAlpha });

	return NOERROR;
}

GLint Player::Update(const GLfloat fTimeDelta)
{
	if (m_bView) { // 2DPlayer
		if (m_pKeyMgr->KeyDown(KEY_LEFT) && !m_pKeyMgr->KeyDown(KEY_SPACE)) {
			m_player->Move(glm::vec3(-5.0, 0.0, 0.0));
		}
		else if (m_pKeyMgr->KeyDown(KEY_RIGHT) && !m_pKeyMgr->KeyDown(KEY_SPACE)) {
			m_player->Move(glm::vec3(5.0, 0.0, 0.0));
		}
		else if (m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyDown(KEY_LEFT) && !m_pKeyMgr->KeyDown(KEY_RIGHT)) {
			
		}
		else if (m_pKeyMgr->KeyDown(KEY_A)) {

		}
		else if (m_pKeyMgr->KeyCombined(KEY_SPACE, KEY_LEFT)) {

		}
		else if (m_pKeyMgr->KeyCombined(KEY_SPACE, KEY_RIGHT)) {

		}
	}

	if (m_pKeyMgr->KeyDown(KEY_F)) {
		m_bView = !m_bView;
	}
	if (m_pKeyMgr->KeyDown(KEY_ESCAPE)) {
		//need to Release Memory
		exit(0);
	}
	m_pRender-> Add_RenderObj(REDER_NONAL, this);
	return GLint();
}

GLvoid Player::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_player->Render();
	return GLvoid();
}


Player* Player::Create()
{
	Player* pInstance = new Player;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}