#pragma once

#include "Utility/NoCopy.h"
#include "SinglyLinkedList.h"

BEGIN_NAMESPACE(Utility)

template<typename DATATYPE>
class Tree : public NoCopy
{
public:
	class Position;
	typedef SinglyLinkedList<Position> PositionList;

	class Position
	{
	public:
		DATATYPE& operator*();
		Position Parent();
		PositionList Children();
		bool IsRoot() const;
		bool IsExternal() const;
		bool IsInternal() const
		{
			return !IsExternal();
		}
	};

public:
	Tree();
	~Tree();

	size_t Size() const;
	bool Empty() const;
	Position Root() const;
	PositionList Nodes() const;
};

END_NAMESPACE(Utility)
