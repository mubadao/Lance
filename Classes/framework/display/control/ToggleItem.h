#ifndef _ToggleItem_H_
#define _ToggleItem_H_

#include "CommonHeader.h"

class ToggleItem : public CCMenuItemImage
{
public:
	ToggleItem();
	virtual ~ToggleItem();
	
	static ToggleItem* create(const char* normalImage, const char* selectedImage, CCObject* target, SEL_MenuHandler selector);

	void addLabel(const char* label, const char* fontName, float fontSize, const ccColor3B& fontColor);

	CCLabelTTF* mLabel;
};

#endif