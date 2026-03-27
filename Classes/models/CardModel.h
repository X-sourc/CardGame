#ifndef _CARD_MODEL_H_
#define _CARD_MODEL_H_

#include "cocos2d.h"
#include "utils/CardEnum.h"

USING_NS_CC;

enum class CardState
{
    CS_CLOSED,
    CS_OPENED,
    CS_REMOVED
};

class CardModel
{
public:
    CardModel(int cardId, CardFaceType face, CardSuitType suit, Vec2 pos);
    int getCardId() const;
    CardFaceType getCardFace() const;
    CardSuitType getCardSuit() const;
    Vec2 getPosition() const;
    void setPosition(Vec2 pos);
    CardState getCardState() const;
    void setCardState(CardState state);

private:
    int _cardId;
    CardFaceType _cardFace;
    CardSuitType _cardSuit;
    Vec2 _position;
    CardState _cardState;
};

#endif