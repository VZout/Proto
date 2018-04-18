#include "Proto.h"

#include "Utility/Datastructures/BinarySearchTree.h"
#include "Utility/Datastructures/OrderedList.h"
#include "Utility/Datastructures/RedBlackTree.h"
// #include "Utility/Algorithms/TreeTraversals.h"
#include "Utility/Datastructures/SinglyLinkedList.h"
// #include "Utility/Datastructures/DoublyLinkedList.h"

USING_NAMESPACE(Utility)

int main(int a_ArgC, const char * a_ArgV[])
{
	UNUSED(a_ArgC);
	UNUSED(a_ArgV);

	SinglyLinkedList<int> sl;
	sl.InsertFront(1);
	SinglyLinkedList<int>::Iterator pos = sl.Begin();
	sl.Insert(pos, 2);

	BinarySearchTree<int> bt;
	bt.Insert(30);
	bt.Insert(10);
	bt.Insert(40);
	bt.Insert(20);
	bt.Insert(50);

	OrderedList<int> ol;
	ol.Insert(1);
	ol.Insert(9);
	ol.Insert(2);
	ol.Insert(8);
	ol.Insert(3);
	ol.Insert(7);
	ol.Insert(4);
	ol.Insert(6);
	ol.Insert(5);
	//ol.Erase(8);
	//ol.Erase(10);	// asserts correctly
	//ol.Erase(6);
	//ol.Erase(4);
	//ol.Erase(7);
	ol.Clear();

	RedBlackTree<int> rbt;
	rbt.Insert(1);
	rbt.Insert(9);
	rbt.Insert(2);
	rbt.Insert(8);
	rbt.Insert(3);
	rbt.Insert(7);
	rbt.Insert(4);
	rbt.Insert(6);
	rbt.Insert(5);
	rbt.Delete(8);
	rbt.Delete(6);
	rbt.Delete(4);
	rbt.Delete(7);
	rbt.Validate();

	return 0;
}
