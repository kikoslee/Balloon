#include "ExplodeScore.h"

ExplodeScore::ExplodeScore(CCPoint pos, int score, int size, ccColor3B color)
{
    initWithString(fcs("%d", score), "HelveticaNeue-Bold", size);
    setColor(color);
	setPosition(pos);
    setAnchorPoint(gAnchorCenter);
    
    float time = 0.8;
    
    int offsetx = (rand()%50 + 30) * (rand() % 2 == 0 ? 1 : -1);
    int offsety = 200;
    
	runAction(CCSequence::create(CCSpawn::create(CCMoveBy::create(time, ccp(offsetx, offsety)), CCScaleTo::create(time, 4), CCFadeOut::create(time), NULL), CCCallFunc::create(this, callfunc_selector(ExplodeScore::_destroy)), NULL));

	autorelease();
}

void ExplodeScore::_destroy()
{
	stopAllActions();
    removeFromParentAndCleanup(true);
}
