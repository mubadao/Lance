#include "ComboBox.h"
#include "ToggleItem.h"

ComboBox::ComboBox()
	: mIsOpen(false)
	, mTarget(NULL)
	, mSelector(NULL)
	, mCurTag(-1)
    , mMenu(NULL)
	, mMainItem(NULL)
	, mOffsetY(0)
{
	mFontName = "Helvetica",
	mFontSize = 32;
	mFontColor = ccWHITE;
}

ComboBox::~ComboBox()
{
}

ComboBox* ComboBox::create(const char* upSkinImage, const char* downSkinImage, const char* listUpImage, const char* listDownImage)
{
	ComboBox* comboBox = new ComboBox();
	comboBox->initWithFile(upSkinImage, downSkinImage, listUpImage, listDownImage);
	comboBox->autorelease();
	return comboBox;
}

void ComboBox::initWithFile(const char* upSkinImage, const char* downSkinImage, const char* listUpImage, const char* listDownImage)
{
	mUpSkinImage = upSkinImage;
	mDownSkinImage = downSkinImage;
	mListUpImage = listUpImage;
	mListDownImage = listDownImage;
	
	mMenu = CCMenu::create(NULL);
	addChild(mMenu);

	mMainItem = ToggleItem::create(upSkinImage, downSkinImage, this, menu_selector(ComboBox::onMenuClick));
	mMainItem->addLabel("", mFontName.c_str(), mFontSize, mFontColor);
	mMenu->addChild(mMainItem);
}

void ComboBox::addItem(const char* label, int tag)
{
	ToggleItem* item = ToggleItem::create(mListUpImage.c_str(), mListDownImage.c_str(), this, menu_selector(ComboBox::onMenuClick));
	item->addLabel(label, mFontName.c_str(), mFontSize, mFontColor);
	item->setTag(tag);
	item->setVisible(false);
	mMenu->addChild(item);
	mItemList.push_back(item);
}

void ComboBox::refreshList()
{
	CCPoint mainPos = mMainItem->getPosition();
	CCSize mainSize = mMainItem->getContentSize();
	
	for(int i = 0; i < mItemList.size(); i++)
	{
		ToggleItem* item = mItemList[i];
		item->setPosition(mainPos.x, mainPos.y + mOffsetY - 8 - mainSize.height - (i * item->getContentSize().height));
		item->setVisible(mIsOpen);
	}
	if (mIsOpen)
		CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority - 1, true);
	else
		CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
}

void ComboBox::setTarget(CCObject* target, SEL_CallFuncO selector)
{
	mTarget = target;
	mSelector = selector;
}

void ComboBox::onMenuClick(CCObject* object)
{
	if(object == mMainItem)
	{
		openList(!mIsOpen);
	}
	else
	{
		for(int i = 0; i < mItemList.size(); i++)
		{
			ToggleItem* item = mItemList[i];
			if(object == item)
			{
				if (mTarget && mSelector)
					(mTarget->*mSelector)(item);
				mCurTag = item->getTag();
				mMainItem->mLabel->setString(item->mLabel->getString());
				openList(false);
				break;
			}
		}
	}
}

void ComboBox::openList(bool open)
{
	if (open == mIsOpen)
		return;

	mIsOpen = open;
	refreshList();
}

void ComboBox::onExit()
{
	CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
	CCLayer::onExit();
}

bool ComboBox::ccTouchBegan( CCTouch *pTouch, CCEvent *pEvent )
{
	mTouchedMenu = mMenu->ccTouchBegan(pTouch, pEvent);
	if (!mTouchedMenu)
		openList(false);
	return true;
}

void ComboBox::ccTouchMoved( CCTouch *pTouch, CCEvent *pEvent )
{
	if (mTouchedMenu)
		mMenu->ccTouchMoved(pTouch, pEvent);  
}

void ComboBox::ccTouchEnded( CCTouch *pTouch, CCEvent *pEvent )
{
	if (mTouchedMenu)
	{
		mMenu->ccTouchEnded(pTouch, pEvent);  
		mTouchedMenu = false;
	}
}

void ComboBox::ccTouchCancelled( CCTouch *pTouch, CCEvent *pEvent )
{
	if (mTouchedMenu)
	{
		mMenu->ccTouchEnded(pTouch, pEvent);  
		mTouchedMenu = false;  
	}
}

void ComboBox::selectItem(int tag)
{
	for(int i = 0; i < mItemList.size(); i++)
	{
		ToggleItem* item = mItemList[i];
		if(item->getTag() == tag)
		{
			mMainItem->mLabel->setString(item->mLabel->getString());
			mCurTag = item->getTag();
			return;
		}
	}
	mCurTag = -1;
	mMainItem->mLabel->setString("");
}

