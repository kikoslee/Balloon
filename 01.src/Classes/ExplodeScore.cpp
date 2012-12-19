#include "PreHeader.h"
#include "ExplodeScore.h"
#include "HBUtilies.h"

ExplodeScore::ExplodeScore(CCPoint pos, int score, int size, ccColor3B color)
{
    initWithString(fcs("%d", score), getLocalizedString("fontNormal"), ccFontRatio(size));
    setColor(color);
	setPosition(pos);
    setAnchorPoint(gAnchorCenter);
    
    float time = 0.8;
    
    int offsetx = (rand()%50 + 30) * (rand() % 2 == 0 ? 1 : -1);
    int offsety = 150;
    
	runAction(CCSequence::create(CCSpawn::create(CCMoveBy::create(time, ccpRatio2(offsetx, offsety)), CCScaleTo::create(time, 4), CCFadeOut::create(time), NULL), CCCallFunc::create(this, callfunc_selector(ExplodeScore::_destroy)), NULL));

	autorelease();
}

void ExplodeScore::_destroy()
{
	stopAllActions();
    removeFromParentAndCleanup(true);
}
