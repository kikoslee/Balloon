#include "DlgChallenge.h"
#include "SceneMainLoader.h"
#include "GlobalData.h"

DlgChallenge::DlgChallenge()
: mLayerBase(NULL)
, mLayerLevel(NULL)
, mLabelGoal(NULL)
, mLabelTime(NULL)
, mLabelGoalTitle(NULL)
, mLabelTimeTitle(NULL)
, mLabelTitle(NULL)
, mBtnStart(NULL)
, mBtnClose(NULL)
, mBtnLeft(NULL)
, mBtnRight(NULL)
, mIconMedal(NULL)
, mCurLevel(0)
, mAnimal(NULL)
{
    setKeypadEnabled(true);
}

DlgChallenge::~DlgChallenge()
{
    CC_SAFE_RELEASE(mLayerBase);
    CC_SAFE_RELEASE(mLayerLevel);
    CC_SAFE_RELEASE(mLabelGoal);
    CC_SAFE_RELEASE(mLabelTime);
    CC_SAFE_RELEASE(mLabelGoalTitle);
    CC_SAFE_RELEASE(mLabelTimeTitle);
    CC_SAFE_RELEASE(mLabelTitle);
    CC_SAFE_RELEASE(mBtnStart);
    CC_SAFE_RELEASE(mBtnClose);
    CC_SAFE_RELEASE(mBtnLeft);
    CC_SAFE_RELEASE(mBtnRight);
    CC_SAFE_RELEASE(mIconMedal);
}

void DlgChallenge::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
//    mLabelCurLevel = createLabelAtlas(fcs("%d", mCurLevel + 1), "font_number.png", 112, 148, '0', 0, 0, gAnchorCenter, mLayerLevel);

    mLabelGoalTitle->setString(gls("Goal"));
    mLabelTimeTitle->setString(gls("Time"));
    
    mBtnStart->setTitleForState(ccs(gls("Start")), CCControlStateNormal);

    mCurLevel = gTestLevel;
    _refreshLevel();    
}

SEL_MenuHandler DlgChallenge::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler DlgChallenge::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnStart", DlgChallenge::onBtnStart);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnLeft", DlgChallenge::onBtnLeft);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnRight", DlgChallenge::onBtnRight);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnClose", DlgChallenge::onBtnClose);
    return NULL;
}

bool DlgChallenge::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerBase", CCLayer*, mLayerBase);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerLevel", CCLayer*, mLayerLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelGoal", CCLabelTTF*, mLabelGoal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTime", CCLabelTTF*, mLabelTime);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelGoalTitle", CCLabelTTF*, mLabelGoalTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTimeTitle", CCLabelTTF*, mLabelTimeTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTitle", CCLabelTTF*, mLabelTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mIconMedal", CCSprite*, mIconMedal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnStart", CCControlButton*, mBtnStart);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnClose", CCControlButton*, mBtnClose);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnLeft", CCControlButton*, mBtnLeft);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnRight", CCControlButton*, mBtnRight);
    return false;
}

void DlgChallenge::onBtnStart(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect(EF_Upgrade);

    HBUmeng::event("Button", "ChellangeStart");
    HBUmeng::event("LevelSelect", fcs("%d", mCurLevel + 1));

    gGameMode = kGameModeTest;
    gTestLevel = mCurLevel;
    GlobalData::save();

    CCDirector::sharedDirector()->replaceScene(HBSceneLoader("SceneMain", SceneMainLoader::loader()));
}

void DlgChallenge::onBtnLeft(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect(EF_Menu);

    mCurLevel--;
    _refreshLevel();
}

void DlgChallenge::onBtnRight(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect(EF_Menu);

    mCurLevel++;
    _refreshLevel();
}

void DlgChallenge::onBtnClose(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect(EF_Menu);
    HBUmeng::event("Button", "ChellangeClose");

    mLayerBase->runAction(CCSequence::create(CCMoveTo::create(0.3, HBgetPositionByPercent(0, 90)), CCCallFunc::create(this, callfunc_selector(DlgChallenge::_closeDialog)), NULL));
}

void DlgChallenge::_refreshLevel()
{
    mCurLevel = MAX(MIN(mCurLevel, LevelCount-1), 0);

//    mLabelCurLevel->setString(fcs("%d", mCurLevel + 1));
    mLabelTitle->setString(fcs("%s %d", gls("Level"), mCurLevel + 1));
    mLabelGoal->setString(fcs("%d", gLevelDetail[mCurLevel].goal));
    mLabelTime->setString(fcs("%d", gLevelDetail[mCurLevel].time));
    
    if (mAnimal)
    {
        mAnimal->removeFromParentAndCleanup(true);
        mAnimal = NULL;
    }
    
    mAnimal = CCSprite::create(fcs("an%d.png", mCurLevel + 1));
    mAnimal->setScale(0.5);
    mLayerLevel->addChild(mAnimal);
    
    if(gLevelDetail[mCurLevel].isClear)
        mIconMedal->setVisible(true);
    else
        mIconMedal->setVisible(false);
}

void DlgChallenge::_closeDialog()
{
    removeFromParentAndCleanup(true);
}

bool DlgChallenge::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    mBtnStart->ccTouchBegan(pTouch, pEvent);
    mBtnClose->ccTouchBegan(pTouch, pEvent);
    mBtnLeft->ccTouchBegan(pTouch, pEvent);
    mBtnRight->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void DlgChallenge::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    mBtnStart->ccTouchEnded(pTouch, pEvent);
    mBtnClose->ccTouchEnded(pTouch, pEvent);
    mBtnLeft->ccTouchEnded(pTouch, pEvent);
    mBtnRight->ccTouchEnded(pTouch, pEvent);
}

void DlgChallenge::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-2, true);
}
