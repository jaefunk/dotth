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
	_Scene = importer.ReadFileFromMemory(data, size, aiProcess_ConvertToLeftHanded);
	if (_Scene == nullptr)
		return false;

	if (_Scene->HasMeshes() == false)
		return false;

	_Meshes.resize(_Scene->mNumMeshes);
	for (unsigned int index = 0; index < _Scene->mNumMeshes; ++index)
	{
		aiMesh* mesh = _Scene->mMeshes[index];
		_Meshes[index].Init(mesh);
		_VertexCount += _Meshes[index]._Vertices.size();
		_IndexCount += _Meshes[index]._Indices.size();
	}
	return true;
}