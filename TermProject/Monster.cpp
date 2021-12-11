#include "stdafx.h"
#include "Monster.h"
#include "CMesh.h"
#include "Player3.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

HRESULT Monster::Initialize(glm::vec3 vPos)
{
	CObj::Initialize();
	m_pMonster = CMesh::Create("../Resource/Monster/podoboo.obj", { 1.0, 1.0, 1.0, m_fAlpha });
	m_pMonster->GetScale() = glm::vec3(0.03, 0.03, 0.03);
	//m_pMonster->GetParent() = 
	m_pMonster->GetPos() = vPos;
	return NOERROR;
}

GLint Monster::Update(const GLfloat fTimeDelta)
{
	if (!bMovingRotate && m_pGameMgr->Get_View() == false)
	{
		++iRotateCount;
		//m_pMonster->GetRotate().x += 90.f / 80.f;
		m_pMonster->GetRotate().x += 0.7f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	else if (bMovingRotate && m_pGameMgr->Get_View())
	{
		++iRotateCount;
		//m_pMonster->GetRotate().x -= 90.f / 80.f;
		m_pMonster->GetRotate().x -= 0.7f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	m_pRender->Add_RenderObj(REDER_NONAL, this);
	return GLint();
}

GLvoid Monster::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pMonster->Render();
	return GLvoid();
}

float Monster::LookPlayerAngle()
{
	glm::vec3 vecPlayer3dPos = dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_PLAYER2).front())->Get_pMesh()->GetPos();

	return 0.0f;
}

Monster* Monster::Create(glm::vec3 vPos)
{
	Monster* pInstance = new Monster;
	if (FAILED(pInstance->Initialize(vPos)))
		SafeDelete(pInstance);
	return pInstance;
}
