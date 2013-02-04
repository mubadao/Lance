#include "CheckBox.h"
CheckBox* CheckBox::create( const char* selectImage, const char* normalImage, CCObject* target, SEL_CallFuncO selector )
{
	CheckBox* pCheckBox = new CheckBox();
	pCheckBox->autorelease();
	pCheckBox->initWithNormalImage(selectImage, normalImage, target, selector);
	return pCheckBox;
}

bool CheckBox::initWithNormalImage( const char* selectImage, const char* normalImage, CCObject* target, SEL_CallFuncO selector )
{
	setTarget(target, selector);
	mNormalMenuItem = CCMenuItemImage::create(
		normalImage,
		normalImage,
		this,
		menu_selector(CheckBox::onNormalClick));
	mSelectMenuItem = CCMenuItemImage::create(
		selectImage,
		selectImage,
		this,
		menu_selector(CheckBox::onSelectClick));
	CCMenu* pMenu = CCMenu::create(mNormalMenuItem, mSelectMenuItem, NULL);
	addChild(pMenu);
	unselect();
	return true;
}

void CheckBox::onNormalClick( CCObject* pSender )
{
	select();
	activate();
}

void CheckBox::onSelectClick( CCObject* pSender )
{
	unselect();
	activate();
}

CheckBox::CheckBox()
	:mIsSelect(false)
{

}

CheckBox::~CheckBox()
{

}

void CheckBox::select()
{
	mIsSelect = true;
	mNormalMenuItem->setVisible(!mIsSelect);
	mSelectMenuItem->setVisible(mIsSelect);
}

void CheckBox::unselect()
{
	mIsSelect = false;
	mNormalMenuItem->setVisible(!mIsSelect);
	mSelectMenuItem->setVisible(mIsSelect);
}

void CheckBox::activate()
{
	if (mTarget && mSelector)
	{
		(mTarget->*mSelector)(this);
	}
}

void CheckBox::setTarget( CCObject *target, SEL_CallFuncO selector )
{
	mTarget = target;
	mSelector = selector;
}

