#ifndef __SINGLETON_H_
#define __SINGLETON_H_
#include "macros.h"

NMS_BEGIN(kcommon)

template<typename T>
class Singleton {
	static void create() { if (!_instance) _instance = new T(); }

	static void destroy() { sdelete(_instance); }

	static T* instance() { return _instance; }

private:
	static T *_instance;
};

template<typename T> T *Singleton<T>::_instance = 0;

NMS_END // end namespace kcommon

#endif // __SINGLETON_H_

