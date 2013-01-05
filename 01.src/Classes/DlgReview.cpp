#include "DlgReview.h"
#include "GlobalData.h"

DlgReview::DlgReview()
: mLayerBase(NULL)
, mLabelTitle(NULL)
, mLabelMsg(NULL)
, mBtnReview(NULL)
, mBtnClose(NULL)
{
    setKeypadEnabled(true);
}

DlgReview::~DlgReview()
{
    CC_SAFE_RELEASE(mLayerBase);
    CC_SAFE_RELEASE(mLabelTitle);
    CC_SAFE_RELEASE(mLabelMsg);
    CC_SAFE_RELEASE(mBtnReview);
    CC_SAFE_RELEASE(mBtnClose);
}

void DlgReview::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    setZOrder(100);
    mLabelTitle->setString(gls("Review"));
    mLabelMsg->setString(gls("ReviewMsg"));
    mBtnReview->setTitleForState(ccs(gls("GoReview")), CCControlStateNormal);
}

SEL_MenuHandler DlgReview::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler DlgReview::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnReview", DlgReview::onBtnReview);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnClose", DlgReview::onBtnClose);
    return NULL;
}

bool DlgReview::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerBase", CCLayer*, mLayerBase);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMsg", CCLabelTTF*, mLabelMsg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTitle", CCLabelTTF*, mLabelTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnReview", CCControlButton*, mBtnReview);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnClose", CCControlButton*, mBtnClose);
    return false;
}

void DlgReview::onBtnReview(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect(EF_Menu);

    HBUmeng::event("Button", "GoReview");
    gIsReviewd = true;
    GlobalData::save();
    mLayerBase->runAction(CCSequence::create(CCMoveTo::create(0.3, getPositionByPercent(0, 90)), CCCallFunc::create(this, callfunc_selector(DlgReview::_closeDialogWithReview)), NULL));
}

void DlgReview::onBtnClose(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect(EF_Menu);
    
    gCurReviewCount = 10;
    GlobalData::save();
    mLayerBase->runAction(CCSequence::create(CCMoveTo::create(0.3, getPositionByPercent(0, 90)), CCCallFunc::create(this, callfunc_selector(DlgReview::_closeDialog)), NULL));
}

void DlgReview::_closeDialog()
{
	removeFromParentAndCleanup(true);
}

void DlgReview::_closeDialogWithReview()
{
    gotoReview();
	removeFromParentAndCleanup(true);
}

bool DlgReview::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    mBtnReview->ccTouchBegan(pTouch, pEvent);
    mBtnClose->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void DlgReview::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    mBtnReview->ccTouchEnded(pTouch, pEvent);
    mBtnClose->ccTouchEnded(pTouch, pEvent);
}

void DlgReview::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-2, true);
}

