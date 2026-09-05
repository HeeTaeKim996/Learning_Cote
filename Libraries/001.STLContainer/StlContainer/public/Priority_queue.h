

#include "SizeType.h"
#include "Mem.h"
#include "Std.h"

template<typename T>
class Priority_queue
{
public:
	Priority_queue(sizeType size);

public:
	T& top() { return *(_arr); }
	bool empty() const { return _size == 0; }
	sizeType size() const noexcept { return _size; }


public:
	void push(const T& value);
	void push(T&& value);

	template<typename... ArgS>
	void emplace(Args&&... args);

	void pop();

private:
	T* _arr;
	sizeType _size;
	sizeType _capacity;
};

template<typename T>
inline Priority_queue<T>::Priority_queue(sizeType size)
	: _arr(m::allocate<T>(size)), _size(size), _capacity(size)
{
}
