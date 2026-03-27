#ifndef _ANIMATION_UTILS_H_
#define _ANIMATION_UTILS_H_

#include "cocos2d.h"

USING_NS_CC;

class AnimationUtils
{
public:
    static Action* createMoveTo(Vec2 pos, float time);
};

#endif