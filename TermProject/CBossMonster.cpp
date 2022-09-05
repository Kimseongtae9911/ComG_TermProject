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
	if (VIEW::VIEW_3D == m_pGameMgr->Get_View() && m_pGameMgr->Get_Camera()->Get_Move())
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
	if (VIEW::VIEW_2D == m_pGameMgr->Get_View())
	{
		if (!bMoveUpDown && m_pBossMonster->GetPos().y >= 4.45f)
		{
			bMoveUpDown = !bMoveUpDown;
		}
		else if (bMoveUpDown && m_pBossMonster->GetPos().y <= 0.f)
		{
			bMoveUpDown = !bMoveUpDown;
		}
		if (!bMoveUpDown)
		{
			if (m_pBossMonster->GetPos().y + 8.5 + 0.05 <= 13.0f) {
				m_pBossMonster->GetPos().y += 0.05f;
			}
		}
		else
			m_pBossMonster->GetPos().y -= 0.05f;
		

		fTime += fTimeDelta;
	}
	else
	{
		f3DTime += fTimeDelta;
	}
	if (!bMovingRotate && VIEW::VIEW_3D == m_pGameMgr->Get_View())
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
	else if (bMovingRotate && VIEW::VIEW_2D == m_pGameMgr->Get_View())
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

	
	if (fTime >= 3 && VIEW::VIEW_2D == m_pGameMgr->Get_View())
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
			fHeight = 11.f;
			break;
		default:
			break;
		}
		if (m_bBullet) {
			CObj* pObj = CBullet::Create(glm::vec3(m_pBossMonster->GetPos().x, fHeight, 0));
			if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_BULLET, pObj)))
				return E_FAIL;
		}
		fTime = 0;
	}
	else if (f3DTime >= 5 && VIEW::VIEW_3D == m_pGameMgr->Get_View())
	{
		CObj* pObj = Monster::Create("../Resource/Monster/bee.obj", m_pBossMonster->GetPos() + glm::vec3(-1.0f, 0.0f, 0.0f), glm::vec3(0.0002, 0.0002, 0.0002));
		pObj->Set_OBJID(OBJ_ID::OBJ_MONSTER2);
		if (FAILED(m_pGameMgr->Add_GameObj(OBJ_ID::OBJ_MONSTER2, pObj)))
			return E_FAIL;
		f3DTime = 0;
	}
	m_pRender->Add_RenderObj(RENDER_ID::RENDER_BOSS, this);

	CObj::UpdateAABB(m_pBossMonster->Get_Matrix(), glm::vec3(30.5f, 35.0f, 30.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 3.5f, 0.0f));
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
	vecPlayer3dPos = dynamic_cast<Player3*>(m_pGameMgr->Get_Obj(OBJ_ID::OBJ_PLAYER2).front())->Get_pMesh()->GetPos();
	//fRatio = abs(vecPlayer3dPos.x - m_pMonster->GetPos().x) / abs(vecPlayer3dPos.z - m_pMonster->GetPos().z);
	//cout << fRatio << endl;
	float dAngle = atan((vecPlayer3dPos.x - m_pBossMonster->GetPos().x) / (vecPlayer3dPos.y - m_pBossMonster->GetPos().y)) * 180 / PI;
	//cout << dAngle << endl;
	if (m_pBossMonster->GetPos().y <= vecPlayer3dPos.y)
	{
		if (m_pBossMonster->GetPos().x <= vecPlayer3dPos.x) // 1
		{
			//cout << 180 - dAngle << endl;
			return 180.f - dAngle;
		}

		else //   4
		{
			//cout << 180 - dAngle << endl;
			return 180.f - dAngle;
		}
	}
	else
	{
		if (m_pBossMonster->GetPos().x <= vecPlayer3dPos.x) //2
		{
			//cout << -dAngle << endl;
			return static_cast<float>(-dAngle);
		}

		else // 3
		{
			//cout << 360 - dAngle << endl;
			return 360.f - dAngle;
		}

	}
}

GLvoid CBossMonster::Render()
{
	m_pShaderLoader->Use_Shader("Default");
	m_pGameMgr->Render_Camera();
	m_pBossMonster->Render();
	CObj::Render();

	return GLvoid();
}


CBossMonster* CBossMonster::Create()
{
	CBossMonster* pInstance = new CBossMonster;
	if (FAILED(pInstance->Initialize()))
		SafeDelete(pInstance);
	return pInstance;
}
