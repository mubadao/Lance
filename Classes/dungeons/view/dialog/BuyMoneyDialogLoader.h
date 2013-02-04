#ifndef _BuyMoneyDialogLoader_H_
#define _BuyMoneyDialogLoader_H_

#include "Global.h"
#include "BuyMoneyDialog.h"

class BuyMoneyDialogLoader : public CCLayerLoader
{
public:
	CCB_STATIC_NEW_AUTORELEASE_OBJECT_METHOD(BuyMoneyDialogLoader, loader);

protected:
	CCB_VIRTUAL_NEW_AUTORELEASE_CREATECCNODE_METHOD(BuyMoneyDialog);
};

#endif
