// HashMapTests.cpp
//
// ICS 45C Spring 2021
// Project #3: Maps and Legends
//
// Write unit tests for your HashMap class here.  I've provided a few tests
// already, though I've commented them out, because they won't compile and
// link until you've implemented some things.
//
// Of course, you'll want to write lots more of these tests yourself, because
// this is an inexpensive way to know whether things are working the way
// you expect -- including scenarios that you won't happen to hit in the
// course of testing your overall program.  (You might also want to be sure
// that your HashMap implementation is complete and correct before you try
// to write the rest of the program around it, anyway; there's a very
// substantial amount of partial credit available if all that works is
// HashMap.)

#include <gtest/gtest.h>
#include "HashMap.hpp"


namespace 
{
    unsigned int someFunction(const std::string& s)
    {
        unsigned int hash = 0; 
        for (unsigned int i = 0; i < s.length(); i++)
        {
            hash = hash * 19 + s[i];
        }
        return hash;
    }
}

namespace 
{
    unsigned int anotherFunction(const std::string& s)
    {
        return 37;
    }
}

TEST(HashMapTests, sizeOfNewlyCreatedHashMapIsZero)
{
    HashMap empty;
    HashMap empty2{someFunction};
    ASSERT_EQ(0, empty.size());
    ASSERT_EQ(0, empty2.size());
}

TEST(HashMapTests, numberOfBucketsOfNewlyCreatedHashMapIsTen)
{
    HashMap empty; 
    HashMap empty2{someFunction};
    ASSERT_EQ(10, empty.bucketCount());
    ASSERT_EQ(10, empty2.bucketCount());
}


TEST(HashMapTests, emptyMapContainsNoKeys)
{
    HashMap empty;
    HashMap empty2{someFunction};
    ASSERT_FALSE(empty.contains("first"));
    ASSERT_FALSE(empty.contains("second"));
    ASSERT_FALSE(empty2.contains("first"));
    ASSERT_FALSE(empty2.contains("second"));
}


TEST(HashMapTests, canConstructWithSomeHashFunction)
{
    HashMap hm{someFunction};
    HashMap hm2{anotherFunction};
}

TEST(HashMapTests, defaultsContainKeysAfterAddingThem)
{
    HashMap hm;
    hm.add("Boo", "perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");

    ASSERT_TRUE(hm.contains("Boo"));
    ASSERT_TRUE(hm.contains("Apple"));
    ASSERT_TRUE(hm.contains("Banana"));
    ASSERT_TRUE(hm.contains("Melon"));
}

TEST(HashMapTests, containKeysAfterAddingThem)
{
    HashMap hm2{someFunction};
    hm2.add("Boo", "perfect");
    hm2.add("Apple", "Red"); 
    hm2.add("Banana", "Yellow");
    hm2.add("Melon", "Green");

    ASSERT_TRUE(hm2.contains("Boo"));
    ASSERT_TRUE(hm2.contains("Apple"));
    ASSERT_TRUE(hm2.contains("Banana"));
    ASSERT_TRUE(hm2.contains("Melon"));
}

TEST(HashMapTests, canCopyEmptyHashMaps)
{
    HashMap map1; 
    HashMap map2 = map1; 

    HashMap map3{someFunction};
    HashMap map4 = map3;

    ASSERT_EQ(map2.size(), map1.size());
    ASSERT_EQ(map2.bucketCount(), map1.bucketCount());
    ASSERT_EQ(map4.size(), map3.size());
    ASSERT_EQ(map4.bucketCount(), map3.bucketCount());
}


TEST(HashMapTests, canCopyNonEmptyDefaultHashMaps)
{
    HashMap map1; 
    map1.add("Boo", "Perfect");
    map1.add("Apple", "Red"); 
    map1.add("Banana", "Yellow");
    map1.add("Melon", "Green");

    HashMap map2 = map1;

    ASSERT_EQ(4, map2.size());
    ASSERT_EQ(10, map2.bucketCount());
    ASSERT_TRUE(map2.contains("Boo"));
    ASSERT_TRUE(map2.contains("Apple"));
    ASSERT_TRUE(map2.contains("Banana"));
    ASSERT_TRUE(map2.contains("Melon"));
    ASSERT_EQ("Perfect", map2.value("Boo"));
    ASSERT_EQ("Red", map2.value("Apple"));
    ASSERT_EQ("Yellow", map2.value("Banana"));
    ASSERT_EQ("Green", map2.value("Melon"));
}

TEST(HashMapTests, canCopyNonEmptyHashMaps)
{
    HashMap map1{someFunction}; 
    map1.add("Boo", "Perfect");
    map1.add("Apple", "Red"); 
    map1.add("Banana", "Yellow");
    map1.add("Melon", "Green");

    HashMap map2 = map1;

    ASSERT_EQ(4, map2.size());
    ASSERT_EQ(10, map2.bucketCount());
    ASSERT_TRUE(map2.contains("Boo"));
    ASSERT_TRUE(map2.contains("Apple"));
    ASSERT_TRUE(map2.contains("Banana"));
    ASSERT_TRUE(map2.contains("Melon"));
    ASSERT_EQ("Perfect", map2.value("Boo"));
    ASSERT_EQ("Red", map2.value("Apple"));
    ASSERT_EQ("Yellow", map2.value("Banana"));
    ASSERT_EQ("Green", map2.value("Melon"));
}

TEST(HashMapTests, canAssignDefaultHashMaps)
{
    HashMap map1; 
    map1.add("Boo", "Perfect");
    map1.add("Apple", "Red"); 
    map1.add("Banana", "Yellow");
    map1.add("Melon", "Green");

    HashMap map2; 
    map2.add("Math", "Easy");
    map2.add("Science", "Hard");
    map2.add("English", "Ok");
    map2.add("History", "Worst");

    map2 = map1;

    ASSERT_FALSE(map2.contains("Math"));
    ASSERT_FALSE(map2.contains("Science"));
    ASSERT_FALSE(map2.contains("English"));
    ASSERT_FALSE(map2.contains("History"));

    ASSERT_TRUE(map2.contains("Boo"));
    ASSERT_TRUE(map2.contains("Apple"));
    ASSERT_TRUE(map2.contains("Banana"));
    ASSERT_TRUE(map2.contains("Melon"));

    ASSERT_EQ("Perfect", map2.value("Boo"));
    ASSERT_EQ("Red", map2.value("Apple"));
    ASSERT_EQ("Yellow", map2.value("Banana"));
    ASSERT_EQ("Green", map2.value("Melon"));
}

TEST(HashMapTests, canAssignHashMapsWithInputFunctions)
{
    HashMap map1{someFunction}; 
    map1.add("Boo", "Perfect");
    map1.add("Apple", "Red"); 
    map1.add("Banana", "Yellow");
    map1.add("Melon", "Green");

    HashMap map2{someFunction}; 
    map2.add("Math", "Easy");
    map2.add("Science", "Hard");
    map2.add("English", "Ok");
    map2.add("History", "Worst");

    map2 = map1;

    ASSERT_FALSE(map2.contains("Math"));
    ASSERT_FALSE(map2.contains("Science"));
    ASSERT_FALSE(map2.contains("English"));
    ASSERT_FALSE(map2.contains("History"));

    ASSERT_TRUE(map2.contains("Boo"));
    ASSERT_TRUE(map2.contains("Apple"));
    ASSERT_TRUE(map2.contains("Banana"));
    ASSERT_TRUE(map2.contains("Melon"));

    ASSERT_EQ("Perfect", map2.value("Boo"));
    ASSERT_EQ("Red", map2.value("Apple"));
    ASSERT_EQ("Yellow", map2.value("Banana"));
    ASSERT_EQ("Green", map2.value("Melon"));
}


TEST(HashMapTests, sizeIsGreaterThanCurrentAfterAdditionInDefault)
{
    HashMap hm; 
    unsigned int before = hm.size();
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");

    ASSERT_GT(hm.size(), before);
}

TEST(HashMapTests, sizeIsGreaterThanCurrentAfterAddition)
{
    HashMap hm{someFunction}; 
    unsigned int before = hm.size();
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");

    ASSERT_GT(hm.size(), before);
}

TEST(HashMapTests, addingDuplicatesDoesntIncreaseSizeOfDefaultHashMap)
{
    HashMap hm; 
    hm.add("Boo", "Perfect");
    hm.add("Boo", "Perfect");

    ASSERT_EQ(1, hm.size());
}


TEST(HashMapTests, addingDuplicatesDoesntIncreaseSizeOfHashMap)
{
    HashMap hm{someFunction}; 
    hm.add("Boo", "Perfect");
    hm.add("Boo", "Perfect");

    ASSERT_EQ(1, hm.size());
}

TEST(HashMapTests, highLoadFactorOfDefaultCausesIncreaseInBucketSize)
{
    HashMap hm; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");
    hm.add("Rice", "White");
    hm.add("Chocolate", "Brown"); 
    hm.add("Gum", "Pink");
    hm.add("Blueberry", "Blue");
    hm.add("Grape", "Purple");

    ASSERT_EQ(21, hm.bucketCount());
}

TEST(HashMapTests, highLoadFactorCausesIncreaseInBucketSize)
{
    HashMap hm{someFunction}; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");
    hm.add("Rice", "White");
    hm.add("Chocolate", "Brown"); 
    hm.add("Gum", "Pink");
    hm.add("Blueberry", "Blue");
    hm.add("Grape", "Purple");

    ASSERT_EQ(21, hm.bucketCount());
}

TEST(HashMapTests, increaseInBucketSizeDecreasesLoadFactorOfDefault)
{
    HashMap hm; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");
    hm.add("Rice", "White");
    hm.add("Chocolate", "Brown"); 
    hm.add("Gum", "Pink");

    double lf1 = hm.loadFactor();

    hm.add("Blueberry", "Blue");
    hm.add("Grape", "Purple");

    ASSERT_GT(lf1, hm.loadFactor());
}

TEST(HashMapTests, increaseInBucketSizeDecreasesLoadFactor)
{
    HashMap hm{someFunction}; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");
    hm.add("Rice", "White");
    hm.add("Chocolate", "Brown"); 
    hm.add("Gum", "Pink");

    double lf1 = hm.loadFactor();

    hm.add("Blueberry", "Blue");
    hm.add("Grape", "Purple");

    ASSERT_GT(lf1, hm.loadFactor());
}


TEST(HashMapTests, reHashStillContainsOriginalKeysValues)
{
    HashMap hm; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");
    hm.add("Rice", "White");
    hm.add("Chocolate", "Brown"); 
    hm.add("Gum", "Pink");

    ASSERT_TRUE(hm.contains("Boo"));
    ASSERT_TRUE(hm.contains("Apple"));
    ASSERT_TRUE(hm.contains("Banana"));
    ASSERT_TRUE(hm.contains("Melon"));
    ASSERT_TRUE(hm.contains("Melon"));
    ASSERT_TRUE(hm.contains("Rice"));
    ASSERT_TRUE(hm.contains("Chocolate"));
    ASSERT_TRUE(hm.contains("Gum"));

    hm.add("Blueberry", "Blue");
    hm.add("Grape", "Purple");

    ASSERT_TRUE(hm.contains("Boo"));
    ASSERT_TRUE(hm.contains("Apple"));
    ASSERT_TRUE(hm.contains("Banana"));
    ASSERT_TRUE(hm.contains("Melon"));
    ASSERT_TRUE(hm.contains("Melon"));
    ASSERT_TRUE(hm.contains("Rice"));
    ASSERT_TRUE(hm.contains("Chocolate"));
    ASSERT_TRUE(hm.contains("Gum"));
}


TEST(HashMapTests, canRemoveAlreadyContainedKeyInDefault)
{
    HashMap hm; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red");

    ASSERT_TRUE(hm.remove("Apple"));
    ASSERT_FALSE(hm.contains("Apple"));
}

TEST(HashMapTests, canRemoveAlreadyContainedKey)
{
    HashMap hm{someFunction}; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red");

    ASSERT_TRUE(hm.remove("Apple"));
    ASSERT_FALSE(hm.contains("Apple"));
}


TEST(HashMapTests, cannotRemoveNotContainedKeyInDefault)
{
    HashMap hm;
    hm.add("Boo", "Perfect");
    
    ASSERT_FALSE(hm.remove("Apple"));
    ASSERT_FALSE(hm.remove("Banana"));
}

TEST(HashMapTests, cannotRemoveNotContainedKey)
{
    HashMap hm{someFunction};
    hm.add("Boo", "Perfect");
    
    ASSERT_FALSE(hm.remove("Apple"));
    ASSERT_FALSE(hm.remove("Banana"));
}


TEST(HashMapTests, sizeDecreasesAfterAdditionAndRemovalInDefault)
{
    HashMap hm;
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");

    unsigned int after_addition = hm.size();

    hm.remove("Boo");
    hm.remove("Apple");

    ASSERT_LT(hm.size(), after_addition);
}

TEST(HashMapTests, sizeDecreasesAfterAdditionAndRemoval)
{
    HashMap hm{someFunction};
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");

    unsigned int after_addition = hm.size();

    hm.remove("Boo");
    hm.remove("Apple");

    ASSERT_LT(hm.size(), after_addition);
}


TEST(HashMapTests, canGetValueIfKeyContainedInDefaultHashMap)
{
    HashMap hm;
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");

    ASSERT_EQ("Perfect", hm.value("Boo"));
    ASSERT_EQ("Red", hm.value("Apple"));
    ASSERT_EQ("Yellow", hm.value("Banana"));
    ASSERT_EQ("Green", hm.value("Melon"));
}

TEST(HashMapTests, canGetValueIfKeyContainedInSomeHashMap)
{
    HashMap hm{someFunction};
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");

    ASSERT_EQ("Perfect", hm.value("Boo"));
    ASSERT_EQ("Red", hm.value("Apple"));
    ASSERT_EQ("Yellow", hm.value("Banana"));
    ASSERT_EQ("Green", hm.value("Melon"));
}


TEST(HashMapTests, canGetEmptyStringIfKeyNotContainedInDefaultHashMap)
{
    HashMap hm;
    hm.add("Boo", "Perfect");

    ASSERT_EQ("", hm.value("Apple"));
}

TEST(HashMapTests, canGetEmptyStringIfKeyNotContainedInSomeHashMap)
{
    HashMap hm{someFunction};
    hm.add("Boo", "Perfect");

    ASSERT_EQ("", hm.value("Apple"));
}

TEST(HashMapTests, largestBucketInDefaultHasFourKeyValuePairs)
{
    HashMap hm; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");
    hm.add("Rice", "White");
    hm.add("Chocolate", "Brown"); 
    hm.add("Gum", "Pink");

    ASSERT_EQ(4, hm.maxBucketSize());
}

TEST(HashMapTests, largestBucketHasFiveKeyValuePairs)
{
    HashMap hm{someFunction}; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");
    hm.add("Rice", "White");
    hm.add("Chocolate", "Brown"); 
    hm.add("Gum", "Pink");

    ASSERT_EQ(2, hm.maxBucketSize());
}

TEST(HashMapTests, assingingHashMapsWithDiffFunctions_CanChangeMaximumBucket)
{

    HashMap map1; 
    map1.add("Boo", "Perfect");
    map1.add("Apple", "Red"); 
    map1.add("Banana", "Yellow");
    map1.add("Melon", "Green");
    map1.add("Rice", "White");
    map1.add("Chocolate", "Brown"); 
    map1.add("Gum", "Pink");

    HashMap map2{someFunction}; 
    map2.add("Boo", "Perfect");
    map2.add("Apple", "Red"); 
    map2.add("Banana", "Yellow");
    map2.add("Melon", "Green");
    map2.add("Rice", "White");
    map2.add("Chocolate", "Brown"); 
    map2.add("Gum", "Pink");

    unsigned int m = map2.maxBucketSize();
    map2 = map1;
    ASSERT_NE(map2.maxBucketSize(), m); 
}


TEST(HashMapTests, clearingDecreasesSizeToZeroInDefault)
{
    HashMap hm; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");
    hm.add("Rice", "White");
    hm.add("Chocolate", "Brown"); 
    hm.add("Gum", "Pink");

    hm.clear();

    ASSERT_EQ(0, hm.size());
}

TEST(HashMapTests, clearingDecreasesSizeToZero)
{
    HashMap hm{someFunction}; 
    hm.add("Boo", "Perfect");
    hm.add("Apple", "Red"); 
    hm.add("Banana", "Yellow");
    hm.add("Melon", "Green");
    hm.add("Rice", "White");
    hm.add("Chocolate", "Brown"); 
    hm.add("Gum", "Pink");

    hm.clear();

    ASSERT_EQ(0, hm.size());
}
