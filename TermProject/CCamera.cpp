#include "stdafx.h"
#include "CCamera.h"
#include "CShader.h"
#include "CGameManager.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
	Release();
}

HRESULT CCamera::Initialize(glm::vec3 vEye, glm::vec3 vAt, glm::vec3 vUp)
{
	CObj::Initialize();
	

	m_vEye = vEye;
	m_vAt = vAt;
	m_vUp = vUp;
	m_vDir = m_vAt - m_vEye;

	return NOERROR;
}

GLint CCamera::Update(const GLfloat fTimeDelta)
{
	// 키누르면 직각 원근 바꾸고 x축 회전
	return GLint();
}

GLvoid CCamera::Render()
{
	GLuint program = CShader::GetInstance()->Get_CurrProgram();

	m_matView = lookAt(m_vEye, m_vAt, m_vUp);
	int viewLoc = glGetUniformLocation(program, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));

	if (m_pGameMgr->Get_View()) {
		int ProjLoc = glGetUniformLocation(program, "projectionTransform");
		glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(Get_Ortho()));
	}
	else {
		int ProjLoc = glGetUniformLocation(program, "projectionTransform");
		glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(Get_Perspective()));
	}
	int PosLoc = glGetUniformLocation(program, "viewPos");
	glUniform3fv(PosLoc, 1, value_ptr(m_vEye));

	//int DirLoc = glGetUniformLocation(program, "vLightDir");
	//glUniform3fv(DirLoc, 1, value_ptr(glm::vec3(m_vLightDir)));
	return GLvoid();
}

glm::mat4 CCamera::Get_Ortho()
{
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::ortho(-20.0f, 20.0f, -10.0f, 10.0f, 1.0f, m_fFar);
	proj = glm::translate(proj, m_vec3Translate);
	proj = glm::rotate(proj, glm::radians(m_vec3Rotate.z), glm::vec3(0.0, 0.0, 1.0));
	return proj;
}

glm::mat4 CCamera::Get_Perspective()
{
	glm::mat4 proj = glm::perspective(glm::radians(m_fFovY), (float)WINCX / (float)WINCY, m_fNear, m_fFar);
	proj = glm::translate(proj, m_vec3Translate);
	proj = glm::rotate(proj, glm::radians(m_vec3Rotate.y), glm::vec3(0.0, 1.0, 0.0));
	proj = glm::rotate(proj, glm::radians(m_vec3Rotate.z), glm::vec3(0.0, 0.0, 1.0));
	return proj;
}

GLvoid CCamera::Release()
{
	return GLvoid();
}

CCamera* CCamera::Create(glm::vec3 vEye, glm::vec3 vAt, glm::vec3 vUp)
{
	CCamera* pInstance = new CCamera;

	if (FAILED(pInstance->Initialize(vEye, vAt, vUp)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
