#include "CTexture.h"

class CMesh
{
public:
	CMesh();
	~CMesh();

public:
	HRESULT Initialize(string path, glm::vec4 vCol);
	GLvoid Render();
	
public:
	HRESULT SetVertexColor(vector<glm::vec3> vertex, vector<glm::vec4> color, glm::vec4 vCol);
	string& Get_Path() { return strPath; };


protected:
	HRESULT Load_Mesh(string strPath);
	HRESULT Load_Material(string strPath);

private:
	MATERIAL* Get_Material(char* chMatName);



protected:
	vector<glm::vec3> m_vecVertex;
	vector<glm::vec2> m_vecUVS;
	vector<glm::vec3> m_vecNormal;
	vector<glm::vec4> m_vecColor;
	CMesh* m_Parent = nullptr;
	glm::vec3 m_vec3PRotate; // 이동전에 적용하는 회전(공전)
	glm::vec3 m_vec3Translate;
	glm::vec3 m_vec3Rotate; // 이동후에 적용하는 회전(자전)
	glm::vec3 m_vec3Scale;

private:
	GLuint m_Vao;
	GLuint m_Vbo[4];

private:
	GLuint m_iCnt;
	GLuint m_iCnt2;

private:
	vector<glm::vec3> m_vecVertices;
	vector<glm::vec2> m_vecTexcoords;
	vector<glm::vec3> m_vecNormals;
	string strPath = "";

private:
	vector<SUBMESH*> m_vecSubMesh;
	vector<MATERIAL*> m_vecMaterials;

private:
	glm::mat4 GetMatrix();

protected:
	GLvoid Release();

public:
	static CMesh* Create(string path, glm::vec4 vCol);

};