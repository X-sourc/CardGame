#include "LevelConfigLoader.h"
#include "utils/CardEnum.h"

LevelConfigLoader* LevelConfigLoader::_instance = nullptr;

LevelConfigLoader* LevelConfigLoader::getInstance()
{
    if (!_instance)
        _instance = new LevelConfigLoader();
    return _instance;
}

LevelConfig LevelConfigLoader::loadLevel(int levelId)
{
    LevelConfig config;

    // 6张桌面牌
    // K♣、3♣、3♦、3♣、3♣、2♣
    config.playFieldCards = {
        // 左边：向右下阶梯
        { CardFaceType(12), CardSuitType(0), Vec2(350, 600), 1 },
        { CardFaceType(2),  CardSuitType(0), Vec2(400, 520), 2 },
        { CardFaceType(2),  CardSuitType(1), Vec2(450, 440), 3 },
        // 右边：向左下阶梯
        { CardFaceType(2),  CardSuitType(0), Vec2(850, 600), 4 },  // 第一张（最上面）
        { CardFaceType(2),  CardSuitType(0), Vec2(800, 550), 5 },  // 向左下
        { CardFaceType(1),  CardSuitType(3), Vec2(750, 500), 6 },  // 再向左下
    };

    // 底牌（左边叠放 + 右边顶牌分离）
    config.stackCards = {
        { CardFaceType(2),  CardSuitType(0), Vec2(400, 200),  7 },  // 3♣ (底层)
        { CardFaceType(0),  CardSuitType(2), Vec2(440, 200),  8 },  // A♥ (叠在 3♣ 上)
        { CardFaceType(3),  CardSuitType(0), Vec2(600, 200),  9 },  // 4♣ (顶牌，右侧)
    };

    return config;
}