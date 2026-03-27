#include "UndoModel.h"

UndoModel::UndoModel(UndoType type, CardModel* card, Vec2 oldPos, CardModel* oldTopCard)
    : _type(type),
    _card(card),
    _oldPos(oldPos),
    _oldTopCard(oldTopCard)
{
}

UndoType UndoModel::getUndoType() const
{
    return _type;
}

CardModel* UndoModel::getCard() const
{
    return _card;
}

Vec2 UndoModel::getOldPosition() const
{
    return _oldPos;
}

CardModel* UndoModel::getOldTopCard() const
{
    return _oldTopCard;
}