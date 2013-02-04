#include "Mask.h"

Mask::Mask()
{
}

Mask::~Mask()
{
}

Mask* Mask::create( float opacity )
{
	Mask* pLayer = new Mask();
    pLayer->initWithColor(ccc4(0, 0, 0, opacity));
    pLayer->setTouchMode(kCCTouchesOneByOne);
	pLayer->setTouchEnabled(true);
    pLayer->setTouchPriority(touch_priority_3);
	return pLayer;
}

bool Mask::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
	return true;
}