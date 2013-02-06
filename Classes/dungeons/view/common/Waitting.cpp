#include "Waitting.h"
#include "AlertDialog.h"

Waitting::Waitting()
	: mMask(NULL)
	, isShow(false)
{
	mMask = Mask::create(100);
	addChild(mMask);
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();  //获取界面大小

	mLoading1 = CCSprite::create("loading_4.png");
	mLoading2 = CCSprite::create("loading_4.png");
	addChild(mLoading1);
	addChild(mLoading2);
	mLoading2->setRotation(180);
	
	mLoading1->setPosition(ccp(size.width/2, size.height/2));
	mLoading2->setPosition(ccp(size.width/2, size.height/2));
}

Waitting::~Waitting()
{
}

void Waitting::show()
{
	if(isShow)
		return;
	isShow = true;
	FRAMEWORK->topLayer->addChild(this);
	
	mLoading1->runAction(CCRepeatForever::create(CCRotateBy::create(2, -180)));
	mLoading2->runAction(CCRepeatForever::create(CCRotateBy::create(2, -180.0)));

	CCSequence* sequence1 = (CCSequence*)CCSequence::create(
		CCDelayTime::create(120.0),
		CCCallFunc::create(this,callfunc_selector(Waitting::onHide)),
		NULL);
	runAction(sequence1);
}

void Waitting::hide()
{
	if(!isShow)
		return;
	stopAllActions();
	removeFromParentAndCleanup(true);
	isShow = false;
}

void Waitting::onHide()
{
	AlertDialog::initContent(gls("176"));
	FRAMEWORK->popup("AlertDialog");
	hide();
}

