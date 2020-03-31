#include "CppUnitTest.h"
#include "RBTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
		
	public:
		
		TEST_METHOD(insert_test)
		{
			RBtree Tree;
			Tree.insert(1, 6);
			bool now = Tree.find(2);
			Tree.insert(2, 10);
			bool later = Tree.find(2);
			Assert::AreEqual(now, !later);



		}
		TEST_METHOD(remove_test)
		{
			RBtree Tree;
			Tree.insert(1, 6);
			bool prev = Tree.find(1);
			Tree.remove(1);
			bool after = Tree.find(1);
			Assert::AreEqual(prev, !after);
			
		}
		TEST_METHOD(clear_test)
		{
			RBtree Tree;
			Tree.insert(1, 9);
			Tree.insert(2, 11);
			Tree.clear();
			Assert::AreEqual(!Tree.find(1), !Tree.find(2));
		}
		TEST_METHOD(find_test)
		{
			RBtree Tree;
			bool now = Tree.find(1);
			Tree.insert(1, 20);
			bool after = Tree.find(1);
			Assert::AreEqual(!now, after);
		}
		TEST_METHOD(print_test)
		{
			RBtree Tree;
			bool now = Tree.print();
			Tree.insert(1, 15);
			Tree.insert(2, 3);
			bool after = Tree.print();
			Assert::AreEqual(!now, after);
		}
		TEST_METHOD(get_keys_test)
		{
			RBtree Tree;
			bool now = Tree.get_keys();
			Tree.insert(1, 5);
			Tree.insert(2, 6);
			bool after = Tree.get_keys();
			Assert::AreEqual(!now, after);
		}
		TEST_METHOD(get_value_test)
		{
			RBtree Tree;
			bool now = Tree.get_values();
			Tree.insert(1, 5);
			Tree.insert(2, 6);
			bool after = Tree.get_values();
			Assert::AreEqual(!now, after);
		}
	};
}
