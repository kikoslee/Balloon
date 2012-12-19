#ifndef _SceneLogoLoader_H_
#define _SceneLogoLoader_H_

#include "SceneLogo.h"

class CCBReader;

class SceneLogoLoader : public CCLayerLoader
{
public:
    CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(SceneLogoLoader, loader);
    
protected:
    CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(SceneLogo);
};

#endif
