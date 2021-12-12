#include "stdafx.h"
#include "CBossMonster.h"
#include "CMesh.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"

CBossMonster::CBossMonster()
{
}

CBossMonster::~CBossMonster()
{
}

HRESULT CBossMonster::Initialize()
{
	CObj::Initialize();
	m_pBossMonster = CMesh::Create("../Resource/Monster/podoboo.obj", { 1.0, 1.0, 1.0, 1.0});
	return NOERROR;
}

GLint CBossMonster::Update(const GLfloat fTimeDelta)
{
	m_pRender->Add_RenderObj(REDER_NONAL, this);
	return GLint();
}

GLvoid CBossMonster::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pBossMonster->Render();
	return GLvoid();
}

float CBossMonster::LookPlayerAngle()
{
	return 0.0f;
}

CBossMonster* CBossMonster::Create()
{
	CBossMonster* pInstance = new CBossMonster;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}
