#include "stdafx.h"
#include "CPlane.h"
#include "CShader.h"

CPlane::CPlane()
{
}

CPlane::~CPlane()
{
}

HRESULT CPlane::Initialize()
{
	m_vecVertices.push_back(glm::vec3(-1.f, 1.f, 0.f));
	m_vecVertices.push_back(glm::vec3(1.f, 1.f, 0.f));
	m_vecVertices.push_back(glm::vec3(-1.f, -1.f, 0.f));

	m_vecVertices.push_back(glm::vec3(1.f, -1.f, 0.f));
	m_vecVertices.push_back(glm::vec3(-1.f, -1.f, 0.f));
	m_vecVertices.push_back(glm::vec3(1.f, 1.f, 0.f));

	m_vecTexcoord.push_back(glm::vec2(0.f, 0.f));
	m_vecTexcoord.push_back(glm::vec2(1.f, 0.f));
	m_vecTexcoord.push_back(glm::vec2(0.f, 1.f));

	m_vecTexcoord.push_back(glm::vec2(1.f, 1.f));
	m_vecTexcoord.push_back(glm::vec2(0.f, 1.f));
	m_vecTexcoord.push_back(glm::vec2(1.f, 0.f));

	glGenVertexArrays(1, &m_Vao); //--- VAO 를 지정하고 할당하기
	glGenBuffers(2, m_Vbo); //--- 2개의 VBO를 지정하고 할당하기

	glBindVertexArray(m_Vao); //--- VAO를 바인드하기

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vecVertices.size(), &m_vecVertices.front(), GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_vecTexcoord.size(), &m_vecTexcoord.front(), GL_STATIC_DRAW);

	return NOERROR;
}

GLvoid CPlane::Render()
{
	GLuint program = CShader::GetInstance()->Use_Shader("UI");

	GLuint iLocation = glGetUniformLocation(program, "modelTransform");
	glUniformMatrix4fv(iLocation, 1, GL_FALSE, value_ptr(Get_Matrix()));

	for (int i = 0; i < 2; ++i)
	{
		glEnableVertexAttribArray(i);
		glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[i]);
		glVertexAttribPointer(i, i == 1 ? 2 : 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
	}

	glDrawArrays(GL_TRIANGLES, 0, m_vecVertices.size());

	for (int i = 0; i < 2; ++i)
		glDisableVertexAttribArray(i);
}

glm::mat4 CPlane::Get_Matrix()
{
	glm::mat4 result(1.0f);
	if (m_Parent) {
		result = m_Parent->Get_Matrix() * result;
	}
	result = glm::rotate(result, glm::radians(m_vec3PRotate.x), glm::vec3(1.0, 0.0, 0.0));
	result = glm::rotate(result, glm::radians(m_vec3PRotate.y), glm::vec3(0.0, 1.0, 0.0));
	result = glm::rotate(result, glm::radians(m_vec3PRotate.z), glm::vec3(0.0, 0.0, 1.0));

	result = glm::translate(result, m_vec3Translate);

	result = glm::rotate(result, glm::radians(m_vec3Rotate.x), glm::vec3(1.0, 0.0, 0.0));
	result = glm::rotate(result, glm::radians(m_vec3Rotate.y), glm::vec3(0.0, 1.0, 0.0));
	result = glm::rotate(result, glm::radians(m_vec3Rotate.z), glm::vec3(0.0, 0.0, 1.0));


	result = glm::scale(result, m_vec3Scale);
	//result = glm::mat4(1.0f);

	return result;
}

GLvoid CPlane::Release()
{
	return GLvoid();
}

CPlane* CPlane::Create()
{
	CPlane* pInstance = new CPlane;

	if (FAILED(pInstance->Initialize()))
	{
		SafeDelete(pInstance);
		return nullptr;
	}

	return pInstance;
}
