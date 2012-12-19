#ifndef _GlobalData_H_
#define _GlobalData_H_

#include "HBCommon.h"

#define kCircleRadius 75

extern float gScreenWidth;
extern float gScreenHeight;
extern float gScreenWidthHalf;
extern float gScreenHeightHalf;

typedef enum
{
    kGameModeNormal,    // 普通
    kGameModeTest       // 段位测试
} GameMode;

typedef enum tagTouchState
{
	kTouchUngrabbed,
	kTouchGrabbed,
} TouchState;

typedef struct
{
    bool isClear;
    int goal;               // 关卡目标
    int time;               // 关卡时间
} LevelDetail;

extern int gTestLevel;              // 选择的等级
extern GameMode gGameMode;          // 玩家选择的模式
extern int gHighScore;
extern const char* gLeaderboardName;

// 评论引导
extern bool gIsReviewd;         // 是否已经进行过评论
extern int gCurReviewCount;     // 当前评论计数,每10次游戏弹出一遍

extern LevelDetail gLevelDetail[10];

class GlobalData
{
public:
    static void save();
    static void load();
};

#endif