#include "stdafx.h"

class CMesh
{
public:
	CMesh();
	~CMesh();

public:
	HRESULT Initialize(string path, glm::vec3 vCol);
	GLvoid Render();
	

protected:
	HRESULT Load_Mesh(string path);

protected:
	GLvoid Release();

protected:
	vector<glm::vec3> m_vecVertex;
	vector<glm::vec2> m_vecUVS;
	vector<glm::vec3> m_vecNormal;
	vector<glm::vec3> m_vecColor;

private:
	GLuint Vao;
	GLuint Vbo[3];

private:
	GLuint m_iCnt;
	GLuint m_iCnt2;


public:
	static CMesh* Create(string path, glm::vec3 vCol);

};