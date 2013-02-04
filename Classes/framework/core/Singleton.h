#ifndef Singleton_h__
#define Singleton_h__
#include <assert.h>

template <typename T> class Singleton
{
public:
	static T* shared()
	{
        static T* ms_Singleton = new T;
        return ms_Singleton;
    }
};

#endif // Singleton_h__