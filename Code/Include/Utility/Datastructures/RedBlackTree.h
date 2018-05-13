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

		m_Root = m_Nill;
	}

	void Insert(DATATYPE a_Data)
	{
		Node *parent = m_Nill;
		Node *node = m_Root;
		while (m_Nill != node)
		{
			parent = node;
			node = (a_Data < node->m_Data) ? node->m_Left : node->m_Right;
		}

		node = new Node();
		node->m_Data = a_Data;
		node->m_Parent = parent;
		if (m_Nill == parent)
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
		node->m_Left = m_Nill;
		node->m_Right = m_Nill;
		node->m_Color = EColor::Red;

		InsertFixup(node);
	}

	void Delete(DATATYPE a_Data)
	{
		Node *node = Find(a_Data);
		Node *substituteNode = m_Nill;
		Node *oldNode = node;
		EColor originalColor = oldNode->m_Color;
		if (node->m_Left == m_Nill)
		{
			substituteNode = node->m_Right;
			Transplant(node, node->m_Right);
		}
		else if (node->m_Right == m_Nill)
		{
			substituteNode = node->m_Left;
			Transplant(node, node->m_Left);
		}
		else 
		{
			oldNode = TreeMinimum(node->m_Right);
			originalColor = oldNode->m_Color;
			substituteNode = oldNode->m_Right;
			if (oldNode->m_Parent == node)
			{
				substituteNode->m_Parent = oldNode;
			}
			else
			{
				Transplant(oldNode, oldNode->m_Right);
				oldNode->m_Right = node->m_Right;
				oldNode->m_Right->m_Parent = oldNode;
			}
			Transplant(node, oldNode);
			oldNode->m_Left = node->m_Left;
			oldNode->m_Left->m_Parent = oldNode;
			oldNode->m_Color = node->m_Color;
		}

		delete node;
		if (originalColor == EColor::Black) 
		{
			DeleteFixup(substituteNode);
		}
	}

#if not defined(NDEBUG)
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
		Node *m_Left = NULLPTR;
		Node *m_Right = NULLPTR;
		Node *m_Parent = NULLPTR;
		EColor m_Color = EColor::Invalid;
	};

private:
	void InsertFixup(Node *z)
	{
		Platform::AssertMessage(NULLPTR != z, "Invalid node encountered while fixing up insert!");
		while (m_Nill != z->m_Parent && EColor::Red == z->m_Parent->m_Color)
		{
			if (z->m_Parent == z->m_Parent->m_Parent->m_Left)
			{
				Node *y = z->m_Parent->m_Parent->m_Right;
				if (m_Nill != y && EColor::Red == y->m_Color)
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
				if (m_Nill != y && EColor::Red == y->m_Color)
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

	void DeleteFixup(Node *a_Node)
	{
		Node* sibling = NULLPTR;
		while (a_Node != m_Root && a_Node->m_Color == EColor::Black)
		{
			if (a_Node == a_Node->m_Parent->m_Left)
			{
				sibling = a_Node->m_Parent->m_Right;
				if (EColor::Red == sibling->m_Color)
				{
					sibling->m_Color = EColor::Black;
					a_Node->m_Parent->m_Color = EColor::Red;
					LeftRotate(a_Node->m_Parent);
					sibling = a_Node->m_Parent->m_Right;
				}
				if (EColor::Black == sibling->m_Left->m_Color && EColor::Black == sibling->m_Right->m_Color)
				{
					sibling->m_Color = EColor::Red;
					a_Node = a_Node->m_Parent;
				}
				else
				{
					if (EColor::Black == sibling->m_Right->m_Color)
					{
						sibling->m_Left->m_Color = EColor::Black;
						sibling->m_Color = EColor::Red;
						RightRotate(sibling);
						sibling = a_Node->m_Parent->m_Right;
					}
					sibling->m_Color = a_Node->m_Parent->m_Color;
					a_Node->m_Parent->m_Color = EColor::Black;
					sibling->m_Right->m_Color = EColor::Black;
					LeftRotate(a_Node->m_Parent);
					a_Node = m_Root;
				}
			}
			else {
				sibling = a_Node->m_Parent->m_Left;
				if (EColor::Red == sibling->m_Color)
				{
					sibling->m_Color = EColor::Black;
					a_Node->m_Parent->m_Color = EColor::Red;
					RightRotate(a_Node->m_Parent);
					sibling = a_Node->m_Parent->m_Left;
				}
				if (EColor::Black == sibling->m_Right->m_Color && EColor::Black == sibling->m_Left->m_Color)
				{
					sibling->m_Color = EColor::Red;
					a_Node = a_Node->m_Parent;
				}
				else
				{
					if (EColor::Black == sibling->m_Left->m_Color)
					{
						sibling->m_Right->m_Color = EColor::Black;
						sibling->m_Color = EColor::Red;
						LeftRotate(sibling);
						sibling = a_Node->m_Parent->m_Left;
					}
					sibling->m_Color = a_Node->m_Parent->m_Color;
					a_Node->m_Parent->m_Color = EColor::Black;
					sibling->m_Left->m_Color = EColor::Black;
					RightRotate(a_Node->m_Parent);
					a_Node = m_Root;
				}
			}
		}
		a_Node->m_Color = EColor::Black;
	}

	void LeftRotate(Node *a_Node)
	{
		Platform::AssertMessage(NULLPTR != a_Node, "Invalid node encountered attempting to rotate left!");
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
		Platform::AssertMessage(NULLPTR != a_Node, "Invalid node encountered attempting to rotate right!");
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
		return NULLPTR;
	}

	Node* TreeMinimum(Node *a_Root)
	{
		Platform::AssertMessage(NULLPTR != a_Root, "Attempt to find minimum value for invalid tree!");
		Node *node = a_Root;
		while (m_Nill != node->m_Left)
		{
			node = node->m_Left;
		}
		return node;
	}

	Node* TreeMaximum(Node *a_Root)
	{
		Platform::AssertMessage(NULLPTR != a_Root, "Attempt to find maximum value for invalid tree!");
		Node *node = a_Root;
		while (m_Nill != node->m_Right)
		{
			node = node->m_Right;
		}
		return node;
	}

#if !defined(NDEBUG)
	bool ValidateRedProperty(Node *a_Node)
	{
		if (m_Nill == a_Node)
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
			(NULLPTR != a_Node->m_Left && EColor::Red == a_Node->m_Left->m_Color ||
			NULLPTR != a_Node->m_Right && EColor::Red == a_Node->m_Right->m_Color))
		{
			return false;
		}

		return true;
	}

	int ValidateBlackHeightProperty(Node *a_Node)
	{
		if (m_Nill == a_Node)
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
	Node *m_Root = NULLPTR;
	Node *m_Nill = NULLPTR;
};

END_NAMESPACE(Utility)
