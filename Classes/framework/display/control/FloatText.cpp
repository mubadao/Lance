#include "FloatText.h"
#include "Framework.h"

FloatText::FloatText()
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
	mBg->setAnchorPoint(ccp(0.5, 1.0));
	addChild(mBg);
    
	mDesc = CCLabelTTF::create("", "Helvetica", 40);
	mDesc->setAnchorPoint(ccp(0.5, 1.3));
	addChild(mDesc);
	
	FRAMEWORK->topLayer->addChild(this);
	
    return true;
}

void FloatText::playAnim(const char* content)
{
    stopAllActions();

	mDesc->setString(content);
	
    CCSize bgSize = mDesc->getContentSize();
	bgSize.width += 10;
	bgSize.height += 10;
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
    
    CCFiniteTimeAction* s4 = CCSequence::create(s3, CCCallFunc::create(this,callfunc_selector(FloatText::playAnimComplete)), NULL);
    
    runAction(s4);
}
void FloatText::playAnimComplete()
{
	setVisible(false);
}
