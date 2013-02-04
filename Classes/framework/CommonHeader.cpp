#include "CommonHeader.h"

bool isTouchInside(CCTouch* pTouch, CCNode* node)
{
    CCPoint touchLocation = pTouch->getLocation();
    touchLocation = node->getParent()->convertToNodeSpace(touchLocation);
    CCRect bBox = node->boundingBox();
    return bBox.containsPoint(touchLocation);
}