#include "pch.h"
#include "CppUnitTest.h"
#include "../aois6(2)/HashTable.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace HashTableTests
{
    TEST_CLASS(HashTableTest)
    {
    public:

        TEST_METHOD(TestInsertAndSearch)
        {
            HashTable hashTable;
            hashTable.insert("key1", "value1");
            hashTable.insert("key2", "value2");
            hashTable.insert("key3", "value3");
            auto result1 = hashTable.search("key1");
            Assert::AreEqual("value1", result1.front().c_str());
            auto result2 = hashTable.search("key2");
            Assert::AreEqual("value2", result2.front().c_str());
            auto result3 = hashTable.search("key3");
            Assert::AreEqual("value3", result3.front().c_str());
        }

        TEST_METHOD(TestRemove)
        {
            HashTable hashTable;
            hashTable.insert("key1", "value1");
            hashTable.insert("key2", "value2");
            hashTable.insert("key3", "value3");
            hashTable.remove("key2");
            auto result1 = hashTable.search("key1");
            Assert::AreEqual("value1", result1.front().c_str());
            auto result2 = hashTable.search("key2");
            Assert::AreEqual("Not Found!", result2.front().c_str());
            auto result3 = hashTable.search("key3");
            Assert::AreEqual("value3", result3.front().c_str());
        }

        TEST_METHOD(TestInsertAndSearchCollision)
        {
            HashTable hashTable;
            hashTable.insert("key1", "value1");
            hashTable.insert("key11", "value11");
            hashTable.insert("key21", "value21");
            auto result1 = hashTable.search("key1");
            Assert::AreEqual("value1", result1.front().c_str());
            auto result2 = hashTable.search("key11");
            Assert::AreEqual("value11", result2.front().c_str());
            auto result3 = hashTable.search("key21");
            Assert::AreEqual("value21", result3.front().c_str());
        }

        TEST_METHOD(TestRemoveNonexistentKey)
        {
            HashTable hashTable;
            hashTable.insert("key1", "value1");
            hashTable.remove("nonexistent_key");
            auto result = hashTable.search("key1");
            Assert::AreEqual("value1", result.front().c_str());
        }

        TEST_METHOD(TestRemoveAll)
        {
            HashTable hashTable;
            hashTable.insert("key1", "value1");
            hashTable.insert("key2", "value2");
            hashTable.insert("key3", "value3");
            hashTable.remove("key1");
            hashTable.remove("key2");
            hashTable.remove("key3");
            auto result1 = hashTable.search("key1");
            Assert::AreEqual("Not Found!", result1.front().c_str());
            auto result2 = hashTable.search("key2");
            Assert::AreEqual("Not Found!", result2.front().c_str());
            auto result3 = hashTable.search("key3");
            Assert::AreEqual("Not Found!", result3.front().c_str());
        }

        TEST_METHOD(TestInsertAndSearchMultipleValues)
        {
            HashTable hashTable;
            hashTable.insert("key1", "value1");
            hashTable.insert("key1", "value2");
            hashTable.insert("key1", "value3");
            auto result = hashTable.search("key1");
            std::vector<std::string> expected = { "value1", "value2", "value3" };
            Assert::IsTrue(std::equal(result.begin(), result.end(), expected.begin()));
        }

    };
}