#pragma once

#include <cstring>
#include <stdexcept>

// std::vector 가 이런식으로 데이터를 관리한다 함

template<typename T>
class Array
{
public:

	Array() {}
	template<size_t N>
	Array(const T(&inArr)[N])
		: _size(N), _offset(new T[N])
	{
		std::memcpy(_offset, inArr, sizeof(T) * N);
	}
	Array(size_t size) : _size(size), _offset(new T[size]) {}
	Array(size_t size, T defaultValue) : _size(size), _offset(new T[size])
	{
		for (size_t i = 0; i < _size; i++)
		{
			_offset[i] = defaultValue;
		}
	}


	~Array()
	{
		delete[] _offset; // 생성 때 new T[] 로 생성했기에, delete[] 호출시 알아서 생성했던 크기만큼 메모리를 해제함
	}



public:
	// 유효성 검사는 [] 에서는 하지 않는다 함
	T& operator[](size_t index)
	{
		return _offset[index];
	}
	const T& operator[](size_t index) const
	{
		return _offset[index];
	}
	size_t size() const { return _size; }

	// at 함수에서는 유효성 검사
	T& at(size_t index)
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index out of range");
		}
		return _offset[index];
	}

	const T& at(size_t index) const
	{
		if (index >= _size)
		{
			throw std::out_of_range("Index out of range");
		}
		return _offset[index];
	}
	

private:
	T* _offset;
	size_t _size;
};

inline void test_Array()
{
	Array<int> array({4, 5, 6});

	for (int i = 0; i < array.size(); i++)
	{
		printf("%d, ", array[i]);
	}
}
