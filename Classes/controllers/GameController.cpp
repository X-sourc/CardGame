#include "GameController.h"
#include "views/GameView.h"
#include "views/CardView.h"
#include "models/GameModel.h"
#include "models/CardModel.h"
#include "models/UndoModel.h"
#include "managers/UndoManager.h"
#include "configs/loaders/LevelConfigLoader.h"
#include "../utils/CardEnum.h"
#include <cmath>

USING_NS_CC;

GameController::GameController(GameView* gameView)
    : _gameView(gameView)
{
    _undoManager = UndoManager::getInstance();
    _levelLoader = LevelConfigLoader::getInstance();
}

GameController::~GameController()
{
}

void GameController::startGame(int levelId)
{
    if (!_gameView || !_levelLoader) return;

    LevelConfig config = _levelLoader->loadLevel(levelId);
    _gameModel = GameModel::create();
    _gameModel->initCards(config.playFieldCards, config.stackCards);
    _gameView->initCardViews(_gameModel);

    if (_gameModel && !_gameModel->getStackCards().empty())
    {
        auto& stacks = _gameModel->getStackCards();
        CardModel* topCard = stacks.back();

        if (topCard)
        {
            _gameModel->setTopStackCard(topCard);
            CCLOG("✅ 游戏启动成功，顶牌点数: %d", (int)topCard->getCardFace());
        }
    }
}

bool GameController::handleCardClick(int cardId)
{
    if (!_gameModel || !_gameView) return false;

    CardModel* clickCard = _gameModel->getCardById(cardId);
    if (!clickCard) return false;

    CCLOG("🖱️ 点击卡牌 ID:%d 点数:%d", cardId, (int)clickCard->getCardFace());

    bool isStackCard = false;
    for (auto c : _gameModel->getStackCards()) {
        if (c && c->getCardId() == cardId) {
            isStackCard = true;
            break;
        }
    }

    bool isTopCard = (_gameModel->getTopStackCard() != nullptr
        && _gameModel->getTopStackCard()->getCardId() == cardId);

    if (isStackCard || isTopCard) {
        handleStackReplace(clickCard);
        return true;
    }
    else {
        if (isCardMatch(clickCard)) {
            handlePlayFieldMatch(clickCard);
            return true;
        }
        else {
            CCLOG("❌ 不匹配");
        }
    }
    return false;
}

bool GameController::isCardMatch(CardModel* card)
{
    if (!_gameModel || !card) return false;

    CardModel* topCard = _gameModel->getTopStackCard();
    if (!topCard) return false;

    int f1 = (int)card->getCardFace();
    int f2 = (int)topCard->getCardFace();
    bool ok = std::abs(f1 - f2) == 1;

    CCLOG("🔍 匹配检查:%d ↔ %d → %s", f1, f2, ok ? "成功" : "失败");
    return ok;
}

void GameController::handleStackReplace(CardModel* card)
{
    if (!card) return;

    CardModel* oldTop = _gameModel->getTopStackCard();
    Vec2 oldPos = _gameView->getCardViewById(card->getCardId())->getPosition();
    UndoModel* undo = new UndoModel(UndoType::UT_STACK_REPLACE, card, oldPos, oldTop);
    _undoManager->addUndoRecord(undo);

    Vec2 topPos(730, 300);
    _gameView->playMatchAnimation(card->getCardId(), topPos);
    card->setPosition(topPos);
    _gameModel->setTopStackCard(card);

    CCLOG("✅ 底牌已设为新顶牌");
}

void GameController::handlePlayFieldMatch(CardModel* card)
{
    if (!card) return;

    CardModel* oldTop = _gameModel->getTopStackCard();
    Vec2 oldPos = _gameView->getCardViewById(card->getCardId())->getPosition();
    UndoModel* undo = new UndoModel(UndoType::UT_PLAYFIELD_MATCH, card, oldPos, oldTop);
    _undoManager->addUndoRecord(undo);

    Vec2 topPos(730, 300);
    _gameView->playMatchAnimation(card->getCardId(), topPos);
    card->setPosition(topPos);
    card->setCardState(CardState::CS_REMOVED);
    _gameModel->setTopStackCard(card);

    CCLOG("✅ 桌面牌匹配成功！");
}

void GameController::handleUndoClick()
{
    if (!_undoManager || _undoManager->isEmpty())
    {
        CCLOG("↩️ 无可回退记录，已回到最初状态");
        return;
    }

    UndoModel* undo = _undoManager->popUndoRecord();
    if (!undo) return;

    CardModel* card = undo->getCard();
    Vec2 oldPos = undo->getOldPosition();
    CardModel* oldTop = undo->getOldTopCard();

    // 动画飞回原位置
    _gameView->playUndoAnimation(undo);

    // 恢复卡牌位置和状态
    if (card) {
        card->setPosition(oldPos);
        card->setCardState(CardState::CS_OPENED);
    }

    // 恢复旧顶牌
    if (_gameModel) {
        _gameModel->setTopStackCard(oldTop);
    }

    delete undo;
    CCLOG("↩️ 回退成功");
}