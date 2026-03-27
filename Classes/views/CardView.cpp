#include "CardView.h"
#include "../models/CardModel.h"
#include "../utils/CardEnum.h"
USING_NS_CC;

CardView::CardView()
    : _model(nullptr)
    , _callback(nullptr)
{
}

CardView::~CardView()
{
}

CardView* CardView::create(CardModel* cardModel)
{
    CardView* ref = new CardView();
    if (ref && ref->init(cardModel))
    {
        ref->autorelease();
        return ref;
    }
    CC_SAFE_DELETE(ref);
    return nullptr;
}

bool CardView::init(CardModel* cardModel)
{
    if (!Sprite::init())
        return false;

    _model = cardModel;

    // 卡牌背景
    setTexture("cards/card_general.png");
    setContentSize(Size(150, 200));
    setAnchorPoint(Vec2(0.5f, 0.5f));

    CardFaceType face = _model->getCardFace();
    CardSuitType suit = _model->getCardSuit();
    bool isRed = (suit == CardSuitType::CST_HEARTS || suit == CardSuitType::CST_DIAMONDS);

    // ==========================
    // 中间：大图片（A 2 3 4 ... J Q K）
    // ==========================
    std::string bigImg;
    switch (face)
    {
    case CardFaceType::CFT_ACE:    bigImg = isRed ? "cards/big_red_A.png" : "cards/big_black_A.png"; break;
    case CardFaceType::CFT_TWO:    bigImg = isRed ? "cards/big_red_2.png" : "cards/big_black_2.png"; break;
    case CardFaceType::CFT_THREE:  bigImg = isRed ? "cards/big_red_3.png" : "cards/big_black_3.png"; break;
    case CardFaceType::CFT_FOUR:   bigImg = isRed ? "cards/big_red_4.png" : "cards/big_black_4.png"; break;
    case CardFaceType::CFT_FIVE:   bigImg = isRed ? "cards/big_red_5.png" : "cards/big_black_5.png"; break;
    case CardFaceType::CFT_SIX:    bigImg = isRed ? "cards/big_red_6.png" : "cards/big_black_6.png"; break;
    case CardFaceType::CFT_SEVEN:  bigImg = isRed ? "cards/big_red_7.png" : "cards/big_black_7.png"; break;
    case CardFaceType::CFT_EIGHT:  bigImg = isRed ? "cards/big_red_8.png" : "cards/big_black_8.png"; break;
    case CardFaceType::CFT_NINE:   bigImg = isRed ? "cards/big_red_9.png" : "cards/big_black_9.png"; break;
    case CardFaceType::CFT_TEN:    bigImg = isRed ? "cards/big_red_10.png" : "cards/big_black_10.png"; break;
    case CardFaceType::CFT_JACK:   bigImg = isRed ? "cards/big_red_J.png" : "cards/big_black_J.png"; break;
    case CardFaceType::CFT_QUEEN:  bigImg = isRed ? "cards/big_red_Q.png" : "cards/big_black_Q.png"; break;
    case CardFaceType::CFT_KING:   bigImg = isRed ? "cards/big_red_K.png" : "cards/big_black_K.png"; break;
    default: break;
    }

    if (!bigImg.empty())
    {
        auto bigSpr = Sprite::create(bigImg);
        bigSpr->setScale(0.7f);
        bigSpr->setPosition(getContentSize().width / 2, getContentSize().height / 2);
        this->addChild(bigSpr, 1);
    }

    // ==========================
    // 左上角：小图片
    // ==========================
    std::string smallImg;
    switch (face)
    {
    case CardFaceType::CFT_ACE:    smallImg = isRed ? "cards/small_red_A.png" : "cards/small_black_A.png"; break;
    case CardFaceType::CFT_TWO:    smallImg = isRed ? "cards/small_red_2.png" : "cards/small_black_2.png"; break;
    case CardFaceType::CFT_THREE:  smallImg = isRed ? "cards/small_red_3.png" : "cards/small_black_3.png"; break;
    case CardFaceType::CFT_FOUR:   smallImg = isRed ? "cards/small_red_4.png" : "cards/small_black_4.png"; break;
    case CardFaceType::CFT_FIVE:   smallImg = isRed ? "cards/small_red_5.png" : "cards/small_black_5.png"; break;
    case CardFaceType::CFT_SIX:    smallImg = isRed ? "cards/small_red_6.png" : "cards/small_black_6.png"; break;
    case CardFaceType::CFT_SEVEN:  smallImg = isRed ? "cards/small_red_7.png" : "cards/small_black_7.png"; break;
    case CardFaceType::CFT_EIGHT:  smallImg = isRed ? "cards/small_red_8.png" : "cards/small_black_8.png"; break;
    case CardFaceType::CFT_NINE:   smallImg = isRed ? "cards/small_red_9.png" : "cards/small_black_9.png"; break;
    case CardFaceType::CFT_TEN:    smallImg = isRed ? "cards/small_red_10.png" : "cards/small_black_10.png"; break;
    case CardFaceType::CFT_JACK:   smallImg = isRed ? "cards/small_red_J.png" : "cards/small_black_J.png"; break;
    case CardFaceType::CFT_QUEEN:  smallImg = isRed ? "cards/small_red_Q.png" : "cards/small_black_Q.png"; break;
    case CardFaceType::CFT_KING:   smallImg = isRed ? "cards/small_red_K.png" : "cards/small_black_K.png"; break;
    default: break;
    }

    if (!smallImg.empty())
    {
        auto smallSpr = Sprite::create(smallImg);
        smallSpr->setScale(0.8f);
        smallSpr->setPosition(30, getContentSize().height - 25);
        this->addChild(smallSpr, 2);
    }

    // ==========================
    // 右上角：花色图片
    // ==========================
    std::string suitImg;
    switch (suit)
    {
    case CardSuitType::CST_CLUBS:    suitImg = "cards/club.png"; break;
    case CardSuitType::CST_DIAMONDS: suitImg = "cards/diamond.png"; break;
    case CardSuitType::CST_HEARTS:   suitImg = "cards/heart.png"; break;
    case CardSuitType::CST_SPADES:   suitImg = "cards/spade.png"; break;
    default: break;
    }

    if (!suitImg.empty())
    {
        auto suitSpr = Sprite::create(suitImg);
        suitSpr->setScale(0.8f);
        suitSpr->setPosition(120, getContentSize().height - 25);
        this->addChild(suitSpr, 2);
    }


    // 触摸
    auto listener = EventListenerTouchOneByOne::create();
    listener->setSwallowTouches(true);
    listener->onTouchBegan = CC_CALLBACK_2(CardView::onTouchBegan, this);
    listener->onTouchEnded = CC_CALLBACK_2(CardView::onTouchEnded, this);
    _eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    return true;
}

bool CardView::onTouchBegan(Touch* touch, Event* event)
{
    Vec2 location = this->convertToNodeSpace(touch->getLocation());
    Rect rect = Rect(0, 0, getContentSize().width, getContentSize().height);
    return rect.containsPoint(location);
}

void CardView::onTouchEnded(Touch* touch, Event* event)
{
    if (_callback)
        _callback(_model->getCardId());
}

void CardView::setCardClickCallback(const CardClickCallback& callback)
{
    _callback = callback;
}

void CardView::playMoveAnimation(const Vec2& targetPos)
{
    auto move = MoveTo::create(0.2f, targetPos);
    this->runAction(move);
}

CardModel* CardView::getCardModel()
{
    return _model;
}