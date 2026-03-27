#ifndef _GAME_CONTROLLER_H_
#define _GAME_CONTROLLER_H_

#include "cocos2d.h"

USING_NS_CC;

class GameView;
class GameModel;
class UndoManager;
class LevelConfigLoader;
class CardModel;

class GameController
{
public:
    GameController(GameView* gameView);
    ~GameController();
    void startGame(int levelId = 1);
    bool handleCardClick(int cardId);
    void handleUndoClick();

private:
    bool isCardMatch(CardModel* card);
    void handleStackReplace(CardModel* card);
    void handlePlayFieldMatch(CardModel* card);

    GameView* _gameView;
    GameModel* _gameModel;
    UndoManager* _undoManager;
    LevelConfigLoader* _levelLoader;
};

#endif