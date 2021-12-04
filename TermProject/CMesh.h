#include "stdafx.h"
#include "CShader.h"
class CMesh
{
public:
	CMesh();
	~CMesh();

public:
	HRESULT Initialize(string path, glm::vec3 vCol);
	GLvoid Render();
	
public:
	HRESULT SetVertexColor(glm::vec4 vCol);


protected:
	HRESULT Load_Mesh(string path);

protected:
	GLvoid Release();

protected:
	vector<glm::vec3> m_vecVertex;
	vector<glm::vec2> m_vecUVS;
	vector<glm::vec3> m_vecNormal;
	vector<glm::vec4> m_vecColor;

private:
	GLuint m_Vao;
	GLuint m_Vbo[4];

private:
	GLuint m_iCnt;
	GLuint m_iCnt2;

private:
	


public:
	static CMesh* Create(string path, glm::vec4 vCol);

};