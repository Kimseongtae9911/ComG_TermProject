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
	
	if (!bMovingCamera && m_pGameMgr->Get_View() == false) // 직각->원근
	{
		RotateForObj(glm::vec3(1.0f, 0, 0), 0.5f);
		if (iCount >= 60)
		{
			bMovingCamera = !bMovingCamera;
			iCount = 0;
			cout << "Ortho" << endl;
		}
		++iCount;
	}
	else if (bMovingCamera && m_pGameMgr->Get_View()) //원근 -> 직각
	{
		RotateForObj(glm::vec3(1.0f, 0, 0), -0.5f);
		if (iCount >= 60)
		{
			bMovingCamera = !bMovingCamera;
			iCount = 0;
		}
		++iCount;
	}
	return GLint();
}

GLvoid CCamera::Render()
{
	GLuint program = CShader::GetInstance()->Get_CurrProgram();

	m_matView = lookAt(m_vEye, m_vAt, m_vUp);
	int viewLoc = glGetUniformLocation(program, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));

	if (m_pGameMgr->Get_View() == true && !bMovingCamera)
	{
		int ProjLoc = glGetUniformLocation(program, "projectionTransform");// 직각
		glUniformMatrix4fv(ProjLoc, 1, GL_FALSE, value_ptr(Get_Ortho()));
	}
	else
	{
		int ProjLoc = glGetUniformLocation(program, "projectionTransform"); //원근
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

GLvoid CCamera::RotateForObj(glm::vec3 vAxis, float fAngle)
{
	glm::vec3 originAt = m_vAt;
	glm::vec3 originEye = m_vEye;

	glm::vec3 At = m_vAt;
	glm::vec3 Eye = m_vEye;

	glm::vec3 Dir = glm::vec3(0.f, 0.f, 0.f) - m_vAt;
	Eye += Dir;
	At += Dir;

	glm::vec4 temp = glm::vec4(Eye, 1.f);
	glm::vec4 tmp = glm::vec4(At, 1.f);
	glm::mat4 temp1 = rotate(glm::mat4(1.f), glm::radians(fAngle), vAxis);
	temp = rotate(glm::mat4(1.f), glm::radians(fAngle), vAxis) * temp;
	//tmp = rotate(mat4(1.f), radians(fAngle), vAxis) * tmp;
	Eye = glm::vec3(temp);
	//At = vec3(tmp);

	m_vEye = Eye - Dir;
	m_vAt = At - Dir;

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
