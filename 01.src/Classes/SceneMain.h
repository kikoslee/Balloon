#ifndef _SceneMain_H_
#define _SceneMain_H_

#include "HBCommon.h"

typedef enum
{
	kStateNone,
	kStateBegin,
	kStateResult,
	kStateFinish
} GameState;

class SceneMain
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    SceneMain();
    virtual ~SceneMain();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SceneMain, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
    
private:
    void onBtnBack(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnTap(CCObject* pSender, CCControlEvent pCCControlEvent);
    
    CCControlButton* mBtnBack;
	CCLabelTTF* mTimeValue;		// 时间文本
	CCLabelTTF* mFinish;		// 提示文字
	CCLabelTTF* mTips;
    CCLabelTTF* mLabelLevel;    // 等级标签
    CCLabelTTF* mLabelGoal;     // 目标标签
    CCLabelTTF* mLabelHigh;     // 最高分标签
    CCLayer* mLayerTimeBar;
    
    CCProgressTimer* mTimeBar;
	CCLabelAtlas* mScoreTotal;	// 分数文本
    
	GameState mGameState;		// 游戏状态
	int mTouchCount;			// 点击数
    int mNextGoal;              // 下一次目标,初始为70/140,每级增加15~30,每个目标达成增加10秒
    int mCurrentLevel;          // 等级
    
    float mLastTime;
    float mLevelTime;
    float mCurrentTime;
    float mTotalTime;
    
    virtual void update(float dt);
    
    void _showResult();
    void _retry();
    void _back();
    void _restart();
    void _doTouch(int index, CCTouch* touch);
    bool _checkTouch(CCSet *pTouches);
    void _updateTimeBar();
    void _updateLevel();
    int _containsTouchLocation(CCTouch* touch);
};

#endif