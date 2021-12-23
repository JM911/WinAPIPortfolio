#pragma once
#include "Scene.h"

class Stage2 :
    public Scene
{
private:
	friend class SceneManager;

private:
	Stage2();
	~Stage2();

public:
	virtual bool Init();
};

