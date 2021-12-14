#include "stdafx.h"
#include "CEnding.h"
#include "CObj.h"
#include "CBackImage.h"
#include "CGameManager.h"
#include "CRenderManager.h"
#include "CSoundManager.h"


CEnding::CEnding()
{
}

CEnding::~CEnding()
{
	Release();
}

HRESULT CEnding::Initialize()
{
	CScene::Initialize();
	//m_pGameMgr->Add_Camera(CCamera::Create(glm::vec3(0.0f, 6.5f, 30.f), glm::vec3(0.f, 6.5f, 0.f), glm::vec3(0.f, 1.f, 0.f)));
	CObj* pObj = nullptr;

	pObj = CBackImage::Create("", "../Resource/UI/Back/Ending.png");
	if (FAILED(m_pGameMgr->Add_GameObj(OBJ_UI, pObj)))
		return E_FAIL;

	m_pSoundMgr->Stop_All();
	m_pSoundMgr->Play_BGM(L"Ending.mp3");
	return NOERROR;
}

GLint CEnding::Update(const GLfloat fTimeDelta)
{
	m_pGameMgr->Update(fTimeDelta);
	return GLint();
}

GLvoid CEnding::Render()
{

	m_pRenderMgr->Render_Object();
	return GLvoid();
}

GLvoid CEnding::Release()
{
	m_pGameMgr->Clear_ObjList();
	return GLvoid();
}

CEnding* CEnding::Create()
{
	CEnding* pInstance = new CEnding();
	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
