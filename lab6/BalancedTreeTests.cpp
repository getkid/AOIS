#include "pch.h"
#include "CppUnitTest.h"
#include "../aois6(2)/BalancedTree.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace BalancedTreeTests
{
    TEST_CLASS(BalancedTreeTests)
    {
    public:
        TEST_METHOD(TestInsertAndSearch)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            auto result = tree.search("key1");
            Assert::AreEqual(std::string("value1"), result.front());
        }

        TEST_METHOD(TestInsertAndRemove)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            tree.remove("key1");
            auto result = tree.search("key1");
            Assert::AreEqual(std::string("Not Found!"), result.front());
        }

        TEST_METHOD(TestInsertAndSearchMultipleValues)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            tree.insert("key1", "value2");
            tree.insert("key1", "value3");
            auto result = tree.search("key1");
            std::vector<std::string> expected = { "value1", "value2", "value3" };
            Assert::IsTrue(std::equal(result.begin(), result.end(), expected.begin()));
        }

        TEST_METHOD(TestRemoveNonexistentKey)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            tree.remove("nonexistent_key");
            auto result = tree.search("key1");
            Assert::AreEqual(std::string("value1"), result.front());
        }
        TEST_METHOD(TestInsertAndSearchEmptyTree)
        {
            BalancedTree tree;
            auto result = tree.search("key1");
            Assert::AreEqual(std::string("Not Found!"), result.front());
        }

        TEST_METHOD(TestRemoveRootNode)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            tree.remove("key1");
            auto result = tree.search("key1");
            Assert::AreEqual(std::string("Not Found!"), result.front());
        }

        TEST_METHOD(TestRemoveNonexistentNode)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            tree.remove("nonexistent_key");
            auto result = tree.search("key1");
            Assert::AreEqual(std::string("value1"), result.front());
        }

        TEST_METHOD(TestRemoveLeafNode)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            tree.insert("key2", "value2");
            tree.remove("key2");
            auto result = tree.search("key2");
            Assert::AreEqual(std::string("Not Found!"), result.front());
            result = tree.search("key1");
            Assert::AreEqual(std::string("value1"), result.front());
        }

        TEST_METHOD(TestRemoveNodeWithOneChild)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            tree.insert("key2", "value2");
            tree.insert("key3", "value3");
            tree.remove("key2");
            auto result = tree.search("key2");
            Assert::AreEqual(std::string("Not Found!"), result.front());
            result = tree.search("key1");
            Assert::AreEqual(std::string("value1"), result.front());
            result = tree.search("key3");
            Assert::AreEqual(std::string("value3"), result.front());
        }
        TEST_METHOD(TestInsertAndSearchSingleNode)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            auto result = tree.search("key1");
            Assert::AreEqual(std::string("value1"), result.front());
        }

        TEST_METHOD(TestInsertAndSearchMultipleNodes)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            tree.insert("key2", "value2");
            tree.insert("key3", "value3");
            auto result = tree.search("key1");
            Assert::AreEqual(std::string("value1"), result.front());
            result = tree.search("key2");
            Assert::AreEqual(std::string("value2"), result.front());
            result = tree.search("key3");
            Assert::AreEqual(std::string("value3"), result.front());
        }

        TEST_METHOD(TestDisplayEmptyTree)
        {
            BalancedTree tree;
            tree.display();
        }

        TEST_METHOD(TestDisplayNonEmptyTree)
        {
            BalancedTree tree;
            tree.insert("key1", "value1");
            tree.insert("key2", "value2");
            tree.insert("key3", "value3");
            tree.display();
        }

    };
}