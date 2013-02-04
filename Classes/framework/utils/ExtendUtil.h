#ifndef ExtendUtil_h__
#define ExtendUtil_h__

#include "Global.h"

class ExtendUtil
{
public:
	static CCNode* readNode(const char * pCCBFileName, CCObject* pOwer)
	{
		cocos2d::extension::CCBReader * ccbReader = new cocos2d::extension::CCBReader(CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary());
		ccbReader->autorelease();
		CCNode * node = ccbReader->readNodeGraphFromFile(pCCBFileName, pOwer);
		return node;
	}
    
    static CCNode* loadItem(const char* pClassName, CCNodeLoader* pCCNodeLoader)
    {
        CCNodeLoaderLibrary* pLoaderLibrary = CCNodeLoaderLibrary::newDefaultCCNodeLoaderLibrary();
        pLoaderLibrary->registerCCNodeLoader(pClassName, pCCNodeLoader);
        
        CCBReader* ccbReader = new CCBReader(pLoaderLibrary);
        CCNode* node = ccbReader->readNodeGraphFromFile(fcs("%s.ccbi", pClassName), NULL);
        ccbReader->release();
        return node;
    }

};
#define ReadItem(pClassName, pCCNodeLoader) ExtendUtil::loadItem(pClassName, pCCNodeLoader)
#define ReadNode(pCCBFileName, pOwer) ExtendUtil::readNode(pCCBFileName, pOwer)
#define RegisterLoader(pClassName, pCCNodeLoader) CCNodeLoaderLibrary::sharedCCNodeLoaderLibrary()->registerCCNodeLoader(pClassName, pCCNodeLoader)
#define CCBI_CREATE_FUNC(pClassName)  \
static pClassName* create(CCObject* pOwer = NULL) \
{	\
	RegisterLoader(#pClassName, pClassName##Loader::loader());	\
	std::string fileName = (#pClassName);	\
	fileName += ".ccbi";	\
	return (pClassName*)(ReadNode(fileName.c_str(), NULL));	\
}

#define SET_CONTROLBUTTON_LABEL(MEMBERVARIABLE, LABEL) \
	MEMBERVARIABLE->setTitleForState(ccs(LABEL),CCControlStateNormal);

#define CCB_CONTROLBUTTON_GLUE(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLE, LABEL) \
	if (pTarget == TARGET && strcmp(pMemberVariableName, MEMBERVARIABLENAME) == 0) { \
		CCControlButton* pOldVar = MEMBERVARIABLE; \
		MEMBERVARIABLE = dynamic_cast<CCControlButton*>(pNode); \
		if(LABEL != NULL) \
			SET_CONTROLBUTTON_LABEL(MEMBERVARIABLE, LABEL) \
		CC_ASSERT(MEMBERVARIABLE); \
		if (pOldVar != MEMBERVARIABLE) { \
			CC_SAFE_RELEASE(pOldVar); \
			MEMBERVARIABLE->retain(); \
		} \
		return true; \
	}

#define CCB_CCLABELTTF_GLUE(TARGET, MEMBERVARIABLENAME, MEMBERVARIABLE, LABEL) \
	if (pTarget == TARGET && strcmp(pMemberVariableName, MEMBERVARIABLENAME) == 0) { \
		CCLabelTTF* pOldVar = MEMBERVARIABLE; \
		MEMBERVARIABLE = dynamic_cast<CCLabelTTF*>(pNode); \
		if(LABEL != NULL) \
			MEMBERVARIABLE->setString(LABEL); \
		CC_ASSERT(MEMBERVARIABLE); \
		if (pOldVar != MEMBERVARIABLE) { \
			CC_SAFE_RELEASE(pOldVar); \
			MEMBERVARIABLE->retain(); \
		} \
		return true; \
	}
#endif // ExtendUtil_h__t
