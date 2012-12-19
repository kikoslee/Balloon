#ifndef _SceneMainLoader_H_
#define _SceneMainLoader_H_

#include "SceneMain.h"

class CCBReader;

class SceneMainLoader : public CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SceneMainLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SceneMain);
};

#endif
