#include "Dialog.h"
#include "NotificationCenter.h"
#include "Framework.h"

Dialog::Dialog()
: mLayerDialog(NULL)
, mMenu(NULL)
, mMenuTouched(false)
{
}

Dialog::~Dialog()
{
	RemoveObserver(this);
}

void Dialog::popup()
{
    FRAMEWORK->getDialogMask()->removeFromParentAndCleanup(true);
	FRAMEWORK->getLayerDialog()->addChild(FRAMEWORK->getDialogMask());
	FRAMEWORK->getLayerDialog()->addChild(this);
}

void Dialog::close()
{
	removeFromParentAndCleanup(true);
	FRAMEWORK->getDialogMask()->removeFromParentAndCleanup(true);
	FRAMEWORK->popupNext();
}