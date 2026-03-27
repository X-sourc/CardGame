#ifndef _LEVEL_CONFIG_LOADER_H_
#define _LEVEL_CONFIG_LOADER_H_

#include "cocos2d.h"
#include "configs/models/LevelConfig.h"

class LevelConfigLoader
{
public:
    static LevelConfigLoader* getInstance();
    LevelConfig loadLevel(int levelId);

private:
    static LevelConfigLoader* _instance;
    LevelConfigLoader() = default;
};

#endif