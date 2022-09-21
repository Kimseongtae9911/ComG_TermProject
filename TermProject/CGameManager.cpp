#include"stdafx.h"
#include "CGameManager.h"
#include "CKeyManager.h"
#include "CMesh.h"
#include "CObj.h"
#include "CObject.h"
#include "CCamera.h"
#include "CKeyManager.h"
#include "Monster.h"
#include "Player2.h"
#include "Player3.h"
#include "CPortal.h"
#include "CRenderManager.h"
#include "CSoundManager.h"

IMPLEMENT_SINGLETON(CGameManager)

CGameManager::CGameManager()
{
}

CGameManager::~CGameManager()
{
}

HRESULT CGameManager::Add_GameObj(OBJ_ID eID, CObj* pObj)
{
	if (!pObj)
		return E_FAIL;

	m_ObjLst[static_cast<int>(eID)].emplace_back(pObj);

	return NOERROR;
}

GLvoid CGameManager::Update(const GLfloat fTimeDelta)
{
	for (int i = 0; i < static_cast<int>(OBJ_ID::OBJ_END); ++i)
	{
		for (auto iter_begin = m_ObjLst[i].begin(); iter_begin != m_ObjLst[i].end();)
		{
			if (static_cast<int>(OBJ_ID::OBJ_END) == (*iter_begin)->Update(fTimeDelta))
			{
				SafeDelete(*iter_begin);
				iter_begin = m_ObjLst[i].erase(iter_begin);
			}
			else
				++iter_begin;
		}
	}

	// 2D, 3D View Change
	CheckViewChange();
	ChangeView();

	if (CKeyManager::GetInstance()->KeyDown(KEY_ESCAPE)) {
		exit(0);
	}

	if (m_pCamera)
		m_pCamera->Update(fTimeDelta);

	return GLvoid();
}

GLvoid CGameManager::CheckViewChange()
{
	// Check Key Pressed
	if (Get_Camera() != nullptr)
	{
		if (VIEW::VIEW_3D == m_View && Get_Camera()->Get_Move()) {
			if (CKeyManager::GetInstance()->KeyDown(KEY_F)) {
				m_View = VIEW::VIEW_2D;

				// Rotate Holding Box
				if (dynamic_cast<Player3*>(m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER2)].front())->GetHoldingBox())
					dynamic_cast<CObject*>(dynamic_cast<Player3*>(m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER2)].front())->GetHoldingBox())->Set_Rotate(glm::vec3(90.0f, 180.0f, 0.0f));

				// Player alpha value
				for (auto i : dynamic_cast<Player2*>(m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER1)].front())->Get_Mesh()->GetSMESH())
					for (size_t j = 0; j < i->color.size(); ++j)
						i->color[j][3] = 1.0f;
				for (auto i : dynamic_cast<Player3*>(m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER2)].front())->Get_pMesh()->GetSMESH())
					for (size_t j = 0; j < i->color.size(); ++j)
						i->color[j][3] = 0.3f;
			}
		}
		else if (VIEW::VIEW_2D == m_View && !Get_Camera()->Get_Move()) {
			if (CKeyManager::GetInstance()->KeyDown(KEY_F)) {
				m_View = VIEW::VIEW_3D;				

				// Player alpha value
				for (auto i : dynamic_cast<Player2*>(m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER1)].front())->Get_Mesh()->GetSMESH())
					for (size_t j = 0; j < i->color.size(); ++j)
						i->color[j][3] = 0.3f;
				for (auto i : dynamic_cast<Player3*>(m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER2)].front())->Get_pMesh()->GetSMESH())
					for (size_t j = 0; j < i->color.size(); ++j)
						i->color[j][3] = 1.0f;
			}
		}
	}
}

GLvoid CGameManager::ChangeView()
{
	// Change View
	if (m_View == VIEW::VIEW_3D && Get_Camera()->Get_Move()) {
		CObj* player = m_ObjLst[static_cast<int>(OBJ_ID::OBJ_PLAYER2)].front();
		if (dynamic_cast<Player3*>(player)->Get_HoldingB()) {
			CObj* pBox = dynamic_cast<Player3*>(player)->GetHoldingBox();
			dynamic_cast<CObject*>(pBox)->Get_Mesh()->GetPos().x = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().x;
			dynamic_cast<CObject*>(pBox)->Get_Mesh()->GetPos().y = dynamic_cast<Player3*>(player)->Get_pMesh()->GetPos().y;
		}
	}
}

HRESULT CGameManager::Clear_ObjList()
{
	for (int i = 0; i < static_cast<int>(OBJ_ID::OBJ_END); ++i)
		Clear_Obj((OBJ_ID)i);	

	return NOERROR;
}

HRESULT CGameManager::Clear_Obj(OBJ_ID eID)
{
	for (auto pObj : m_ObjLst[static_cast<int>(eID)])
		SafeDelete(pObj);
	m_ObjLst[static_cast<int>(eID)].clear();

	return NOERROR;
}

HRESULT CGameManager::Add_Camera(CCamera* pCamera)
{
	if (!pCamera)
		return E_FAIL;

	if (m_pCamera)
		SafeDelete(m_pCamera);
	m_pCamera = pCamera;

	return NOERROR;
}

HRESULT CGameManager::Delete_Camera()
{
	if(m_pCamera)
		SafeDelete(m_pCamera);
	return NOERROR;
}

GLvoid CGameManager::Render_Camera()
{
	if (m_pCamera)
		m_pCamera->Render();
	return GLvoid();
}

GLvoid CGameManager::init()
{
	m_View = VIEW::VIEW_2D;
	return GLvoid();
}
