#include "SceneLogo.h"
#include "GlobalData.h"
#include "SceneMainLoader.h"
#include "DlgChallengeLoader.h"

SceneLogo::SceneLogo()
: mBtnChallenge(NULL)
, mBtnFree(NULL)
, mBtnScore(NULL)
, mBtnMore(NULL)
, mLogo(NULL)
, mLayerMadel(NULL)
{
}

SceneLogo::~SceneLogo()
{
    CC_SAFE_RELEASE(mBtnChallenge);
    CC_SAFE_RELEASE(mBtnFree);
    CC_SAFE_RELEASE(mBtnScore);
    CC_SAFE_RELEASE(mBtnMore);
    CC_SAFE_RELEASE(mLogo);
    CC_SAFE_RELEASE(mLayerMadel);
}

void SceneLogo::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mBtnChallenge->setTitleForState(ccs(gls("Challenge")), CCControlStateNormal);
    mBtnFree->setTitleForState(ccs(gls("Free Mode")), CCControlStateNormal);
    mBtnScore->setTitleForState(ccs(gls("Score")), CCControlStateNormal);
    mBtnMore->setTitleForState(ccs(gls("More")), CCControlStateNormal);
    
    for (int i = 0; i < 10; i++)
    {
        if (gLevelDetail[i].isClear)
            createImageWithFrameName("icon_medal.png", -4.5 + (5 - i) * 9, 0, mLayerMadel);
        else
            createImageWithFrameName("icon_medal_d.png", -4.5 + (5 - i) * 9, 0, mLayerMadel);
    }
}

SEL_MenuHandler SceneLogo::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler SceneLogo::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnChallenge", SceneLogo::onBtnChallenge);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnFree", SceneLogo::onBtnFree);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnScore", SceneLogo::onBtnScore);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnMore", SceneLogo::onBtnMore);
    return NULL;
}

bool SceneLogo::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnChallenge", CCControlButton*, mBtnChallenge);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnFree", CCControlButton*, mBtnFree);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnScore", CCControlButton*, mBtnScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnMore", CCControlButton*, mBtnMore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLogo", CCSprite*, mLogo);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerMadel",  CCLayer*, mLayerMadel);
    return false;
}

void SceneLogo::onBtnChallenge(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("Menu.wav");
    HBUmeng::event("Button", "Chellange");
    CCDirector::sharedDirector()->getRunningScene()->addChild(HBLayerLoader("DlgChallenge", DlgChallengeLoader::loader()));
}

void SceneLogo::onBtnFree(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("Menu.wav");
    HBUmeng::event("Button", "Classic");
    gGameMode = kGameModeNormal;
    CCDirector::sharedDirector()->replaceScene(HBSceneLoader("SceneMain", SceneMainLoader::loader()));
}

void SceneLogo::onBtnScore(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("Menu.wav");
    HBUmeng::event("Button", "Leaderboard");
    HBScore::showBoard(gLeaderboardName);
}

void SceneLogo::onBtnMore(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("Menu.wav");    
    HBUmeng::event("Button", "MoreGames");
#if CC_TARGET_PLATFORM == CC_PLATFORM_IOS
    gotoUrl("itms-apps://itunes.com/apps/limin");
#else
#endif
}

////for android
//void LayerLogo::keyBackClicked()
//{
//#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
//    exitApplication();
//#endif // CC_PLATFORM_ANDROID
//}
//
//void LayerLogo::keyMenuClicked()
//{
//}
