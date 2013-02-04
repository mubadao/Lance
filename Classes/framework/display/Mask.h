#ifndef _Mask_H_
#define _Mask_H_

#include "CommonHeader.h"

class Mask : public CCLayerColor
{
public:
	Mask();
	virtual ~Mask();

	static Mask* create(float opacity);

	virtual bool ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent);
};

#endif