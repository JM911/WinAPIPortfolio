#pragma once
#include "Scene.h"

class GameClearScene :
    public Scene
{
private:
    friend class SceneManager;

private:
    GameClearScene();
    ~GameClearScene();

public:
    virtual bool Init();

public:
    void RetryButtonCallback(float fDeltaTime);
    void EndButtonCallback(float fDeltaTime);
};

