#ifndef _Dialog_H_
#define _Dialog_H_

#include "CommonHeader.h"

class Dialog : public CCLayer
{
public:
	Dialog();
	virtual ~Dialog();

	virtual void refresh() {}
	virtual void popup();
	virtual void close();

protected:
	CCLayer* mLayerDialog;
    
	CCMenu* mMenu;
	bool mMenuTouched;    
};

#endif