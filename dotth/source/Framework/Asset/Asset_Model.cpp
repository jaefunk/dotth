#include "Asset_Model.h"

Asset_Model::Asset_Model(void) : Asset_Renderable(ASSET_TYPE::MODEL)
{
}

void Asset_Model::Bind(void)
{

}

bool Asset_Model::OnLoad(void * data, size_t size)
{
	Assimp::Importer importer;
	_Scene = importer.ReadFileFromMemory(data, size, aiProcess_ConvertToLeftHanded | aiProcess_Triangulate | aiProcess_OptimizeMeshes);
	if (_Scene == nullptr)
		return false;

	if (_Scene->HasMeshes() == false)
		return false;

	for (unsigned int index = 0; index < _Scene->mNumMeshes; ++index)
	{
		aiMesh* raw = _Scene->mMeshes[index];

		std::vector<VertexPNU> _Vertices;
		_Vertices.resize(raw->mNumVertices);
		for (unsigned int index = 0; index < raw->mNumVertices; ++index)
		{
			const aiVector3D& p = raw->mVertices[index];
			_Vertices[index].p.x = p.x;
			_Vertices[index].p.y = p.y;
			_Vertices[index].p.z = p.z;

			const aiVector3D& n = raw->mNormals[index];
			_Vertices[index].n.x = n.x;
			_Vertices[index].n.y = n.y;
			_Vertices[index].n.z = n.z;

			if (raw->HasTextureCoords(0))
			{
				const aiVector3D& u = raw->mTextureCoords[0][index];
				_Vertices[index].u.x = u.x;
				_Vertices[index].u.y = u.y;
			}

			//const aiVector3D& t = raw->mTangents[index];
			//const aiVector3D& b = raw->mBitangents[index];
		}

		std::vector<unsigned int> _Indices;
		_Indices.resize(raw->mNumFaces * 3);
		for (unsigned int index = 0; index < raw->mNumFaces; ++index)
		{
			const aiFace& face = raw->mFaces[index];
			unsigned int current = index * 3;
			_Indices[current + 0] = face.mIndices[0];
			_Indices[current + 1] = face.mIndices[1];
			_Indices[current + 2] = face.mIndices[2];
		}


		Drawable drawable;
		drawable.SetVertex(_Vertices);
		drawable.SetIndex(_Indices);
		_Drawables.push_back(drawable);
	}
	return true;
}