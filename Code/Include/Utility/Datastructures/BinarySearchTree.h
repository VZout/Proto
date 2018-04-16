#pragma once

#include "Proto.h"

// http://www.doc.ic.ac.uk/~ar3/lectures/ProgrammingII/LargePrintOut/Lecture7PrintOut.pdf

BEGIN_NAMESPACE(Utility)

template<typename DATATYPE>
class BinarySearchTree
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
		if (nullptr == m_Root)
		{
			m_Root = new Node();
			m_Root->m_Data = a_Data;
		}
		else
		{
			Insert(m_Root, a_Data);
		}
	}

private:
	void Insert(Node *&a_Node, DATATYPE a_Data)
	{
		if (nullptr == a_Node)
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

	Node *m_Root = nullptr;
};
END_NAMESPACE(Utility)
