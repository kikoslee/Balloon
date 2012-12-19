#include "PreHeader.h"
#include "DialogReview.h"
#include "HBUtilies.h"
#include "GlobalData.h"

typedef enum
{
    kMenuTagClose,
    kMenuTagReview,
} MenuTag;

DialogReview::DialogReview()
{
}

DialogReview::~DialogReview()
{
    
}

DialogReview* DialogReview::create(CCNode* parent)
{
    DialogReview *pRet = new DialogReview;
    if(pRet && pRet-> _init(parent))
    {
        pRet->autorelease();
        return pRet;
    }
    CC_SAFE_DELETE(pRet);
    return NULL;
}

bool DialogReview::_init(CCNode* parent)
{
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    CCLayerColor::initWithColor(ccc4(0,0,0,200), s.width, s.height);
	parent->addChild(this);
    
    float w2 = 160;
    
    _layerBase = CCLayer::create();
    _layerBase->setPosition(ccpRatio2(w2,270));
    addChild(_layerBase);

    createImageWithFrameName("dlg_bg.png", 0, 0, _layerBase);
    createLabel(getLocalizedString("Review"), getLocalizedString("fontNormal"), 24, gAnchorCenter, ccYELLOW, 0, 70, _layerBase);
    
    CCLabelTTF* text = CCLabelTTF::create(getLocalizedString("ReviewMsg"), getLocalizedString("fontNormal"), 16, CCSizeMake(ccFontRatio(230), ccFontRatio(100)), kCCTextAlignmentCenter);
	text->setAnchorPoint(ccp(0.5,0));
	text->setColor(ccWHITE);
	text->setPosition(ccpRatio(0,-60));
//    createStroke(text, 1, ccBLACK);
	_layerBase->addChild(text);
    
	CCMenu* menu = createMenu(_layerBase);
    
	createMenuItemWithCache("btn_close.png", "btn_close_d.png", 130, 105, kMenuTagClose, menu, this, menu_selector(DialogReview::_menuCallback));
    
    CCMenuItem* review = createMenuItemWithCache("btn_normal.png", "btn_normal_d.png", 0, -140, kMenuTagReview, menu, this, menu_selector(DialogReview::_menuCallback));
    addMenuLabel(review, getLocalizedString("GoReview"), getLocalizedString("fontNormal"), 20, ccYELLOW);

    GlobalData::save();

	setTouchEnabled(true);
    
    _layerBase->setScale(0);
    _layerBase->runAction(CCEaseElasticOut::create(CCScaleTo::create(0.3, 1)));
    
    return true;
}

void DialogReview::_menuCallback(CCMenuItem* sender)
{
    MenuTag tag = (MenuTag)sender->getTag();
    
    SimpleAudioEngine::sharedEngine()->playEffect("Menu.wav");
    
    switch (tag)
    {
        case kMenuTagReview:
            gIsReviewd = true;
            GlobalData::save();
            _layerBase->runAction(CCSequence::create(CCEaseElasticIn::create(CCScaleTo::create(0.3, 1)), CCCallFunc::create(this, callfunc_selector(DialogReview::_closeDialogWithReview)), NULL));
            break;
        case kMenuTagClose:
            gCurReviewCount = 10;
            GlobalData::save();
            _layerBase->runAction(CCSequence::create(CCEaseBounceOut::create(CCScaleTo::create(0.3, 1)), CCCallFunc::create(this, callfunc_selector(DialogReview::_closeDialog)), NULL));
            break;
        default:
            break;
    }
}

void DialogReview::_closeDialog()
{
	removeFromParentAndCleanup(true);
}

void DialogReview::_closeDialogWithReview()
{
    HBUtilies::gotoReview();
	removeFromParentAndCleanup(true);
}

void DialogReview::onEnter()
{
	CCLayer::onEnter();
	CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);    
}

void DialogReview::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool DialogReview::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	return true;
}