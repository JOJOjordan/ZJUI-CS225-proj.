// The code of B+ tree is mainly from handerliu, https://blog.csdn.net/liu1064782986/article/details/7982290
// We add 5 functions in the B+ tree class, to complete the assignment

 #include <iostream>
 #include "BPlus_tree.h"

// helper function for test
void test2_insert(CBPlusTree *tree) {
    int arr[30];
    for (int i = 0; i < 30; i++) {
        arr[i] = i;
    }
    tree->insert(3, arr[3]);
    tree->insert(1, arr[1]);
    tree->insert(3, arr[3]);
    tree->insert(24, arr[24]);
    tree->insert(7, arr[7]);
    tree->insert(11, arr[11]);
    tree->insert(13, arr[13]);
    tree->insert(19, arr[19]);
    tree->insert(10, arr[10]);
    tree->insert(6, arr[6]);
}

 int main() {
     // test 1
     CBPlusTree *tree1 = new CBPlusTree();
     int arr[100];
     cout << "Test1--------------------" << endl;
     cout << "Insert key value 0, 1, 2, ..., 29 to the B+ tree." << endl;
     for (int i = 0; i < 30; i++) {
         arr[i] = i;
         tree1->insert(i, arr[i]);
     }
     cout << "The minimum key value is : " << tree1->minimum() << endl;
     cout << "The maximum key value is : " << tree1->maximum() << endl;
     cout << "The predecessor of 20 is : " << tree1->predecessor(20) << endl;
     cout << "The successor   of 7 is : " << tree1->successor(7) << endl;
     
     
     // test 2
     CBPlusTree *tree2 = new CBPlusTree();
     cout << "\n" << "Test2--------------------" << endl;
     cout << "Insert key value 3,1,3,24,7,11,13,19,10,6 to the B+ tree." << endl;
     test2_insert(tree2);
     cout << "The minimum key value is : " << tree2->minimum() << endl;
     cout << "The maximum key value is : " << tree2->maximum() << endl;
     cout << "The predecessor of  7 is : " << tree2->predecessor(7) << endl;
     cout << "The successor   of 13 is : " << tree2->successor(13) << endl;
     cout << "The predecessor  of 1 is : ";
     tree2->predecessor(1);
     cout << "\nThe successor   of 24 is : ";
     tree2->successor(24);
     
     // test 3
     CBPlusTree *tree3 = new CBPlusTree();
     cout << "\n\n" << "Test3--------------------" << endl;
     cout << "Empty B+ tree." << endl;
     cout << "The minimum key value is : ";
     tree3->minimum();
     cout << "\nThe maximum key value is : ";
     tree3->maximum();
     cout << "\nThe predecessor  of 5 is : ";
     tree3->predecessor(5);
     cout << "\nThe successor   of 10 is : ";
     tree3->successor(10);
     cout << "\n";
 }

