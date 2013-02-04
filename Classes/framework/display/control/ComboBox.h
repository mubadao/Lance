#ifndef _ComboBox_H_
#define _ComboBox_H_

#include "ToggleItem.h"

class ComboBox : public CCLayer
{
public:
	ComboBox();
	virtual ~ComboBox();
	
	static ComboBox* create(const char* upSkinImage, const char* downSkinImage, const char* listUpImage, const char* listDownImage);

	void initWithFile(const char* upSkinImage, const char* downSkinImage, const char* listUpImage, const char* listDownImage);
	void addItem(const char* label, int tag);
	void refreshList();
	void setTarget(CCObject* target, SEL_CallFuncO selector);
	void onMenuClick(CCObject* object);
	void openList(bool open);
	void selectItem(int tag);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);  
	virtual void ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent);  
	virtual void ccTouchEnded(CCTouch *pTouch, CCEvent *pEvent);  
	virtual void ccTouchCancelled(CCTouch *pTouch, CCEvent *pEvent);

	virtual void onExit();

protected:
	string mUpSkinImage;
	string mDownSkinImage;
	string mListUpImage;
	string mListDownImage;

	string mFontName;
	float mFontSize;
	ccColor3B mFontColor;

	CCMenu* mMenu;
	ToggleItem* mMainItem;
	vector<ToggleItem*> mItemList;
	
	CCObject* mTarget;
	SEL_CallFuncO mSelector;
	
	bool mIsOpen;
	bool mTouchedMenu;

	CC_SYNTHESIZE(int, mCurTag, CurTag);
    CC_SYNTHESIZE(float, mOffsetY, OffsetY);
};

#endif