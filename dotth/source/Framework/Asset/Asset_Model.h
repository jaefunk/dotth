#pragma once

#include "Framework/Asset/Asset_Renderable.h"
#include "Graphics/Drawable.h"

#ifdef max
#undef max
#endif
#ifdef min
#undef min
#endif

#include "assimp/Importer.hpp"
#include "assimp/postprocess.h"
#include "assimp/scene.h"

class Asset_Model : public Asset_Renderable
{
public:
	Asset_Model(void);
	virtual void Bind(void) override;

private:
	virtual bool OnLoad(void* data, size_t size) override;

public:
	const aiScene* _Scene;
	std::vector<Drawable> _Drawables;
};