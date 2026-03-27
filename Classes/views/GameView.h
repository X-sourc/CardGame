#ifndef _GAME_VIEW_H_
#define _GAME_VIEW_H_

#include "cocos2d.h"

USING_NS_CC;

class GameModel;
class CardView;
class UndoModel;
class GameController;

class GameView : public Layer
{
public:
    static Scene* createScene();
    virtual bool init() override;
    void initCardViews(GameModel* model);
    void playMatchAnimation(int cardId, Vec2 pos);
    void playUndoAnimation(UndoModel* undo);
    CREATE_FUNC(GameView);

    GameController* getController() { return _controller; }

    CardView* getCardViewById(int id);

private:
    std::map<int, CardView*> _cardMap;
    GameController* _controller;
};

#endif