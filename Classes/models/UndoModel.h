#ifndef _UNDO_MODEL_H_
#define _UNDO_MODEL_H_

#include "cocos2d.h"
#include "models/CardModel.h"

USING_NS_CC;

enum class UndoType
{
    UT_STACK_REPLACE,
    UT_PLAYFIELD_MATCH
};

class UndoModel
{
public:
    UndoModel(UndoType type, CardModel* card, Vec2 oldPos, CardModel* oldTopCard);
    UndoType getUndoType() const;
    CardModel* getCard() const;
    Vec2 getOldPosition() const;
    CardModel* getOldTopCard() const;

private:
    UndoType _type;
    CardModel* _card;
    Vec2 _oldPos;
    CardModel* _oldTopCard;
};

#endif