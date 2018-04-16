#pragma once

//https://www.cs.usfca.edu/~galles/visualization/RedBlack.html
//http://cs.armstrong.edu/liang/animation/web/RBTree.html

#include "Platform/Debug/AssertMessage.h"

BEGIN_NAMESPACE(Utility)

template<typename DATATYPE>
class RedBlackTree
{
public:
	RedBlackTree()
	{
		m_Nill = new Node();
		m_Nill->m_Left = m_Nill;
		m_Nill->m_Right = m_Nill;
		m_Nill->m_Parent = m_Nill;
		m_Nill->m_Color = EColor::Black;
	}

	void Insert(DATATYPE a_Data)
	{
		Node *parent = nullptr;
		Node *node = m_Root;
		while (nullptr != node)
		{
			parent = node;
			node = (a_Data < node->m_Data) ? node->m_Left : node->m_Right;
		}
		Platform::AssertMessage(nullptr == node, "Unexpected valid node encountered!");
		node = new Node();
		node->m_Data = a_Data;
		node->m_Parent = parent;
		if (nullptr == parent)
		{
			m_Root = node;
			m_Root->m_Left = m_Nill;
			m_Root->m_Right = m_Nill;
			m_Root->m_Parent = m_Nill;
		}
		else if (node->m_Data < parent->m_Data)
		{
			parent->m_Left = node;
		}
		else
		{
			parent->m_Right = node;
		}
		node->m_Left = nullptr;
		node->m_Right = nullptr;
		node->m_Color = EColor::Red;

		InsertFixup(node);
	}

	void Erase(DATATYPE a_Data)
	{
	}

#if defined(_DEBUG)
	void Validate()
	{
		Platform::AssertMessage(ValidateRedProperty(m_Root), "Red property violated!");
		Platform::AssertMessage(0 != ValidateBlackHeightProperty(m_Root), "Black height property violated!");
	}
#endif

private:
	enum class EColor
	{
		Red,
		Black,
		Invalid
	};

	struct Node
	{
		DATATYPE m_Data;
		Node *m_Left = nullptr;
		Node *m_Right = nullptr;
		Node *m_Parent = nullptr;
		EColor m_Color = EColor::Invalid;
	};

private:
	void InsertFixup(Node *z)
	{
		Platform::AssertMessage(nullptr != z, "Invalid node encountered while fixing up insert!");
		while (m_Nill != z->m_Parent && EColor::Red == z->m_Parent->m_Color)
		{
			if (z->m_Parent == z->m_Parent->m_Parent->m_Left)
			{
				Node *y = z->m_Parent->m_Parent->m_Right;
				if (EColor::Red == y->m_Color)
				{
					z->m_Parent->m_Color = EColor::Black;
					y->m_Color = EColor::Black;
					z->m_Parent->m_Parent->m_Color = EColor::Red;
					z = z->m_Parent->m_Parent;
				}
				else if (z == z->m_Parent->m_Right)
				{
					z = z->m_Parent;
					LeftRotate(z);
					z->m_Parent->m_Color = EColor::Black;
					z->m_Parent->m_Parent->m_Color = EColor::Red;
					RightRotate(z->m_Parent->m_Parent);
				}
			}
			else
			{
				// INCORRECT
				Node *y = z->m_Parent->m_Parent->m_Left;
				if (EColor::Red == y->m_Color)
				{
					z->m_Parent->m_Color = EColor::Black;
					y->m_Color = EColor::Black;
					z->m_Parent->m_Parent->m_Color = EColor::Red;
					z = z->m_Parent->m_Parent;
				}
				else if (z == z->m_Parent->m_Left)
				{
					z = z->m_Parent;
					LeftRotate(z);
					z->m_Parent->m_Color = EColor::Black;
					z->m_Parent->m_Parent->m_Color = EColor::Red;
					RightRotate(z->m_Parent->m_Parent);
				}
			}
		}
		m_Root->m_Color = EColor::Black;
	}

	void DeleteFixup(Node *a_Node)
	{
		Platform::AssertMessage(nullptr != a_Node, "Invalid node encountered while fixing up delete!");
	}

	void LeftRotate(Node *a_Node)
	{
		Platform::AssertMessage(nullptr != a_Node, "Invalid node encountered attempting to rotate left!");
		Node *node = a_Node->m_Right;
		a_Node->m_Right = node->m_Left;
		if (nullptr != node->m_Left)
		{
			node->m_Left->m_Parent = a_Node;
		}
		node->m_Parent = a_Node->m_Parent;
		if (nullptr == a_Node->m_Parent)
		{
			m_Root = node;
		}
		else if (a_Node == a_Node->m_Parent->m_Left)
		{
			a_Node->m_Parent->m_Left = node;
		}
		else
		{
			a_Node->m_Parent->m_Right = node;
		}
		node->m_Left = a_Node;
		a_Node->m_Parent = node;
	}

	void RightRotate(Node *a_Node)
	{
		Platform::AssertMessage(nullptr != a_Node, "Invalid node encountered attempting to rotate right!");
		Node *node = a_Node->m_Left;
		a_Node->m_Left = node->m_Right;
		if (nullptr != node->m_Right)
		{
			node->m_Right->m_Parent = a_Node;
		}
		node->m_Parent = a_Node->m_Parent;
		if (nullptr == a_Node->m_Parent)
		{
			m_Root = node;
		}
		else if (a_Node == a_Node->m_Parent->m_Right)
		{
			a_Node->m_Parent->m_Right = node;
		}
		else
		{
			a_Node->m_Parent->m_Left = node;
		}
		node->m_Right = a_Node;
		a_Node->m_Parent = node;
	}

	void Transplant()
	{
	}

#if defined(_DEBUG)
	bool ValidateRedProperty(Node *a_Node)
	{
		if (nullptr == a_Node)
		{
			return true;
		}

		if (!ValidateRedProperty(a_Node->m_Left))
		{
			return false;
		}

		if (!ValidateRedProperty(a_Node->m_Right))
		{
			return false;
		}

		if (EColor::Red == a_Node->m_Color &&
			(nullptr != a_Node->m_Left && EColor::Red == a_Node->m_Left->m_Color ||
			nullptr != a_Node->m_Right && EColor::Red == a_Node->m_Right->m_Color))
		{
			return false;
		}

		return true;
	}

	int ValidateBlackHeightProperty(Node *a_Node)
	{
		if (nullptr == a_Node)
			return 1;

		int leftBlackHeight = ValidateBlackHeightProperty(a_Node->m_Left);
		if (leftBlackHeight == 0)
			return leftBlackHeight;

		int rightBlackHeight = ValidateBlackHeightProperty(a_Node->m_Right);
		if (rightBlackHeight == 0)
			return rightBlackHeight;

		if (leftBlackHeight != rightBlackHeight)
			return 0;
		else
			return leftBlackHeight + (EColor::Black == a_Node->m_Color ? 1 : 0);
	}
#endif
	Node *m_Root = nullptr;
	Node *m_Nill = nullptr;
};

END_NAMESPACE(Utility)
