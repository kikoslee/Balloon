#include "DlgScore.h"
#include "GlobalData.h"
#include "SceneLogoLoader.h"
#include "DlgChallengeLoader.h"
#include "DlgReviewLoader.h"

DlgScore::DlgScore()
: mLayerBase(NULL)
, mLayerScore(NULL)
, mLabelTitle(NULL)
, mLabelComplete(NULL)
, mBtnRetry(NULL)
, mIconStar(NULL)
, mIconMedal(NULL)
, mLabelScore(NULL)
, mIsClear(false)
{
}

DlgScore::~DlgScore()
{
    CC_SAFE_RELEASE(mLayerBase);
    CC_SAFE_RELEASE(mLayerScore);
    CC_SAFE_RELEASE(mLabelTitle);
    CC_SAFE_RELEASE(mLabelComplete);
    CC_SAFE_RELEASE(mBtnRetry);
    CC_SAFE_RELEASE(mIconStar);
    CC_SAFE_RELEASE(mIconMedal);
}

void DlgScore::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mLabelScore = HBcreateLabelAtlas(fcs("%d", gCurScore), "font_number.png", 112, 148, '0', 0, 0, gAnchorCenter, mLayerScore);

    if (kGameModeTest == gGameMode)
    {
        // 挑战模式
        mLabelTitle->setString(fcs("%s %d", gls("Level"), gTestLevel + 1));
        mIconStar->setVisible(false);
        mIconMedal->setVisible(true);
        
        if ( gCurScore >= gLevelDetail[gTestLevel].goal)
        {
            // 成功
            HBUmeng::event("LevelComplete", fcs("%d", gTestLevel+1));
            mIconMedal->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_medal.png"));

            gLevelDetail[gTestLevel].isClear = true;
            mIsClear = true;
            
            if (gTestLevel == 9)
            {
                //最后一关
                mLabelComplete->setString(gls("All Clear!!!"));
                mBtnRetry->setTitleForState(ccs(gls("Close")), CCControlStateNormal);
            }
            else
            {
                mLabelComplete->setString(gls("Mission Complete!"));
                mBtnRetry->setTitleForState(ccs(gls("Next")), CCControlStateNormal);
            }            
        }
        else
        {
            mLabelComplete->setString(gls("Mission Failed!"));
            mIconMedal->setDisplayFrame(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName("icon_medal_d.png"));

            mBtnRetry->setTitleForState(ccs(gls("Retry")), CCControlStateNormal);
        }        
    }
    else
    {
        // 普通模式
        HBUmeng::event("SingleScore", fcs("%d", gCurScore));
        mBtnRetry->setTitleForState(ccs(gls("Again")), CCControlStateNormal);
        mLabelTitle->setString(gls("Result"));

        mIconMedal->setVisible(false);
        if ( gCurScore > gHighScore )
        {
            gHighScore = gCurScore;
            mIconStar->setVisible(true);
            mLabelComplete->setString(gls("High score!"));
            
            HBScore::reportScore(gLeaderboardName, gHighScore);
        }
        else
        {
            mIconStar->setVisible(false);
            mLabelComplete->setString(fcs("%s:%d", gls("High score"), gHighScore));
        }
    }
    
    _checkReview();
    GlobalData::save();
}

SEL_MenuHandler DlgScore::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler DlgScore::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnRetry", DlgScore::onBtnRetry);
    return NULL;
}

bool DlgScore::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerBase", CCLayer*, mLayerBase);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerScore", CCLayer*, mLayerScore);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelComplete", CCLabelTTF*, mLabelComplete);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelTitle", CCLabelTTF*, mLabelTitle);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mIconStar", CCSprite*, mIconStar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mIconMedal", CCSprite*, mIconMedal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnRetry", CCControlButton*, mBtnRetry);
    return false;
}

void DlgScore::onBtnRetry(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect(EF_Menu);
    mLayerBase->runAction(CCSequence::create(CCMoveTo::create(0.3, HBgetPositionByPercent(0, 90)), CCCallFunc::create(this, callfunc_selector(DlgScore::_closeDialog)), NULL));
}

void DlgScore::_closeDialog()
{
    if (kGameModeTest == gGameMode)
    {
        if (mIsClear)
        {
            if (gTestLevel == 9)
                CCDirector::sharedDirector()->replaceScene(HBSceneLoader("SceneLogo", SceneLogoLoader::loader()));
            else
            {
                gTestLevel ++;
                CCDirector::sharedDirector()->getRunningScene()->addChild(HBLayerLoader("DlgChallenge", DlgChallengeLoader::loader()));
            }
        }
    }
	removeFromParentAndCleanup(true);
}

void DlgScore::_checkReview()
{
    // 已经评论过了,就不弹了
    if (gIsReviewd)
        return;
    
    gCurReviewCount --;
    gCurReviewCount = MAX(0, gCurReviewCount);
    
    //测试代码
//    gCurReviewCount = 0;
    
    if (gCurReviewCount == 0)
        addChild(HBLayerLoader("DlgReview", DlgReviewLoader::loader()));
}

bool DlgScore::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    mBtnRetry->ccTouchBegan(pTouch, pEvent);
    
    return true;
}

void DlgScore::ccTouchEnded(CCTouch* pTouch, CCEvent* pEvent)
{
    mBtnRetry->ccTouchEnded(pTouch, pEvent);
}

void DlgScore::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority-1, true);
}

