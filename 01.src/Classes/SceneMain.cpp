#include "SceneMain.h"
#include "SceneLogoLoader.h"
#include "GlobalData.h"
#include "DlgScoreLoader.h"
#include "ExplodeScore.h"

SceneMain::SceneMain()
: mBtnBack(NULL)
, mBtnRetry(NULL)
, mTimeValue(NULL)
, mFinish(NULL)
, mTips(NULL)
, mLabelLevel(NULL)
, mLabelGoal(NULL)
, mLabelHigh(NULL)
, mLayerTimeBar(NULL)
, mLayerAnimal(NULL)
, mBtnMain(NULL)
, mAnimal(NULL)
{
    setKeypadEnabled(true);
}

SceneMain::~SceneMain()
{
    CC_SAFE_RELEASE(mBtnBack);
    CC_SAFE_RELEASE(mBtnRetry);
    CC_SAFE_RELEASE(mTimeValue);
    CC_SAFE_RELEASE(mFinish);
    CC_SAFE_RELEASE(mTips);
    CC_SAFE_RELEASE(mLabelLevel);
    CC_SAFE_RELEASE(mLabelGoal);
    CC_SAFE_RELEASE(mLabelHigh);
    CC_SAFE_RELEASE(mLayerTimeBar);
    CC_SAFE_RELEASE(mLayerAnimal);
    CC_SAFE_RELEASE(mBtnMain);
}

void SceneMain::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    setTouchMode(kCCTouchesOneByOne);
    mBtnBack->setTitleForState(ccs(gls("Back")), CCControlStateNormal);
    mBtnRetry->setTitleForState(ccs(gls("Retry")), CCControlStateNormal);
    mTips->setString(gls("TOUCH TO START"));
    mFinish->setString(gls("FINISH"));
    
	CCSprite* sprite = CCSprite::create("ui_time.png");
    mTimeBar = CCProgressTimer::create(sprite);
    mTimeBar->setType(kCCProgressTimerTypeBar);
	mTimeBar->setMidpoint(ccp(0,0));
	mTimeBar->setBarChangeRate(ccp(1,0));
	mTimeBar->setPercentage(100);
    mTimeBar->setPosition(ccp(246, -77));
	mLayerTimeBar->addChild(mTimeBar);
    
    mTimeValue->setZOrder(100);
    
    // Score
    mScoreTotal = HBcreateLabelAtlas(fcs("%d", 0), "font_number.png", 112, 148, '0', 0, 20, gAnchorCenter, mLayerAnimal);
    mScoreTotal->setZOrder(200);
    
    if (gGameMode == kGameModeTest)
        mLevelTime = gLevelDetail[gTestLevel].time;
    else
        mLevelTime = 10.0f;
    
    _restart();
	scheduleUpdate();
}

SEL_MenuHandler SceneMain::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler SceneMain::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnBack", SceneMain::onBtnBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnRetry", SceneMain::onBtnRetry);
    return NULL;
}

bool SceneMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnBack", CCControlButton*, mBtnBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnRetry", CCControlButton*, mBtnRetry);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTimeValue", CCLabelTTF*, mTimeValue);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFinish", CCLabelTTF*, mFinish);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTips", CCLabelTTF*, mTips);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelLevel", CCLabelTTF*, mLabelLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelGoal", CCLabelTTF*, mLabelGoal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelHigh", CCLabelTTF*, mLabelHigh);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerTimeBar", CCLayer*, mLayerTimeBar);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerAnimal", CCLayer*, mLayerAnimal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnMain", CCSprite*, mBtnMain);
    return false;
}

void SceneMain::onBtnBack(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect(EF_Menu);
    CCDirector::sharedDirector()->replaceScene(HBSceneLoader("SceneLogo", SceneLogoLoader::loader()));
}

void SceneMain::onBtnRetry(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect(EF_Menu);
	_restart();
}

void SceneMain::update(float dt)
{
    if (mGameState == kStateBegin)
    {
        mLastTime -= dt;
        mTotalTime += dt;
        if (mLastTime <= 0)
        {
            mLastTime = 0;
            mGameState = kStateResult;
            
            Audio->playEffect(EF_Done);
            mFinish->runAction(CCSequence::create(CCSpawn::create(CCFadeIn::create(0.5), CCMoveBy::create(0.5, ccp(0, -50)), NULL), CCDelayTime::create(0.3), CCCallFunc::create(this, callfunc_selector(SceneMain::_showResult)), NULL));
        }
        
        _updateTimeBar();
    }
}

void SceneMain::_showResult()
{
    gCurScore = mTouchCount;
    CCDirector::sharedDirector()->getRunningScene()->addChild(HBLayerLoader("DlgScore", DlgScoreLoader::loader()));
    _restart();
}

void SceneMain::_updateTimeBar()
{
    mTimeBar->setPercentage(100 * mLastTime / mLevelTime);
    mTimeValue->setString(fcs("%.02f", mLastTime));
}

void SceneMain::_updateLevel()
{
    mLabelLevel->setString(fcs("%d", mCurrentLevel));
    mLabelGoal->setString(fcs("%s:%d", gls("Goal"), mNextGoal));
}

void SceneMain::_restart()
{
    // init data
    if (gGameMode == kGameModeTest)
    {
        mCurrentLevel = gTestLevel + 1;
        mNextGoal = gLevelDetail[gTestLevel].goal;

        if (mAnimal)
        {
            mAnimal->removeFromParentAndCleanup(true);
            mAnimal = NULL;
        }
        
        mAnimal = CCSprite::create(fcs("an%d.png", gTestLevel + 1));
        mAnimal->setAnchorPoint(ccp(0.5, 0));
        mAnimal->setScale(0.2);
        mLayerAnimal->addChild(mAnimal);
    }
    else
    {
        mCurrentLevel = 1;
        mNextGoal = 50;
    }
    
    mTotalTime = 0;
    
    _updateLevel();
    
	mTimeBar->setPercentage(100);
    
	mTimeValue->setString(fcs("%.02f", mLevelTime));
	mScoreTotal->setString("0");
    
    mTips->setPosition(HBgetPositionByPercent(50, 50));
	mTips->setOpacity(255);
    mTips->setColor(ccYELLOW);
    mTips->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCTintTo::create(1, 0, 0, 255), CCTintTo::create(1, 255, 255, 0), NULL)));
    
	mTouchCount = 0;
	mGameState = kStateNone;
    
	mFinish->setPosition(HBgetPositionByPercent(50, 80));
	mFinish->setOpacity(0);
    
    mLabelHigh->setString(fcs("%s:%d", gls("High"), gHighScore));
    
    mTouched = false;
    mCurTouch = NULL;
}

bool SceneMain::_checkTouch(CCTouch *pTouch)
{
	CCPoint location = pTouch->getLocation();
    
	if(ccpDistance(mBtnMain->getPosition(), location) <= mBtnMain->getContentSize().width / 2)
    {
        switch(mGameState)
        {
            case kStateNone:
                _doTouch(0, pTouch);
                Audio->playEffect(EF_Tap);
                mGameState = kStateBegin;
                mLastTime = mLevelTime;
                mTips->runAction(CCSpawn::create(CCFadeOut::create(0.3), CCMoveBy::create(0.3, ccp(0,50)), NULL));
                break;
            case kStateBegin:
                _doTouch(0, pTouch);
                Audio->playEffect(EF_Tap);
                break;
            default:
                break;
        }
        
        return true;
    }
    
    return false;
}

void SceneMain::_doTouch(int index, CCTouch* touch)
{
    mTouchCount ++;
    mBtnMain->runAction(CCSequence::create(CCScaleTo::create(0.02, 0.7), CCScaleTo::create(0.02, 1.0), NULL));

    CCPoint pos = ccp(mBtnMain->getContentSize().width / 2, mBtnMain->getContentSize().height / 2);
    ExplodeScore* s = new ExplodeScore(pos, mTouchCount, 40, ccYELLOW);
    mBtnMain->addChild(s);
    
    mScoreTotal->setString(fcs("%d", mTouchCount));
    
    if (gGameMode == kGameModeTest)
    {
        if (mTouchCount == mNextGoal)
            Audio->playEffect(EF_Upgrade);
        mAnimal->setScale(MIN(1.5, 0.2 + (float)mTouchCount / (float)mNextGoal * 0.6));
    }
    else if (mTouchCount >= mNextGoal)
    {
        mCurrentLevel++;
        mLastTime += 1.5;
        mNextGoal += 15 + (mCurrentLevel - 1);
        _updateTimeBar();
        _updateLevel();
        Audio->playEffect(EF_Upgrade);
    }
}

bool SceneMain::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    if (!mTouched)
    {
        if (_checkTouch(pTouch))
        {
            mCurTouch = pTouch;
            mTouched = true;
            return true;
        }
    }
    
    return false;
}

void SceneMain::ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent)
{
    if (pTouch == mCurTouch)
    {
        mTouched = false;
    }
}

void SceneMain::registerWithTouchDispatcher()
{
    CCDirector* pDirector = CCDirector::sharedDirector();
    pDirector->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
}

//for android
void SceneMain::keyBackClicked()
{
#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID
    Audio->playEffect(EF_Menu);
    CCDirector::sharedDirector()->replaceScene(HBSceneLoader("SceneLogo", SceneLogoLoader::loader()));
#endif // CC_PLATFORM_ANDROID
}
