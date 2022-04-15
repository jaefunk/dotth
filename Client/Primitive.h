
#pragma once

#include "Object.h"
#include "StaticMeshComponent.h"

class Primitive : public Object
{
public:
	virtual void OnInit(void) override;
	virtual void OnUpdate(void) override;
	virtual void OnDraw(void) override;

public:
	virtual std::shared_ptr<dotth::model> CreatePrimitive(void) 
	{
		return nullptr;
	}

protected:
	std::shared_ptr<dotth::model> primitive;
	std::shared_ptr<StaticMeshComponent> staticMeshComponent;
};

class Plane : public Primitive
{
private:
	unsigned int angleCount;
public:
	Plane(unsigned int inAngleCount);
public:
	virtual std::shared_ptr<dotth::model> CreatePrimitive(void);
};

class Triangle : public Primitive
{
public:
	virtual std::shared_ptr<dotth::model> CreatePrimitive(void);
};

class Square : public Primitive
{
public:
	virtual std::shared_ptr<dotth::model> CreatePrimitive(void);
};

class Cube : public Primitive
{
public:
	virtual std::shared_ptr<dotth::model> CreatePrimitive(void);
};