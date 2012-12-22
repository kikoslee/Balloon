#ifndef _ExplodeScore_H_
#define _ExplodeScore_H_

#include "HBCommon.h"

class ExplodeScore : public CCLabelTTF
{
	void _destroy();
    
public:
	ExplodeScore(CCPoint pos, int score, int size, ccColor3B color);
	
};

#endif