#include "GameModel.h"
#include "cocos2d.h"

USING_NS_CC;

GameModel* GameModel::create()
{
    GameModel* model = new GameModel();
    if (model && model->init())
    {
        return model;
    }
    delete model;
    return nullptr;
}

bool GameModel::init()
{
    _topCard = nullptr;
    return true;
}

void GameModel::initCards(const std::vector<CardConfig>& playField, const std::vector<CardConfig>& stack)
{
    CCLOG("initCards: 桌面牌数量 = %d, 底牌数量 = %d", (int)playField.size(), (int)stack.size());

    // 清空原有数据
    _playCards.clear();
    _stackCards.clear();

    // 自动加载 JSON 配置的桌面牌
    for (auto& cfg : playField)
    {
        _playCards.push_back(new CardModel(cfg.cardId, cfg.cardFace, cfg.cardSuit, cfg.position));
    }

    // 自动加载 JSON 配置的底牌
    for (auto& cfg : stack)
    {
        _stackCards.push_back(new CardModel(cfg.cardId, cfg.cardFace, cfg.cardSuit, cfg.position));
    }

    CCLOG("initCards 完成，最终桌面牌 = %d, 底牌 = %d", (int)_playCards.size(), (int)_stackCards.size());

    // 初始化后保存第一个状态
    saveState();
}

CardModel* GameModel::getCardById(int cardId)
{
    for (auto c : _playCards)
    {
        if (c->getCardId() == cardId)
            return c;
    }
    for (auto c : _stackCards)
    {
        if (c->getCardId() == cardId)
            return c;
    }
    return nullptr;
}

void GameModel::setTopStackCard(CardModel* card)
{
    _topCard = card;
}

CardModel* GameModel::getTopStackCard()
{
    return _topCard;
}

std::vector<CardModel*>& GameModel::getPlayFieldCards()
{
    return _playCards;
}

std::vector<CardModel*>& GameModel::getStackCards()
{
    return _stackCards;
}

    // 保存状态

void GameModel::saveState()
{
    GameState state;
    state.playCards = _playCards;
    state.stackCards = _stackCards;
    state.topCard = _topCard;
    _stateHistory.push(state);
}
    //回退
void GameModel::undo()
{
    if (_stateHistory.size() <= 1) {
        CCLOG("已经是最初状态，无法回退");
        return;
    }
    // 弹出当前状态
    _stateHistory.pop();
    // 恢复上一个状态
    GameState lastState = _stateHistory.top();
    _playCards = lastState.playCards;
    _stackCards = lastState.stackCards;
    _topCard = lastState.topCard;

    CCLOG("✅ 回退成功！恢复到上一步");
}

//是否可以回退
bool GameModel::canUndo()
{
    return _stateHistory.size() > 1;
}