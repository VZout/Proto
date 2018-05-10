#pragma once

#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Utility)

template<typename DATATYPE>
class DoublyLinkedList : public Utility::NoCopy
{
public:
	struct Node
	{
		Node() { }

		DATATYPE m_Data;
		Node *m_Next = NULLPTR;
		Node *m_Previous = NULLPTR;
	};

	class Iterator
	{
	public:
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

		Iterator& operator--()
		{
			m_Node = m_Node->m_Previous;
			return *this;
		}

	private:
		Iterator(Node *a_Node)
		{
			m_Node = a_Node;
		}

		Node *m_Node = NULLPTR;
	};

public:
	DoublyLinkedList() 
	{
		m_Head = new Node();
		m_Tail = new Node();
		m_Head->m_Next = m_Tail;
		m_Tail->m_Previous = m_Head;
	}

	virtual ~DoublyLinkedList() 
	{
		while (!IsEmpty())
		{
			RemoveFront();
		}
		delete m_Head;
		delete m_Tail;
	}

	size_t Size() const
	{
		return m_Size;
	}

	bool IsEmpty() const
	{
		Platform::AssertMessage(NULLPTR != m_Head, "Attempt to query an invalid list!");
		Platform::AssertMessage(NULLPTR != m_Tail, "Attempt to query an invalid list!");
		return (m_Head->m_Next == m_Tail);
	}

	Iterator Begin() const
	{
		return Iterator(m_Head->m_Next);
	}

	Iterator End() const
	{
		return Iterator(m_Tail->m_Previous);
	}

	void InsertFront(DATATYPE a_Data)
	{
		Insert(Begin(), a_Data);
	}

	void InsertBack(DATATYPE a_Data)
	{
		Insert(End(), a_Data);
	}

	void Insert(const Iterator &a_Position, DATATYPE a_Data)
	{
		Node *position = a_Position.m_Node;
		Node *previous = position->m_Previous;
		Node *node = new Node(a_Data);
		node->m_Next = position;
		node->m_Previous = previous;
		position->m_Previous = node;
		previous->m_Next = node;
	}

	void EraseFront()
	{
		Erase(Front());
	}

	void EraseBack()
	{
		Erase(--End());
	}

	void Erase(const Iterator &a_Position)
	{
		Node *node = a_Position.m_Node;
		Node *next = node->m_Next;
		Node *previous = node->m_Previous;
		previous->m_Next = next;
		next->m_Previous = previous;
		delete node;
		m_Size--;
	}

private:
	size_t m_Size = 0;
	Node *m_Head = NULLPTR;
	Node *m_Tail = NULLPTR;
};

END_NAMESPACE(Utility)
