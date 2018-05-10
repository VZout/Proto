#pragma once

#include "Platform/Debug/AssertMessage.h"
#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Utility)

template<typename DATATYPE>
class BinarySearchTree : Utility::NoCopy
{
public:
	struct Node
	{
		DATATYPE m_Data;
		Node *m_Left;
		Node *m_Right;
	};

public:
	BinarySearchTree() {}
	~BinarySearchTree()
	{
	}

	size_t IsEmpty() const
	{
		return m_Size;
	}

	DATATYPE GetRoot() const
	{
		return Position(m_Root);
	}

	void Insert(DATATYPE a_Data)
	{
		if (NULLPTR == m_Root)
		{
			m_Root = new Node();
			m_Root->m_Data = a_Data;
		}
		else
		{
			Insert(m_Root, a_Data);
		}
	}

	void Remove(DATATYPE a_Data)
	{
		Platform::AssertMessage("Not implemented!");
	}

private:
	void Insert(Node *&a_Node, DATATYPE a_Data)
	{
		if (NULLPTR == a_Node)
		{
			a_Node = new Node();
			a_Node->m_Data = a_Data;
		}
		else
		{
			if (a_Data <= a_Node->m_Data)
			{
				Insert(a_Node->m_Left, a_Data);
			}
			else
			{
				Insert(a_Node->m_Right, a_Data);
			}
		}
	}

	Node *m_Root = NULLPTR;
};
END_NAMESPACE(Utility)
