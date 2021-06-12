#include "CppUnitTest.h"
#include "../Game/code/QuadtreeNode.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

TEST_CLASS(Tests)
{
public:

	TEST_METHOD(QuadTreeTest1)
	{
		Rect boundary = Rect(400, 300, 400, 300);
		QuadtreeNode<Rect> qtree = QuadtreeNode<Rect>(boundary, 8);
		std::array<Rect, 20> objects;
		for (int i = 0; i < 20; ++i)
		{
			objects[i] = Rect(i * 30, i * 30 + 10, 5, 5);
			qtree.insert(objects[i]);
		}
		Rect rectangle = Rect(600, 450, 200, 150);
		std::vector<Rect*> found;
		qtree.query(rectangle, found);
		int n = found.size();
		Assert::AreEqual(n, 6);
	}

	TEST_METHOD(QuadTreeTest2)
	{
		Rect boundary = Rect(400, 300, 400, 300);
		QuadtreeNode<Rect> qtree = QuadtreeNode<Rect>(boundary, 8);
		std::array<Rect, 20> objects;
		for (int i = 0; i < 20; ++i)
		{
			objects[i] = Rect(i * 30, i * 30 + 10, 5, 5);
			qtree.insert(objects[i]);
		}
		Rect rectangle = Rect(600, 450, 2, 2);
		std::vector<Rect*> found;
		qtree.query(rectangle, found);
		int n = found.size();
		Assert::AreEqual(n, 0);
	}
};
