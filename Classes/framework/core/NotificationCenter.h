/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org
Copyright (c) 2011      Erawppa
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

#ifndef __NOTIFICATIONCENTER_H__
#define __NOTIFICATIONCENTER_H__

#include <vector>
using namespace std;

#include "cocos2d.h"
using namespace cocos2d;

#include "Singleton.h"

#define ImageDownloadNotification "ImageDownloadNotification"

class ImageNCInfo : public CCObject
{
public:
    ImageNCInfo(const string& name, const string& observerId, CCLayer* layer)
    : mImageName(name)
    , mObserverId(observerId)
    , mLayer(layer)
    {
        mLayer->retain();
    }
    
    ~ImageNCInfo()
    {
        mLayer->release();
    }
    
    string mImageName;
    string mObserverId;
	CCLayer* mLayer;
};

class NotificationObserver : public CCObject
{
public:
    NotificationObserver(CCObject *target, SEL_CallFuncO selector, const char* name, CCObject *obj);
    ~NotificationObserver();      
    
	void performSelector(CCObject *obj);
    
private:
    NotificationObserver() {}
    
    CC_SYNTHESIZE_READONLY(CCObject *, m_target, Target);
	CC_SYNTHESIZE_READONLY(SEL_CallFuncO, m_selector, Selector);
	CC_SYNTHESIZE_READONLY(char*, m_name, Name);
	CC_SYNTHESIZE_READONLY(CCObject *, m_object, Object);
    
    // 是否已经被删除
    CC_SYNTHESIZE(bool, mIsDeleted, IsDeleted);
};

class NotificationCenter : public CCObject, public Singleton<NotificationCenter>
{
public:
	NotificationCenter();
	~NotificationCenter();
    
    int addImgObserver(const char* name, CCLayer* layer);
    void addObserver(CCObject *target, SEL_CallFuncO selector, const char* name, CCObject *obj);
	void addObserver(CCObject *target, CCArray* nameList, SEL_CallFuncO selector);
    
    void removeObserver(CCObject *target, const char* name);
	void removeObserver(CCObject *target);
    
	void postNotification(const char* name);
	void postNotification(const char* name, CCObject *object);
    
private:
    
    void _imageLoaded(ImageNCInfo* img);
    
    // 数组正在循环中的标志
    bool mInUse;
    
    // 在循环中发生了数组删除请求,这里做好标记
    bool mNeedRemove;
    
    bool observerExisted(CCObject *target, const char* name);
    
    typedef std::vector<NotificationObserver*> vectorObserver;
    vectorObserver m_observers;
    vectorObserver mPendingAddObservers;
};

#define NOTICENTER NotificationCenter::shared()

#define RegisterObserver(target, selector, name, obj) NOTICENTER->addObserver(target, selector, name, obj)
#define RemoveObserver(target) NOTICENTER->removeObserver(target)
#define RegisterObservers(target, nameList, selector) NOTICENTER->addObserver(target, nameList, selector)
#define PostNotification(name, object) NOTICENTER->postNotification(name, object)

#endif//__CCNOTIFICATIONCENTER_H__