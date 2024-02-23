#include "bst.h"

#include <iostream>
#include <sstream>

class TreeVisitor {
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

stringstream TreeVisitor::SS;

template <class T>
void visitorSimple(const T &Item)
{
	cout << "visitorSimple: " << Item;
}

