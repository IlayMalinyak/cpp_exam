//
// Created by ilay on 8/6/2020.
//

#ifndef EXAMCPP_DEEPSUBMIT_HPP
#define EXAMCPP_DEEPSUBMIT_HPP

#include "VLVector.hpp"
#include "helpers/Helpers.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include "Student.hpp"
#include <typeinfo>

#ifndef __DISABLE_PRESUBMISSION_TESTS
#define PRESUBMISSION_ASSERT(testCase) __ASSERT_TEST("Presubmission", testCase)
#else
#define PRESUBMISSION_ASSERT(testCase)
#endif

//-------------------------------------------------------
// Tests
//-------------------------------------------------------

int __Mypresubmit_testCreateVLAs() {
    VLVector<int, STATIC_CAP> intVec{};
    VLVector<std::string, STATIC_CAP> stringVec{};
    VLVector<double, 4> doubleVec{};
    std::vector<std::string> normalStringVec {"mike", "elli", "yehuda", "Ilay"};
    VLVector<std::string, STATIC_CAP> iterVec(normalStringVec.begin(), normalStringVec.end());
    VLVector<std::string, STATIC_CAP> copyVec(iterVec);
    VLVector<std::string, 1> iterVecDynamic(normalStringVec.begin(), normalStringVec.end());
    VLVector<std::string, 1> copyVecDynamic(iterVecDynamic);
    VLVector<Student, 2> studentVec{};


    ASSERT_VLA_PROPERTIES(intVec, false, STATIC_CAP, 0)
    ASSERT_VLA_PROPERTIES(stringVec, false, STATIC_CAP, 0)
    ASSERT_VLA_PROPERTIES(doubleVec, false, 4, 0)
    ASSERT_VLA_PROPERTIES(iterVec, false, STATIC_CAP, 4) // check static construction with range
    ASSERT_VLA_PROPERTIES(copyVec, false, STATIC_CAP, 4) // check static copy construction
    ASSERT_VLA_PROPERTIES(iterVecDynamic, false, 6, 4) // check dynamic construction with range
    ASSERT_VLA_PROPERTIES(copyVecDynamic, false, 6, 4) // check dynamic copy construction

    auto dynamicallyAllocated = new VLVector<int, STATIC_CAP>;
    delete dynamicallyAllocated;

    return 1;
}


int __Mypresubmit_testPushBack() {
    VLVector<int, STATIC_CAP> statVec;
    VLVector<int, 0> dynamicVec;
    statVec.push_back(1);
    dynamicVec.push_back(1);
    VLVector<int, 1> changerVec(dynamicVec.begin(), dynamicVec.end());
    ASSERT_VLA_PROPERTIES(changerVec, false, 3, 1);
    changerVec.push_back(2);
    ASSERT_VLA_PROPERTIES(changerVec, false, 3, 2);
    ASSERT_VLA_PROPERTIES(statVec, false, STATIC_CAP, 1);
    changerVec.push_back(3);
    ASSERT_VLA_PROPERTIES(changerVec, false, 6, 3);
    changerVec.push_back(4);
    ASSERT_VLA_PROPERTIES(changerVec, false, 6, 4);
    changerVec.push_back(5);
    ASSERT_VLA_PROPERTIES(changerVec, false, 6, 5);
    changerVec.push_back(5);
    ASSERT_VLA_PROPERTIES(changerVec, false, 10, 6);

    VLVector<Student, 2> studentVec{};
    Student s1 = Student("ilay", 87);
    studentVec.push_back(s1);
    ASSERT_VLA_PROPERTIES(studentVec, false, 2, 1);
    studentVec.push_back(Student());
    ASSERT_VLA_PROPERTIES(studentVec, false, 4, 2);
    studentVec.push_back(Student("ella", 100));

    ASSERT_VLA_PROPERTIES(studentVec, false, 4, 3);
    return 1;
}

int __Mypresubmit_testSize() {
#define TYPE "size_t";
    VLVector<int, STATIC_CAP> vec;
    ASSERT_TRUE(vec.size() == 0)
    vec.push_back(1);
    VLVector<int , 1> vec2(vec.begin(), vec.end());
    ASSERT_TRUE((vec.size() == vec2.size()) == 1);
    vec2.pop_back();
    ASSERT_TRUE(vec.size() != vec2.size())
    ASSERT_TRUE(vec2.size() == 0);
    return 1;
}




int __Mypresubmit_testCapacity() {
    VLVector<int, 2> vec;
    VLVector<int, 0> vec2;
    // push_back with capacity 2
    ASSERT_TRUE(vec.capacity() == 2); // 2
    vec.push_back(1);
    ASSERT_TRUE(vec.capacity() == 2); // 2
    vec.push_back(2);
    ASSERT_TRUE(vec.capacity() == 4); // 4
    vec.push_back(3);
    ASSERT_TRUE(vec.capacity() == 4); // 4
    vec.push_back(4);
    ASSERT_TRUE(vec.capacity() == 7); // 7

    // push back with capacity 0
    ASSERT_TRUE(vec2.capacity() == 1); // 1
    vec2.push_back(1);
    ASSERT_TRUE(vec2.capacity() == 3); // 3
    vec2.push_back(2);
    ASSERT_TRUE(vec2.capacity() == 3); // 3
    vec2.push_back(3);
    ASSERT_TRUE(vec2.capacity() ==6); // 6

    // iterator constructor 3 elements with capacity 3
    VLVector<int, 3> vec3(vec2.begin(), vec2.end());
    ASSERT_TRUE(vec3.capacity() == 6); // 6
    vec3.push_back(4);
    ASSERT_TRUE(vec3.capacity() == 6); // 6

    //iterator constructor 4 elements with capacity 3
    VLVector<int, 3>vec4(vec3);
    ASSERT_TRUE(vec4.capacity() == 6); // 6
    return 1;
}

int __Mypresubmit_testEmpty() {
    VLVector<int, STATIC_CAP> vec;
    ASSERT_TRUE(vec.empty())
    vec.push_back(1);
    ASSERT_TRUE(!vec.empty())
    return 1;
}

int __Mypresubmit_testClear() {
    VLVector<int, STATIC_CAP> vec;
    if (!vec.empty()) {
        return 0;
    }
    vec.push_back(1);
    vec.clear();
    ASSERT_TRUE(vec.empty())
    std::vector<int> values{1,2,3,4,5,6};
    vec.insert(vec.begin(), values.begin(), values.end());
    ASSERT_TRUE(!vec.empty())
    vec.clear();
    ASSERT_TRUE(vec.empty());
    return 1;

}

int __Mypresubmit_testPopBack() {
    VLVector<int, 3> vec2{};
    vec2.push_back(0);
    vec2.push_back(1);
    vec2.push_back(2);
    vec2.push_back(3);
    vec2.pop_back();
    ASSERT_TRUE(vec2.capacity() == 6);
    vec2.pop_back();
    ASSERT_TRUE(vec2.capacity() == 3);
    vec2.pop_back();
    ASSERT_TRUE(vec2.capacity() == 3);
    vec2.pop_back();
    ASSERT_TRUE(vec2.capacity() == 3);
    ASSERT_TRUE((vec2.empty()));
    VLVector<int, STATIC_CAP> vec;
    if (!vec.empty()) {
        return 0;
    }
    vec.push_back(1);
    vec.pop_back();

    RETURN_ASSERT_TRUE(vec.empty())
}

int __Mypresubmit_testGetElement() {
    VLVector<int, STATIC_CAP> vec;
    vec.push_back(1);
    ASSERT_TRUE(vec.at(0) == 1)  // using VLVector::at
    ASSERT_TRUE(vec[0] == 1) // using VLVector::operator[]

    Student s1 = Student("ilay", 60);
    Student s2 = Student("ella", 100);
    VLVector<Student, 3> studentVec{};
    studentVec.push_back(s1);
    studentVec.insert(studentVec.begin(), s2);
    ASSERT_TRUE(studentVec[0].getAverage() == 100);
    ASSERT_TRUE(studentVec.at(1).getAverage() == 60);
    try
    {
        int x = vec.at(-1);
        x+= 1;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << e.what() << std::endl;
    }
    try
    {
        int x = vec.at(1);
        x+= 1;
    }
    catch (const std::out_of_range &e)
    {
        std::cout << e.what() << std::endl;
    }

    return 1;


}

int __Mypresubmit_testData() {
    VLVector<int, STATIC_CAP> vec;
    VLVector<int, 0> vec1{};
    vec1.data();
    vec.data();
    return 1;
}

int __Mypresubmit_testComparison() {
    VLVector<int, STATIC_CAP> vec1{};
    VLVector<int, STATIC_CAP> vec2{};
    vec1.push_back(1);
    vec2.insert(vec2.begin(), 1);
    ASSERT_TRUE(vec1 == vec2)
    vec2.insert(vec2.begin() + 1, 2);
    ASSERT_TRUE(vec1 != vec2)
    return 1;

}

int __Mypresubmit_testAssignment() {
    VLVector<int, 2> vec1{};
    vec1.push_back(1);

    VLVector<int, 2> vec2 = vec1;
    ASSERT_TRUE(vec1 == vec2);
    vec1.push_back(2);
    VLVector<int, 2> vec3 = vec1;
    ASSERT_TRUE(vec3.capacity() == 4);
    return 1;
}

int __Mypresubmit_testIterator() {
    VLVector<int, STATIC_CAP> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);
    vec.push_back(4);
    auto it = vec.begin();
    for (int i = 0; i < 3; i++)
    {
        int x = *it;
        std::cout << x << std::endl;
        *it = i + 10;

        it++;
        --it;
        ++it;
        it--;
        it++;
    }
    it++;
    ASSERT_TRUE(it == vec.end());
    ASSERT_TRUE(it >= vec.begin());
    vec.begin();
    vec.end();
    vec.cbegin();
    vec.cend();

    return 1;
}

int __Mypresubmit_testInsert1() {
    VLVector<int, STATIC_CAP> vec;
    vec.push_back(0);
    vec.push_back(2);
    auto it = vec.begin();
    ++it;
    vec.insert(it, 1);
    ASSERT_TRUE(vec[1] == 1)
    VLVector<int , 3> vec2(vec.begin(), vec.end());
    auto it2 = vec2.begin() + 1;
    auto it3 = vec2.insert(it2, 10);
    ASSERT_TRUE(vec2[1] == 10)
    ASSERT_TRUE(vec2[2] == 1)
    ASSERT_TRUE(vec2[3] == 2)
    ASSERT_TRUE(vec2.capacity() == 6)
    it3 += 2;
    auto it4 = vec2.insert(it3, 9);
    ASSERT_TRUE(*it4 == 9);
    ASSERT_TRUE(vec2[3] == 9);
    ASSERT_TRUE(vec2[4] == 2);

    auto it5 = vec2.insert(it4, 8);
//    auto b = vec2.begin();
//    while (b!= vec2.end())
//    {
//        std::cout << *b << std::endl;
//    }

    ASSERT_TRUE(vec2[3] == 8);
    ASSERT_TRUE(vec2[4] == 9);
    ASSERT_TRUE(vec2[5] == 2);
    ASSERT_TRUE(vec2.capacity() == 10);
    vec2.insert(it5, 7);
    ASSERT_TRUE(vec2[3] == 7);
    ASSERT_TRUE(vec2[4] == 8);
    ASSERT_TRUE(vec2[5] == 9);
    ASSERT_TRUE(vec2[6] == 2);
    ASSERT_TRUE(vec2.capacity() == 10);
    ASSERT_TRUE(vec2.size() == 7);

    VLVector<int, 3> vector{};
    vector.push_back(1);
    vector.insert(vector.begin(), 0);
    ASSERT_VLA_PROPERTIES(vector, false, 3, 2);
    return 1;
}

int __Mypresubmit_testInsert2() {
    VLVector<int, STATIC_CAP> vec;
    vec.push_back(0);
    std::vector<int> values{1, 2, 3, 4};
    auto it = vec.begin();
    ++it;
    vec.insert(it, values.begin(), values.end());
    ASSERT_TRUE(vec.size() == 5)

    VLVector<int, 3> vec2{};
    auto it2 = vec2.insert(vec2.begin(), vec.begin(), vec.end());
    ASSERT_TRUE(vec2.capacity() == 7);
    ASSERT_TRUE(*it2 == 0);
    vec2.insert(vec2.end(), vec2.begin(), vec2.begin() + 2);
    ASSERT_TRUE(vec2.capacity() == 12);
    vec2.insert(vec2.begin() + 7, vec.begin(), vec.begin() + 1);
    ASSERT_TRUE(vec2.capacity() == 12);
    ASSERT_TRUE(vec2.size() == 8);

    return 1;
}

int __Mypresubmit_testErase1() {
    VLVector<int, STATIC_CAP> vec;
    for (int i = 0; i < 5; ++i) {
        vec.push_back(i);
    }
    auto it = vec.erase(vec.begin());
    ASSERT_TRUE(vec.size() == 4)
    ASSERT_TRUE(*it == 1);
    for (int i = 0; i < 4; ++i)
    {
        ASSERT_TRUE(vec[i] == i + 1);
    }
    VLVector<int, 3> vec2(vec.begin(), vec.end());
    ASSERT_TRUE(vec2.capacity() == 6);
    auto it2 = vec2.begin() + 1;
    for (int i = 0; i < 2; i++)
    {
        auto it3 = vec2.erase(it2);
        ASSERT_TRUE(vec2[1] == i + 3);
        it2 = it3;
    }
    ASSERT_TRUE(vec2.capacity() == 3)
    it2 = vec2.erase(it2);
    ASSERT_TRUE(it2 == vec2.end());
    it2--;
    it2 = vec2.erase(it2);
    return 1;
}

int __Mypresubmit_testErase2() {
    VLVector<int, 5> vec;
    for (int i = 0; i < 10; ++i) {
        vec.push_back(i);
    }
    ASSERT_TRUE(vec.capacity() == 15);
    auto first = VLVector<int, 5>::iterator(&vec[6]);
    auto last = vec.end();
    auto it = vec.erase(first, last);
    ASSERT_TRUE(vec.capacity() == 15);
    ASSERT_TRUE(vec.size() == 6);
    ASSERT_TRUE(it == vec.end());
    first = vec.begin()  + 5;
    auto it2 = vec.erase(first, it);
    ASSERT_TRUE(vec.capacity() == 9);
    ASSERT_TRUE(it2 == vec.end());
    VLVector<int, 5> vec2 = vec;
    vec.erase(vec.begin() + 1, vec.end());
    vec2.erase(vec2.begin(), vec2.end());
    ASSERT_TRUE(vec.capacity() == 5)
    ASSERT_TRUE(vec.size() == 1)
    ASSERT_TRUE(vec2.empty());


    return 1;
}

int __Mypresubmit_testIteratorsCtor() {
    /* Create the values */
    std::vector<int> values{1, 2};

    /* Create the vec */
    VLVector<int, STATIC_CAP> vec(values.begin(), values.end());
    RETURN_ASSERT_TRUE(vec.size() == 2 && vec[0] == 1)
}

int __Mypresubmit_testCopyCtor() {
    VLVector<int, STATIC_CAP> vec1{};
    vec1.push_back(5);

    VLVector<int, STATIC_CAP> vec2(vec1);
    RETURN_ASSERT_TRUE(vec2[0] == 5)
}

//-------------------------------------------------------
//  The main entry point
//-------------------------------------------------------
int runMyPreSubmissionChecks() {
    PRESUBMISSION_ASSERT(__Mypresubmit_testCreateVLAs)
    PRESUBMISSION_ASSERT(__Mypresubmit_testPushBack)
    PRESUBMISSION_ASSERT(__Mypresubmit_testSize)
    PRESUBMISSION_ASSERT(__Mypresubmit_testCapacity)
    PRESUBMISSION_ASSERT(__Mypresubmit_testInsert1)
    PRESUBMISSION_ASSERT(__Mypresubmit_testInsert2)
    PRESUBMISSION_ASSERT(__Mypresubmit_testErase1)
    PRESUBMISSION_ASSERT( __Mypresubmit_testErase2)
    PRESUBMISSION_ASSERT(__Mypresubmit_testPopBack)
    PRESUBMISSION_ASSERT(__Mypresubmit_testEmpty)
    PRESUBMISSION_ASSERT(__Mypresubmit_testClear)
    PRESUBMISSION_ASSERT(__Mypresubmit_testGetElement)
    PRESUBMISSION_ASSERT(__Mypresubmit_testData) // TODO follow from this one
    PRESUBMISSION_ASSERT(__Mypresubmit_testComparison)
    PRESUBMISSION_ASSERT(__Mypresubmit_testAssignment)
    PRESUBMISSION_ASSERT(__Mypresubmit_testIterator)
    PRESUBMISSION_ASSERT(__Mypresubmit_testIteratorsCtor)
    PRESUBMISSION_ASSERT(__Mypresubmit_testCopyCtor)

    return 1;
}

#endif //EXAMCPP_DEEPSUBMIT_HPP
