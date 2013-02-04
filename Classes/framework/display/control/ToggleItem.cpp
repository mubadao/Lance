#include "ToggleItem.h"

ToggleItem* ToggleItem::create(const char *normalImage, const char *selectedImage, CCObject* target, SEL_MenuHandler selector)
{
	ToggleItem* item = new ToggleItem();
	item->initWithNormalImage(normalImage, selectedImage, NULL, target, selector);
    item->autorelease();
	return item;
}

ToggleItem::ToggleItem()
	: mLabel(NULL)
{
}

ToggleItem::~ToggleItem()
{
}

void ToggleItem::addLabel(const char* label, const char* fontName, float fontSize, const ccColor3B& fontColor)
{
	if (mLabel)
		mLabel->removeFromParent();
	mLabel = CCLabelTTF::create(label, fontName, fontSize);
	mLabel->setColor(fontColor);
	mLabel->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
	addChild(mLabel);
}

