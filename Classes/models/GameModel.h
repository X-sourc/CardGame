#ifndef _GAME_MODEL_H_
#define _GAME_MODEL_H_

#include "cocos2d.h"
#include <vector>
#include <stack>   
#include "models/CardModel.h"
#include "configs/models/LevelConfig.h"

USING_NS_CC;

// 保存一步游戏状态
struct GameState
{
    std::vector<CardModel*> playCards;
    std::vector<CardModel*> stackCards;
    CardModel* topCard;
};

class GameModel
{
public:
    static GameModel* create();
    bool init();

    void initCards(const std::vector<CardConfig>& playField, const std::vector<CardConfig>& stack);
    CardModel* getCardById(int cardId);
    void setTopStackCard(CardModel* card);
    CardModel* getTopStackCard();
    std::vector<CardModel*>& getPlayFieldCards();
    std::vector<CardModel*>& getStackCards();

    // 回退功能
    void saveState();  // 保存当前状态
    void undo();       // 回退上一步
    bool canUndo();    // 是否可以回退

private:
    std::vector<CardModel*> _playCards;
    std::vector<CardModel*> _stackCards;
    CardModel* _topCard;

    // 状态栈
    std::stack<GameState> _stateHistory;
};

#endif