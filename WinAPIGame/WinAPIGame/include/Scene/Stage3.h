#pragma once
#include "Scene.h"

class Stage3 :
    public Scene
{
private:
	friend class SceneManager;

private:
	Stage3();
	~Stage3();

public:
	virtual bool Init();
};

