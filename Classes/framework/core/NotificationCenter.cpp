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

#include "NotificationCenter.h"
#include "cocoa/CCArray.h"
#include <string>
#include "FileDownload.h"

using namespace std;

static NotificationCenter *s_sharedNotifCenter = NULL;

NotificationCenter::NotificationCenter()
: mInUse(false)
, mNeedRemove(false)
{
}

NotificationCenter::~NotificationCenter()
{
}

bool NotificationCenter::observerExisted(CCObject *target,const char* name)
{
    vectorObserver::iterator itr;
    for(itr = m_observers.begin(); itr != m_observers.end(); ++itr)
    {
        if (!strcmp((*itr)->getName(), name) && (*itr)->getTarget() == target)
            return true;
    }
    return false;
}

int NotificationCenter::addImgObserver(const char* name, CCLayer* layer)
{
    static unsigned int gImageDownloadNotificationID = 0;

    CCString* strObserverID = CCString::createWithFormat("ImageDownload%d", gImageDownloadNotificationID);
        
    ImageNCInfo* info = new ImageNCInfo(name, strObserverID->getCString(), layer);
        
    NotificationObserver* observer = new NotificationObserver(this, callfuncO_selector(NotificationCenter::_imageLoaded), strObserverID->getCString(), info);
    assert (observer);
        
    m_observers.push_back(observer);
    gImageDownloadNotificationID ++;
    
    return gImageDownloadNotificationID - 1;
}

void NotificationCenter::addObserver(CCObject *target, SEL_CallFuncO selector, const char* name, CCObject *obj)
{
    if (observerExisted(target, name))
        return;
    
    NotificationObserver *observer = new NotificationObserver(target, selector, name, obj);
    assert (observer);
    
    if (mInUse)
        mPendingAddObservers.push_back(observer);
    else
        m_observers.push_back(observer);
}

void NotificationCenter::addObserver( CCObject *target, CCArray* nameList, SEL_CallFuncO selector )
{
	CCObject* obj = NULL;
	CCARRAY_FOREACH(nameList, obj)
	{
		const char* name = ((CCString*)(obj))->getCString();
		addObserver(target, selector, name, NULL);
	}
}

void NotificationCenter::removeObserver(CCObject *target,const char *name)
{
    vectorObserver::iterator itr;
    for (itr = m_observers.begin(); itr != m_observers.end(); ++itr)
    {
        if (!strcmp((*itr)->getName(),name) && (*itr)->getTarget() == target)
        {
            if (mInUse)
            {
                (*itr)->setIsDeleted(true);
                mNeedRemove = true;
            }
            else
            {
                delete *itr;
                m_observers.erase(itr);
            }
            return;
        }
    }
}

void NotificationCenter::removeObserver( CCObject *target )
{
    vectorObserver::iterator itr;
    for (itr = m_observers.begin(); itr != m_observers.end();)
	{
		if ((*itr)->getTarget() == target)
        {
            if (mInUse)
            {
                (*itr)->setIsDeleted(true);
                ++itr;
                mNeedRemove = true;
            }
            else
            {
                delete *itr;
                itr = m_observers.erase(itr);
            }
        }
        else
            ++itr;
	}
}

void NotificationCenter::postNotification(const char *name, CCObject *object)
{
    vectorObserver::iterator itr;
    
    mInUse = true;
    mNeedRemove = false;
    
    int i = 0;
    for (itr = m_observers.begin(); itr != m_observers.end(); ++itr, i++)
    {
        if ((*itr) != NULL)
        {
            if (!(*itr)->getIsDeleted())
            {
                if (!strcmp(name, (*itr)->getName()))
                    (*itr)->performSelector(object);
            }
        }
    }
    
    if (mNeedRemove)
    {
        for (itr = m_observers.begin(); itr != m_observers.end();)
        {
            if ((*itr)->getIsDeleted())
            {
                delete *itr;
                itr = m_observers.erase(itr);
            }
            else
                ++itr;
        }
    }
    
    if (mPendingAddObservers.size() > 0)
    {
        for (itr = mPendingAddObservers.begin(); itr != mPendingAddObservers.end(); ++itr)
        {
            m_observers.push_back(*itr);
        }
        mPendingAddObservers.clear();
    }
    
    mNeedRemove = false;
    mInUse = false;
}

void NotificationCenter::postNotification(const char *name)
{
    postNotification(name,NULL);
}

void NotificationCenter::_imageLoaded(ImageNCInfo* img)
{
	CCLOG("imageLoaded success,imageName:%s", img->mImageName.c_str());
    
    CCSprite* sprite = getSpriteFromWriteablePath(img->mImageName.c_str());

    CCLOG("got sprite 0x%X", sprite);
    
    //TODO:这里可以去掉
    float scalex = img->mLayer->getContentSize().width  / (float)sprite->getContentSize().height;
    float scaley = img->mLayer->getContentSize().height  / (float)sprite->getContentSize().height;
    sprite->setScaleX(scalex);
    sprite->setScaleX(scaley);

    sprite->setAnchorPoint(ccp(0,0));
    img->mLayer->addChild(sprite);
    
	removeObserver(this, img->mObserverId.c_str());
    img->release();
}


////////////////////////////////////////////////////////////////////////////////
///
/// NotificationObserver
///
////////////////////////////////////////////////////////////////////////////////
NotificationObserver::NotificationObserver(CCObject *target, SEL_CallFuncO selector, const char *name, CCObject *obj)
{
    m_target = target;
    m_selector = selector;
    m_object = obj;
    mIsDeleted = false;
    
    m_name = new char[strlen(name)+1];
    memset(m_name,0,strlen(name)+1);
    
    string orig (name);
    orig.copy(m_name,strlen(name),0);
}

NotificationObserver::~NotificationObserver()
{
    if (m_name)
        delete m_name;
}

void NotificationObserver::performSelector( CCObject *obj )
{
	if (m_target)
	{
		m_object = obj;
		(m_target->*m_selector)(this);
	}
}