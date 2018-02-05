// testTree.cpp
//======================================================
// Programmer: Daniel P. Mullen
//
// Summary: This file is just a test suite for the tree
//          class
//
// Date Last Modified: 2017/12/03 (DPM) - File created and
//                                        finished.
//======================================================

//===Preprocessors=====
#include <iostream>
#include <cassert>
#include "constants.h"
#include "Node.h"
#include "Tree.h"

using namespace std;
//=====================

int main()
{
    //===TopText============================
    cout << "=====================" << endl;
    cout << "Tree Class Test Suite" << endl;
    cout << "=====================" << endl;
    //======================================

    //===TestDefaultCTOR====================
    {
        cout << "Testing Default CTOR..." << endl;
        // creates a tree with default values
        Tree testTree;

        // creates a pointer to the root
        Node* root = testTree.GetRoot();
        Node* rootP = root;

        assert(testTree.GetRoot() == rootP);
        assert(testTree.GetRoot() == root);
        assert(testTree.GetRoot()->GetText() == DEFAULT_TEXT);
        assert(testTree.GetRoot()->LChild() == 0);
        assert(testTree.GetRoot()->RChild() == 0);

        cout << "Default CTOR Works!" << endl;
        cout << "Get Root Method Works As Well!" << endl;
        cout << "-------------------" << endl;

    } // end test default CTOR
    //======================================

    //===TestKnownCTOR====================
    {
        cout << "Testing Known CTOR..." << endl;
        // creates a tree with assigned values
        Tree testTree(TREE_Q, Q_Yes, Q_No);

        assert(testTree.GetRoot()->GetText() == TREE_Q);
        assert(testTree.GetRoot()->LChild()->GetText() == Q_Yes);
        assert(testTree.GetRoot()->RChild()->GetText() == Q_No);

        cout << "Known CTOR Works!" << endl;
        cout << "-------------------" << endl;

    } // end Known CTOR test
    //======================================

    //===TestIsEmpty====================
    {
        cout << "Testing IsEmpty Method..." << endl;

        // creates a tree with assigned values
        Tree testNotEmptyTree(TREE_Q, Q_Yes, Q_No);

        assert(!testNotEmptyTree.IsEmpty());

        // creates tree with no children
        Tree testEmptyTree;

        assert(testEmptyTree.IsEmpty());

        delete(testNotEmptyTree.GetRoot()->LChild());
        delete(testNotEmptyTree.GetRoot()->RChild());

        testNotEmptyTree.GetRoot()->AppendLeft(0);
        testNotEmptyTree.GetRoot()->AppendRight(0);

        assert(testNotEmptyTree.IsEmpty());

        cout << "IsEmpty Method Works!" << endl;
        cout << "-------------------" << endl;

    } // end IsEmpty Test
    //======================================

    //===BottomText=========================
    cout << "=====================" << endl;
    cout << "End Test Suite" << endl;
    cout << "=====================" << endl;

    return 0;

} // end main