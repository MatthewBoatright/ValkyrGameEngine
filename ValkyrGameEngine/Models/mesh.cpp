#include "mesh.h"

namespace Valkyr {
	namespace Graphics {

		Mesh::Mesh()
		{

		}

		Mesh::~Mesh()
		{
			clear();
		}

		bool Mesh::loadMesh(const std::string & filePath)
		{
			clear();

			bool ret = false;
			Assimp::Importer importer;

			const unsigned int aiFlags = (aiProcess_Triangulate | aiProcess_GenSmoothNormals | aiProcess_FlipUVs);
			const aiScene * scene = importer.ReadFile(filePath, aiFlags);

			if (scene)
				ret = initFromAIScene(scene, filePath);
			else
				printf("Could not load mesh from file '%s': %s\n", filePath, importer.GetErrorString());

			return ret;
		}

		void Mesh::render()
		{		

			for (unsigned int i = 0; i < m_Entries.size(); i++) 
			{
				m_Entries[i].VAO->bind();
				m_Entries[i].IBO->bind();

				const unsigned int MaterialIndex = m_Entries[i].MaterialIndex;

				if (MaterialIndex < m_Textures.size() && m_Textures[MaterialIndex]) {
					m_Textures[MaterialIndex]->bind(GL_TEXTURE0);
				}

				glDrawElements(GL_TRIANGLES, m_Entries[i].IBO->getSize(), GL_UNSIGNED_INT, 0);
			}
		}

		bool Mesh::initFromAIScene(const aiScene * scene, const std::string & filePath)
		{
			m_Entries.resize(scene->mNumMeshes);
			m_Textures.resize(scene->mNumTextures);

			for (int i = 0; i < m_Entries.size(); i++)
			{
				const aiMesh * mesh = scene->mMeshes[i];
				initMesh(i, mesh);
			}

			return true; //initMaterials(scene, filePath);
		}

		void Mesh::initMesh(unsigned int index, const aiMesh * mesh)
		{
			m_Entries[index].MaterialIndex = mesh->mMaterialIndex;

			std::vector<glm::vec3> indexed_pos;
			std::vector<glm::vec2> indexed_uv;
			std::vector<glm::vec3> indexed_normal;
			std::vector<unsigned int> indices;

			const aiVector3D zero(0.0f, 0.0f, 0.0f);

			for (int i = 0; i < mesh->mNumVertices; i++)
			{
				const aiVector3D * pos = &(mesh->mVertices[i]);
				const aiVector3D * normal = &(mesh->mNormals[i]);
				const aiVector3D * uv = mesh->HasTextureCoords(0) ? &(mesh->mTextureCoords[0][i]) : &zero;

				indexed_pos.push_back(glm::vec3(pos->x, pos->y, pos->z));
				indexed_uv.push_back(glm::vec2(uv->x, uv->y));
				indexed_normal.push_back(glm::vec3(normal->x, normal->y, normal->z));
			}						  
					
			for (int i = 0; i < mesh->mNumFaces; i++)
			{
				const aiFace & face = mesh->mFaces[i];
				indices.push_back(face.mIndices[0]);
				indices.push_back(face.mIndices[1]);
				indices.push_back(face.mIndices[2]);
			}

			m_Entries[index].init(indexed_pos, indexed_uv, indexed_normal, indices);
		}

		bool Mesh::initMaterials(const aiScene * scene, const std::string & filePath)
		{
			std::string::size_type slashIndex = filePath.find_last_of("/");
			std::string dir;

			if (slashIndex == std::string::npos)
				dir = ".";
			else if (slashIndex == 0)
				dir = "/";
			else
				dir = filePath.substr(0, slashIndex);

			bool ret = true;

			for (int i = 0; i < scene->mNumMaterials; i++)
			{
				const aiMaterial * material = scene->mMaterials[i];

				//m_Textures[i] = NULL;

				if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0)
				{
					aiString path;

					if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path, NULL, NULL, NULL, NULL, NULL) == AI_SUCCESS)
					{
						std::string fullPath = dir + "/" + path.data;
						m_Textures[i] = new Texture(fullPath.c_str(), GL_TEXTURE_2D);

						if (!m_Textures[i]->load())
						{
							printf("Could not load mesh from file '%s'.\n", filePath);
							delete m_Textures[i];
							m_Textures[i] = NULL;
							ret = false;
						}
					}
				}

				if (!m_Textures[i])
				{
					m_Textures[i] = new Texture("uvmap.dds");
					ret = m_Textures[i]->load();
				}
			}

			return ret;
		}

		void Mesh::clear()
		{
			for (int i = 0; i < m_Textures.size(); i++)
			{
				if (m_Textures[i])
				{
					delete m_Textures[i];
					m_Textures[i] = NULL;
				}
			}
		}

		Mesh::MeshEntry::MeshEntry()
		{
			VAO = new VertexArray();
			MaterialIndex = 0;
		}

		Mesh::MeshEntry::~MeshEntry()
		{

		}

		void Mesh::MeshEntry::init(const std::vector<glm::vec3> & pos, const std::vector<glm::vec2> & uv, const std::vector<glm::vec3> & normal, const std::vector<unsigned int> & indices)
		{
			VAO->addBuffer(new VertexBuffer(pos), 0);
			VAO->addBuffer(new VertexBuffer(uv), 1);
			VAO->addBuffer(new VertexBuffer(normal), 2);
			IBO = new IndexBuffer(indices);
		}

	}
}