#pragma once

#include "Node.h"

class Object : public Node<Object>
{
public:
	void Init(void);
	void Update(void);
	void Draw(void);
	void Destroy(void);

protected:
	virtual void OnInit(void);
	virtual void OnDestroy(void);
	virtual void OnUpdate(void);
	virtual void OnDraw(void);
};
