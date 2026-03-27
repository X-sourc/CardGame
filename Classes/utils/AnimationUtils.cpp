#include "AnimationUtils.h"

USING_NS_CC;

Action* AnimationUtils::createMoveTo(Vec2 pos, float time)
{
    return MoveTo::create(time, pos);
}