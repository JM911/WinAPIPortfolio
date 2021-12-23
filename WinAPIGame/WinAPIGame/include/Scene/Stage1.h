#pragma once
#include "Scene.h"

class Stage1 :
    public Scene
{
private:
	friend class SceneManager;

private:
	Stage1();
	~Stage1();

public:
	virtual bool Init();
};

