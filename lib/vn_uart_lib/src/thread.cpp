
// #include "libvncxx/thread.h"
// #include "libvncxx/exceptions.h"

// #if _WIN32
// 	#include <Windows.h>
// #elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	#include <pthread.h>
// 	#include <unistd.h>
// #else
// 	#error "Unknown System"
// #endif

// using namespace std;

// namespace vn {
// namespace xplat {

// struct Thread::Impl
// {
// 	#if _WIN32
// 	HANDLE ThreadHandle;
// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	pthread_t ThreadHandle;
// 	void* Data;
// 	#else
// 	#error "Unknown System"
// 	#endif

// 	Thread::ThreadStartRoutine StartRoutine;

// 	Impl() :
// 		#if _WIN32
// 		ThreadHandle(NULL),
// 		#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 		ThreadHandle(0),
// 		Data(NULL),
// 		#else
// 		#error "Unknown System"
// 		#endif
// 		StartRoutine(NULL)
// 	{ }

// 	#if __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__

// 	static void* StartRoutineWrapper(void* data)
// 	{
// 		Impl* impl = (Impl*) data;

// 		impl->StartRoutine(impl->Data);

// 		return NULL;
// 	}

// 	#endif
// };

// Thread::Thread(
// 	ThreadStartRoutine startRoutine) :
// 	_pimpl(new Thread::Impl())
// {
// 	_pimpl->StartRoutine = startRoutine;
// }

// Thread::~Thread()
// {
// 	delete _pimpl;
// }

// Thread* Thread::startNew(ThreadStartRoutine startRoutine, void* routineData)
// {
// 	Thread* newThread = new Thread(startRoutine);

// 	newThread->start(routineData);

// 	return newThread;
// }

// void Thread::start(void* routineData)
// {
// 	if (_pimpl->StartRoutine != NULL)
// 	{
// 		#if _WIN32
		
// 		_pimpl->ThreadHandle = CreateThread(
// 			NULL,
// 			0,
// 			(LPTHREAD_START_ROUTINE) _pimpl->StartRoutine,
// 			routineData,
// 			0,
// 			NULL);

// 		if (_pimpl->ThreadHandle == NULL)
// 			return;

// 		#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__

// 		_pimpl->Data = routineData;

// 		int errorCode = pthread_create(
// 			&_pimpl->ThreadHandle,
// 			NULL,
// 			Impl::StartRoutineWrapper,
// 			_pimpl);

// 		if (errorCode != 0)
// 			return;

// 		#else
// 		#error "Unknown System"
// 		#endif
// 	}
// 	else
// 	{
// 		return;
// 	}
// }

// void Thread::join()
// {
// 	#if _WIN32
	
// 	WaitForSingleObject(
// 		_pimpl->ThreadHandle,
// 		INFINITE);

// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
	
// 	if (pthread_join(
// 		_pimpl->ThreadHandle,
// 		NULL))
// 		return;

// 	#else
// 	#error "Unknown System"
// 	#endif
// }

// void Thread::sleepSec(uint32_t numOfSecsToSleep)
// {
// 	#if _WIN32
// 	Sleep(numOfSecsToSleep * 1000);
// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	sleep(numOfSecsToSleep);
// 	#else
// 	#error "Unknown System"
// 	#endif
// }

// void Thread::sleepMs(uint32_t numOfMsToSleep)
// {
// 	#if _WIN32
// 	Sleep(numOfMsToSleep);
// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	usleep(numOfMsToSleep * 1000);
// 	#else
// 	#error "Unknown System"
// 	#endif
// }

// void Thread::sleepUs(uint32_t numOfUsToSleep)
// {
// 	#if _WIN32
// 	return;
// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	usleep(numOfUsToSleep);
// 	#else
// 	#error "Unknown System"
// 	#endif
// }

// void Thread::sleepNs(uint32_t numOfNsToSleep)
// {
// 	#if _WIN32
// 	return;
// 	#elif __linux__ || __APPLE__ || __CYGWIN__ || __QNXNTO__ || __IMXRT1062__
// 	return;
// 	#endif
// }

// }
// }