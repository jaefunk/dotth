#pragma once

#include "AssetBase.h"
#include "Texture2D.h"
#include "Shader.h"


struct MeshRenderParameter
{
	std::string name;
	void* value;
	unsigned int size;
};

class Material : public Base
{
public:
	Material(void);
	void Load(std::string texture, std::string vShader, std::string pShader, std::string gShader = "");

private:
	std::shared_ptr<Texture2D> texture2D;
	std::shared_ptr<VertexShader> vertexShader;
	std::shared_ptr<PixelShader> pixelShader;
	std::shared_ptr<GeometryShader> geometryShader;

public:
	bool SetTexture(std::shared_ptr<Texture2D> newTexture);
	bool SetVertexShader(std::shared_ptr<VertexShader> newShader);
	bool SetPixelShader(std::shared_ptr<PixelShader> newShader);

public:
	void Bind(std::vector<MeshRenderParameter> parameters);
};