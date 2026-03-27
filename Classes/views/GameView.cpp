#include "GameView.h"
#include "views/CardView.h"
#include "models/GameModel.h"
#include "models/UndoModel.h"
#include "controllers/GameController.h"

USING_NS_CC;

Scene* GameView::createScene()
{
    auto scene = Scene::create();
    auto layer = GameView::create();
    scene->addChild(layer);
    return scene;
}

bool GameView::init()
{
    if (!Layer::init()) return false;

    Size winSize = Director::getInstance()->getWinSize();

    // 棕色
    auto brownBg = LayerColor::create(Color4B(101, 67, 33, 255));
    brownBg->setContentSize(Size(winSize.width, winSize.height * 0.7f));
    brownBg->setPosition(Vec2(0, winSize.height * 0.3f));
    this->addChild(brownBg, -1);

    // 紫色
    auto purpleBg = LayerColor::create(Color4B(74, 40, 92, 255));
    purpleBg->setContentSize(Size(winSize.width, winSize.height * 0.3f));
    purpleBg->setPosition(Vec2(0, 0));
    this->addChild(purpleBg, -1);

    CCLOG("✅ GameView 初始化成功，已显示棕色+紫色牌桌背景！");

    // 初始化控制器并启动游戏
    _controller = new GameController(this);
    _controller->startGame(1);

  
    // 回退按钮
   
    float purpleHeight = winSize.height * 0.3f;
    auto undoLabel = Label::createWithSystemFont("undo", "SimHei", 36);
    undoLabel->setTextColor(Color4B::WHITE);
    auto undoBtn = MenuItemLabel::create(undoLabel, [=](Ref* sender) {
        _controller->handleUndoClick();
        });
    undoBtn->setPosition(Vec2(winSize.width - 100, purpleHeight / 2));
    auto menu = Menu::create(undoBtn, nullptr);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 100);
    return true;
}

void GameView::initCardViews(GameModel* model)
{
    CCLOG("✅ initCardViews 开始创建卡牌");

    _cardMap.clear();

   
    //左侧 3 张：向右下阶梯
   
    float leftX = 250;
    float topY = 1550;
    float stepX = 70;
    float stepY = -220;

    
    // 右侧 3 张：向左下阶梯
   
    float rightStartX = 840;   // 最右侧起点
    float rightStepX = -70;    // X 减小 → 向左
    float rightStepY = -220;    // Y 减小 → 向下

    int index = 0;
    for (auto c : model->getPlayFieldCards())
    {
        auto cv = CardView::create(c);
        cv->setCardClickCallback([=](int cardId) {
            _controller->handleCardClick(cardId);
            });
        cv->setScale(1.8f);
        if (index < 3) {
            // 左边：向右下
            cv->setPosition(Vec2(leftX + index * stepX, topY + index * stepY));
        }
        else {
            // 右边：向左下
            int idx = index - 3;
            cv->setPosition(Vec2(rightStartX + idx * rightStepX, topY + idx * rightStepY));
        }

        addChild(cv, 10 + index);
        _cardMap[c->getCardId()] = cv;
        CCLOG("创建桌面卡牌 ID: %d", c->getCardId());
        index++;
    }

    // 底牌区位置
    int stackIndex = 0;
    for (auto c : model->getStackCards())
    {
        auto cv = CardView::create(c);
        cv->setCardClickCallback([=](int cardId) {
            _controller->handleCardClick(cardId);
            });
        cv->setScale(1.8f);
        if (stackIndex == 0) {
            cv->setPosition(Vec2(210, 300));
        }
        else if (stackIndex == 1) {
            cv->setPosition(Vec2(410, 300));
        }
        else {
            cv->setPosition(Vec2(730, 300));
        }

        addChild(cv, 100);
        _cardMap[c->getCardId()] = cv;
        CCLOG("创建底牌卡牌 ID: %d", c->getCardId());
        stackIndex++;
    }

    CCLOG("✅ 卡牌创建完成，总数：%d", (int)_cardMap.size());
}


//飞过去的卡牌一定在最上面

void GameView::playMatchAnimation(int cardId, Vec2 pos)
{
    auto cv = getCardViewById(cardId);
    if (cv) {
        this->reorderChild(cv, 200); 
        cv->playMoveAnimation(pos);
    }
}

// 回退时恢复原来的层级
void GameView::playUndoAnimation(UndoModel* undo)
{
    auto cv = getCardViewById(undo->getCard()->getCardId());
    if (cv) {
        // 回退时恢复原来的显示顺序
        if (undo->getUndoType() == UndoType::UT_PLAYFIELD_MATCH) {
            this->reorderChild(cv, 10);  // 桌面牌
        }
        else {
            this->reorderChild(cv, 100); // 底牌/顶牌
        }
        cv->playMoveAnimation(undo->getOldPosition());
    }
}

CardView* GameView::getCardViewById(int id)
{
    auto it = _cardMap.find(id);
    if (it != _cardMap.end()) {
        return it->second;
    }
    return nullptr;
}