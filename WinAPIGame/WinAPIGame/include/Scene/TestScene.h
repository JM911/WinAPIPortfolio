#pragma once
#include "Scene.h"

class TestScene	:
	public Scene
{
private:
	friend class SceneManager;

private:
	TestScene();
	~TestScene();

public:
	virtual bool Init();
};

