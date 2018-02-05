
#include <iostream>
#include <stdlib.h>

#include "Tree.h"

// need this for dtor
//=========================================
//pre: must send in an assigned node pointer (prefarably the root)
//post: memory freed up
void remove(Node* root)
{
    if (root == NULL) return;
    remove(root->LChild());
    remove(root->RChild());
    delete root;

}
//====================================

// ======================================================================
Tree::Tree()								//CTOR
//..........................................
//POST: new tree is created with a root
{
	this->root = new Node;
	
	// NOTE:  we must use the functions in the Node class to change things!
	root->AppendLeft( 0 );
	root->AppendRight( 0 );
}//CTOR


// ======================================================================
Tree::Tree(string questionText, string leftObject, string rightObject)
//..........................................
//POST: new tree is created with a root with known question and left/right objects
{
	this->root = new Node(questionText);
	
	// NOTE:  we must use the functions in the Node class to change things!
	root->AppendLeft( new Node(leftObject) );
	root->AppendRight( new Node(rightObject) );
}//CTOR


// ======================================================================
Tree::~Tree()								//DTOR
{
    remove(this->GetRoot());
} //DTOR
	
	
// ======================================================================
bool Tree::IsEmpty(void) const
//..........................................
//POST: RETURN == whether or not the root node has children
{
	return (root->RChild() == 0  &&  root->LChild() == 0);
}// IsEmpty


// ======================================================================
Node* Tree::GetRoot(void) const
//..........................................
//POST: RETURN == address of root node
{
	return root;
}// GetRoot

// ======================================================================
void Tree::SaveTreeToFile(string outputFileName)
//..........................................
//POST: entire tree saved to a file
{
    this->FOUT.clear();                         // reset the stream just in case
    this->FOUT.open( outputFileName.c_str() );	// attempt to OPEN output FILE

    // TRAP
    if (FOUT.fail() )			// but did open fail?
    {
        cout << "ERROR: output file called " << outputFileName
             << " didn't open " << endl << "Program terminating ..." << endl;
        // system("PAUSE");
        exit(-1);
    } // if

    // call recursive (private) method to do all the work
    this->RecursiveNodeSAVEtoFile( this->root );

    this->FOUT.close();

} // SaveTreeToFile


// ======================================================================
void Tree::RecursiveNodeSAVEtoFile(Node* pNode)
//..........................................
// PRE:  outstream is open and ready
//       Assigned(pNode) (any node in tree)
// POST: pNode and children written to file
{

    this->FOUT << pNode->GetText() << endl;

    if ( pNode->LChild() != 0 )
    {
        this->FOUT << 1 << endl;
        RecursiveNodeSAVEtoFile( pNode->LChild() );
    }
    else
        this->FOUT << 0 << endl;


    if ( pNode->RChild() != 0 )
    {
        this->FOUT << 1 << endl;
        RecursiveNodeSAVEtoFile( pNode->RChild() );
    }
    else
        this->FOUT << 0 << endl;

} // RecursiveNodeSAVEtoFile


// ======================================================================
void Tree::ReadTreeFromFile(string inputFileName)
//..........................................
//POST: entire tree loaded from a file
{
    this->FIN.clear();					// reset the stream just in case
    this->FIN.open( inputFileName.c_str() );		// attempt to OPEN output FILE

    // TRAP
    if (FIN.fail() )			// but did open fail?
    {
        cout << "ERROR: input file called " << inputFileName
             << " didn't open " << endl << "Program terminating ..." << endl;
        // system("PAUSE");
        exit(-1);
    } // if

    // call recursive (private) method to do all the work
    this->root = this->RecursiveNodeREADfromFile( );

    this->FIN.close();

} // ReadTreeFromFile



Node* Tree::RecursiveNodeREADfromFile( )
//..........................................
// PRE:  ifstream is open and ready
//       Assigned(pNode) (any node in tree)
// POST: pNode and children read from file and saved in Tree

{
    short marker;
    string theText;
    string flushRestOfLine;

    getline(this->FIN, theText );
    Node* pNode = new Node(theText);

    this->FIN >> marker;   getline(this->FIN, flushRestOfLine );
    if (marker == 1 )
        pNode->AppendLeft( RecursiveNodeREADfromFile() );
    else
        pNode->AppendLeft(0);

    this->FIN >> marker;   getline(this->FIN, flushRestOfLine );

    if (marker == 1 )
        pNode->AppendRight( RecursiveNodeREADfromFile() );
    else
        pNode->AppendRight(0);


    return pNode;

} // RecursiveNodeREADfromFile

