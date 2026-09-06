

/*
_EXPORT_STD template <class _RanIt>
_CONSTEXPR20 void sort(const _RanIt _First, const _RanIt _Last) { // order [_First, _Last)
    _STD sort(_First, _Last, less<>{});
}

==>> Algorithm 의 sort 함수다. 보다시피 인자로 특정 클래스를 받는 게 아니라,
     _First, _Last 로 들어온 인자가 동일한 클래스인지만 검수하고 있다.

     Interater 클래스들은 동일 인터페이스를 상속받지 않는다. 
     단지 아래처럼 규격에 필요한 함수들을 구현만 해놓으면 된다.
     
     규격 자체를 정의하는 인터페이스로 구현이 되지 않았기에, 인터페이스를 만들었어도,
     특정 함수가 요구하는 함수 구현이 안돼있을 수 있다. 이렇다면 컴파일 시 함수 구현이 안된 걸로
     오류가 남
*/


template<typename T>
class IteratorTemplate
{
private:
    T* _ptr;

public:
    IteratorTemplate(T* ptr)
        : _ptr(ptr)
    {
    }

    T& operator*() const
    {
        return *_ptr;
    }

    T* operator->() const
    {
        return _ptr;
    }

    IteratorTemplate& operator++()
    {
        ++_ptr;
        return *this;
    }

    IteratorTemplate& operator--()
    {
        --_ptr;
        return *this;
    }

    IteratorTemplate operator+(sizeType n) const
    {
        return IteratorTemplate(_ptr + n);
    }

    IteratorTemplate operator-(sizeType n) const
    {
        return IteratorTemplate(_ptr - n);
    }

    difference_type operator-(const IteratorTemplate& other) const
    {
        return _ptr - other._ptr;
    }
};