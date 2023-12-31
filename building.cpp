//============================================================================
// Name        : Building
// Test Desc.  : For building in the build section.
//                  Also can have calls made for 'testing' within this, and then you can see -g information.
// Author      : Jeffrey Caruso, Yusuf Pisan
// Date    	   : Fall 2023
//============================================================================


#include "applib/bst.h" 
#include <string>

int main()
{
    BST<string> bt; // = BST<string>("test");
    string addStr = "t"; //est";
    bt.add(addStr);

    //copy constructor usage (to help with debugging the CC)
	BST<string> B4(bt);

    return 0;
}
