#pragma once
#include "CObj.h"

class CCamera : public CObj
{
public:
	CCamera();
	~CCamera();

public:
	glm::mat4 Get_View() { return m_matView; }
	glm::mat4 Get_Proj() { return m_matProj; }

public:
	virtual HRESULT Initialize(glm::vec3 vEye, glm::vec3 vAt, glm::vec3 vUp);
	virtual GLint Update(const GLfloat fTimeDelta);
	virtual GLvoid Render();

private:
	glm::vec3 m_vEye = glm::vec3(0.f, 1.f, 1.f);
	glm::vec3 m_vAt = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_vUp = glm::vec3(0.f, 1.f, 0.f);
	glm::vec3 m_vDir = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_vLightDir = glm::vec3(0.f, 0.f, 0.f);
	glm::vec3 m_vec3PRotate{ 0.0, 0.0, 0.0 };
	glm::vec3 m_vec3Translate{ 0.0, 0.0, 0.0 };
	glm::vec3 m_vec3Rotate{ 0.0, 0.0, 0.0 };
	float m_fDistance = 3.f;

private:
	GLfloat m_fFovY = 30.f;
	GLfloat m_fNear = 0.1f;
	GLfloat m_fFar = 200.0f;

private:
	glm::mat4 m_matView = glm::mat4(1.f);
	glm::mat4 m_matProj = glm::mat4(1.f);

private:
	GLfloat m_fAngle = 0.f;

private:
	GLvoid Release();
	glm::mat4 Get_Ortho();
	glm::mat4 Get_Perspective();

public:
	static CCamera* Create(glm::vec3 vEye, glm::vec3 vAt, glm::vec3 vUp);
};

