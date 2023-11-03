// #include "libvncxx/criticalsection.h"

// #if _WIN32
// 	#include <Windows.h>
// #elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	#include <pthread.h>
// #else
// 	#include <pthread.h>
// 	// #error "Unknown System"
// #endif

// #include "libvncxx/exceptions.h"

// using namespace std;

// namespace vn {
// namespace xplat {

// struct CriticalSection::Impl
// {
// 	#if _WIN32
// 	CRITICAL_SECTION CriticalSection;
// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	pthread_mutex_t CriticalSection;
// 	#else

// 	pthread_mutex_t CriticalSection;
// 	// #error "Unknown System"
// 	#endif

// 	Impl()
// 	{
// 	}
// };

// CriticalSection::CriticalSection() :
// 	_pi(new Impl())
// {
// 	#if _WIN32
// 	InitializeCriticalSection(&_pi->CriticalSection);
// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	pthread_mutex_init(&_pi->CriticalSection, NULL);
// 	#else
// 	// #error "Unknown System"

// 	pthread_mutex_init(&_pi->CriticalSection, NULL);
// 	#endif
// }

// CriticalSection::~CriticalSection()
// {
// 	#if _WIN32
// 	DeleteCriticalSection(&_pi->CriticalSection);
// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	pthread_mutex_destroy(&_pi->CriticalSection);
// 	#else
// 	// #error "Unknown System"
// 	pthread_mutex_destroy(&_pi->CriticalSection);
// 	#endif

// 	delete _pi;
// }

// void CriticalSection::enter()
// {
// 	#if _WIN32
// 	EnterCriticalSection(&_pi->CriticalSection);
// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	pthread_mutex_lock(&_pi->CriticalSection);
// 	#else
// 	// #error "Unknown System"
// 	pthread_mutex_lock(&_pi->CriticalSection);
// 	#endif
// }

// void CriticalSection::leave()
// {
// 	#if _WIN32
// 	LeaveCriticalSection(&_pi->CriticalSection);
// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	pthread_mutex_unlock(&_pi->CriticalSection);
// 	#else
// 	// #error "Unknown System"

// 	pthread_mutex_lock(&_pi->CriticalSection);
// 	#endif
// }

// }
// }
