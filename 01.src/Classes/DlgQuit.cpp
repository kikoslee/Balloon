#include "DlgQuit.h"
#include "GlobalData.h"

DlgQuit::DlgQuit()
: mLabelMsg(NULL)
, mBtnQuit(NULL)
, mBtnCancel(NULL)
{
}

DlgQuit::~DlgQuit()
{
    CC_SAFE_RELEASE(mLabelMsg);
    CC_SAFE_RELEASE(mBtnQuit);
    CC_SAFE_RELEASE(mBtnCancel);
}

void DlgQuit::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelMsg->setString(gls("QuitMsg"));
    
    mBtnQuit->setTitleForState(ccs(gls("Quit")), CCControlStateNormal);
    mBtnCancel->setTitleForState(ccs(gls("Cancel")), CCControlStateNormal);
}

SEL_MenuHandler DlgQuit::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler DlgQuit::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnQuit", DlgQuit::onBtnQuit);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnCancel", DlgQuit::onBtnCancel);
    return NULL;
}

bool DlgQuit::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelMsg", CCLabelTTF*, mLabelMsg);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnQuit", CCControlButton*, mBtnQuit);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnCancel", CCControlButton*, mBtnCancel);
    return false;
}

void DlgQuit::onBtnQuit(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    HBExitApplication();
}

void DlgQuit::onBtnCancel(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("Menu.wav");
    removeFromParentAndCleanup(true);
    gIsDlgQuitShow = false;
}

bool DlgQuit::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    mBtnQuit->ccTouchBegan(pTouch, pEvent);
    mBtnCancel->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void DlgQuit::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    mBtnQuit->ccTouchEnded(pTouch, pEvent);
    mBtnCancel->ccTouchEnded(pTouch, pEvent);
}

void DlgQuit::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-3, true);
}

