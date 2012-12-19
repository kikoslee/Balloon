#ifndef _SceneLogo_H_
#define _SceneLogo_H_

#include "HBCommon.h"

class SceneLogo
: public CCLayer
, public CCBSelectorResolver
, public CCBMemberVariableAssigner
, public CCNodeLoaderListener
{
public:
    SceneLogo();
    virtual ~SceneLogo();
    
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_WITH_INIT_METHOD(SceneLogo, create);

    virtual SEL_MenuHandler onResolveCCBCCMenuItemSelector(CCObject* pTarget, const char* pSelectorName);
    virtual SEL_CCControlHandler onResolveCCBCCControlSelector(CCObject* pTarget, const char* pSelectorName);
    virtual bool onAssignCCBMemberVariable(CCObject* pTarget, const char* pMemberVariableName, CCNode* pNode);
    virtual void onNodeLoaded(CCNode* pNode, CCNodeLoader* pNodeLoader);

private:
    CCControlButton* mBtnChallenge;
    CCControlButton* mBtnFree;
    CCControlButton* mBtnScore;
    CCControlButton* mBtnMore;
    
    CCSprite* mLogo;
    CCLayer* mLayerMadel;

    void onBtnChallenge(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnFree(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnScore(CCObject* pSender, CCControlEvent pCCControlEvent);
    void onBtnMore(CCObject* pSender, CCControlEvent pCCControlEvent);
};


#endif