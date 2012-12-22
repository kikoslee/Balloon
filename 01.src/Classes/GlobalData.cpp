#include "GlobalData.h"

float gScreenWidth;
float gScreenHeight;
float gScreenWidthHalf;
float gScreenHeightHalf;

int gTestLevel = 0;
GameMode gGameMode = kGameModeNormal;
int gCurScore = 0;
int gHighScore = 0;
const char* gLeaderboardName = "balloon.free";

// 评论引导
bool gIsReviewd = false;        // 是否已经进行过评论
int gCurReviewCount = 3;        // 当前评论计数,每10次游戏弹出一遍

LevelDetail gLevelDetail[10] = {
    { false,  40, 10 },
    { false,  80, 15 },
    { false,  90,  8 },
    { false, 120, 20 },
    { false, 150, 12 },
    { false, 160, 10 },
    { false,  50,  5 },
    { false,  70,  3 },
    { false, 600, 25 },
    { false, 300, 20 }
};

void GlobalData::load()
{
    CCUserDefault* ud = CCUserDefault::sharedUserDefault();

    gHighScore = ud->getIntegerForKey("highestScore", 0);
    gTestLevel = ud->getIntegerForKey("curStage", 0);
    for (int i=0; i<10; i++)
        gLevelDetail[i].isClear = ud->getBoolForKey(fcs("levelDetail%d", i), false);
    
    gIsReviewd = ud->getBoolForKey("isReviewed", false);
    gCurReviewCount = ud->getIntegerForKey("CurReviewCount", 3);
}

void GlobalData::save()
{
    CCUserDefault* ud = CCUserDefault::sharedUserDefault();

    int oldScore = ud->getIntegerForKey("highestScore", 0);
    if (gHighScore > oldScore)
        ud->setIntegerForKey("highestScore", gHighScore);
    
    ud->setIntegerForKey("curStage", gTestLevel);

    for (int i=0; i<10; i++)
        ud->setBoolForKey(fcs("levelDetail%d", i), gLevelDetail[i].isClear);
    
    ud->setBoolForKey("isReviewed", gIsReviewd);
    ud->setIntegerForKey("CurReviewCount", gCurReviewCount);
    
    ud->flush();
}

