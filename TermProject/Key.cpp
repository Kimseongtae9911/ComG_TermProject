#include "Key.h"

Key::Key()
{
}

Key::~Key()
{
	CObj::Release();
}

HRESULT Key::Initialize()
{
	return E_NOTIMPL;
}

GLint Key::Update(const GLfloat fTimeDelta)
{
	if (m_bView) {

	}
	else {

	}
	return GLint();
}

GLvoid Key::Render()
{
	return GLvoid();
}
