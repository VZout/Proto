#pragma once

#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Utility)

template<typename DATATYPE>
class SinglyLinkedList : public Utility::NoCopy
{
public:
	struct Node
	{
		Node(DATATYPE a_Data)
			: m_Data(a_Data)
		{
		}

		DATATYPE m_Data;
		Node *m_Next = nullptr;
	};

public:
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

	private:
		Iterator(Node *a_Node)
		{
			m_Node = a_Node;
		}

		Node *m_Node = nullptr;

		friend class SinglyLinkedList;
	}; 

public:
	SinglyLinkedList()
	{
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
		return nullptr == m_Head;
	}

	Iterator Begin() const
	{
		return Iterator(m_Head);
	}

	void InsertFront(DATATYPE a_Data)
	{
		Node *node = new Node(a_Data);
		node->m_Next = m_Head;
		m_Head = node;
		++m_Size;
	}

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
			Node *node = new Node(a_Data);
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
	Node * m_Head = nullptr;
};

END_NAMESPACE(Utility)
