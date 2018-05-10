#pragma once

//#include "Platform/Debug/AssertMessage.h"
#include "Utility/NoCopy.h"

#include <assert.h>

BEGIN_NAMESPACE(Utility)

template<typename DATATYPE>
class OrderedList : public Utility::NoCopy
{
public:
	ENUM EOrder
	{
		Ascending,
		Descending
	};

	struct Node
	{
		Node() 
			: m_Data(DATATYPE())
			, m_Next(NULLPTR)
		{
		}

		DATATYPE m_Data;
		Node *m_Next;
	};

	class Iterator
	{
	public:
		Iterator()
			: m_Node(NULLPTR)
		{
		}

		DATATYPE operator *()
		{
			return m_Node->m_Data;
		}

		bool operator==(const Iterator &a_Rhs) const
		{
			return m_Node == a_Rhs.m_Node;
		}

		bool operator!=(const Iterator &a_Rhs) const
		{
			return !(*this == a_Rhs);
		}

		Iterator& operator++()
		{
			m_Node = m_Node->m_Next;
			return *this;
		}

		Iterator operator+(int a_Step)
		{
			Node *node = m_Node;
			while (a_Step > 0)
			{
				node = node->m_Next;
				--a_Step;
			}
			return Iterator(node);
		}

	private:
		Iterator(Node *a_Node)
		{
			m_Node = a_Node;
		}

		Node *m_Node;

		friend class OrderedList;
	};

public:
#if defined(PROTO_CPP03)
	OrderedList(EOrder a_Order = Ascending)
#else
	OrderedList(EOrder a_Order = EOrder::Ascending)
#endif
	{
		m_Head = new Node();
		m_Tail = new Node();
		m_Head->m_Next = m_Tail;
		m_Order = a_Order;
		m_Size = 0;
	}

	virtual ~OrderedList()
	{
		Clear();
	}

	size_t Size() const
	{
		return m_Size;
	}

	bool IsEmpty() const
	{
		return NULLPTR == m_Head;
	}

	EOrder GetOrder() const
	{
		return m_Order;
	}

	Iterator Begin() const
	{
		return Iterator(m_Head->m_Next);
	}

	Iterator End() const
	{
		return Iterator(m_Tail);
	}

	void Insert(DATATYPE a_Data)
	{
		if (m_Head->m_Next == m_Tail)
		{
			Node *node = new Node();
			node->m_Data = a_Data;
			node->m_Next = m_Head->m_Next;
			m_Head->m_Next = node;
			++m_Size;
		}
		else
		{
			Node *previous = m_Head;
			switch (m_Order)
			{
#if defined(PROTO_CPP03)
				case Ascending:
#else
				case EOrder::Ascending:
#endif
				{
					while (previous->m_Next->m_Data < a_Data && previous->m_Next != m_Tail)
					{
						previous = previous->m_Next;
					}
					break;
				}
#if defined(PROTO_CPP03)
				case Descending:
#else
				case EOrder::Descending:
#endif
				{
					while (previous->m_Next->m_Data > a_Data && previous->m_Next != m_Tail)
					{
						previous = previous->m_Next;
					}
					break;
				}
			}
			Node *node = new Node();
			node->m_Data = a_Data;
			node->m_Next = previous->m_Next;
			previous->m_Next = node;
			++m_Size;
		}
	}

	Iterator Find(DATATYPE a_Data)
	{
		Node *node = m_Head->m_Next;
		bool found = false;
		switch (m_Order)
		{
#if defined(PROTO_CPP03)
		case Ascending:
#else
		case EOrder::Ascending:
#endif
			{
				while (node->m_Data < a_Data && node != m_Tail)
				{
					node = node->m_Next;
					found = true;
				}
				break;
			}
#if defined(PROTO_CPP03)
			case Descending:
#else
			case EOrder::Descending:
#endif
			{
				while (node->m_Data < a_Data && node != m_Tail)
				{
					node = node->m_Next;
					found = true;
				}
				break;
			}
		}

		return found ? Iterator(node) : Iterator(m_Tail);
	}

	void Erase(DATATYPE a_Data)
	{
		Node *node = m_Head->m_Next;
		Node *previous = m_Head;
		while (node->m_Data < a_Data && node->m_Next != m_Tail)
		{
			if (node->m_Data == a_Data)
			{
				break;
			}
			previous = node;
			node = node->m_Next;
		}
		//Platform::AssertMessage(node->m_Data == a_Data, "Requested item is not found in this ordered list!");
		assert(node->m_Data == a_Data);
		previous->m_Next = node->m_Next;
		delete node;
		m_Size--;
	}

	void Clear()
	{
		Node *currentNode = m_Head;
		Node *nextNode = m_Head->m_Next;
		do
		{
			delete currentNode;
			currentNode = nextNode;
			nextNode = nextNode->m_Next;
		} while (nextNode != NULLPTR);
		delete m_Tail;
		m_Size = 0;
	}

private:
	EOrder m_Order;
	size_t m_Size;
	Node *m_Head;
	Node *m_Tail;
};

END_NAMESPACE(Utility)
