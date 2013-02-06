#include "FloatText.h"
#include "Framework.h"

FloatText* FloatText::ms_Singleton =  NULL;

FloatText::FloatText()
	: mBg(NULL)
	, mDesc(NULL)
{
}

FloatText::~FloatText()
{
}

bool FloatText::init()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    setPosition(ccp(winSize.width/2, winSize.height/2+40));
    setVisible(false);
    
	mBg = CCScale9Sprite::create("bg_21.png");
	addChild(mBg);
    
	mDesc = CCLabelTTF::create("", "Helvetica", 40);
	addChild(mDesc);
	
	FRAMEWORK->topLayer->addChild(this);
	
    return true;
}

void FloatText::playAnim(const char* content)
{
    stopAllActions();

	mDesc->setString(content);
	
    CCSize bgSize = mDesc->getContentSize();
	bgSize.width += 40;
	bgSize.height += 20;
	mBg->setContentSize(bgSize);
	
    setVisible(true);
	setPosition(ccp(320, 560));
    
	CCFiniteTimeAction* s1 = CCSequence::create(
		CCFadeIn::create(0.5),
		CCDelayTime::create(1.0),
		CCFadeOut::create(0.3),
		NULL);

    CCFiniteTimeAction* s2 = CCSequence::create(
        CCMoveBy::create(0.5, ccp(0, 100)),
        CCDelayTime::create(1.0),
        CCMoveBy::create(0.3, ccp(0, 40)),
        NULL);
    
    CCFiniteTimeAction* s3 = CCSpawn::create(s1, s2, NULL);
    
    CCFiniteTimeAction* s4 = CCSequence::create(s3, CCCallFunc::create(this,callfunc_selector(FloatText::_playAnimComplete)), NULL);
    
    runAction(s4);
}

void FloatText::_playAnimComplete()
{
	setVisible(false);
}

FloatText* FloatText::shared()
{
	if (ms_Singleton == NULL)
		ms_Singleton = FloatText::create();
	return ms_Singleton;
}
