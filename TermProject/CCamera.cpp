#include "CCamera.h"

CCamera::CCamera()
{
}

CCamera::~CCamera()
{
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

	m_matProj = perspective(radians(m_fFovY), (float)WINCX / (float)WINCY, m_fNear, m_fFar);
	int ProjLoc = glGetUniformLocation(program, "projectionTransform");
	glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(m_matProj));

	int PosLoc = glGetUniformLocation(program, "viewPos");
	glUniform3fv(PosLoc, 1, value_ptr(m_vEye));

	//int DirLoc = glGetUniformLocation(program, "vLightDir");
	//glUniform3fv(DirLoc, 1, value_ptr(glm::vec3(m_vLightDir)));
	return GLvoid();
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
