#pragma once


namespace m
{
	template<typename T>
	[[nodiscard]] inline T* allocate(uint32 capacity) // ※ [[nodiscard]] : 호출자가 이 함수의 반환값을 변수에 저장하지 않고 버릴시, 컴파일 경고 발생
	{
		return static_cast<T*>(::operator new(capacity * sizeof(T)));
		// ■ ::operater new 
		//	new 는 메모리 할당 + 객체 생성자 호출인 반면,
		//	::operator new 는 메모리 할당만 함 ( C 의 malloc 과 같은 역할 )
	}

	template<typename T>
	inline void deallocate(const T* pos)
	{
		::operator delete(const_cast<void*>(static_cast<const volatile void*>(pos)));

		// ■ ::operator delete
		//	delete 는 메모리 수거 + 객체 소멸자 호출 인 반면,
		//	::operator delete 는 메모리 수거만 함 (C 의 free 와 같은 역할 )
		// 
		// □ const_cast
		//	const 를 제거.
		//	위 인자로 const T* 가 들어왔는데, 여기서 const 를 강제로 제거
		// 
		// □ static_cast<const volatile void*>
		//	모든 포인터 변형을 방지하고 void* 로 안전하게 업캐스팅하기 위한 목적
	}











	template<typename T, typename ...Args>
	inline void construct(const T* pos, Args && ...args)
	{
		::new (const_cast<void*>(static_cast<const volatile void*>(pos))) T(Std::forward<Args>(args)...);

		// ■ ::new
		//	placement new 라고 한다. (자주 언급되니 기억하자)
		//	new 가 메모리 할당 + 객체 생성자 호출인 반면,
		//  ::new 는 이미 할당되어 있는 메모리 주소에, 객체 생성자만 직접 호출
		// 
		//	※ 문법은 
		//	::new(메모리 주소) 타입(생성자_인자..) 
		//  이다  
		// 
		//	※ new = ::operator new + ::new
	}

	template<typename T, typename ...Args>
	inline void constructRange(const T* begin, const T* end, Args && ...args)
	{
		for (T* i = const_cast<T*>(begin); i != end; i++)
		{
			construct(i, Std::forward<Args>(args)...);
		}
	}



	template<typename T>
	inline void copyConstructRange(const T* dst, const T* begin, const T* end)
	{
		for (T* from = const_cast<T*>(begin); from != end; from++, dst++)
		{
			construct(dst, static_cast<const T&>(*from));
		}

		// □ Args&&... 와 static_cast<const T&>(..)
		//	Args&&.. 에 인자로 const T& 를 넘긴다
		// 	인자로 넘어가서 ::new(메모리주소) 타입(생성자인자) 의 생성자 인자로 const T& 가 넘어가고,
		//	위에 작성한 생성자 Vector<T>::Vector(const Vector& other) 로 호출된다
	}

	template<typename T>
	inline void moveConstructRange(const T* dst, T* begin, T* end)
	{
		for (; begin != end; dst++, begin++)
		{
			construct(dst, static_cast<T&&>(*begin));
		}

		// □ 마찬가지로 생성자 Vector(Vector&& other) 로 호출
	}




	template<typename T>
	inline void moveConstructBackward(const T* dst, T* rbegin, T* rend)
	{
		for (; rbegin != rend; dst--, rbegin--)
		{
			construct(dst, static_cast<T&&>(*rbegin));
		}
	}










	template<typename T>
	inline void destruct(T* pos)
	{
		pos->~T();
	}

	template<typename T>
	inline void destructRange(T* begin, T* end)
	{
		for (; begin != end; begin++)
		{
			begin->~T();
		}
	}

	template<typename T>
	inline void copyRange(T* dst, const T* begin, const T* end)
	{
		for (; begin != end; ++dst, ++begin)
		{
			*dst = *begin; // T에서 정의한 대입연산자 정의에 따라, operator=(const T& .. ) 에 할당한 대로 할당될 예정
		}
	}

	template<typename T>
	inline void moveRange(T* dst, const T* begin, const T* end)
	{
		T* pos = const_cast<T*>(begin);

		for (; pos != end; dst++, pos++)
		{
			*dst = static_cast<T&&>(*pos);
		}
	}

	template<typename T>
	inline void moveBackward(T* dst, const T* rbegin, const T* rend)
	{
		T* pos = const_cast<T*>(rbegin);
		for (; pos != rend; dst--, pos--)
		{
			*dst = static_cast<T&&>(*pos);
		}
	}
}