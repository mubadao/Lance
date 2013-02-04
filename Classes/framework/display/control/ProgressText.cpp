#include "ProgressText.h"
#include "StringUtil.h"

ProgressText::ProgressText()
    : mMinValue(0)
    , mMaxValue(100)
    , mCurValue(0)
    , mCount(NULL)
    , mMode(PROGRESS_TEXT_FORMAT_PERCENT)
{
}

ProgressText::~ProgressText()
{
}

void ProgressText::setPecent( float value )
{
	mCurValue = MIN(mMaxValue, MAX(mMinValue, value));
	mProgress->setPercentage(mCurValue / mMaxValue * 100);

	if (mMode == PROGRESS_TEXT_FORMAT_PERCENT)
	{
		int val = int(value / mMaxValue * 100);
		mCount->setString(fcs("%d%%", val));
	}
	else if (mMode == PROGRESS_TEXT_FORMAT_CURMAX)
	{
		mCount->setString(fcs("%d/%d", int(value), int(mMaxValue)));
	}
	else
	{
		mCount->setString(fcs("%d", (int)value));
	}	
}

void ProgressText::setRange( float min, float max )
{
    assert(max > 0);
    assert(max > min);
	mMinValue = min;
	mMaxValue = max;
}

ProgressText* ProgressText::create( const char *pszProgressFileName, const char* fontName, float fontSize )
{
	ProgressText* pProgressText = new ProgressText();
	pProgressText->initWithFile(pszProgressFileName, fontName, fontSize);
	return pProgressText;
}

void ProgressText::initWithFile( const char *pszProgressFileName, const char* fontName, float fontSize )
{
	CCSprite* pSprite = CCSprite::create(pszProgressFileName);
	CCSize size = pSprite->getContentSize();

	mProgress = CCProgressTimer::create(pSprite);
	mProgress->setType(kCCProgressTimerTypeBar);
	mProgress->setMidpoint(ccp(0,0));
	mProgress->setBarChangeRate(ccp(1,0));
	mProgress->setPercentage(80);

	mCount = CCLabelTTF::create("", fontName, fontSize);
	mCount->setPosition(ccp(0, 0));
	addChild(mProgress);
	addChild(mCount);
}
