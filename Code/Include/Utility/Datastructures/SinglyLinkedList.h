#pragma once

#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Utility)

template<typename DATATYPE>
class SinglyLinkedList : public Utility::NoCopy
{
public:
	struct Node
	{
		Node() { }

		DATATYPE m_Data = DATATYPE();
		Node *m_Next = NULLPTR;
	};

	class Iterator
	{
	public:
		Iterator()
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

		Node *m_Node = NULLPTR;

		friend class SinglyLinkedList;
	}; 

public:
	SinglyLinkedList()
	{
		m_Head = new Node();
		m_Tail = new Node();
		m_Head->m_Next = m_Tail;
	}
	
	virtual ~SinglyLinkedList()
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

	Iterator Begin() const
	{
		return Iterator(m_Head->m_Next);
	}

	Iterator End() const
	{
		return Iterator(m_Tail);
	}

	void InsertFront(DATATYPE a_Data)
	{
		Node *node = new Node();
		node->m_Data = a_Data;
		node->m_Next = m_Head->m_Next;
		m_Head->m_Next = node;
		++m_Size;
	}

	// insert before iterator position
	void Insert(const Iterator &a_Position, DATATYPE a_Data)
	{
		if (a_Position.m_Node == m_Head)
		{
			InsertFront(a_Data);
		}
		else
		{
			Node *previous = m_Head;
			while (previous->m_Next != a_Position.m_Node)
			{
				previous = previous->m_Next;
			}
			Node *node = new Node();
			node->m_Data = a_Data;
			node->m_Next = previous->m_Next;
			previous->m_Next = node;
			++m_Size;
		}
	}

	void EraseFront()
	{
		Node *node = m_Head;
		m_Head = node->m_Next;
		delete node;
		--m_Size;
	}

	void Erase(const Iterator &a_Position)
	{
		Node *previous = m_Head;
		while (previous->m_Next != a_Position.m_Node)
		{
			previous = previous->m_Next;
		}
		previous->m_Next = a_Position.m_Node->m_Next;
		delete a_Position.m_Node;
		--m_Size;
	}

	void Clear()
	{
		while (!IsEmpty())
		{
			EraseFront();
		}
	}

private:
	size_t m_Size = 0;
	Node *m_Head = NULLPTR;
	Node *m_Tail = NULLPTR;
};

END_NAMESPACE(Utility)
