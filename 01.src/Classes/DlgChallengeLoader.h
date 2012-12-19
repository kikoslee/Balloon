#ifndef _DlgChallengeLoader_H_
#define _DlgChallengeLoader_H_

#include "DlgChallenge.h"

class CCBReader;

class DlgChallengeLoader : public CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(DlgChallengeLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(DlgChallenge);
};

#endif
