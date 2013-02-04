#ifndef _TableView_h__
#define _TableView_h__
#include "Global.h"

#define SELECT_NONE 1000

class TableView : public CCLayer, public CCRGBAProtocol
{
	/** Color: conforms with CCRGBAProtocol protocol */
	CC_PROPERTY_PASS_BY_REF(ccColor3B, m_tColor, Color);
	/** Opacity: conforms with CCRGBAProtocol protocol */
	CC_PROPERTY(GLubyte, m_cOpacity, Opacity);
	/** whether or not the menu will receive events */
	bool m_bEnabled;
    
public:
    TableView()
        :m_pSelectedItem(NULL)
    {}
    virtual ~TableView(){}

	CC_DEPRECATED_ATTRIBUTE static TableView* menuWithArray(CCArray* pArrayOfItems);

	CC_DEPRECATED_ATTRIBUTE static TableView* menuWithItem(CCMenuItem* item);

    /** creates an empty TableView */
    static TableView* create();

	static TableView* create(const char* image, ...);

    /** creates a TableView with a CCArray of CCMenuItem objects */
    static TableView* createWithArray(CCArray* pArrayOfItems);

    /** initializes an empty TableView */
    bool init();

    /** initializes a TableView with it's items */
    bool initWithItems(CCMenuItem* item, va_list args);

    /** initializes a TableView with a NSArray of CCMenuItem objects */
    bool initWithArray(CCArray* pArrayOfItems);

    /** align items vertically */
    void alignItemsVertically();
    /** align items vertically with padding
    @since v0.7.2
    */
    void alignItemsVerticallyWithPadding(float padding);

    /** align items horizontally */
    void alignItemsHorizontally();
    /** align items horizontally with padding
    @since v0.7.2
    */
    void alignItemsHorizontallyWithPadding(float padding);

    /** align items in rows of columns */
    void alignItemsInColumns(unsigned int columns, ...);
    void alignItemsInColumns(unsigned int columns, va_list args);

    /** align items in columns of rows */
    void alignItemsInRows(unsigned int rows, ...);
    void alignItemsInRows(unsigned int rows, va_list args);

    /** set event handler priority. By default it is: kTableViewTouchPriority */
    void setHandlerPriority(int newPriority);

    //super methods
    virtual void addChild(CCNode * child);
    virtual void addChild(CCNode * child, int zOrder);
    virtual void addChild(CCNode * child, int zOrder, int tag);
    virtual void registerWithTouchDispatcher();

    /**
    @brief For phone event handle functions
    */
    virtual bool ccTouchBegan(CCTouch* touch, CCEvent* event);
    virtual void ccTouchEnded(CCTouch* touch, CCEvent* event);
    virtual void ccTouchCancelled(CCTouch *touch, CCEvent* event);
    virtual void ccTouchMoved(CCTouch* touch, CCEvent* event);

    /**
    @since v0.99.5
    override onExit
    */
    virtual void onExit();

    virtual void setOpacityModifyRGB(bool bValue) {CC_UNUSED_PARAM(bValue);}
    virtual bool isOpacityModifyRGB(void) { return false;}
    
    virtual bool isEnabled() { return m_bEnabled; }
    virtual void setEnabled(bool value) { m_bEnabled = value; };

	void setItemPosition(int tag, CCPoint& pos);
	void getItemPosition(int tag, CCPoint& pos);

protected:
	CCObject* mTarget;
	SEL_CallFuncO mSelector;
	tCCMenuState m_eState;
	CCMenuItem *m_pSelectedItem;
    CCMenuItem* itemForTouch(CCTouch * touch);

public:
	void setTarget( CCObject *target, SEL_CallFuncO selector );
	void selectItem(int tag);
};
#endif // _TableView_h__