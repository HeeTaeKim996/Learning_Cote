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




public:
	T* data()				{ return _arr; }
	const T* data() const	{ return _arr; }

	T* begin()				{ return _arr; }
	const T* begin() const	{ return _arr; }

	T* end()				{ return _arr + _size; }
	const T* end() const	{ return _arr + _size; }

	T& front()				{ return *_arr; }
	const T& front() const	{ return *_arr; }

	T& back()				{ return *(end() - 1); }
	const T& back() const	{ return *(end() - 1); }

	T& at(uint32 index)			{ return _arr[index]; }
	const T& at(uint32 index)	{ return _arr[index]; }

	T& operator[](uint32 index)				{ _arr[index]; }
	const T& operator[](uint32 index) const { _arr[index]; }

	Vector& operator = (const Vector& other);
	Vector& operator = (Vector&& other);

};





template<typename T>
inline Vector<T>::Vector() : Vector(0)
{
}

template<typename T>
inline Vector<T>::Vector(uint32 const size)
	: _arr(m::allocate<T>(size)), _size(size), _capacity(size)
{
}

template<typename T>
inline Vector<T>::Vector(const Vector& other)
	: _size(other._size), _capacity(other._capacity), _arr(m::allocate<T>(_capacity))
{
	//  원본에 이해가 안되는 부분이 2개 있었고, 수정했다
	//	1) allocate(_capacity) 를 할당하지 않고 공란을 뒀다. _capacity 를 할당했다
	//	2) copyRange 하면 안된다. 위에 보면 allocate 로 공간 할당만 한 상태이다. 이때 해야할 건 copyConstructRange 이다

	m::copyConstructRange<T>(_arr, other.begin(), other.end());
}

template<typename T>
inline Vector<T>::Vector(Vector&& other)
	: _arr(other._arr), _size(other._size), _capacity(other._capacity)
{
	other._size = 0;
	other._capacity = 0;
	other._arr = nullptr;
}

template<typename T>
inline Vector<T>::~Vector()
{
	m::destructRange<T>(begin(), end());
	m::deallocate<T>(_arr);
	_arr = nullptr;
}






template<typename T>
inline  Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	T* dst =  m::allocate(other._capacity);
	m::copyConstructRange(dst, other.begin(), other.end());

	m::destructRange<T>(begin(), end());
	m::deallocate(_arr);

	_arr = dst;
	_size		= other._size;
	_capacity	= other._capacity;
	

	return *this;
}

template<typename T>
inline  Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
	m::destructRange<T>(begin(), end());
	m::deallocate<T>(_arr);
	
	_size		= other._size;
	_capacity	= other._capacity;
	_arr		= other._arr;

	other._size = 0;
	other._capacity = 0;
	other._arr = nullptr;
	
	return *this;
}