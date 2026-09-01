#pragma once

#include <stdexcept>
	
template<typename T, size_t N>
class FixedArray
{
public:
	FixedArray() {}
	FixedArray(const T(&inArr)[N])
		// const T(&inArr)[N]
		// : const T &inArr[N] 로 하면, []가 & 보다 우선순위가 높아, 
		//   N 개의 요소 모두에 대한 참조를 의미한다.
		//   C++ 는 위 구문 컴파일시 오류 발생.
		//   const T(&inArr)[] 를 하면, & 를 우선 처리하여, 
		//   배열의 시작 주소 에 대한 참조로 읽어드린다.
	{
		memcpy(_elems, inArr, sizeof(T) * N);
	}

public:
	T& operator [](int index) 
	{
		return _elems[index];
	}
	const T& operator [](int index) const
	{
		return _elems[index];
	}

	size_t size() const
	{
		return N;
	}


public:
	T _elems[N];
};






inline void test_FixedArray()
{
	int arrs[] = { 1, 2, 3, 4, 5 };
	
	FixedArray<int, 5> array(arrs);

	for (int i = 0; i < array.size(); i++)
	{
		printf("%d, ", array[i]);
	}
	printf("\n");
}