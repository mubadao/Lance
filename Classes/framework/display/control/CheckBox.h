#ifndef CheckBox_h__
#define CheckBox_h__

#include "cocos2d.h"
using namespace cocos2d;

class CheckBox : public CCNode
{
public:
	CheckBox();
	~CheckBox();

	bool initWithNormalImage(const char* selectImage, const char* normalImage, CCObject* target, SEL_CallFuncO selector);
	static CheckBox* create(const char* selectImage, const char* normalImage, CCObject* target, SEL_CallFuncO selector);
    
    bool isSelect(){return mIsSelect;}
	void setTarget(CCObject *target, SEL_CallFuncO selector);
protected:
	CCMenuItemImage* mNormalMenuItem;
	CCMenuItemImage* mSelectMenuItem;
	CCObject* mTarget;
	SEL_CallFuncO mSelector;
	CC_SYNTHESIZE_READONLY(bool, mIsSelect, IsSelect);
	void select();
	void unselect();
	void activate();
private:
	void onNormalClick( CCObject* pSender );
	void onSelectClick( CCObject* pSender );
};
#endif // CheckBox_h__
