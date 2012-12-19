#include "SceneMain.h"
#include "SceneLogoLoader.h"
//#include "GlobalData.h"
//#include "HBUtilies.h"
//#include "DialogScore.h"
//#include "GlobalData.h"
//#include "ExplodeScore.h"

SceneMain::SceneMain()
: mBtnBack(NULL)
, mTimeValue(NULL)
, mFinish(NULL)
, mTips(NULL)
, mLabelLevel(NULL)
, mLabelGoal(NULL)
, mLabelHigh(NULL)
, mLayerTimeBar(NULL)
{
}

SceneMain::~SceneMain()
{
    CC_SAFE_RELEASE(mBtnBack);
    CC_SAFE_RELEASE(mTimeValue);
    CC_SAFE_RELEASE(mFinish);
    CC_SAFE_RELEASE(mTips);
    CC_SAFE_RELEASE(mLabelLevel);
    CC_SAFE_RELEASE(mLabelGoal);
    CC_SAFE_RELEASE(mLabelHigh);
    CC_SAFE_RELEASE(mLayerTimeBar);
}

void SceneMain::onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader)
{
    mBtnBack->setTitleForState(ccs(gls("Back")), CCControlStateNormal);
    
	CCSprite* sprite = CCSprite::create("ui_time.png");
    mTimeBar = CCProgressTimer::create(sprite);
    mTimeBar->setType(kCCProgressTimerTypeBar);
	mTimeBar->setMidpoint(ccp(0,0));
	mTimeBar->setBarChangeRate(ccp(1,0));
	mTimeBar->setPercentage(100);
    mTimeBar->setPosition(ccp(246, -77));
	mLayerTimeBar->addChild(mTimeBar);
}

SEL_MenuHandler SceneMain::onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName)
{
    return NULL;
}

SEL_CCControlHandler SceneMain::onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName)
{
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnBack", SceneMain::onBtnBack);
	CCB_SELECTORRESOLVER_CCCONTROL_GLUE(this, "onBtnTap", SceneMain::onBtnTap);
    return NULL;
}

bool SceneMain::onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode)
{
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mBtnBack", CCControlButton*, mBtnBack);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTimeValue", CCLabelTTF*, mTimeValue);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mFinish", CCLabelTTF*, mFinish);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mTips", CCLabelTTF*, mTips);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelLevel", CCLabelTTF*, mLabelLevel);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelGoal", CCLabelTTF*, mLabelGoal);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLabelHigh", CCLabelTTF*, mLabelHigh);
    CCB_MEMBERVARIABLEASSIGNER_GLUE(this, "mLayerTimeBar", CCLayer*, mLayerTimeBar);
    return false;
}

void SceneMain::onBtnBack(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("Menu.wav");
    CCDirector::sharedDirector()->replaceScene(HBSceneLoader("SceneLogo", SceneLogoLoader::loader()));
    //    HBUmeng::event("Button", "Chellange");
    //    DialogChellange::create(this);
}

void SceneMain::onBtnTap(CCObject* pSender, CCControlEvent pCCControlEvent)
{
    Audio->playEffect("Menu.wav");
    //    HBUmeng::event("Button", "Classic");
    //    gGameMode = kGameModeNormal;
    //    CCDirector::sharedDirector()->replaceScene(LayerMain::scene());
}

void SceneMain::update(float dt)
{
    
}

/*
bool LayerMain::init()
{

    // Time Bar
    mTimeBar = createImage("time_bar.png", 44, gScreenHeight-100, this);
    mTimeBar->setAnchorPoint(gAnchorLeft);
        
    // Score
    mScoreTotal = createLabelAtlas(fcs("%d", 0), "font_number.png", 56, 74, '0', gScreenWidthHalf, gScreenHeightHalf+80, gAnchorCenter, this);
    
    if (gGameMode == kGameModeTest)
        mLevelTime = gLevelDetail[gTestLevel].time;
    else
        mLevelTime = 10.0f;
 
	scheduleUpdate();
    _restart();

	return true;
}

void LayerMain::update(float dt)
{
    if (mGameState == kStateBegin)
    {
        mLastTime -= dt;
        mTotalTime += dt;
        if (mLastTime <= 0)
        {
            mLastTime = 0;
            mGameState = kStateResult;
            mCircle->setVisible(false);
            
            SimpleAudioEngine::sharedEngine()->playEffect("Done.wav");
            mFinish->runAction(CCSequence::create(CCSpawn::create(CCFadeIn::create(0.5), CCMoveBy::create(0.5, ccpRatio2(0, -50)), NULL), CCDelayTime::create(0.3), CCCallFunc::create(this, callfunc_selector(LayerMain::_showResult)), NULL));
        }
    
        _updateTimeBar();
    }
}

void LayerMain::_showResult()
{
    DialogScore::create(mTouchCount, this);
    _restart();
}

void LayerMain::_updateTimeBar()
{
    float pos = mLastTime / mLevelTime;
    mTimeBar->setTextureRect(ccRectRatio2(0, 0, MAX(10,pos * 177 + 10), 37));
    mTimeValue->setString(fcs("%.02f", mLastTime));
}

void LayerMain::_updateLevel()
{
    mLabelLevel->setString(fcs("Lv.%d", mCurrentLevel));
    mLabelGoal->setString(fcs("%d", mNextGoal));
}

void LayerMain::_restart()
{
    // init data
    if (gGameMode == kGameModeTest)
    {
        mCurrentLevel = gTestLevel+1;
        mNextGoal = gLevelDetail[gTestLevel].goal;
    }
    else
    {
        mCurrentLevel = 1;
        mNextGoal = 50;
    }
    
    mTotalTime = 0;
    
    _updateLevel();
    
	mTimeBar->setTextureRect(ccRectRatio2(0, 0, 247, 37));

	mTimeValue->setString(fcs("%.02f", mLevelTime));
	mScoreTotal->setString("0");
	mCircle->setVisible(true);
    
    mTips->setPosition(ccpRatio(160, 265));
	mTips->setOpacity(255);
    mTips->setColor(ccYELLOW);
    mTips->runAction(CCRepeatForever::create((CCActionInterval*)CCSequence::create(CCTintTo::create(1, 0, 0, 255), CCTintTo::create(1, 255, 255, 0), NULL)));
    
	mTouchState = kTouchUngrabbed;
	mTouchCount = 0;
	mGameState = kStateNone;
    
	mFinish->setPosition(ccpRatio(160,300));
	mFinish->setOpacity(0);
    
    mLabelHigh->setString(fcs("%d", gHighScore));
}

int LayerMain::_containsTouchLocation(CCTouch* touch)
{
	CCPoint location = touch->getLocation();

	if(ccpDistance(mCircle->getPosition(), location) <= ccFontRatio(kCircleRadius))
		return 0;
    
	return 2;
}

void LayerMain::_doTouch(int index, CCTouch* touch)
{
    if(mTouchState != kTouchGrabbed)
    {
        mTouchState = kTouchGrabbed;
        mTouch = touch;
        mTouchCount ++;
        mCircle->runAction(CCSequence::create(CCScaleTo::create(0.01, 0.8), CCScaleTo::create(0.01, 1.0), NULL));
        
        CCPoint pos = ccpRatio(160, 160 + 30);

        ExplodeScore* s = new ExplodeScore(pos, mTouchCount, 20, ccYELLOW);
        addChild(s);
        
        mScoreTotal->setString(fcs("%d", mTouchCount));
        
        if (mTouchCount >= mNextGoal && kGameModeTest != gGameMode)
        {
            mCurrentLevel++;
            mLastTime += 1.5;
            mNextGoal += 15 + (mCurrentLevel - 1);
            _updateTimeBar();
            _updateLevel();
            SimpleAudioEngine::sharedEngine()->playEffect("upgrade.m4a");
        }
    }
}

bool LayerMain::_checkTouch(CCSet *pTouches)
{
    bool isTouch = false;
    for (CCSetIterator itr = pTouches->begin(); itr != pTouches->end(); ++itr)
    {
        CCTouch* touch = (CCTouch*)*itr;
        int touchIn = _containsTouchLocation(touch);
        if(touchIn == 2 )
            continue;
        else if(touchIn == 0)
        {
            isTouch = true;
            _doTouch(0, touch);
        }
    }
    
    return isTouch;
}

void LayerMain::ccTouchesBegan(CCSet *pTouches, CCEvent *pEvent)
{
	switch(mGameState)
	{
	case kStateNone:
        if(_checkTouch(pTouches))
        {
            SimpleAudioEngine::sharedEngine()->playEffect("Tap.wav");
            mGameState = kStateBegin;
            mLastTime = mLevelTime;
            mTips->runAction(CCSpawn::create(CCFadeOut::create(0.3), CCMoveBy::create(0.3, ccpRatio2(0,50)), NULL));
        }
        break;
    case kStateBegin:
        if(_checkTouch(pTouches)) 
            SimpleAudioEngine::sharedEngine()->playEffect("Tap.wav");
        break;
    default:
        break;
	}
}

void LayerMain::ccTouchesEnded(CCSet *pTouches, CCEvent *pEvent)
{
	switch(mGameState)
	{
    case kStateBegin:
        for (CCSetIterator itr = pTouches->begin(); itr != pTouches->end(); ++itr)
        {
            CCTouch* touch = (CCTouch*)*itr;
            if(touch == mTouch)
            {
                mTouchState = kTouchUngrabbed;
                mTouch = NULL;
            }
        }
        break;
    default:
        break;
	}
}

void LayerMain::_back()
{
    SimpleAudioEngine::sharedEngine()->playEffect("Menu.wav");
    CCDirector::sharedDirector()->replaceScene(LayerLogo::scene());
}

void LayerMain::_retry()
{
    SimpleAudioEngine::sharedEngine()->playEffect("Menu.wav");
	_restart();
}

void LayerMain::registerWithTouchDispatcher()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addStandardDelegate(this,0);
}

void LayerMain::keyBackClicked()
{
	_back();
}

void LayerMain::keyMenuClicked()
{

}
*/