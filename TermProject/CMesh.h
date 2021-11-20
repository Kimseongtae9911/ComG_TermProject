#include "stdafx.h"

class CMesh
{
public:
	CMesh();
	~CMesh();

public:
	HRESULT Initialize(string path);
	GLvoid Render();
	

protected:
	HRESULT Load_Mesh(string path);

protected:
	vector<glm::vec3> m_vecVertex;
	vector<glm::vec2> m_vecUVS;
	vector<glm::vec3> m_vecNormal;

private:
	GLuint Vao;
	GLuint Vbo[3];

private:
	GLvoid Release();

public:
	static CMesh* Create(string path);

};