#pragma once

#include <unordered_map>
#include <string>

#define FLAG_USE_WSTRING

//#define FLAG_DEBUG_TRACE_NODE

#ifdef FLAG_USE_WSTRING
#define CHAR wchar_t
#define STRING wstring
#else
#define CHAR char
#define STRING string
#endif



class Trie
{
public:
	static void test();
};

template<typename T>
class TrieNode
{
public:
	TrieNode() {}
	~TrieNode();
	
public:
	void insert(const CHAR* key, T* inValue);
	TrieNode<T>* find(const CHAR* key);
	bool remove(const CHAR* key);

public:
	T* getValue() { return value; }

private:
	bool terminal = false;
	unordered_map<CHAR, TrieNode*> children;
	T* value = nullptr;
};

template<typename T>
inline TrieNode<T>::~TrieNode()
{
	for (auto& [c, child] : children)
	{
		delete child;
	}
}

template<typename T>
inline void TrieNode<T>::insert(const CHAR* key, T* inValue)
{
#ifdef FLAG_DEBUG_TRACE_NODE
	printf("INSERT : %c\t %p\n", *key, this);
#endif


	// 삽입 때 종단 \0 은 children[..] 에 추가 되지 않고, 노드로 생성되지도 않는다는 점에 주의한다. 
	// 인자로 key == '\0' 을 받는 노드는 '\0' 노드가 아니라, 마지막 단어 노드이다.
	// 아래 remove 와 관련된 내용이니 주의. 
	if (*key == 0)
	{
		terminal = true;
		value = inValue;
		return;
	}
		
	auto it = children.find(*key);
	if (it == children.end())
	{
		children[*key] = new TrieNode();
	}
	children[*key]->insert(key + 1, inValue); 
	// key + 1 : const CHAR* key 의 다음 문자열 을 받아 삽입한다
	// EX) root 에 "APPLE" 을 insert 시, 루트 노드의 자식은 A를 받고, 
	// 해당 노드는 자식을 생성하여 (또는 가져와서) P 를 받고.. 를 반복하고,
	// 마지막으로 '\n' 을 받는 자식은 전달받은 T* 를 자신의 T* 에 저장한다 


}

template<typename T>
inline TrieNode<T>* TrieNode<T>::find(const CHAR* key)
{
#ifdef FLAG_DEBUG_TRACE_NODE
	printf("FIND : %c\t %ull\n", *key, this);
#endif

	if (*key == 0)
	{
		// 아래 remove 에 따라 종단이라도 terminal 이 false 가 될 수 있다.
		if (terminal)
		{
			return this;
		}
		else
		{
			return nullptr;
		}
	}

	auto it = children.find(*key);
	if (it == children.end()) return nullptr;
	return children[*key]->find(key + 1);
	// 예시로 루트 노드에 APPLE 입력시,
	// 마찬가지로 루트 노드의 A 자식을 찾고, A자식은 P 자식을 찾고.. E 자식은 '\n' == 0 자식을 찾고,
	// '\n' 노드는 자신을 return 한다
}

template<typename T>
inline bool TrieNode<T>::remove(const CHAR* key)
{
	// 종단 \0 은 insert 때 node로 추가되지 않았다. 현 key 를 받는 노드가 \0 라면, 그 노드가 종단 노드이다.
	// 종단 노드는 다른 insert 함수에 의해 자식을 가질 수 있으므로, 바로 삭제처리 하지 않고, 우선 terminal 만 false로 둔 후, 
	// 자식이 없을 때 삭제 처리하도록 부모에게 요청한다
	if (*key == '\0')
	{
		if (terminal)
		{
			value = nullptr;
			terminal = false;

			return children.empty();
		}

	}

	auto it = children.find(*key);
	if (it != children.end())
	{
		if (it->second->remove(key + 1) == true)
		{
			delete it->second;
			children.erase(it);


#ifdef FLAG_DEBUG_TRACE_NODE
			printf("DELETED : %c\t %ull\n", *key, this);
#endif
		}
	}


	return children.empty();
}
