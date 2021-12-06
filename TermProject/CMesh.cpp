#define _CRT_SECURE_NO_WARNINGS

#include "CMesh.h"

CMesh::CMesh()
{
}

CMesh::~CMesh()
{
	Release();
}

HRESULT CMesh::Initialize(string path, glm::vec4 vCol)
{
	if (path == "")
		return E_FAIL;

	if (FAILED(Load_Mesh(path)))
		return E_FAIL;

	path.replace(path.end() - 3, path.end(), "");
	int index = path.rfind('/');


	for (auto pMesh : m_vecSubMesh)
	{
		glGenBuffers(4, pMesh->vbo);

		// 인덱스에 해당하는 정점 할당
		for (int i = 0; i < pMesh->indices[0].size(); ++i)
		{
			pMesh->vertex.push_back(m_vecVertices[pMesh->indices[0][i]]);
			pMesh->texcoord.push_back(m_vecTexcoords[pMesh->indices[1][i]]);
			pMesh->normal.push_back(m_vecNormals[pMesh->indices[2][i]]);
		}

		if (FAILED(SetVertexColor(pMesh->vertex, pMesh->color, vCol)))
			return E_FAIL;

		glBindBuffer(GL_ARRAY_BUFFER, pMesh->vbo[0]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * pMesh->vertex.size(), &pMesh->vertex.front(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, pMesh->vbo[1]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * pMesh->texcoord.size(), &pMesh->texcoord.front(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, pMesh->vbo[2]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * pMesh->normal.size(), &pMesh->normal.front(), GL_STATIC_DRAW);

		glBindBuffer(GL_ARRAY_BUFFER, pMesh->vbo[3]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec4) * pMesh->color.size(), &pMesh->color.front(), GL_STATIC_DRAW);

		pMesh->material = Get_Material(pMesh->matname);
		if (pMesh->material)
		{
			MATERIAL* pMat = pMesh->material;
			string strNewPath = path;
			strNewPath = strNewPath.replace(strNewPath.end() - (strNewPath.size() - index - 1), strNewPath.end(), pMat->map_Kd);
			pMat->texture = CTexture::Create("", strNewPath); 
		}
	}




	return NOERROR;
}

GLvoid CMesh::Render()
{
	GLuint iLocation = CShader::GetInstance()->Use_Shader("Default"); //일단
	for (auto pMesh : m_vecSubMesh)
	{
		for (int i = 0; i < 4; ++i)
		{
			glEnableVertexAttribArray(i);
			glBindBuffer(GL_ARRAY_BUFFER, pMesh->vbo[i]);
			//glVertexAttribPointer(i, i == 1 ? 2 : 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
			switch (i)
			{
			case 0:
				glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
				break;
			case 1:
				glVertexAttribPointer(i, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
				break;
			case 2:
				glVertexAttribPointer(i, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
				break;
			case 3:
				glVertexAttribPointer(i, 4, GL_FLOAT, GL_FALSE, 0, (void*)0);
				break;
			default:
				break;
			}
		}

		if (pMesh->material && pMesh->material->texture)
			pMesh->material->texture->Render();

		glDrawArrays(GL_TRIANGLES, 0, pMesh->vertex.size());

		for (int i = 0; i < 4; ++i)
			glDisableVertexAttribArray(i);
	}
	return GLvoid();
}

HRESULT CMesh::Load_Mesh(string path)
{
	FILE* file = nullptr;
	if (FAILED(fopen_s(&file, path.c_str(), "r")))
	{
		cout << "Impossible to open the file !" << endl;
		return E_FAIL;
	}

	SUBMESH* pCurrPart = nullptr;

	while (true)
	{
		char chLineHeader[128] = {};
		int res = fscanf_s(file, "%s", chLineHeader, 128);

		if (res == EOF)
			break;

		if (strcmp(chLineHeader, "#") == 0)
			continue;
		else if (strcmp(chLineHeader, "v") == 0)
		{
			// 좌표 - v
			glm::vec3 vertex;
			fscanf_s(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			m_vecVertices.push_back(vertex);
		}
		else if (strcmp(chLineHeader, "vt") == 0)
		{
			// 텍스쳐 좌표 - vt
			glm::vec2 uv;
			fscanf_s(file, "%f %f\n", &uv.x, &uv.y);
			uv.y = 1.f - uv.y;
			m_vecTexcoords.push_back(uv);
		}
		else if (strcmp(chLineHeader, "vn") == 0)
		{
			// 노말 좌표 - vn
			glm::vec3 normal;
			fscanf_s(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
			m_vecNormals.push_back(normal);
		}

		else if (strcmp(chLineHeader, "f") == 0)
		{
			// 인덱스 - f
			int temp[3][3];
			int matches = fscanf_s(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n",
				&temp[0][0], &temp[0][1], &temp[0][2], &temp[1][0], &temp[1][1], &temp[1][2], &temp[2][0], &temp[2][1], &temp[2][2]);
			if (matches != 9)
			{
				cout << "File can't be read by our simple parser : ( Try exporting with other options" << endl;
				return E_FAIL;
			}
			if (!pCurrPart)
				pCurrPart = new SUBMESH;
			for (int i = 0; i < 3; ++i)
			{
				pCurrPart->indices[0].push_back(temp[i][0] - 1);
				pCurrPart->indices[1].push_back(temp[i][1] - 1);
				pCurrPart->indices[2].push_back(temp[i][2] - 1);
			}
		}
		//else if (strcmp(chLineHeader, "g") == 0)
		//{
		//	if (pCurrPart != nullptr)
		//		m_vecSubMesh.push_back(pCurrPart);
		//	pCurrPart = new SUBMESH;
		//	fscanf_s(file, "%s", pCurrPart->name, 256);
		//}
		else if (strcmp(chLineHeader, "usemtl") == 0)
		{
			/*if (!pCurrPart)
				pCurrPart = new SUBMESH;*/
			if (pCurrPart != nullptr)
				m_vecSubMesh.push_back(pCurrPart);
			pCurrPart = new SUBMESH;
			fscanf_s(file, "%s", pCurrPart->matname, 256);
		}
		else if (strcmp(chLineHeader, "mtllib") == 0)
		{
			// Material Load
			// ★★★★mat 파일 이름 obj파일 이름과 같아야함★★★★
			string strNewPath = path;
			strNewPath.replace(strNewPath.end() - 3, strNewPath.end(), "mtl");
			Load_Material(strNewPath);
		}
	}

	if (pCurrPart != nullptr)
		m_vecSubMesh.push_back(pCurrPart);

	return NOERROR;
}

HRESULT CMesh::Load_Material(string strPath)
{
	FILE* file = nullptr;
	if (FAILED(fopen_s(&file, strPath.c_str(), "r")))
	{
		cout << "Impossible to open the file !" << endl;
		return E_FAIL;
	}

	MATERIAL* pCurrMat = nullptr;

	while (true)
	{
		char chLineHeader[128];
		int res = fscanf_s(file, "%s", chLineHeader, 128);
		if (res == EOF)
			break;

		if (strcmp(chLineHeader, "#") == 0)
			continue;
		else if (strcmp(chLineHeader, "newmtl") == 0)
		{
			pCurrMat = new MATERIAL;
			fscanf_s(file, "%s", pCurrMat->name, 256);
			m_vecMaterials.push_back(pCurrMat);
		}
		else if (strcmp(chLineHeader, "Ka") == 0)
		{
			if (pCurrMat)
				fscanf_s(file, "%f %f %f", &pCurrMat->Ka[0], &pCurrMat->Ka[1], &pCurrMat->Ka[2]);
		}
		else if (strcmp(chLineHeader, "Kd") == 0)
		{
			if (pCurrMat)
				fscanf_s(file, "%f %f %f", &pCurrMat->Kd[0], &pCurrMat->Kd[1], &pCurrMat->Kd[2]);
		}
		else if (strcmp(chLineHeader, "Ks") == 0)
		{
			if (pCurrMat)
				fscanf_s(file, "%f %f %f", &pCurrMat->Ks[0], &pCurrMat->Ks[1], &pCurrMat->Ks[2]);
		}
		else if (strcmp(chLineHeader, "Tf") == 0)
		{
			if (pCurrMat)
				fscanf_s(file, "%f %f %f", &pCurrMat->Tf[0], &pCurrMat->Tf[1], &pCurrMat->Tf[2]);
		}
		else if (strcmp(chLineHeader, "illum") == 0)
		{
			if (pCurrMat)
				fscanf_s(file, "%i", &pCurrMat->illum);
		}
		else if (strcmp(chLineHeader, "map_Kd") == 0)
		{
			if (pCurrMat)
			{
				char temp[2048];
				fscanf_s(file, "%s", temp, 2048);
				pCurrMat->map_Kd = temp;
			}
		}
		else if (strcmp(chLineHeader, "Ns") == 0)
		{
			if (pCurrMat)
				fscanf_s(file, "%f", &pCurrMat->Ns);
		}
		else if (strcmp(chLineHeader, "Ni") == 0)
		{
			if (pCurrMat)
				fscanf_s(file, "%f", &pCurrMat->Ni);
		}
		else if (strcmp(chLineHeader, "d") == 0)
		{
			if (pCurrMat)
				fscanf_s(file, "%f", &pCurrMat->d);
		}
	}

	return NOERROR;
}

MATERIAL* CMesh::Get_Material(char* chMatName)
{
	if (strcmp(chMatName, "") == 0)
		return nullptr;

	MATERIAL* pOut = nullptr;
	for (auto pMat : m_vecMaterials)
	{
		if (strcmp(pMat->name, chMatName) == 0)
			pOut = pMat;;
	}
	return pOut;
}

HRESULT CMesh::SetVertexColor(vector<glm::vec3> vertex, vector<glm::vec4> &color, glm::vec4 vCol)
{
	/*for (auto pMesh : m_vecSubMesh)
	{
		for (GLuint i = 0; i < pMesh->vertex.size(); ++i)
			pMesh->color.emplace_back(vCol);
	}*/
	for (GLuint i = 0; i < vertex.size(); ++i)
		color.emplace_back(vCol);

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
	m_vecVertices.clear();
	m_vecTexcoords.clear();
	m_vecNormals.clear();
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
