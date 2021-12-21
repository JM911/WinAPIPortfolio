#pragma once
#include "Scene.h"

class TestSceneTwo :
    public Scene
{
private:
	friend class SceneManager;

private:
	TestSceneTwo();
	~TestSceneTwo();

public:
	virtual bool Init();
};

