//============================================================================
// Name        : Test1
// Test Desc.  : Test == (basic)
//				 	(coverage for old test 1 method)
// Author      : Jeffrey Caruso
// Date    	   : Fall 2023
//============================================================================

#include <gtest/gtest.h>
#include "applib/bst.h"

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

/**
 * Testing BST - Binary Search Tree functions
 *
 * This file has series of tests for BST
 * Each test is independent and uses assert statements
 * Test functions are of the form
 *
 *      test_netidXX()
 *
 * where netid is UW netid and XX is the test number starting from 01
 *
 * Test functions can only use the public functions from BST
 * testBSTAll() is called from main in main.cpp
 * testBSTAll calls all other functions
 * @author Multiple
 * @date ongoing
 */

/**
 * Trying to avoid global variables,
 * by creating a singleton class with our visitor functions
 * stringstream SS contains the output from visitor
 */
class TreeVisitor
{
public:
	// never create an instance of TreeVisitor object
	// we'll just use the static functions
	TreeVisitor() = delete;

	// insert output to SS rather than cout, so we can test it
	static stringstream SS;

	// get SS as a string
	static string getSS() { return SS.str(); }

	// set SS to be empty string
	static void resetSS() { SS.str(string()); }

	// instead of cout, insert item into SS, a stringstream object
	static void visitor(const string &Item) { SS << Item; }

	// instead of cout, insert item into SS, a stringstream object
	static void visitor(const int &Item) { SS << Item; }
};

// initialize the static variable
//  warning: initialization of 'SS' with static storage duration
//  may throw an exception that cannot be caught [cert-err58-cpp]
//  Not sure how to do it without making code harder to read
//  NOLINTNEXTLINE
stringstream TreeVisitor::SS;

template <class T>
void visitorSimple(const T &Item)
{
	cout << "visitorSimple: " << Item;
}

// Testing ==
TEST(Test1, TestEquality)
{
	BST<string> B1;
	BST<string> B2;
	BST<string> B3;

	EXPECT_TRUE(B1 == B2 && (!(B1 != B2)));
	B1.add("c");
	B2.add("c");
	B3.add("b");

	//   assert(B1 == B2 && (!(B1 != B2)));
	EXPECT_TRUE(B1 == B2 && (!(B1 != B2)));
	//   assert(B1 != B3 && (!(B1 == B3)));
	EXPECT_TRUE(B1 != B2 && (!(B1 == B3)));

	// cout << "Starting testPisan01" << endl;
	//   cout << "* Testing == and !=" << endl;
	//   BST<string> B1;
	//   BST<string> B2;
	//   BST<string> B3;
	//   // == and != for empty trees
	//   assert(B1 == B2 && (!(B1 != B2)));
	//   B1.add("c");
	//   B2.add("c");
	//   B3.add("b");
	//   // == and !- for 1-Node trees B1, B2, B3
	//   assert(B1 == B2 && (!(B1 != B2)));
	//   assert(B1 != B3 && (!(B1 == B3)));
	//   cout << "Ending testPisan01" << endl;
}
