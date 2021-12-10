#include "CStage1.h"
#include "Player3.h"
#include "Player.h"

#include "CCamera.h"

CStage1::CStage1()
{
}

CStage1::~CStage1()
{
}

HRESULT CStage1::Initialize()
{
	CScene::Initialize();
	m_pGameMgr->Add_Camera(CCamera::Create(glm::vec3(0.f, 0.f, 5.f), glm::vec3(0.f, 0.0f, 0.f), glm::vec3(0.f, 1.f, 0.f)));
	CObj* pObj = nullptr;
	pObj = Player::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_PLAYER1, pObj)))
		return E_FAIL;
	pObj = Player3::Create();
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_PLAYER1, pObj)))
		return E_FAIL;
	return NOERROR;
}

GLint CStage1::Update(const GLfloat fTimeDelta)
{
	m_pGameMgr->Update(fTimeDelta);
	return GLint();
}

GLvoid CStage1::Render()
{
	m_pRenderMgr->Render_Object();
	return GLvoid();
}

GLvoid CStage1::Release()
{
	m_pGameMgr->Clear_ObjList();
	return GLvoid();
}

CStage1* CStage1::Create()
{
	CStage1* pInstance = new CStage1();
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
