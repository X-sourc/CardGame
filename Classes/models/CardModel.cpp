#include "CardModel.h"

CardModel::CardModel(int cardId, CardFaceType face, CardSuitType suit, Vec2 pos)
    : _cardId(cardId),
    _cardFace(face),
    _cardSuit(suit),
    _position(pos),
    _cardState(CardState::CS_OPENED)
{
}

int CardModel::getCardId() const
{
    return _cardId;
}

CardFaceType CardModel::getCardFace() const
{
    return _cardFace;
}

CardSuitType CardModel::getCardSuit() const
{
    return _cardSuit;
}

Vec2 CardModel::getPosition() const
{
    return _position;
}

void CardModel::setPosition(Vec2 pos)
{
    _position = pos;
}

CardState CardModel::getCardState() const
{
    return _cardState;
}

void CardModel::setCardState(CardState state)
{
    _cardState = state;
}