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
	m_pMonster->GetPos() = vPos;
	LookPlayerAngle();
	return NOERROR;
}

GLint Monster::Update(const GLfloat fTimeDelta)
{
	if (!bMovingRotate && m_pGameMgr->Get_View() == false)
	{
		++iRotateCount;
		m_pMonster->GetRotate().x += 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	else if (bMovingRotate && m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pMonster->GetRotate().x -= 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	LookPlayerAngle();

	if (!m_pGameMgr->Get_View())
	{
		//m_pMonster->GetPos().y = 0.0f;
		//if (LookPlayerAngle() >= iLookRotCount)
		//{
		//	++iLookRotCount;

		//	m_pMonster->GetRotate().y += 5.5;

		//}
		//else
		//{
		//	--iLookRotCount;

		//	m_pMonster->GetRotate().y -= 5.5;

		//}
		float f = LookPlayerAngle();
		if (f >= m_pMonster->GetRotate().y)
		{
			if (f - m_pMonster->GetRotate().y <= m_pMonster->GetRotate().y + 360 - f /*&& f >= m_pMonster->GetRotate().y*/)
			{
				m_pMonster->GetRotate().y += 5.5;
			}
			else
			{
				m_pMonster->GetRotate().y -= 5.5;
			}
		}
		else
		{
			if (f + 360 - m_pMonster->GetRotate().y <= m_pMonster->GetRotate().y - f/* && f <= m_pMonster->GetRotate().y*/)
			{
				m_pMonster->GetRotate().y += 5.5;
			}
			else
			{
				m_pMonster->GetRotate().y -= 5.5;
			}
		}
		if (m_pMonster->GetRotate().y >= 360)
		{
			m_pMonster->GetRotate().y -= 360;
		}
		else if (m_pMonster->GetRotate().y <= 0)
		{
			m_pMonster->GetRotate().y += 360;
		}
		//if (vecPlayer3dPos.x - m_pMonster->GetPos().x >= 0)
		//	m_pMonster->GetPos().x += 0.02;
		//else
		//	m_pMonster->GetPos().x -= 0.02;
		//if (vecPlayer3dPos.y - m_pMonster->GetPos().y >= 0) 
		//{
		//	m_pMonster->GetPos().y += 0.02;
		//}
		//else 
		//{
		//	m_pMonster->GetPos().y -= 0.02;
		//}
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
	vecPlayer3dPos = dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_PLAYER2).front())->Get_pMesh()->GetPos();
	//fRatio = abs(vecPlayer3dPos.x - m_pMonster->GetPos().x) / abs(vecPlayer3dPos.z - m_pMonster->GetPos().z);
	//cout << fRatio << endl;
	double dAngle = atan((vecPlayer3dPos.x - m_pMonster->GetPos().x) / (vecPlayer3dPos.y - m_pMonster->GetPos().y)) * 180/ PI;
	//cout << dAngle << endl;
	if (m_pMonster->GetPos().y <= vecPlayer3dPos.y)
	{
		if (m_pMonster->GetPos().x <= vecPlayer3dPos.x) // 1
		{
			//cout << 180 - dAngle << endl;
			return 180 - dAngle;
		}
			
		else //   4
		{
			//cout << 180 - dAngle << endl;
			return 180 - dAngle;
		}
	}
	else
	{
		if (m_pMonster->GetPos().x <= vecPlayer3dPos.x) //2
		{
			//cout << -dAngle << endl;
			return -dAngle;
		}
			
		else // 3
		{
			//cout << 360 - dAngle << endl;
			return 360 - dAngle;
		}
			
	}
}

Monster* Monster::Create(glm::vec3 vPos)
{
	Monster* pInstance = new Monster;
	if (FAILED(pInstance->Initialize(vPos)))
		SafeDelete(pInstance);
	return pInstance;
}
