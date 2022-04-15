
#include "Primitive.h"

void Primitive::OnInit(void)
{
	primitive = CreatePrimitive();
	if (primitive == nullptr)
		return;

	auto staticMesh = new StaticMesh;
	staticMesh->Load(primitive);
	staticMesh->GetMaterial(0)->Load(
		"uv_checker",
		"../Output/Client/x64/Debug/test_vs.cso",
		"../Output/Client/x64/Debug/test_ps.cso",
		"../Output/Client/x64/Debug/test_gs.cso");
	staticMeshComponent = AddComponent<StaticMeshComponent>();
	staticMeshComponent->SetStaticMesh(staticMesh);	
}

void Primitive::OnUpdate(void)
{
	//RotateYaw(0.01f);
	//RotatePitch(0.005f);
}

void Primitive::OnDraw(void)
{	
}

std::shared_ptr<dotth::model> Triangle::CreatePrimitive(void)
{
	/*
	*		   a
	*		  / \
	*		 /___\
	*		c	  b
	*/

	std::shared_ptr<dotth::model> model = std::make_shared<dotth::model>();
	model->name = "triangle";
	
	model->root = new dotth::node;
	model->root->name = "root";

	dotth::mesh* mesh = new dotth::mesh;
	mesh->name = "triangleMesh";
	dotth::vector3 pa(0.f, 0.5f, 0.f);
	dotth::vector3 pb(0.5f, -0.5f, 0.f);
	dotth::vector3 pc(-0.5f, -0.5f, 0.f);
	mesh->positions = { pa, pb, pc };

	dotth::vector4 ca(1.f, 0.0f, 0.f, 1.f);
	dotth::vector4 cb(0.f, 1.0f, 0.f, 1.f);
	dotth::vector4 cc(0.f, 0.0f, 1.f, 1.f);
	mesh->colors = { ca, cb, cc };

	enum point { A, B, C };
	mesh->indices = { A, B, C };

	model->meshes.push_back(mesh);

	return model;
}

std::shared_ptr<dotth::model> Square::CreatePrimitive(void)
{
	/*
	*	 a-----b
	*	 |	   |
	* 	 |	   |
	*	 d-----c
	*/

	std::shared_ptr<dotth::model> model = std::make_shared<dotth::model>();
	model->name = "square";

	model->root = new dotth::node;
	model->root->name = "root";

	dotth::mesh* mesh = new dotth::mesh;
	mesh->name = "squareMesh";
	dotth::vector3 pa(-0.5f, 0.5f, 0.f);
	dotth::vector3 pb(0.5f, 0.5f, 0.f); 
	dotth::vector3 pc(0.5f, -0.5f, 0.f);
	dotth::vector3 pd(-0.5f, -0.5f, 0.f); 
	mesh->positions = { pa, pb, pc, pd };

	dotth::vector4 ca(1.f, 0.f, 0.f, 1.f);
	dotth::vector4 cb(0.f, 1.f, 0.f, 1.f);
	dotth::vector4 cc(0.f, 0.f, 1.f, 1.f);
	dotth::vector4 cd(1.f, 0.f, 1.f, 1.f);
	mesh->colors = { ca, cb, cc, cd };

	enum point { A, B, C, D };
	mesh->indices = { A, B, C, A, C, D };

	model->meshes.push_back(mesh);

	return model;
}

std::shared_ptr<dotth::model> Cube::CreatePrimitive(void)
{
	/*	
	*       F-------------------E
	*      /|                  /|
	*     / |                 / |
	*    /  |                /  |
	*   A-------------------B   |
	*   |   |               |   |
	*   |   |               |   |
	*   |   |               |   |
	*   |   |               |   |
	*   |   G---------------|---H
	*   |  /                |  /
	*   | /                 | /
	*   |/                  |/
	*   D-------------------C
	*/

	std::shared_ptr<dotth::model> model = std::make_shared<dotth::model>();
	model->name = "cube";

	model->root = new dotth::node;
	model->root->name = "root";

	dotth::mesh* mesh = new dotth::mesh;
	mesh->name = "cubeMesh";
	dotth::vector3 pa(-0.5f, 0.5f, -0.5f);
	dotth::vector3 pb(0.5f, 0.5f, -0.5f);
	dotth::vector3 pc(0.5f, -0.5f, -0.5f);
	dotth::vector3 pd(-0.5f, -0.5f, -0.5f);
	dotth::vector3 pe(0.5f, 0.5f, 0.5f);
	dotth::vector3 pf(-0.5f, 0.5f, 0.5f);
	dotth::vector3 pg(-0.5f, -0.5f, 0.5f);
	dotth::vector3 ph(0.5f, -0.5f, 0.5f);

	dotth::vector4 ca(1.f, 0.f, 0.f, 1.f);
	dotth::vector4 cb(0.f, 1.f, 0.f, 1.f);
	dotth::vector4 cc(0.f, 0.f, 1.f, 1.f);
	dotth::vector4 cd(1.f, 0.f, 1.f, 1.f);
	dotth::vector4 ce(1.f, 0.f, 0.f, 1.f);
	dotth::vector4 cf(0.f, 1.f, 0.f, 1.f);
	dotth::vector4 cg(0.f, 0.f, 1.f, 1.f);
	dotth::vector4 ch(1.f, 0.f, 1.f, 1.f);

	mesh->positions = { pa, pb, pc, pd, pe, pf, pg, ph };
	mesh->colors = { ca, cb, cc, cd, ce, cf, cg, ch };
	
	enum point { A, B, C, D, E, F, G, H };
	mesh->indices = { 
		A, B, C, A, C, D,	// front
		E, F, G, E, G, H,	// back
		F, E, B, F, B, A,	// top
		D, C, H, D, H, G,	// bottom
		F, A, D, F, D, G,	// left
		B, E, H, B, H, C,	// right
	};

	model->meshes.push_back(mesh);

	return model;
}

Plane::Plane(unsigned int inAngleCount)
{
	angleCount = inAngleCount;
}

std::shared_ptr<dotth::model> Plane::CreatePrimitive(void)
{
	if (angleCount <= 2)
		return nullptr;

	std::shared_ptr<dotth::model> model = std::make_shared<dotth::model>();
	model->name = "plane";

	model->root = new dotth::node;
	model->root->name = "root";

	dotth::mesh* mesh = new dotth::mesh;
	mesh->name = "planeMesh";

	const float unitAngle = 2.f * 3.141592f / static_cast<float>(angleCount);
	for (unsigned int i = 0; i < angleCount; ++i)
	{
		float angle = -unitAngle * static_cast<float>(i);
		mesh->positions.push_back(dotth::vector3(cosf(angle)*0.5f, sinf(angle) * 0.5f, 0.f));
		mesh->colors.push_back(dotth::vector4(1.f, 1.f, 1.f, 1.f));

		if (i >= 2)
		{
			mesh->indices.push_back(0);
			mesh->indices.push_back(i-1);
			mesh->indices.push_back(i);
		}
	}

	//enum point { A, B, C, D, E, F, G, H };
	//mesh->indices = {
	//	A, B, C
	//};
	//dotth::vector4 ca(1.f, 0.0f, 0.f, 1.f);
	//dotth::vector4 cb(0.f, 1.0f, 0.f, 1.f);
	//dotth::vector4 cc(0.f, 0.0f, 1.f, 1.f);
	//mesh->colors = { ca, cb, cc };
	model->meshes.push_back(mesh);

	return model;
}
