#include "applib/bst.h" 
#include <string>

int main()
{
    BST<string> bt; // = BST<string>("test");
    string addStr = "t"; //est";
    bt.add(addStr);

    //copy constructor usage (to help with debugging the CC)
	BST<string> B4(bt);

    // addStr = "z";
    // bt.add(addStr);
    return 0;
}