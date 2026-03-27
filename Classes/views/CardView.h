#pragma once

#include "cocos2d.h"
#include "../models/CardModel.h"

typedef std::function<void(int)> CardClickCallback;

class CardView : public cocos2d::Sprite
{
public:
    CardView();
    ~CardView();

    static CardView* create(CardModel* cardModel);
    bool init(CardModel* cardModel);

    void setCardClickCallback(const CardClickCallback& callback);
    void playMoveAnimation(const cocos2d::Vec2& targetPos);
    CardModel* getCardModel();

private:
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);

    CardModel* _model;
    CardClickCallback _callback;
};