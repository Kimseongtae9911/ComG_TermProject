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
	m_player_2D = CMesh::Create("Player_2D", { 1.0, 1.0, 1.0, m_fAlpha });
	m_player_3D = CMesh::Create("Player_3D", { 1.0, 1.0, 1.0, m_fAlpha });

	return NOERROR;
}

GLint Player::Update(const GLfloat fTimeDelta)
{
	if (m_bPlayer) { // 2D플레이어
		if (m_pKeyMgr->KeyDown(KEY_LEFT) && !m_pKeyMgr->KeyDown(KEY_SPACE)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_RIGHT) && !m_pKeyMgr->KeyDown(KEY_SPACE)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_SPACE) && !m_pKeyMgr->KeyDown(KEY_LEFT) && !m_pKeyMgr->KeyDown(KEY_RIGHT)) {
			
		}
		else if (m_pKeyMgr->KeyDown(KEY_A)) {

		}
		else if (m_pKeyMgr->KeyDown(KEY_F)) {

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

		}
	}
	return GLint();
}

GLvoid Player::Render()
{
	return GLvoid();
}