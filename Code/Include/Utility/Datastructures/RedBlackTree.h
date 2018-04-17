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
		Node *z = Find(a_Data);

		Node *y = z;
		Node *x = nullptr;
		EColor originalColor = y->m_Color;
		if (m_Nill == z->m_Left)
		{
			x = z->m_Right;
			Transplant(z, z->m_Right);
		}
		else if (m_Nill == z->m_Right)
		{
			x = z->m_Left;
			Transplant(z, z->m_Left);
		}
		else
		{
			y = TreeMinimum(z->m_Right);
			originalColor = y->m_Color;
			x = y->m_Right;
			if (y->m_Parent == z)
			{
				x->m_Parent = y;
			}
			else
			{
				Transplant(y, y->m_Right);
				y->m_Right = z->m_Right;
				y->m_Right->m_Parent = y;
			}
			Transplant(z, y);
			y->m_Left = z->m_Left;
			y->m_Left->m_Parent = y;
			y->m_Color = z->m_Color;
		}

		// delete node; // ??
		if (EColor::Black == originalColor)
		{
			DeleteFixup(x);
		}
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
				else 
				{
					if (z == z->m_Parent->m_Right)
					{
						z = z->m_Parent;
						LeftRotate(z);
					}
					z->m_Parent->m_Color = EColor::Black;
					z->m_Parent->m_Parent->m_Color = EColor::Red;
					RightRotate(z->m_Parent->m_Parent);
				}
			}
			else
			{
				Node *y = z->m_Parent->m_Parent->m_Left;
				if (EColor::Red == y->m_Color)
				{
					z->m_Parent->m_Color = EColor::Black;
					y->m_Color = EColor::Black;
					z->m_Parent->m_Parent->m_Color = EColor::Red;
					z = z->m_Parent->m_Parent;
				}
				else
				{
					if (z == z->m_Parent->m_Left)
					{
						z = z->m_Parent;
						RightRotate(z);
					}
					z->m_Parent->m_Color = EColor::Black;
					z->m_Parent->m_Parent->m_Color = EColor::Red;
					LeftRotate(z->m_Parent->m_Parent);
				}
			}
		}

		m_Root->m_Color = EColor::Black;
	}

	void DeleteFixup(Node *x)
	{
		Platform::AssertMessage(nullptr != x, "Invalid node encountered while fixing up delete!");
		Node *w = m_Nill;
		while (x != m_Root && EColor::Black == x->m_Color)
		{
			if (x == x->m_Parent->m_Left)
			{
				w = x->m_Parent->m_Right;
				if (EColor::Red == w->m_Color)
				{
					w->m_Color = EColor::Black;
					x->m_Parent->m_Color = EColor::Red;
					LeftRotate(x->m_Parent);
					w = x->m_Parent->m_Right;
				}

				if (EColor::Black == w->m_Left->m_Color && EColor::Black == w->m_Right->m_Color)
				{
					w->m_Color = EColor::Red;
					x = x->m_Parent;
				}
				else
				{
					if (EColor::Black == w->m_Right->m_Color)
					{
						w->m_Left->m_Color = EColor::Black;
						w->m_Color = EColor::Red;
						RightRotate(w);
						w = x->m_Parent->m_Right;
					}
					w->m_Color = x->m_Parent->m_Color;
					x->m_Parent->m_Color = EColor::Black;
					w->m_Right->m_Color = EColor::Black;
					LeftRotate(x->m_Parent);
					x = m_Root;
				}
			}
			else
			{
				w = x->m_Parent->m_Left;
				if (EColor::Red == w->m_Color)
				{
					w->m_Color = EColor::Black;
					x->m_Parent->m_Color = EColor::Red;
					RightRotate(x->m_Parent);
					w = x->m_Parent->m_Left;
				}

				if (EColor::Black == w->m_Right->m_Color && EColor::Black == w->m_Left->m_Color)
				{
					w->m_Color = EColor::Red;
					x = x->m_Parent;
				}
				else
				{
					if (EColor::Black == w->m_Left->m_Color)
					{
						w->m_Right->m_Color = EColor::Black;
						w->m_Color = EColor::Red;
						LeftRotate(w);
						w = x->m_Parent->m_Left;
					}
					w->m_Color = x->m_Parent->m_Color;
					x->m_Parent->m_Color = EColor::Black;
					w->m_Left->m_Color = EColor::Black;
					RightRotate(x->m_Parent);
					x = m_Root;
				}
			}
		}
		x->m_Color = EColor::Black;
	}

	void LeftRotate(Node *a_Node)
	{
		Platform::AssertMessage(nullptr != a_Node, "Invalid node encountered attempting to rotate left!");
		Node *node = a_Node->m_Right;
		a_Node->m_Right = node->m_Left;
		if (m_Nill != node->m_Left)
		{
			node->m_Left->m_Parent = a_Node;
		}
		node->m_Parent = a_Node->m_Parent;
		node->m_Left = a_Node;
		if (m_Nill == a_Node->m_Parent)
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
		a_Node->m_Parent = node;
	}

	void RightRotate(Node *a_Node)
	{
		Platform::AssertMessage(nullptr != a_Node, "Invalid node encountered attempting to rotate right!");
		Node *node = a_Node->m_Left;
		a_Node->m_Left = node->m_Right;
		if (m_Nill != node->m_Right)
		{
			node->m_Right->m_Parent = a_Node;
		}
		node->m_Parent = a_Node->m_Parent;
		if (m_Nill == a_Node->m_Parent)
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

	void Transplant(Node *u, Node *v)
	{
		if (m_Nill == u->m_Parent)
		{
			m_Root = v;
		}
		else if (u == u->m_Parent->m_Left)
		{
			u->m_Parent->m_Left = v;
		}
		else
		{
			u->m_Parent->m_Right = v;
		}
		v->m_Parent = u->m_Parent;
	}

	Node* Find(DATATYPE a_Data)
	{
		Node *node = m_Root;
		while (m_Nill != node)
		{
			if (node->m_Data > a_Data)
			{
				node = node->m_Left;
			}
			else if (node->m_Data < a_Data)
			{
				node = node->m_Right;
			}
			else
			{
				return node;
			}
		}
		return nullptr;
	}

	Node* TreeMinimum(Node *a_Root)
	{
		Platform::AssertMessage(nullptr != a_Root, "Attempt to find minimum value for invalid tree!");
		Node *node = a_Root;
		while (m_Nill != node->m_Left)
		{
			node = node->m_Left;
		}
		return node;
	}

	Node* TreeMaximum(Node *a_Root)
	{
		Platform::AssertMessage(nullptr != a_Root, "Attempt to find maximum value for invalid tree!");
		Node *node = a_Root;
		while (m_Nill != node->m_Right)
		{
			node = node->m_Right;
		}
		return node;
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
		{
			return 1;
		}

		const int leftBlackHeight = ValidateBlackHeightProperty(a_Node->m_Left);
		if (leftBlackHeight == 0)
		{
			return leftBlackHeight;
		}

		const int rightBlackHeight = ValidateBlackHeightProperty(a_Node->m_Right);
		if (rightBlackHeight == 0)
		{
			return rightBlackHeight;
		}

		if (leftBlackHeight != rightBlackHeight)
		{
			return 0;
		}
		else
		{
			return leftBlackHeight + (EColor::Black == a_Node->m_Color ? 1 : 0);
		}
	}
#endif
	Node *m_Root = nullptr;
	Node *m_Nill = nullptr;
};

END_NAMESPACE(Utility)
