#include "applib/bst.h" 
#include <string>

int main()
{
    BST<string> bt; // = BST<string>("test");
    string addStr = "t"; //est";
    bt.add(addStr);
    addStr = "z";
    bt.add(addStr);
    return 0;
}