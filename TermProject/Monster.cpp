#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
	CObj::Release();
}

HRESULT Monster::Initialize()
{
	return E_NOTIMPL;
}

GLint Monster::Update(const GLfloat fTimeDelta)
{
	if (m_bView) { //2D
		if (m_pKeyMgr->KeyDown(KEY_F)) {
			m_bView = !m_bView;
		}
	}
	else { //3D
		if (m_pKeyMgr->KeyDown(KEY_F)) {
			m_bView = !m_bView;
		}
	}
	

	m_pRender->Add_RenderObj(REDER_NONAL, this);
	return GLint();
}

GLvoid Monster::Render()
{
	return GLvoid();
}
