#include "SceneNode.h"
#pragma once
class Light :
	public SceneNode
{
public:
	Light(void);
	~Light(void);
	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);
	//XMVECTOR GetDiffuseColor();
	//XMVECTOR GetDirection();

private:
	//XMVECTOR m_diffuseColor;
	//XMVECTOR m_direction;
};