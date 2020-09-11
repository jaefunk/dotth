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
		Mesh mesh(raw);

		Drawable drawable;
		drawable.SetVertex(mesh._Vertices);
		drawable.SetIndex(mesh._Indices);
		_Drawables.push_back(drawable);
		//_VertexCount += _Meshes[index]._Vertices.size();
		//_IndexCount += _Meshes[index]._Indices.size();
	}
	return true;
}