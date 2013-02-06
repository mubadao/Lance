/****************************************************************************
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2008-2010 Ricardo Quesada

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
#include "TableTextView.h"
#include "CCDirector.h"
#include "CCApplication.h"
#include "support/CCPointExtension.h"
#include "touch_dispatcher/CCTouchDispatcher.h"
#include "touch_dispatcher/CCTouch.h"
#include "CCStdC.h"

#include <vector>
#include <stdarg.h>

using namespace std;

enum 
{
	kDefaultPadding =  5,
};

TableTextView* TableTextView::create(const char* fontName,...)
{
	va_list args;
	va_start(args,fontName);
	float fontSize = (float)va_arg(args, int);
    ccColor3B fontColor = va_arg(args, ccColor3B);
	const char* parm1 = va_arg(args, const char*);
	const char* parm2;
	int parm3;
	const char* parm4;
	CCArray* pArray = CCArray::create();
	CCArray* pLabelArray = CCArray::create();
	while(parm1) 
	{
		parm2 = va_arg(args, const char*);
		parm3 = va_arg(args, int);
		parm4 = va_arg(args, const char*);
		CCMenuItemImage* itemImage = CCMenuItemImage::create( parm1, parm2, NULL, NULL);
		itemImage->setTag(parm3);
		CCLabelTTF* label = CCLabelTTF::create(parm4, fontName, fontSize);
		label->setColor(fontColor);
		pArray->addObject(itemImage);
		pLabelArray->addObject(label);
		parm1 = va_arg(args, const char*);
	}
	return createWithArray(pArray, pLabelArray);
}

TableTextView* TableTextView::createWithArray(CCArray* pArrayOfItems, CCArray* pArrayOfLabels)
{
	TableTextView *pRet = new TableTextView();
	if (pRet && pRet->initWithArray(pArrayOfItems, pArrayOfLabels))
	{
		pRet->autorelease();
	}
	else
	{
		CC_SAFE_DELETE(pRet);
	}

	return pRet;
}

bool TableTextView::init()
{
	return initWithArray(NULL, NULL);
}

bool TableTextView::initWithArray(CCArray* pArrayOfItems, CCArray* pArrayOfLabels)
{
	if (CCLayer::init())
	{
		setTouchEnabled(true);

		m_bEnabled = true;
		// menu in the center of the screen
		CCSize s = CCDirector::sharedDirector()->getWinSize();

		ignoreAnchorPointForPosition(true);
		setAnchorPoint(ccp(0.5f, 0.5f));
		setContentSize(s);

		setPosition(ccp(s.width/2, s.height/2));

		if (pArrayOfItems != NULL)
		{
			int z=0;
			CCObject* pObj = NULL;
			CCARRAY_FOREACH(pArrayOfItems, pObj)
			{
				CCMenuItem* item = (CCMenuItem*)pObj;
				CCLabelTTF* label = (CCLabelTTF*)pArrayOfLabels->objectAtIndex(z);
				label->setPosition(ccp(item->getContentSize().width * item->getScaleX() / 2.0f, item->getContentSize().height * item->getScaleY() / 2.0f));
				item->addChild(label);
				addChild(item, z);
				z++;
			}
		}

		//    [self alignItemsVertically];
		m_pSelectedItem = NULL;
		m_eState = kCCMenuStateWaiting;
		return true;
	}
	return false;
}

/*
* override add:
*/
void TableTextView::addChild(CCNode * child)
{
	CCLayer::addChild(child);
}

void TableTextView::addChild(CCNode * child, int zOrder)
{
	CCLayer::addChild(child, zOrder);
}

void TableTextView::addChild(CCNode * child, int zOrder, int tag)
{
	CCAssert( dynamic_cast<CCMenuItem*>(child) != NULL, "Menu only supports MenuItem objects as children");
	CCLayer::addChild(child, zOrder, tag);
}

void TableTextView::onExit()
{
	if (m_eState == kCCMenuStateTrackingTouch)
	{
		m_pSelectedItem->unselected();
		m_eState = kCCMenuStateWaiting;
		m_pSelectedItem = NULL;
	}

	CCLayer::onExit();
}

//Menu - Events

void TableTextView::setHandlerPriority(int newPriority)
{
	CCTouchDispatcher* pDispatcher = CCDirector::sharedDirector()->getTouchDispatcher();
	pDispatcher->setPriority(newPriority, this);
}

void TableTextView::registerWithTouchDispatcher()
{
	CCDirector* pDirector = CCDirector::sharedDirector();
	pDirector->getTouchDispatcher()->addTargetedDelegate(this, kCCMenuHandlerPriority, true);
}

bool TableTextView::ccTouchBegan(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	if (m_eState != kCCMenuStateWaiting || ! m_bVisible || !m_bEnabled)
	{
		return false;
	}

	for (CCNode *c = m_pParent; c != NULL; c = c->getParent())
	{
		if (c->isVisible() == false)
		{
			return false;
		}
	}

	CCMenuItem* selectItem = itemForTouch(touch);

	if(selectItem == NULL || selectItem == m_pSelectedItem)
		return false;

	if (m_pSelectedItem != selectItem)
	{
		m_pSelectedItem = selectItem;
		m_eState = kCCMenuStateTrackingTouch;
		return true;
	}
	return false;
}

void TableTextView::ccTouchEnded(CCTouch *touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchEnded] -- invalid state");
	if (m_pSelectedItem)
	{
		selectItem(m_pSelectedItem->getTag());
		if (mTarget && mSelector)
		{
			(mTarget->*mSelector)(m_pSelectedItem);
		}
	}
	m_eState = kCCMenuStateWaiting;
}

void TableTextView::ccTouchCancelled(CCTouch *touch, CCEvent* event)
{
	CC_UNUSED_PARAM(touch);
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchCancelled] -- invalid state");
	m_eState = kCCMenuStateWaiting;
}

void TableTextView::ccTouchMoved(CCTouch* touch, CCEvent* event)
{
	CC_UNUSED_PARAM(event);
	CCAssert(m_eState == kCCMenuStateTrackingTouch, "[Menu ccTouchMoved] -- invalid state");
	CCMenuItem *currentItem = itemForTouch(touch);
	if (currentItem != m_pSelectedItem) 
	{
		if (m_pSelectedItem)
		{
			m_pSelectedItem->unselected();
		}
		m_pSelectedItem = currentItem;
		if (m_pSelectedItem)
		{
			m_pSelectedItem->selected();
		}
	}
}

//Menu - Alignment
void TableTextView::alignItemsVertically()
{
	alignItemsVerticallyWithPadding(kDefaultPadding);
}

void TableTextView::alignItemsVerticallyWithPadding(float padding)
{
	float height = -padding;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				height += pChild->getContentSize().height * pChild->getScaleY() + padding;
			}
		}
	}

	float y = height / 2.0f;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				pChild->setPosition(ccp(0, y - pChild->getContentSize().height * pChild->getScaleY() / 2.0f));
				y -= pChild->getContentSize().height * pChild->getScaleY() + padding;
			}
		}
	}
}

void TableTextView::alignItemsHorizontally(void)
{
	alignItemsHorizontallyWithPadding(kDefaultPadding);
}

void TableTextView::alignItemsHorizontallyWithPadding(float padding)
{

	float width = -padding;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				width += pChild->getContentSize().width * pChild->getScaleX() + padding;
			}
		}
	}

	float x = -width / 2.0f;
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				pChild->setPosition(ccp(x + pChild->getContentSize().width * pChild->getScaleX() / 2.0f, 0));
				x += pChild->getContentSize().width * pChild->getScaleX() + padding;
			}
		}
	}
}

void TableTextView::alignItemsInColumns(unsigned int columns, ...)
{
	va_list args;
	va_start(args, columns);

	alignItemsInColumns(columns, args);

	va_end(args);
}

void TableTextView::alignItemsInColumns(unsigned int columns, va_list args)
{
	vector<unsigned int> rows;
	while (columns)
	{
		rows.push_back(columns);
		columns = va_arg(args, unsigned int);
	}

	int height = -5;
	unsigned int row = 0;
	unsigned int rowHeight = 0;
	unsigned int columnsOccupied = 0;
	unsigned int rowColumns;

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				CCAssert(row < rows.size(), "");

				rowColumns = rows[row];
				// can not have zero columns on a row
				CCAssert(rowColumns, "");

				float tmp = pChild->getContentSize().height;
				rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

				++columnsOccupied;
				if (columnsOccupied >= rowColumns)
				{
					height += rowHeight + 5;

					columnsOccupied = 0;
					rowHeight = 0;
					++row;
				}
			}
		}
	}    

	// check if too many rows/columns for available menu items
	CCAssert(! columnsOccupied, "");

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	row = 0;
	rowHeight = 0;
	rowColumns = 0;
	float w = 0.0;
	float x = 0.0;
	float y = (float)(height / 2);

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				if (rowColumns == 0)
				{
					rowColumns = rows[row];
					w = winSize.width / (1 + rowColumns);
					x = w;
				}

				float tmp = pChild->getContentSize().height;
				rowHeight = (unsigned int)((rowHeight >= tmp || isnan(tmp)) ? rowHeight : tmp);

				pChild->setPosition(ccp(x - winSize.width / 2,
					y - pChild->getContentSize().height / 2));

				x += w;
				++columnsOccupied;

				if (columnsOccupied >= rowColumns)
				{
					y -= rowHeight + 5;

					columnsOccupied = 0;
					rowColumns = 0;
					rowHeight = 0;
					++row;
				}
			}
		}
	}    
}

void TableTextView::alignItemsInRows(unsigned int rows, ...)
{
	va_list args;
	va_start(args, rows);

	alignItemsInRows(rows, args);

	va_end(args);
}

void TableTextView::alignItemsInRows(unsigned int rows, va_list args)
{
	vector<unsigned int> columns;
	while (rows)
	{
		columns.push_back(rows);
		rows = va_arg(args, unsigned int);
	}

	vector<unsigned int> columnWidths;
	vector<unsigned int> columnHeights;

	int width = -10;
	int columnHeight = -5;
	unsigned int column = 0;
	unsigned int columnWidth = 0;
	unsigned int rowsOccupied = 0;
	unsigned int columnRows;

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				// check if too many menu items for the amount of rows/columns
				CCAssert(column < columns.size(), "");

				columnRows = columns[column];
				// can't have zero rows on a column
				CCAssert(columnRows, "");

				// columnWidth = fmaxf(columnWidth, [item contentSize].width);
				float tmp = pChild->getContentSize().width;
				columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

				columnHeight += (int)(pChild->getContentSize().height + 5);
				++rowsOccupied;

				if (rowsOccupied >= columnRows)
				{
					columnWidths.push_back(columnWidth);
					columnHeights.push_back(columnHeight);
					width += columnWidth + 10;

					rowsOccupied = 0;
					columnWidth = 0;
					columnHeight = -5;
					++column;
				}
			}
		}
	}

	// check if too many rows/columns for available menu items.
	CCAssert(! rowsOccupied, "");

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();

	column = 0;
	columnWidth = 0;
	columnRows = 0;
	float x = (float)(-width / 2);
	float y = 0.0;

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				if (columnRows == 0)
				{
					columnRows = columns[column];
					y = (float) columnHeights[column];
				}

				// columnWidth = fmaxf(columnWidth, [item contentSize].width);
				float tmp = pChild->getContentSize().width;
				columnWidth = (unsigned int)((columnWidth >= tmp || isnan(tmp)) ? columnWidth : tmp);

				pChild->setPosition(ccp(x + columnWidths[column] / 2,
					y - winSize.height / 2));

				y -= pChild->getContentSize().height + 10;
				++rowsOccupied;

				if (rowsOccupied >= columnRows)
				{
					x += columnWidth + 5;
					rowsOccupied = 0;
					columnRows = 0;
					columnWidth = 0;
					++column;
				}
			}
		}
	}
}

// Opacity Protocol

/** Override synthesized setOpacity to recurse items */
void TableTextView::setOpacity(GLubyte var)
{
	m_cOpacity = var;

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pChild);
				if (pRGBAProtocol)
				{
					pRGBAProtocol->setOpacity(m_cOpacity);
				}
			}
		}
	}
}

GLubyte TableTextView::getOpacity(void)
{
	return m_cOpacity;
}

void TableTextView::setColor(const ccColor3B& var)
{
	m_tColor = var;

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild)
			{
				CCRGBAProtocol *pRGBAProtocol = dynamic_cast<CCRGBAProtocol*>(pChild);
				if (pRGBAProtocol)
				{
					pRGBAProtocol->setColor(m_tColor);
				}
			}
		}
	}
}

const ccColor3B& TableTextView::getColor(void)
{
	return m_tColor;
}

CCMenuItem* TableTextView::itemForTouch(CCTouch *touch)
{
	CCPoint touchLocation = touch->getLocation();

	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCNode* pChild = dynamic_cast<CCNode*>(pObject);
			if (pChild && pChild->isVisible() && ((CCMenuItem*)pChild)->isEnabled())
			{
				CCPoint local = pChild->convertToNodeSpace(touchLocation);
				CCRect r = ((CCMenuItem*)pChild)->rect();
				r.origin = CCPointZero;

				if (r.containsPoint(local))
				{
					return (CCMenuItem*)pChild;
				}
			}
		}
	}

	return NULL;
}

void TableTextView::setTarget( CCObject *target, SEL_CallFuncO selector )
{
	mTarget = target;
	mSelector = selector;
}

void TableTextView::selectItem( int tag )
{
	if (m_pChildren && m_pChildren->count() > 0)
	{
		CCObject* pObject = NULL;
		CCARRAY_FOREACH(m_pChildren, pObject)
		{
			CCMenuItem* pChild = dynamic_cast<CCMenuItem*>(pObject);
			if((pChild->getTag() == tag) && SELECT_NONE != tag)
			{
				m_pSelectedItem = pChild;
				pChild->selected();
			}
			else
			{
				pChild->unselected();
			}
		}
	}

	if(SELECT_NONE == tag)
		m_pSelectedItem = NULL;
}
