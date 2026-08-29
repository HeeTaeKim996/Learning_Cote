#pragma once

namespace MemoryTracker
{
	inline int g_allocCount = 0;
	inline int g_deallocCount = 0;

	inline void printState()
	{
		printf("MemoryTracker : alloc(%d), dealloc(%d)\n",
			g_allocCount, g_deallocCount);
	}
}

template<typename T, typename... Args>
T* TrackNew(Args&&... args)
{
#ifdef _DEBUG
	MemoryTracker::g_allocCount++;
#endif
	return new T(std::forward<Args>(args)...);
}

template<typename T>
void TrackDelete(T*& ptr)
{
	if (ptr != nullptr)
	{
#ifdef _DEBUG
		MemoryTracker::g_deallocCount++;
#endif
		delete ptr;
		ptr = nullptr; // Dangling 포인트 방지
	}
}