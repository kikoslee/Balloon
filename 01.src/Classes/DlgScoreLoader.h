#ifndef _DlgScoreLoader_H_
#define _DlgScoreLoader_H_

#include "DlgScore.h"

class CCBReader;

class DlgScoreLoader : public CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(DlgScoreLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(DlgScore);
};

#endif
