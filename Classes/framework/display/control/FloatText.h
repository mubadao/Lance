#ifndef _FloatText_H_
#define _FloatText_H_

#include "CommonHeader.h"

class FloatText : public Singleton<FloatText>, public CCLayer
{
public:
	FloatText();
	~FloatText();

	CREATE_FUNC(FloatText)

	virtual bool init();
	
	void playAnim(const char* content);
	void playAnimComplete();

private:
	CCLabelTTF* mDesc;
	CCScale9Sprite* mBg;
	
};

#endif