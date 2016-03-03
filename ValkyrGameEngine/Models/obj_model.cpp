#include "obj_model.h"

namespace Valkyr { namespace Graphics { 

	OBJModel::OBJModel(const char * filename)
	{
		if (!fileExists(filename) || !init(filename))
			loadDefaultModel();
	}

	bool OBJModel::init(const char * filename)
	{
		std::vector<unsigned int> vertex_indices, uv_indices, normal_indices;
		std::vector<glm::vec3> temp_vertices;
		std::vector<glm::vec2> temp_uvs;
		std::vector<glm::vec3> temp_normals;

		FILE * file = fopen(filename, "r");
		while (true)
		{
			char header[128];
			int res = fscanf(file, "%s", &header);
			if (res == EOF)
				break;

			// Vertex
			if (strcmp(header, "v") == 0)
			{
				glm::vec3 vertexVector;
				fscanf(file, "%f %f %f\n", &vertexVector.x, &vertexVector.y, &vertexVector.z);
				temp_vertices.push_back(vertexVector);
			}

			// Texture UV
			if (strcmp(header, "vt") == 0)
			{
				m_HasUV = true;
				glm::vec2 uvVector;
				fscanf(file, "%f %f\n", &uvVector.x, &uvVector.y);
				temp_uvs.push_back(uvVector);
			}

			// Normal
			if (strcmp(header, "vn") == 0)
			{
				m_HasNormals = true;
				glm::vec3 normalVector;
				fscanf(file, "%f %f %f\n", &normalVector.x, &normalVector.y, &normalVector.z);
				temp_normals.push_back(normalVector);
			}

			// Group
			if (strcmp(header, "g") == 0)
			{

			}

			// Face
			if (strcmp(header, "f") == 0)
			{
				unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];

				// UV and Normals found
				if (m_HasUV && m_HasNormals)
				{
					fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
					vertex_indices.push_back(vertexIndex[0]);
					vertex_indices.push_back(vertexIndex[1]);
					vertex_indices.push_back(vertexIndex[2]);
					uv_indices.push_back(uvIndex[0]);
					uv_indices.push_back(uvIndex[1]);
					uv_indices.push_back(uvIndex[2]);
					normal_indices.push_back(normalIndex[0]);
					normal_indices.push_back(normalIndex[1]);
					normal_indices.push_back(normalIndex[2]);
				}

				// UV but no Normals found
				else if (m_HasUV && !(m_HasNormals))
				{
					fscanf(file, "%d/%d %d/%d %d/%d\n", &vertexIndex[0], &uvIndex[0], &vertexIndex[1], &uvIndex[1], &vertexIndex[2], &uvIndex[2]);
					vertex_indices.push_back(vertexIndex[0]);
					vertex_indices.push_back(vertexIndex[1]);
					vertex_indices.push_back(vertexIndex[2]);
					uv_indices.push_back(uvIndex[0]);
					uv_indices.push_back(uvIndex[1]);
					uv_indices.push_back(uvIndex[2]);
					normal_indices.push_back(NULL);
					normal_indices.push_back(NULL);
					normal_indices.push_back(NULL);
				}

				// Normals but no UV
				else if ((!m_HasUV) && m_HasNormals)
				{
					fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexIndex[0], &normalIndex[0], &vertexIndex[1], &normalIndex[1], &vertexIndex[2], &normalIndex[2]);
					vertex_indices.push_back(vertexIndex[0]);
					vertex_indices.push_back(vertexIndex[1]);
					vertex_indices.push_back(vertexIndex[2]);
					uv_indices.push_back(NULL);
					uv_indices.push_back(NULL);
					uv_indices.push_back(NULL);
					normal_indices.push_back(normalIndex[0]);
					normal_indices.push_back(normalIndex[1]);
					normal_indices.push_back(normalIndex[2]);

				}

				// Just vertex components
				else
				{
					fscanf(file, "%d %d %d\n", &vertexIndex[0], &vertexIndex[1], &vertexIndex[2]);
					vertex_indices.push_back(vertexIndex[0]);
					vertex_indices.push_back(vertexIndex[1]);
					vertex_indices.push_back(vertexIndex[2]);
					uv_indices.push_back(NULL);
					uv_indices.push_back(NULL);
					uv_indices.push_back(NULL);
					normal_indices.push_back(NULL);
					normal_indices.push_back(NULL);
					normal_indices.push_back(NULL);
				}
			}
		}
		fclose(file);

		m_VertexArray.addBuffer(new VertexBuffer(temp_vertices),0);
		m_VertexArray.addBuffer(new VertexBuffer(temp_uvs),		1);
		m_VertexArray.addBuffer(new VertexBuffer(temp_normals),	2);

		m_Size = temp_vertices.size();

		//std::vector<glm::vec3> out_vertices;
		//std::vector<glm::vec2> out_uvs;
		//std::vector<glm::vec3> out_normals;

		//// For each vertex of each triangle
		//for (unsigned int i = 0; i < vertex_indices.size(); i++) {

		//	// Get the indices of its attributes
		//	unsigned int vertexIndex = vertex_indices[i];
		//	unsigned int uvIndex = uv_indices[i];
		//	unsigned int normalIndex = normal_indices[i];

		//	
		//	(uvIndex == 0) ? uvIndex = 0 : uvIndex--;
		//	(normalIndex == 0) ? normalIndex = 0 : normalIndex--;

		//	glm::vec3 vertex = (vertexIndex > 0) ? temp_vertices[vertexIndex - 1] : NULL;
		//	glm::vec2 uv = temp_uvs[uvIndex];
		//	glm::vec3 normal = temp_normals[normalIndex];

		//	// Put the attributes in buffers
		//	out_vertices.push_back(vertex);
		//	out_uvs.push_back(uv);
		//	out_normals.push_back(normal);
		//}

		return true;
	}

	void OBJModel::loadDefaultModel()
	{

	}

} }