#pragma once

#include "Std.h"

// 원본 깃허브
// - https://github.com/ross1573/mini_vector
//
// □ 수정한 부분 정리
//	1) 원본의 __copy_construct_range 함수에서, for 문 (3) 항에 dst++ 가 누락된 듯 싶다. 제마니이의 도움을 받아 dst++를 추가했다
//	
//	2) 원본의 move_range 함수에서, T* pos = __arr + (begin - this->begin()); 으로 pos를 할당하는데,
//	   this->begin() == __arr 이다. 의미없는 뺑뺑이가 이해가 가질 않는다. 
//     그래서 moveRange 함수에서 T* pos = const_cast<T*>(begin); 으로 수정했다
//	 ※ moveBackward 함수도 마찬가지로 수정함
//


template<typename T>
class Vector
{
public:
	typedef unsigned long uint32;

	
private:
	T* _arr;
	uint32 _size;
	uint32 _capacity;
	


public:
	Vector();
	explicit Vector(uint32 const size); // ※ explicit : 생성자에서의 암시적 형변환을 방지. (EX. explicit 이 없을시, Vector vec(10); 은 Vector vec = 10; 로 대체될 수 있음
	Vector(const Vector& other);
	Vector(Vector&& other);
	~Vector();








private:
	[[nodiscard]] T* allocate(uint32 capacity); // ※ [[nodiscard]] : 호출자가 이 함수의 반환값을 변수에 저장하지 않고 버릴시, 컴파일 경고 발생
	void deallocate(const T* pos);


	template<typename... Args>
	void construct(const T* pos, Args&&... args);
	template<typename... Args>
	void constructRange(const T* begin, const T* end, Args&&... args);

	void copyConstructRange(const T* dst, const T* begin, const T* end);
	void moveConstructRange(const T* dst, T* begin, T* end);

	void moveConstructBackward(const T* dest, T* rbegin, T* rend);


	void destruct(T* pos);
	void destructRange(T* begin, T* end);


	void copyRange(T* dst, const T* begin, const T* end);
	void moveRange(T* dst, const T* begin, const T* end);
	void moveBackward(T* dst, const T* rbegin, const T* rend);
};





template<typename T>
inline Vector<T>::Vector() : Vector(0)
{
}

template<typename T>
inline Vector<T>::Vector(uint32 const size)
	: _arr(allocate(size)), _size(size), _capacity(size)
{
}

template<typename T>
inline Vector<T>::Vector(const Vector& other)
	: _size(other._size), _capacity(other._capacity), _arr(allocate())
{
	// @@ TODO : 여기서부터 생성자 작업 재개
}

template<typename T>
inline Vector<T>::Vector(Vector&& other)
{
}

template<typename T>
inline Vector<T>::~Vector()
{
}












template<typename T>
inline T* Vector<T>::allocate(uint32 capacity)
{
	return static_cast<T*>(::operator new(capacity * sizeof(T)));
	// ■ ::operater new 
	//	new 는 메모리 할당 + 객체 생성자 호출인 반면,
	//	::operator new 는 메모리 할당만 함 ( C 의 malloc 과 같은 역할 )
}

template<typename T>
inline void Vector<T>::deallocate(const T* pos)
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











template<typename T>
template<typename ...Args>
inline void Vector<T>::construct(const T* pos, Args && ...args)
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

template<typename T>
template<typename ...Args>
inline void Vector<T>::constructRange(const T* begin, const T* end, Args && ...args)
{
	for (T* i = const_cast<T*>(begin); i != end; i++)
	{
		construct(i, Std::forward<Args>(args)...);
	}
}



template<typename T>
inline void Vector<T>::copyConstructRange(const T* dst, const T* begin, const T* end)
{
	for (T* from = const_cast<T*>(begin); from != end; from++, dst++) 
		// @@@ 원본에는 dst++ 가 없다. 작성자의 버그로 추정되기에, 제미나이의 도움을 받아 dst++ 부분을 추가했다
	{
		construct(dst, static_cast<const T&>(*from));
	}

	// □ Args&&... 와 static_cast<const T&>(..)
	//	Args&&.. 에 인자로 const T& 를 넘긴다
	// 	인자로 넘어가서 ::new(메모리주소) 타입(생성자인자) 의 생성자 인자로 const T& 가 넘어가고,
	//	위에 작성한 생성자 Vector<T>::Vector(const Vector& other) 로 호출된다
}

template<typename T>
inline void Vector<T>::moveConstructRange(const T* dst, T* begin, T* end)
{
	for (; begin != end; dst++, begin++)
	{
		construct(dst, static_cast<T&&>(*begin));
	}

	// □ 마찬가지로 생성자 Vector(Vector&& other) 로 호출
}




template<typename T>
inline void Vector<T>::moveConstructBackward(const T* dst, T* rbegin, T* rend)
{
	for (; rbegin != rend; dst--, rbegin--)
	{
		construct(dst, static_cast<T&&>(*rbegin));
	}
}










template<typename T>
inline void Vector<T>::destruct(T* pos)
{
	pos->~T();
}

template<typename T>
inline void Vector<T>::destructRange(T* begin, T* end)
{
	for (; begin != end; begin++)
	{
		begin->~T();
	}
}

template<typename T>
inline void Vector<T>::copyRange(T* dst, const T* begin, const T* end)
{
	for (; begin != end; ++dst, ++begin)
	{
		*dst = *begin;
	}
}

template<typename T>
inline void Vector<T>::moveRange(T* dst, const T* begin, const T* end)
{
	//T* pos = _arr + (begin - this->begin());)
	T* pos = const_cast<T*>(begin);
	
	for (; pos != end; dst++, pos++)
	{
		*dst = static_cast<T&&>(*pos);
	}
}

template<typename T>
inline void Vector<T>::moveBackward(T* dst, const T* rbegin, const T* rend)
{
	T* pos = const_cast<T*>(rbegin);
	for (; pos != rend; dst--, pos--)
	{
		*dst = static_cast<T&&>(*pos);
	}
}
