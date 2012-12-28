#ifndef _DlgScore_H_
#define _DlgScore_H_

#include "HBCommon.h"

class DlgScore
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    DlgScore();
    virtual ~DlgScore();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(DlgScore, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);
    
    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();
    
private:
    CCLayer* mLayerBase;
    CCLayer* mLayerScore;
    CCLabelTTF* mLabelTitle;
    CCLabelTTF* mLabelComplete;
    CCControlButton* mBtnRetry;
    CCSprite* mIconStar;
    CCSprite* mIconMedal;
    
    CCLabelAtlas* mLabelScore;

    bool mIsClear;

    void _closeDialog();
    void _checkReview();
    void _showDialogReview();
    
    void onBtnRetry(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnBack(CCObject* pSender, CCControlEvent pCCControlEvent);
};

#endif
