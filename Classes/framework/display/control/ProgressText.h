#ifndef _ProgressText_H_
#define _ProgressText_H_

#include "CommonHeader.h"

enum ProgressTextFormat
{
	PROGRESS_TEXT_FORMAT_PERCENT    = 0,	//%45
	PROGRESS_TEXT_FORMAT_CURMAX     = 1,	//12/67
	PROGRESS_TEXT_FORMAT_CURONLY    = 2     //45
};

class ProgressText : public CCNode
{
	ProgressText();
	~ProgressText();

    // 显示模式
    CC_SYNTHESIZE(ProgressTextFormat, mMode, Mode);

protected:
    // 数值文本
	CCLabelTTF* mCount;
    // 进度条
	CCProgressTimer* mProgress;
    // 最大值/最小值/当前值
	float mMaxValue, mMinValue, mCurValue;
    
public:
    // 设定当前值
	void setPecent(float value);
    // 设定区间
	void setRange(float min, float max);
    
	CCLabelTTF* getText() {return mCount; }
    
	void initWithFile(const char* pszProgressFileName, const char* fontName, float fontSize);
	static ProgressText* create(const char* pszProgressFileName, const char* fontName, float fontSize);
};

#endif