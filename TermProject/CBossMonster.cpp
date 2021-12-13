#include "stdafx.h"
#include "CBossMonster.h"
#include"CBullet.h"
#include "CMesh.h"
#include "Player3.h"
#include "Monster.h"
#include "CKeyManager.h"
#include "CRenderManager.h"
#include "CShader.h"
#include "CGameManager.h"
#include "CCamera.h"


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
	m_pBossMonster->GetPos() = glm::vec3(5.0f, 0, 0);
	m_pBossMonster->GetScale() = glm::vec3(0.2f, 0.2f, 0.2f);
	m_pBossMonster->GetRotate().y = -20.f;
	return NOERROR;
}

GLint CBossMonster::Update(const GLfloat fTimeDelta)
{
	if (!m_pGameMgr->Get_View() && m_pGameMgr->Get_Camera()->Get_Move())
	{
		float f = LookPlayerAngle();
		if (f >= 0 && f <= 22.5)
		{
			if (f >= 0 && f <= 22.5 && m_pBossMonster->GetRotate().y != 360 && m_pBossMonster->GetRotate().y <= 45)
			{
				m_pBossMonster->GetRotate().y -= 2.5;
				if (m_pBossMonster->GetRotate().y < 0)
					m_pBossMonster->GetRotate().y = 360;
			}
		}
		else if (f >= 360 - 22.5 && f <= 360)
		{
			if (f >= 360 - 22.5 && f <= 360 && m_pBossMonster->GetRotate().y != 0 && m_pBossMonster->GetRotate().y >= 360 - 45)
			{
				m_pBossMonster->GetRotate().y += 2.5;
				if (m_pBossMonster->GetRotate().y > 360)
					m_pBossMonster->GetRotate().y = 0;
			}
		}
		//if (f >= 360 - 22.5 && f <= 22.5)
		//{
		//	if (f >= 0 && f <= 22.5 && m_pBossMonster->GetRotate().y != 0 && m_pBossMonster->GetRotate().y <= 45)
		//	{
		//		m_pBossMonster->GetRotate().y -= 2.5;
		//		if (m_pBossMonster->GetRotate().y < 0)
		//			m_pBossMonster->GetRotate().y = 360;
		//	}
		//	else if (f >= 360 - 22.5 && f <= 360 && m_pBossMonster->GetRotate().y != 0 && m_pBossMonster->GetRotate().y >= 360 - 45)
		//	{
		//		m_pBossMonster->GetRotate().y += 2.5;
		//		if (m_pBossMonster->GetRotate().y > 360)
		//			m_pBossMonster->GetRotate().y = 0;
		//	}
		//}
		else if (f >= 22.5 && f <= 67.5)
		{
			if (f >= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 45)
			{
				m_pBossMonster->GetRotate().y += 2.5;
				if (m_pBossMonster->GetRotate().y >= 45)
					m_pBossMonster->GetRotate().y = 45;
			}
			else if (f <= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 45)
			{
				m_pBossMonster->GetRotate().y -= 2.5;
				if (m_pBossMonster->GetRotate().y <= 45)
					m_pBossMonster->GetRotate().y = 45;
			}
		}
		else if (f >= 67.5 && f <= 112.5)
		{
			if (f >= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 90)
			{
				m_pBossMonster->GetRotate().y += 2.5;
				if (m_pBossMonster->GetRotate().y >= 90)
					m_pBossMonster->GetRotate().y = 90;
			}
			else if (f <= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 90)
			{
				m_pBossMonster->GetRotate().y -= 2.5;
				if (m_pBossMonster->GetRotate().y <= 90)
					m_pBossMonster->GetRotate().y = 90;
			}
		}
		else if (f >= 112.5 && f <= 157.5)
		{
			if (f >= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 135)
			{
				m_pBossMonster->GetRotate().y += 2.5;
				if (m_pBossMonster->GetRotate().y >= 135)
					m_pBossMonster->GetRotate().y = 135;
			}
			else if (f <= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 135)
			{
				m_pBossMonster->GetRotate().y -= 2.5;
				if (m_pBossMonster->GetRotate().y <= 135)
					m_pBossMonster->GetRotate().y = 135;
			}
		}
		else if (f >= 157.5 && f <= 202.5)
		{
			if (f >= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 180)
			{
				m_pBossMonster->GetRotate().y += 2.5;
				if (m_pBossMonster->GetRotate().y >= 180)
					m_pBossMonster->GetRotate().y = 180;
			}
			else if (f <= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 180)
			{
				m_pBossMonster->GetRotate().y -= 2.5;
				if (m_pBossMonster->GetRotate().y <= 180)
					m_pBossMonster->GetRotate().y = 180;
			}
		}
		else if (f >= 202.5 && f <= 247.5)
		{
			if (f >= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 225)
			{
				m_pBossMonster->GetRotate().y += 2.5;
				if (m_pBossMonster->GetRotate().y >= 225)
					m_pBossMonster->GetRotate().y = 225;
			}
			else if (f <= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 225)
			{
				m_pBossMonster->GetRotate().y -= 2.5;
				if (m_pBossMonster->GetRotate().y <= 225)
					m_pBossMonster->GetRotate().y = 225;
			}
		}
		else if (f >= 247.5 && f <= 292.5)
		{
			if (f >= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 270)
			{
				m_pBossMonster->GetRotate().y += 2.5;
				if (m_pBossMonster->GetRotate().y >= 270)
					m_pBossMonster->GetRotate().y = 270;
			}
			else if (f <= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 270)
			{
				m_pBossMonster->GetRotate().y -= 2.5;
				if (m_pBossMonster->GetRotate().y <= 270)
					m_pBossMonster->GetRotate().y = 270;
			}
		}
		else if (f >= 292.5 && f <= 337.5)
		{
		if (f >= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 315)
		{
			m_pBossMonster->GetRotate().y += 2.5;
			if (m_pBossMonster->GetRotate().y >= 315)
				m_pBossMonster->GetRotate().y = 315;
		}
		else if (f <= m_pBossMonster->GetRotate().y && m_pBossMonster->GetRotate().y != 315)
		{
			m_pBossMonster->GetRotate().y -= 2.5;
			if (m_pBossMonster->GetRotate().y <= 315)
				m_pBossMonster->GetRotate().y = 315;
		}
		}

		//if (f >= m_pBossMonster->GetRotate().y)
		//{
		//	if (f - m_pBossMonster->GetRotate().y <= m_pBossMonster->GetRotate().y + 360 - f /*&& f >= m_pMonster->GetRotate().y*/)
		//	{
		//		m_pBossMonster->GetRotate().y += 3.5;
		//	}
		//	else
		//	{
		//		m_pBossMonster->GetRotate().y -= 3.5;
		//	}
		//}
		//else
		//{
		//	if (f + 360 - m_pBossMonster->GetRotate().y <= m_pBossMonster->GetRotate().y - f/* && f <= m_pMonster->GetRotate().y*/)
		//	{
		//		m_pBossMonster->GetRotate().y += 3.5;
		//	}
		//	else
		//	{
		//		m_pBossMonster->GetRotate().y -= 3.5;
		//	}
		//}
		//if (m_pBossMonster->GetRotate().y >= 360)
		//{
		//	m_pBossMonster->GetRotate().y -= 360;
		//}
		//else if (m_pBossMonster->GetRotate().y <= 0)
		//{
		//	m_pBossMonster->GetRotate().y += 360;
		//}
	}
	if (m_pGameMgr->Get_View())
	{
		if (!bMoveUpDown && m_pBossMonster->GetPos().y >= 5.f)
		{
			bMoveUpDown = !bMoveUpDown;
		}
		else if (bMoveUpDown && m_pBossMonster->GetPos().y <= 0.f)
		{
			bMoveUpDown = !bMoveUpDown;
		}
		if(!bMoveUpDown)
			m_pBossMonster->GetPos().y += 0.05f;
		else
			m_pBossMonster->GetPos().y -= 0.05f;
		

		fTime += fTimeDelta;
	}
	else
	{
		f3DTime += fTimeDelta;
	}
	if (!bMovingRotate && m_pGameMgr->Get_View() == false)
	{
		++iRotateCount;
		m_pBossMonster->GetRotate().x += 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			m_pBossMonster->GetRotate().y += 20.f;
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}
	else if (bMovingRotate && m_pGameMgr->Get_View())
	{
		++iRotateCount;
		m_pBossMonster->GetRotate().x -= 90.f / 80.f;
		if (iRotateCount >= 80)
		{
			m_pBossMonster->GetRotate().y -= 20.f;
			iRotateCount = 0;
			bMovingRotate = !bMovingRotate;
		}
	}

	
	if (fTime >= 3 && m_pGameMgr->Get_View())
	{
		int Height = RandHeight();
		float fHeight = 0;
		switch (Height)
		{
		case 0:
			fHeight = 4.5f;
			break;
		case 1:
			fHeight = 8.f;
			break;
		case 2:
			fHeight = 12.f;
			break;
		default:
			break;
		}
		CObj* pObj = CBullet::Create(glm::vec3(m_pBossMonster->GetPos().x,fHeight,0));
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_BULLET, pObj)))
			return E_FAIL;
		cout << "11" << endl;
		fTime = 0;
	}
	else if (f3DTime >= 5 && !m_pGameMgr->Get_View())
	{
		//CObj* pObj = Monster::Create("../Resource/Monster/bee.obj", m_pBossMonster->GetPos() + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0002, 0.0002, 0.0002), 1);
		//if (FAILED(m_pGameMgr->Add_GameObj(OBJ_MONSTER2, pObj)))
		//	return E_FAIL;
		f3DTime = 0;
	}
	m_pRender->Add_RenderObj(REDER_NONAL, this);
	return GLint();
}


int CBossMonster::RandHeight()
{
	std::random_device rd;
	std::default_random_engine dre(rd());
	std::uniform_int_distribution<int> uid(0, 2);
	int iRand = uid(dre);
	return iRand;
}

float CBossMonster::LookPlayerAngle()
{
	vecPlayer3dPos = dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_PLAYER2).front())->Get_pMesh()->GetPos();
	//fRatio = abs(vecPlayer3dPos.x - m_pMonster->GetPos().x) / abs(vecPlayer3dPos.z - m_pMonster->GetPos().z);
	//cout << fRatio << endl;
	double dAngle = atan((vecPlayer3dPos.x - m_pBossMonster->GetPos().x) / (vecPlayer3dPos.y - m_pBossMonster->GetPos().y)) * 180 / PI;
	//cout << dAngle << endl;
	if (m_pBossMonster->GetPos().y <= vecPlayer3dPos.y)
	{
		if (m_pBossMonster->GetPos().x <= vecPlayer3dPos.x) // 1
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
		if (m_pBossMonster->GetPos().x <= vecPlayer3dPos.x) //2
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

GLvoid CBossMonster::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pBossMonster->Render();
	return GLvoid();
}


CBossMonster* CBossMonster::Create()
{
	CBossMonster* pInstance = new CBossMonster;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}
