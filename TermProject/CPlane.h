#pragma once
class CPlane 
{
public:
	CPlane();
	~CPlane();

public:
	HRESULT Initialize();
	GLvoid Render();

public:
	glm::mat4 Get_Matrix();

private:
	GLuint m_Vao, m_Vbo[2];
	vector<glm::vec3> m_vecVertices;
	vector<glm::vec2> m_vecTexcoord;

private:
	CPlane* m_Parent = nullptr;
	glm::vec3 m_vec3PRotate{ 0.0, 0.0, 0.0 };
	glm::vec3 m_vec3Translate{ 0.0, 0.0, 0.0 };
	glm::vec3 m_vec3Rotate{ 0.0, 0.0, 0.0 };
	glm::vec3 m_vec3Scale{ 1.0, 1.0, 1.0 };

public:
	glm::vec3& GetPos() { return m_vec3Translate; };
	glm::vec3& GetScale() { return m_vec3Scale; };
	glm::vec3& GetTrans() { return m_vec3Translate; };
	glm::vec3& GetRotate() { return m_vec3Rotate; };
	glm::vec3& GetRotateP() { return m_vec3PRotate; };

private:
	GLvoid Release();

public:
	static CPlane* Create();
};

