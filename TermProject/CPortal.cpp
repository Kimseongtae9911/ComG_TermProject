#include "stdafx.h"
#include "CPortal.h"
#include "CMesh.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"

CPortal::CPortal()
{
}

CPortal::~CPortal()
{
}

HRESULT CPortal::Initialize(glm::vec3 vPos)
{
	CObj::Initialize();
	m_pPortal = CMesh::Create("../Resource/Portal Door/Portal Door.obj", { 1.0, 1.0, 1.0, 0.3 });
	m_pPortal->GetScale() = glm::vec3(0.15f, 0.15f, 0.15f);
	m_pPortal->GetPos() = vPos;
	//m_pPortal->GetScale().x = -90;
	CPortal::Get_BB() = { m_pPortal->GetPos().x - 1.0f, m_pPortal->GetPos().x  + 1.0f,  m_pPortal->GetPos().y + 1.0f, m_pPortal->GetPos().y - 1.0f};

	return NOERROR;
}

GLint CPortal::Update(const GLfloat fTimeDelta)
{
	if (!bMovingRotate && m_pGameMgr->Get_View() == false)
	{
		++iRotateCount;
		m_pPortal->GetRotate().x += 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	else if (bMovingRotate && m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pPortal->GetRotate().x -= 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	
	cout << "Left - " << CPortal::Get_BB().left << endl;
	cout << "Right - " << CPortal::Get_BB().right << endl;
	cout << "Top - " << CPortal::Get_BB().top << endl;
	cout << "Bottom - " << CPortal::Get_BB().bottom << endl;

	m_pRender->Add_RenderObj(REDER_NONAL, this);
	return GLint();
}

GLvoid CPortal::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pPortal->Render();
	return GLvoid();
}

GLvoid CPortal::Release()
{
	return GLvoid();
}

CPortal* CPortal::Create(glm::vec3 vPos)
{
	CPortal* pInstance = new CPortal;

	if (FAILED(pInstance->Initialize(vPos)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
