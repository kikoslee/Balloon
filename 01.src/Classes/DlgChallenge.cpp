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
, mIconMedal(NULL)
, mCurLevel(0)
{
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
    CC_SAFE_RELEASE(mIconMedal);
}

void DlgChallenge::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelCurLevel = createLabelAtlas(fcs("%d", mCurLevel + 1), "font_number.png", 112, 148, '0', 0, 0, gAnchorCenter, mLayerLevel);

    mLabelTitle->setString(gls("Level Select"));
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
    return false;
}

void DlgChallenge::onBtnStart(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("upgrade.m4a");

    HBUmeng::event("Button", "ChellangeStart");
    HBUmeng::event("LevelSelect", fcs("%d", mCurLevel + 1));

    gGameMode = kGameModeTest;
    gTestLevel = mCurLevel;
    GlobalData::save();

    CCDirector::sharedDirector()->replaceScene(HBSceneLoader("SceneMain", SceneMainLoader::loader()));
}

void DlgChallenge::onBtnLeft(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("Menu.wav");

    mCurLevel--;
    _refreshLevel();
}

void DlgChallenge::onBtnRight(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("Menu.wav");

    mCurLevel++;
    _refreshLevel();
}

void DlgChallenge::onBtnClose(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("Menu.wav");
    HBUmeng::event("Button", "ChellangeClose");

    mLayerBase->runAction(CCSequence::create(CCMoveTo::create(0.3, getPositionByPercent(ccp(0, 0.9))), CCCallFunc::create(this, callfunc_selector(DlgChallenge::_closeDialog)), NULL));
}

void DlgChallenge::_refreshLevel()
{
    mCurLevel = MAX(MIN(mCurLevel, 9), 0);

    mLabelCurLevel->setString(fcs("%d", mCurLevel + 1));
    mLabelGoal->setString(fcs("%d", gLevelDetail[mCurLevel].goal));
    mLabelTime->setString(fcs("%d", gLevelDetail[mCurLevel].time));
    
    if(gLevelDetail[mCurLevel].isClear)
        mIconMedal->setVisible(true);
    else
        mIconMedal->setVisible(false);
}

void DlgChallenge::_closeDialog()
{
    removeFromParentAndCleanup(true);
}
