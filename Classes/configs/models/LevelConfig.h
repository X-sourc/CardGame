#ifndef _LEVEL_CONFIG_H_
#define _LEVEL_CONFIG_H_

#include "cocos2d.h"
#include "utils/CardEnum.h"

USING_NS_CC;

struct CardConfig
{
    CardFaceType cardFace;
    CardSuitType cardSuit;
    Vec2 position;
    int cardId;
};

class LevelConfig
{
public:
    std::vector<CardConfig> playFieldCards;
    std::vector<CardConfig> stackCards;
};

#endif