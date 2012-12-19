#include "PreHeader.h"
#include "DialogScore.h"
#include "DialogReview.h"
#include "HBUtilies.h"
#include "HBScore.h"
#include "LayerLogo.h"
#include "GlobalData.h"
#include "DialogChellange.h"
#include "HBUmeng.h"
#include "HBLocaleUtil.h"
#include "HBShare.h"

typedef enum
{
    kMenuTagClose,
    kMenuTagRetry,
    kMenuTagShare1,
    kMenuTagShare2,
} MenuTag;

DialogScore::DialogScore()
{
    std::string strr;
    
}

DialogScore::~DialogScore()
{
    
}

DialogScore* DialogScore::create(int count, CCNode* parent)
{
    DialogScore *pRet = new DialogScore;
    if(pRet && pRet->_initWithCount(count, parent))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool DialogScore::_initWithCount(int count, CCNode* parent)
{
    _isClear = false;
    
    CCLabelTTF* label = createLabel(getLocalizedString("Result"), getLocalizedString("fontNormal"), 24, gAnchorCenter, ccWHITE, 0, 65, _layerBase);
    if (kGameModeTest == gGameMode)
        label->setString(fcs(getLocalizedString("Mission %d"), gTestLevel + 1));

    createLabelAtlas(fcs("%d", count), "font_number.png", 56, 74, '0', 0, 5, gAnchorCenter, _layerBase);
    
	CCMenu* menu = createMenu(_layerBase);
    
//	CCMenuItem* item = createMenuItemWithCache("btn_close.png", "btn_close_d.png", ccp(130, 105), kMenuTagClose, menu, this, menu_selector(DialogScore::_menuCallback));
    
    CCMenuItem* retry = createMenuItemWithCache("btn_normal.png", "btn_normal_d.png", 70, -130, kMenuTagRetry, menu, this, menu_selector(DialogScore::_menuCallback));
    CCLabelTTF* labelMenu = addMenuLabel(retry, getLocalizedString("Again"), getLocalizedString("fontNormal"), 20, ccYELLOW);
    
    if (kGameModeNormal == gGameMode)
    {
        // 普通模式
        HBUmeng::event("SingleScore", fcs("%d", count));
        
        if ( count > gHighScore )
        {
            createImageWithFrameName("icon_star.png", -85, -60, _layerBase);
            createLabel(getLocalizedString("High score!"), getLocalizedString("fontNormal"), 24, gAnchorLeft, ccWHITE, -65, -62, _layerBase);
            
            gHighScore = count;
            HBScore::reportScore(gLeaderboardName, count);
            _checkReview();
        }
        else
        {
            createLabel(getLocalizedString("High score:"), getLocalizedString("fontNormal"), 24, gAnchorLeft, ccWHITE, -85, -62, _layerBase);
            createLabel(fcs("%d", gHighScore), getLocalizedString("fontNormal"), 30, gAnchorLeft, ccYELLOW, 45, -62, _layerBase);
        }
        
    }
    else
    {
        CCLabelTTF* labelClear = createLabel(getLocalizedString("Mission Complete!"), getLocalizedString("fontNormal"), 20, gAnchorLeft, ccWHITE, -65, -62, _layerBase);

        // 挑战模式
        if (count >= gLevelDetail[gTestLevel].goal)
        {
            // 成功
            HBUmeng::event("LevelComplete", fcs("%d", gTestLevel+1));
            createImageWithFrameName("icon_medal.png", -85, -60, _layerBase);
            gLevelDetail[gTestLevel].isClear = true;
            _isClear = true;
            _checkReview();
            
            if (gTestLevel == 9)
            {
                //最后一关
                labelClear->setString(getLocalizedString("All Clear!!!"));
                labelMenu->setString(getLocalizedString("Close"));
            }
            else
                labelMenu->setString(getLocalizedString("Next"));
            
        }
        else
        {
            createImageWithFrameName("icon_medal_d.png", -85, -60, _layerBase);
            labelClear->setString(getLocalizedString("Mission Failed!"));
            labelMenu->setString(getLocalizedString("Retry"));
            share1->setVisible(false);
            share2->setVisible(false);
        }
        
    }
    

    GlobalData::save();

	setTouchEnabled(true);
    
	_layerBase->runAction(CCMoveTo::create(0.3, ccpRatio(gScreenWidthHalf,280)));

    return true;
}

void DialogScore::_menuCallback(CCMenuItem* sender)
{
//	SimpleAudioEngine::sharedEngine()->playEffect(EF_CLICK);
    MenuTag tag = (MenuTag)sender->getTag();
    
    SimpleAudioEngine::sharedEngine()->playEffect("Menu.wav");
    
    switch (tag)
    {
        case kMenuTagRetry:
            _layerBase->runAction(CCSequence::create(CCMoveBy::create(0.3, ccpRatio(0,280)), CCCallFunc::create(this, callfunc_selector(DialogScore::_closeDialog)), NULL));
            break;
        case kMenuTagClose:
//            if (kGameModeTest == gGameMode)
//                CCDirector::sharedDirector()->replaceScene(LayerLogo::scene());
//            else {
                _layerBase->runAction(CCSequence::create(CCMoveBy::create(0.3, ccpRatio(0,280)), CCCallFunc::create(this, callfunc_selector(DialogScore::_closeDialog)), NULL));
//            }
            break;
        case kMenuTagShare1:
            HBUmeng::event("Button", "ScoreShare1");
            if (HBLocaleUtil::isChinese())
                HBShare::shared()->shareTo(HBShare_Sina, _shareMsg.c_str());
            else
                HBShare::shared()->shareTo(HBShare_Facebook, _shareMsg.c_str());
            break;
        case kMenuTagShare2:
            HBUmeng::event("Button", "ScoreShare2");
            if (HBLocaleUtil::isChinese())
                HBShare::shared()->shareTo(HBShare_QQ, _shareMsg.c_str());
            else
                HBShare::shared()->shareTo(HBShare_Twitter, _shareMsg.c_str());
            break;
        default:
            break;
    }
}

void DialogScore::_closeDialog()
{
    if (kGameModeTest == gGameMode)
    {
        if (_isClear)
        {
            if (gTestLevel == 9)
                CCDirector::sharedDirector()->replaceScene(LayerLogo::scene());
            else
            {
                gTestLevel ++;
                DialogChellange::create(getParent());
            }
        }
    }
	removeFromParentAndCleanup(true);
}

void DialogScore::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);    
}

void DialogScore::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool DialogScore::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return true;
}

void DialogScore::_checkReview()
{
    // 已经评论过了,就不弹了
    if (gIsReviewd)
        return;
    
    gCurReviewCount --;
    gCurReviewCount = MAX(0, gCurReviewCount);
    
    //测试代码
//    gCurReviewCount = 0;
    
    if (HBUmeng::getParamValue("isReviewEnable") == 1 && gCurReviewCount == 0)
    {
        runAction(CCSequence::create(CCDelayTime::create(0.5), CCCallFunc::create(this, callfunc_selector(DialogScore::_showDialogReview)), NULL));
    }
}

void DialogScore::_showDialogReview()
{
    DialogReview::create(getParent());
}
