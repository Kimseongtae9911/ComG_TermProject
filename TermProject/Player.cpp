#include "stdafx.h"
#include "Player.h"

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
	m_player_2D = CMesh::Create("../Resource/Ghost/ghost.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	//m_player_3D = CMesh::Create("Player_3D", { 1.0, 1.0, 1.0, m_fAlpha });

	return NOERROR;
}

GLint Player::Update(const GLfloat fTimeDelta)
{
	if (m_bView) { // 2D플레이어
		if (m_pKeyMgr->KeyDown(KEY_LEFT) && !m_pKeyMgr->KeyDown(KEY_SPACE)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_RIGHT) && !m_pKeyMgr->KeyDown(KEY_SPACE)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyDown(KEY_LEFT) && !m_pKeyMgr->KeyDown(KEY_RIGHT)) {
			
		}
		else if (m_pKeyMgr->KeyDown(KEY_A)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_F)) {
			m_bView = !m_bView;
		}
		else if (m_pKeyMgr->KeyCombined(KEY_SPACE, KEY_LEFT)) {

		}
		else if (m_pKeyMgr->KeyCombined(KEY_SPACE, KEY_RIGHT)) {

		}
	}
	else { // 3D플레이어
		if (m_pKeyMgr->KeyDown(KEY_LEFT)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_RIGHT)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_UP)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_DOWN)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_A)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_F)) {
			m_bView = !m_bView;
			
		}
	}


	m_pRender-> Add_RenderObj(REDER_NONAL, this);
	return GLint();
}

GLvoid Player::Render()
{
	m_player_2D->Render();
	return GLvoid();
}


Player* Player::Create()
{
	Player* pInstance = new Player;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}