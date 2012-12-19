#ifndef _DlgChallenge_H_
#define _DlgChallenge_H_

#include "HBCommon.h"

class DlgChallenge
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    DlgChallenge();
    virtual ~DlgChallenge();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(DlgChallenge, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

private:
    CCLayer* mLayerBase;
    CCLayer* mLayerLevel;
    CCLabelTTF* mLabelGoal;
    CCLabelTTF* mLabelTime;
    CCLabelTTF* mLabelTitle;
    CCLabelTTF* mLabelGoalTitle;
    CCLabelTTF* mLabelTimeTitle;
    CCControlButton* mBtnStart;
    CCSprite* mIconMedal;
    
    int mCurLevel;
    CCLabelAtlas* mLabelCurLevel;

    void _refreshLevel();
    
	bool _initWithLevel(CCNode* parent);
	void _menuCallback(CCMenuItem* sender);
    void _closeDialog();
    
    void onBtnStart(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnLeft(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnRight(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnClose(CCObject* pSender, CCControlEvent pCCControlEvent);
    
};

#endif