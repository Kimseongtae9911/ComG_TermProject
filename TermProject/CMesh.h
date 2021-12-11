#pragma once

class CTexture;
class CMesh
{
public:
	CMesh();
	~CMesh();

public:
	HRESULT Initialize(string path, glm::vec4 vCol);
	GLvoid Render();
	
public:
	HRESULT SetVertexColor(vector<glm::vec3> vertex, vector<glm::vec4> &color, glm::vec4 vCol);
	string& Get_Path() { return strPath; };


protected:
	HRESULT Load_Mesh(string strPath);
	HRESULT Load_Material(string strPath);


private:
	MATERIAL* Get_Material(char* chMatName);
	


protected:
	CMesh* m_Parent = nullptr;
	glm::vec3 m_vec3PRotate{0.0, 0.0, 0.0};
	glm::vec3 m_vec3Translate{ 0.0, 0.0, 0.0 };
	glm::vec3 m_vec3Rotate{ 0.0, 0.0, 0.0 };
	glm::vec3 m_vec3Scale{ 1.0, 1.0, 1.0 };

private:
	GLuint m_Vao;
	GLuint m_Vbo[4];

private:
	GLuint m_iCnt;
	GLuint m_iCnt2;

protected:
	vector<glm::vec3> m_vecVertices;
	vector<glm::vec2> m_vecTexcoords;
	vector<glm::vec3> m_vecNormals;
	vector<glm::vec4> m_vecColor;
	string strPath = "";

private:
	vector<SUBMESH*> m_vecSubMesh;
	vector<MATERIAL*> m_vecMaterials;

public:
	glm::mat4 Get_Matrix();
	glm::vec3& GetPos() { return m_vec3Translate; }
	glm::vec3& GetScale() { return m_vec3Scale; }
	glm::vec3& GetTrans() { return m_vec3Translate; }
	vector<SUBMESH*>& GetSMESH() { return m_vecSubMesh; }
	GLvoid Move(glm::vec3 move) { m_vec3Translate += move; }
	GLvoid Rotate(glm::vec3 vecAngle) { m_vec3PRotate += vecAngle; }
	//GLvoid Rotate(glm::vec3 Axis, float fAngle);
	
protected:
	GLvoid Release();

public:
	static CMesh* Create(string path, glm::vec4 vCol);

};