#include "CMesh.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
	Release();
}

HRESULT CMesh::Initialize(string path, glm::vec3 vCol)
{
	if (path == "")
		return E_FAIL;
	if(FAILED(Load_Mesh(path)))
		return E_FAIL;
	//m_iCnt = m_vecVertex.size();
	//m_iCnt2 = m_vecNormal.size();

	glGenVertexArrays(1, &m_Vao); //--- VAO 를 지정하고 할당하기
	glGenBuffers(4, m_Vbo); //--- 2개의 VBO를 지정하고 할당하기

	glBindVertexArray(m_Vao); //--- VAO를 바인드하기
	
	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vecVertex.size(), &m_vecVertex.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

 	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * m_vecNormal.size(), &m_vecNormal.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * m_vecColor.size(), &m_vecColor.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, m_Vbo[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * m_vecUVS.size(), &m_vecUVS.front(), GL_STATIC_DRAW);
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(3);




	return E_NOTIMPL;
}

GLvoid CMesh::Render()
{

	return GLvoid();
}

HRESULT CMesh::Load_Mesh(string path)
{
	vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	vector< glm::vec3 > temp_vertices;
	vector< glm::vec2 > temp_uvs;
	vector< glm::vec3 > temp_normals;

	FILE* file = nullptr;
	if (FAILED(fopen_s(&file, path.c_str(), "r")))
	{
		cout << "Impossible to open the file !" << endl;
		return E_FAIL;
	}

	while (true)
	{
		char chLineHeader[128];
		int res = fscanf_s(file, "%s", chLineHeader, 128);
		if (res == EOF)
			break;

		if (strcmp(chLineHeader, "v") == 0)
		{
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
		}
		else if (strcmp(chLineHeader, "vt") == 0)
		{
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			temp_uvs.push_back(uv);
		}
		else if (strcmp(chLineHeader, "vn") == 0)
		{
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			temp_normals.push_back(normal);
		}
		else if (strcmp(chLineHeader, "f") == 0)
		{
			string vertex1, vertex2, vertex3;
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
			if (matches != 9)
			{
				cout << "File can't be read by our simple parser : ( Try exporting with other options" << endl;
				return E_FAIL;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}
	}

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 vertex = temp_vertices[vertexIndex - 1];
		m_vecVertex.push_back(vertex);
	}

	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 uv = temp_uvs[uvIndex - 1];
		m_vecUVS.push_back(uv);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 normal = temp_normals[normalIndex - 1];
		m_vecNormal.push_back(normal);
	}

	return NOERROR;
}

HRESULT CMesh::SetVertexColor(glm::vec4 vCol)
{
	m_vecColor.clear();

	for (GLuint i = 0; i < m_vecVertex.size(); ++i)
		m_vecColor.emplace_back(vCol);

	return NOERROR;
}

glm::mat4 CMesh::GetMatrix()
{
	glm::mat4 result(1.0f);
	if (m_Parent) {
		result = m_Parent->GetMatrix() * result;
	}

	result = glm::rotate(result, glm::radians(m_vec3PRotate.y), glm::vec3(0.0, 1.0, 0.0));

	result = glm::translate(result, m_vec3Translate);

	result = glm::rotate(result, glm::radians(m_vec3Rotate.x), glm::vec3(1.0, 0.0, 0.0));
	result = glm::rotate(result, glm::radians(m_vec3Rotate.y), glm::vec3(0.0, 1.0, 0.0));
	result = glm::rotate(result, glm::radians(m_vec3Rotate.z), glm::vec3(0.0, 0.0, 1.0));


	result = glm::scale(result, m_vec3Scale);

	return result;
}

GLvoid CMesh::Release()
{
	m_vecVertex.clear();
	m_vecUVS.clear();
	m_vecNormal.clear();
	m_vecColor.clear();

	return GLvoid();
}

CMesh* CMesh::Create(string path, glm::vec4 vCol)
{
	CMesh* pInstance = new CMesh;

	if (FAILED(pInstance->Initialize(path, vCol)))
	{
		SafeDelete(pInstance);
		return nullptr;
	}
	return pInstance;
}
