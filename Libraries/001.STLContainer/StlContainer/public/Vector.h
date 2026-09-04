#pragma once

#include "Std.h"

// 참조 원본 깃허브
// - https://github.com/ross1573/mini_vector

typedef unsigned long sizeType;

template<typename T>
class Vector
{
private:
	T* _arr;
	sizeType _size;
	sizeType _capacity;
	


public:
	Vector();
	explicit Vector(sizeType const size); // ※ explicit : 생성자에서의 암시적 형변환을 방지. (EX. explicit 이 없을시, Vector vec(10); 은 Vector vec = 10; 로 대체될 수 있음
	Vector(const Vector& other);
	Vector(Vector&& other);
	~Vector();

public:
	sizeType size() const noexcept { return _size; }
	sizeType capacity() const noexcept { return _capacity; }

	T* data()				{ return _arr; }
	const T* data() const	{ return _arr; }

	T* begin()				{ return _arr; }
	const T* begin() const	{ return _arr; }

	T* end()				{ return _arr + _size; }
	const T* end() const	{ return _arr + _size; }

	T& front()				{ return *_arr; }
	const T& front() const	{ return *_arr; }

	T& back()				{ return *(_arr + _size - 1); }
	const T& back() const	{ return *(_arr + _size - 1); }

	T& at(sizeType index)				{ return _arr[index]; }
	const T& at(sizeType index) const	{ return _arr[index]; }

	T& operator[](sizeType index)				{ return _arr[index]; }
	const T& operator[](sizeType index) const { return _arr[index]; }

	Vector& operator = (const Vector& other);
	Vector& operator = (Vector&& other);



public:
	void push_back(const T& value);
	void push_back(T&& value);
	void pop_back();
	template <typename... Args>
	T& emplace_back(Args&&... args);

	void insert(const T* pos, const T& value);
	void insert(const T* pos, T* begin, T* end);

	void erase(const T* pos);
	void erase(const T* begin, const T* end);

	void reserve(sizeType capacity);

	void resize(sizeType size);
	void resize(sizeType size, const T& value);

	void swap(Vector& other);
	
	void clear();

	void shrink_to_fit();
};





template<typename T>
inline Vector<T>::Vector() : Vector(0)
{
}

template<typename T>
inline Vector<T>::Vector(sizeType const size)
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

	m::copyConstructRange<T>(_arr, other._arr, other._arr + other._size);
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
	m::destructRange<T>(_arr, _arr + _size);
	m::deallocate<T>(_arr);
	_arr = nullptr;
}






template<typename T>
inline  Vector<T>& Vector<T>::operator=(const Vector<T>& other)
{
	T* dst =  m::allocate<T>(other._capacity);
	m::copyConstructRange<T>(dst, other._arr, other._arr + other._size);

	m::destructRange<T>(_arr, _arr + _size);
	m::deallocate<T>(_arr);

	_arr = dst;
	_size		= other._size;
	_capacity	= other._capacity;
	

	return *this;
}

template<typename T>
inline  Vector<T>& Vector<T>::operator=(Vector<T>&& other)
{
	m::destructRange<T>(_arr, _arr + _size);
	m::deallocate<T>(_arr);
	
	_size		= other._size;
	_capacity	= other._capacity;
	_arr		= other._arr;

	other._size = 0;
	other._capacity = 0;
	other._arr = nullptr;
	
	return *this;
}





































template<typename T>
inline void Vector<T>::push_back(const T& value)
{
	if (_size < _capacity)
	{
		m::construct<T>(_arr + _size++, value); // T 가 생성자로 const T& 를 받는다는 전제
	}
	else
	{
		sizeType newCap = _capacity == 0 ? 1 : _capacity * 2;
		T* newArr = m::allocate<T>(newCap);

		T* dst = newArr + _size;
		m::construct<T>(dst, value);
		dst -= 1;

		m::moveConstructBackward<T>(dst, _arr + _size - 1, _arr - 1); // 여기서 (2) 는 rbegin 역할, (3) 은 rend

		m::destructRange<T>(_arr, _arr + _size);
		m::deallocate<T>(_arr);

		_arr = newArr;
		_capacity = newCap;
		_size++;
	}
}


template<typename T>
inline void Vector<T>::push_back(T&& value)
{
	if (_size < _capacity)
	{
		m::construct<T>(_arr + _size++, static_cast<T&&>(value)); // T 가 생성자로 rvalue를 받는다는 전제
	}
	else
	{
		sizeType newCap = _capacity == 0 ? 1 : _capacity * 2;
		T* newArr = m::allocate<T>(newCap);

		T* dst = newArr + _size;
		m::construct<T>(dst, static_cast<T&&>(value));
		dst -= 1;
		m::moveConstructBackward<T>(dst, _arr + _size - 1, _arr - 1);

		m::destructRange<T>(_arr, _arr + _size);
		m::deallocate<T>(_arr);

		_arr = newArr;
		_capacity = newCap;
		_size++;
	}
}



template<typename T>
inline void Vector<T>::pop_back()
{
	// 방어코드는 작성하지 않는다. stl vector 도 성능을 위해 사용자에게 책임을 맡긴다 함
	// if (_size == 0) return;

	m::destruct<T>(_arr + --_size);
}




template<typename T>
template<typename... Args>
inline T& Vector<T>::emplace_back(Args&&... args)
{
	if (_size < _capacity)
	{
		m::construct<T>(_arr + _size++, Std::forward<Args>(args)...);
	}
	else
	{
		sizeType newCap = _capacity == 0 ? 1 : _capacity * 2;
		T* newArr = m::allocate<T>(newCap);

		T* dst = newArr + _size;
		m::construct<T>(dst, Std::forward<Args>(args)...);
		dst -= 1;
		m::moveConstructBackward<T>(dst, _arr + _size - 1, _arr - 1);

		m::destructRange<T>(_arr, _arr + _size);
		m::deallocate<T>(_arr);

		_arr = newArr;
		_capacity = newCap;
		++_size;
	}

	return back(); // emplace_back 은 T의 생성자 인자를 받아 T를 생성하고 삽입한 후, T를 리턴
}

















template<typename T>
inline void Vector<T>::insert(const T* itPos, const T& value)
{
	if (itPos == _arr + _size)
	{
		push_back(value);
	}
	else
	{
		T* begin = const_cast<T*>(&value);
		T* end = begin + 1;

		insert(itPos, begin, end);
	}
}

template<typename T>
inline void Vector<T>::insert(const T* itPos, T* srcBegin, T* srcEnd)
{
	sizeType insertingSize = sizeType(srcEnd - srcBegin);

	sizeType newSize = _size + insertingSize;

	T* pos = const_cast<T*>(itPos);

	if (newSize > _capacity)
	{
		sizeType newCap = _capacity * 2 > newSize ? _capacity * 2 : newSize;
		T* newArr = m::allocate<T>(newCap);

		T* dst = newArr;


		m::moveConstructRange<T>(dst, _arr, pos);
		dst += sizeType(pos - _arr);

		m::copyConstructRange<T>(dst, srcBegin, srcEnd);
		dst += insertingSize;

		m::moveConstructRange<T>(dst, pos, _arr + _size);

		m::destructRange<T>(_arr, _arr + _size);
		m::deallocate<T>(_arr);

		_arr = newArr;
		_capacity = newCap;
	}
	else
	{
		// 삽입으로 인해 기존 end 밖으로 밀려나는 애들을, T 생성과 함께 복사(?)
		m::moveConstructBackward<T>(_arr + newSize - 1,
			_arr + _size - 1, _arr + _size - insertingSize - 1);

		// 삽입으로 인해 뒤로 밀려나지만, end 밖으로 밀려나지는 않는 애들을 복사
		m::moveBackward<T>(_arr + _size - 1, _arr + _size - insertingSize - 1, pos - 1);

		// 새로 삽입되는 애들을 복사
		m::copyRange<T>(pos, srcBegin, srcEnd);
	}

	_size = newSize;
}

template<typename T>
inline void Vector<T>::erase(const T* itPos)
{
	T* pos = const_cast<T*>(itPos);


	m::moveRange<T>(pos, pos + 1, _arr + _size);
	m::destruct<T>(_arr + _size - 1);

	_size--;
}

template<typename T>
inline void Vector<T>::erase(const T* itBegin, const T* itEnd)
{
	T* begin = const_cast<T*>(itBegin);
	T* end = const_cast<T*>(itEnd);

	m::destructRange<T>(begin, end);
	m::moveRange<T>(begin, end, _arr + _size);
	
	_size -= (sizeType)(itEnd - itBegin);
}

template<typename T>
inline void Vector<T>::reserve(sizeType capacity)
{
	if (_capacity >= capacity) return;

	T* dst = m::allocate<T>(capacity);

	m::moveConstructRange<T>(dst, _arr, _arr + _size);

	m::destructRange<T>(_arr, _arr + _size);
	m::deallocate<T>(_arr);

	_arr = dst;
	_capacity = capacity;

}

template<typename T>
inline void Vector<T>::resize(sizeType newSize)
{
	if (_size == newSize) return;

	if (newSize > _size)
	{
		if (newSize > _capacity)
		{
			sizeType newCap = _capacity * 2 > newSize ? _capacity * 2 : newSize;
			T* dst = m::allocate<T>(newCap);

			m::moveConstructRange<T>(dst, _arr, _arr + _size);
			m::constructRange<T>(dst + _size, dst + newSize); // (3) 항인 Args... 를 생략하면, 기본 생성자로 생성

			m::destructRange<T>(_arr, _arr + _size);
			m::deallocate<T>(_arr);

			_arr = dst;
			_capacity = newCap;
		}
		else
		{
			m::constructRange<T>(_arr + _size, _arr + newSize);
		}
	}
	else
	{
		m::destructRange<T>(_arr + newSize, _arr + _size);
	}

	_size = newSize;
}

template<typename T>
inline void Vector<T>::resize(sizeType newSize, const T& value)
{
	if (newSize == _size) return;

	if (newSize > _size)
	{
		if (newSize > _capacity)
		{
			sizeType newCap = _capacity * 2 > newSize ? _capacity * 2 : newSize;
			T* dst = m::allocate<T>(newCap);

			m::moveConstructRange<T>(dst, _arr, _arr + _size);
			m::constructRange<T>(dst + _size, dst + newSize, value);

			m::destructRange<T>(_arr, _arr + _size);
			m::deallocate<T>(_arr);

			_arr = dst;
			_capacity = newCap;
		}
		else
		{
			m::constructRange<T>(_arr + _size, _arr + newSize, value);
		}
	}
	else
	{
		m::destructRange<T>(_arr + newSize, _arr + _size);
	}

	_size = newSize;
}








template<typename T>
inline void Vector<T>::swap(Vector& other)
{
	sizeType tempSize = _size;
	sizeType tempCapacity = _capacity;
	T* tempArr = _arr;

	_size = other._size;
	_capacity = other._capacity;
	_arr = other._arr;

	other._size = tempSize;
	other._capacity = tempCapacity;
	other._arr = tempArr;
}



template<typename T>
inline void Vector<T>::clear()
{
	m::destructRange<T>(_arr, _arr + _size);
	_size = 0;
}

template<typename T>
inline void Vector<T>::shrink_to_fit()
{
	if (_size == 0)
	{
		_capacity = 0;
		m::deallocate<T>(_arr);
		_arr = nullptr;
		return;
	}

	sizeType newCap = _size;
	if (newCap == _capacity) return;

	T* dst = m::allocate<T>(newCap);
	m::moveConstructRange<T>(dst, _arr, _arr + _size);

	m::destructRange<T>(_arr, _arr + _size);
	m::deallocate<T>(_arr);

	_arr = dst;
	_capacity = newCap;
}
