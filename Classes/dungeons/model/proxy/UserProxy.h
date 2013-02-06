#ifndef _UserProxy_h_
#define _UserProxy_h_

#include "Global.h"
#include "DataVO.h"

class UserProxy : public Singleton<UserProxy>
{
	void testData();
public:
	UserProxy();
	~UserProxy();
    
	UserVO userVO;
	UserVO mLastUserVO;
    XMLVersionMap mXMLVersionMap;
    string mServerUrl;
    string mConfigUrl;
    string mResourceUrl;
    string mHtmlUrl;
    long getAllEnergyTime();
    long getAllPowerTime();
    int getEnergyMax();
	void saveUserInfo();
};

#endif