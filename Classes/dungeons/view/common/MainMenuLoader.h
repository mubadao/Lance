#ifndef MainMenuLoader_h__
#define MainMenuLoader_h__

#include "Global.h"
#include "MainMenu.h"

class MainMenuLoader : public cocos2d::extension::CCNodeLoader {
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(MainMenuLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(MainMenu);
};

#endif // MainMenuLoader_h__
