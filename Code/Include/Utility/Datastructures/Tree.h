#pragma once

#include "Proto.h"

BEGIN_NAMESPACE(Utility)

template<typename DATATYPE>
class Tree
{
public:
	struct Node
	{
		DATATYPE m_Data;
	};

public:
	void Root() {}
	void Parent(Node *a_Node) { UNUSED(a_Node); }
	void Children(Node *a_Node) { UNUSED(a_Node); }
	bool IsInternal(Node *a_Node) const { UNUSED(a_Node); }
	bool IsExternal(Node *a_Node) const { UNUSED(a_Node); return false; }
	bool IsRoot(Node *a_Node) const { UNUSED(a_Node); return false; }
	size_t Size() const { return 0; }
	bool IsEmpty() const { return false; }
	void Elements() {}
	void Positions() {}
	DATATYPE Replace(Node *a_Node, DATATYPE a_Data) { UNUSED(a_Node); UNUSED(a_Data); return DATATYPE(); }
};

END_NAMESPACE(Utility)
