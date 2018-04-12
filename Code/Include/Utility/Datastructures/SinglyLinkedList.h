#pragma once

#include "Utility/NoCopy.h"

BEGIN_NAMESPACE(Utility)

template<typename DATATYPE>
class SinglyLinkedList : public Utility::NoCopy
{
public:
	struct Node
	{
		DATATYPE m_Data;
		Node *m_Next = nullptr;
	};

public:
	SinglyLinkedList() { }
	virtual ~SinglyLinkedList() { }

	Node* First() { return nullptr; }
	Node* Last() { return nullptr; }
	Node* Previous(Node *a_Node) { UNUSED(a_Node);  return nullptr; }
	Node* Next(Node *a_Node) { UNUSED(a_Node);  return nullptr; }
	
	DATATYPE Replace(Node *a_Node, DATATYPE a_Data) { UNUSED(a_Node); UNUSED(a_Data); return DATATYPE(); }
	Node* InsertFirst(DATATYPE a_Data) { UNUSED(a_Data); return nullptr; }
	Node* InsertLast(DATATYPE a_Data) { UNUSED(a_Data); return nullptr; }
	Node* InsertBefore(Node *a_Node, DATATYPE a_Data) { UNUSED(a_Node); UNUSED(a_Data); return nullptr; }
	Node* InsertAfter(Node *a_Node, DATATYPE a_Data) { UNUSED(a_Node); UNUSED(a_Data); return nullptr; }
	DATATYPE Remove(Node *a_Node) { UNUSED(a_Node); return DATATYPE(); }

private:
	Node * m_Head = nullptr;
};

END_NAMESPACE(Utility)
