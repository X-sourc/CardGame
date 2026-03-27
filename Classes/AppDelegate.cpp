#include "AppDelegate.h"
#include "views/GameView.h"
#include "controllers/GameController.h"
#include "managers/UndoManager.h"
#include "base/CCDirector.h"
#include <windows.h>
USING_NS_CC;

static cocos2d::Size designResolutionSize = cocos2d::Size(1080, 2080);

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
    // 销毁回退管理器，防止内存泄漏
    UndoManager::destroyInstance();
}

void AppDelegate::initGLContextAttrs()
{
    GLContextAttrs glContextAttrs = { 8, 8, 8, 8, 24, 8 };
    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching()
{
    SetConsoleOutputCP(CP_UTF8); 
    cocos2d::Director::getInstance()->setDisplayStats(false);
    auto director = Director::getInstance();
    auto glView = director->getOpenGLView();

    if (!glView)
    {
        glView = GLViewImpl::createWithRect("CardGame", Rect(0, 0, 1080, 2080), 0.8f);
        director->setOpenGLView(glView);
    }

    glView->setDesignResolutionSize(
        designResolutionSize.width,
        designResolutionSize.height,
        ResolutionPolicy::EXACT_FIT
    );

    director->setDisplayStats(false);
    director->setAnimationInterval(1.0 / 60);

    // 启动游戏场景
    auto scene = GameView::createScene();
    director->runWithScene(scene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    Director::getInstance()->stopAnimation();
}

void AppDelegate::applicationWillEnterForeground()
{
    Director::getInstance()->startAnimation();
}