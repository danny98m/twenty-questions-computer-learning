// testNode.cpp
//======================================================
// Programmer: Daniel P. Mullen
//
// Summary: This file is just a test suite for the node
//          class
//
// Date Last Modified: 2017/12/02 (DPM) - File created and
//                                        finished.
//======================================================

//===Preprocessors=====
#include <iostream>
#include <cassert>
#include "constants.h"
#include "Node.h"

using namespace std;
//=====================


int main()
{
    //===TopText============================
    cout << "==================" << endl;
    cout << "Node Class Testing" << endl;
    cout << "==================" << endl;
    cout << endl;
    //======================================

    //===DefaultCTORTest====================
    {
        cout << "Testing Default CTOR..." << endl;

        Node testNode1;       //creates test node

        assert(testNode1.GetText() == DEFAULT_TEXT);
        assert(testNode1.LChild() == 0);
        assert(testNode1.RChild() == 0);

        cout << "Default CTOR Okay!" << endl;
        cout << "-----------------------" << endl;

    } // end default CTOR test
    //======================================

    //===TextCTORTest=======================
    {
        cout << "Testing Text CTOR..." << endl;

        //creates test node with a message
        Node testNode1(TEST_TEXT);

        assert(testNode1.GetText() == TEST_TEXT);
        assert(testNode1.LChild() == 0);
        assert(testNode1.RChild() == 0);

        cout << "Text CTOR Okay!" << endl;
        cout << "-----------------------" << endl;

    } // end text ctor test
    //======================================

    //===CopyCTORTest=======================
    {
        cout << "Testing Copy CTOR..." << endl;

        //creates test node with a message
        Node testNode1(COPY_STR);
        //test node copied from testNode1
        Node testNode2(testNode1);

        assert(testNode2.GetText() == testNode1.GetText());
        assert(testNode2.LChild() == testNode1.LChild());
        assert(testNode2.RChild() == testNode1.RChild());

        testNode2.StoreText(NEWSTR);

        assert(testNode2.GetText() == NEWSTR);

        cout << "Copy CTOR Okay!" << endl;
        cout << "-----------------------" << endl;

    } // end copy CTOR test
    //======================================

    //===StoreTextTest======================
    {
        cout << "Testing StoreText Method..." << endl;

        //creates test node with default text
        Node testNode1;

        testNode1.StoreText(FIRST_STR);

        assert(testNode1.GetText() == FIRST_STR);

        testNode1.StoreText(SECOND_STR);

        assert(testNode1.GetText() == SECOND_STR);

        testNode1.StoreText(NULL_TEXT);

        assert(testNode1.GetText() == NULL_TEXT);

        cout << "Store Text Method Okay!" << endl;
        cout << "Get Text Method Works Too" << endl;
        cout << "-----------------------" << endl;

    } // end test StoreText
    //======================================

    //===TestAppend=========================
    {
        cout << "Testing Append Methods..." << endl;

        //creates first test node (essentially the root)
        Node testNodeRoot(ROOT_TEXT);

        //creates two child nodes
        Node testNodeLChild;
        Node testNodeRChild;

        //creates pointers to child nodes
        Node* testNodeLChildP;
        testNodeLChildP = &testNodeLChild;
        Node* testNodeRChildP;
        testNodeRChildP = &testNodeRChild;

        testNodeLChildP->StoreText(LCHILD_TEXT);
        testNodeRChildP->StoreText(RCHILD_TEXT);

        testNodeRoot.AppendLeft(testNodeLChildP);
        testNodeRoot.AppendRight(testNodeRChildP);


        assert(testNodeRoot.LChild()->GetText() == LCHILD_TEXT);
        assert(testNodeRoot.RChild()->GetText() == RCHILD_TEXT);

        cout << "Append Methods Work!" << endl;
        cout << "LChild and RChild Work As Well" << endl;
        cout << "-----------------------" << endl;

    } // end test Append
    //======================================

    //===TestIsLeaf=========================
    {
        cout << "Testing Is Leaf Method..." << endl;

        //creates first test node (essentially the root)
        Node testNodeRoot(ROOT_TEXT);

        //createst two child nodes
        Node testNodeLChild;
        Node testNodeRChild;

        //creates pointers to child nodes
        Node* testNodeLChildP;
        testNodeLChildP = &testNodeLChild;
        Node* testNodeRChildP;
        testNodeRChildP = &testNodeRChild;

        testNodeLChildP->StoreText(LCHILD_TEXT);
        testNodeRChildP->StoreText(RCHILD_TEXT);

        testNodeRoot.AppendLeft(testNodeLChildP);
        testNodeRoot.AppendRight(testNodeRChildP);

        assert(!testNodeRoot.IsLeaf());
        assert(testNodeLChild.IsLeaf());
        assert(testNodeRChild.IsLeaf());

        cout << "Is Leaf Method Work!" << endl;
        cout << "-----------------------" << endl;

    } // end test IsLeaf
    //======================================

    //===EndText============================
    cout << "-----------------------" << endl;
    cout << "End." << endl;
    //======================================

    return 0;

} // end main

//---------------------------------EOF------------------------------