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
	
	if (!bMovingCamera && VIEW::VIEW_3D == m_pGameMgr->Get_View()) // 직각->원근
	{
		RotateX(0.5f);
		//RotateForObj(glm::vec3(1.0f, 0, 0), 0.5f);
		++iCount;
		if (iCount >= 80)
		{
			bMovingCamera = !bMovingCamera;
			iCount = 0;
			cout << "Ortho" << endl;
		}
		
	}
	else if (bMovingCamera && VIEW::VIEW_2D == m_pGameMgr->Get_View()) //원근 -> 직각
	{
		RotateX(-0.5f);
		//RotateForObj(glm::vec3(1.0f, 0, 0), -0.5f);
		++iCount;
		if (iCount >= 80)
		{
			bMovingCamera = !bMovingCamera;
			iCount = 0;
		}
		
	}
	return GLint();
}

GLvoid CCamera::Render()
{
	GLuint program = CShader::GetInstance()->Get_CurrProgram();

	m_matView = lookAt(m_vEye, m_vAt, m_vUp);
	int viewLoc = glGetUniformLocation(program, "viewTransform");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, value_ptr(m_matView));

	int lightLoc = glGetUniformLocation(program, "lightPos");
	glUniform3fv(lightLoc, 1, value_ptr(m_vLightPos));
	
	int lightColorLocation = glGetUniformLocation(program, "lightColor");
	glUniform3f(lightColorLocation, m_vLightColor.x, m_vLightColor.y, m_vLightColor.z);

	int lightOnLocation = glGetUniformLocation(program, "light_on");
	glUniform1i(lightOnLocation, m_iLight);

	int lightIntensityLocation = glGetUniformLocation(program, "light_intensity");
	glUniform1f(lightIntensityLocation, m_fLintensity);

	if (VIEW::VIEW_2D == m_pGameMgr->Get_View() && !bMovingCamera)
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

	return GLvoid();
}

glm::mat4 CCamera::Get_Ortho()
{
	m_vLightPos = glm::vec3(30.0f, 50.0f, 10.0f);
	glm::mat4 proj = glm::mat4(1.0f);
	proj = glm::ortho(-16.0f, 16.0f, -8.0f, 8.0f, 1.0f, m_fFar);
	proj = glm::translate(proj, m_vec3Translate);
	proj = glm::rotate(proj, glm::radians(m_vec3Rotate.y), glm::vec3(0.0, 1.0, 0.0));
	return proj;
}

glm::mat4 CCamera::Get_Perspective()
{
	m_vLightPos = { 30.0f, 6.5f, 0.0f };
	glm::mat4 proj = glm::perspective(glm::radians(m_fFovY), (float)WINCX / (float)WINCY, m_fNear, m_fFar);
	proj = glm::translate(proj, m_vec3Translate);
	proj = glm::rotate(proj, glm::radians(m_vec3Rotate.y), glm::vec3(0.0, 1.0, 0.0));
	proj = glm::translate(proj, glm::vec3(-m_vEye));
	proj = glm::rotate(proj, glm::radians(m_vec3Rotate.x), glm::vec3(1.0, 0.0, 0.0));
	proj = glm::translate(proj, glm::vec3(m_vEye));
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
