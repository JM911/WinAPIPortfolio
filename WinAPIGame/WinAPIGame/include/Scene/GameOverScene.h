#pragma once
#include "Scene.h"

class GameOverScene :
    public Scene
{
private:
    friend class SceneManager;

private:
    GameOverScene();
    ~GameOverScene();

public:
    virtual bool Init();
};

