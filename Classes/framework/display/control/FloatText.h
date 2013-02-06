#ifndef _FloatText_H_
#define _FloatText_H_

#include "CommonHeader.h"

class FloatText : public Singleton<FloatText>, public CCLayer
{
public:
	FloatText();
	~FloatText();

	static FloatText* shared();

	CREATE_FUNC(FloatText)

	virtual bool init();
	
	void playAnim(const char* content);

private:
	static FloatText* ms_Singleton;

	CCLabelTTF* mDesc;
	CCScale9Sprite* mBg;
	
	void _playAnimComplete();
};

#endif