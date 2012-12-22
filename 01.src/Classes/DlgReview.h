#ifndef _DlgReview_H_
#define _DlgReview_H_

#include "HBCommon.h"

class DlgReview
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    DlgReview();
    virtual ~DlgReview();

    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(DlgReview, create);
    
    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

    bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
    void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);
    void registerWithTouchDispatcher();

private:
    CCLayer* mLayerBase;
    CCLabelTTF* mLabelTitle;
    CCLabelTTF* mLabelMsg;
    CCControlButton* mBtnReview;
    CCControlButton* mBtnClose;

    void _closeDialog();
    void _closeDialogWithReview();

    void onBtnReview(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnClose(CCObject* pSender, CCControlEvent pCCControlEvent);
};

#endif