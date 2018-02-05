// main.cpp
//=====================================================================
// Programmer: Daniel P. Mullen
//
// Summary: This program is a question game where the computer attempts
//          to guess what the user is thinking from eliminating options
//          based on user response to questions. If the computer is
//          defeated it then learns what the user was thinking and a
//          question is added to include that thought in the next game.
//
// Date Last Modified:
//      2017/12/3 (DPM) - File created. Created tree with custom root.
//                        Created functions to playGame, playAgain, and
//                        get user input to test if answerIsYes. Still
//                        does not add new questions correctly (I think I
//                        am causing a memory leak somewhere). Also horrid
//                        documentation.
//      2017/12/4 (DPM) - Got adding new questions and answers working. Fixed
//                        memory leak. Can now save game, load game, or create
//                        a whole new game. Still pretty bad documentation though.
//      2017/12/5 (DPM) - Created some new functions for the sake of prettier code.
//                        Made much better documentation, removed some unused variables.
//======================================================================
//----------------------------------------------------------------------
//===I/O================================================================
// Input: Strings in response to prompted questions from stdin(keyboard)
//        using getline(cin).
//
// Output: Prompts mostly asking for y or n responses to stdout(console)
//======================================================================

//===Preprocessors===============
#include <iostream>
#include "Node.h"
#include "Tree.h"
#include <algorithm>

using namespace std;
//===============================




int main()
{
    //===Function Declarations============================================================
    void playGame(/*in*/ Node* currP, /*inout*/ Tree &T, /*inout*/ string &outputFileName);
    void print_GameHeader ();
    bool answerIsYes();
    bool playAgain();
    //====================================================================================

    // loadFile set default to InstrumentGame.txt
    string loadFile = "InstrumentGame.txt";

    // output set to input by default
    string outputFileName = loadFile;

    Tree questionTree;         // tree to hold all the questions
    Node* currP;            // pointer to current node

    //===WantToPlayInstrumentGame?===============
    print_GameHeader();

    if (answerIsYes())
    {
        loadFile = "InstrumentGame.txt";
        outputFileName = loadFile;
    } // end if
    //============================================

    //no? Well How About....======================
    else
    {
        //===CreateANewGame?=========================================================
        cout << "Would you like to create a new game? (Y or N)" << endl;
        if (answerIsYes())
        {
            // assign name to a new file for a new game
            cout << "Please enter the desired file name for your game including file extension" << endl;
            getline(cin, loadFile);
            outputFileName = loadFile;   // change outputFileName to same as loadFile (input)

            // create first question
            cout << "What is your first question?" << endl;
            string firstQuestion;
            getline(cin, firstQuestion);
            questionTree.GetRoot()->StoreText(firstQuestion);

            // logs an answer to the question
            cout << "Now enter something that ANSWERS the question" << endl;
            string yesToQ;
            getline(cin, yesToQ);
            questionTree.GetRoot()->AppendLeft(new Node(yesToQ));

            // logs something that doesn't answer the question
            cout << "Now enter something that DOES NOT ANSWER the question" << endl;
            string noToQ;
            getline(cin, noToQ);
            questionTree.GetRoot()->AppendRight(new Node(noToQ));

            // saves root question
            questionTree.SaveTreeToFile(outputFileName);

            // proceed to playing new game
            cout << "New game created" << endl;
            cout << "Launching new game..." << endl;

        } // end if
        //============================================================================

        //===LoadAGame================================================================
        else
        {
            cout << "Enter the name of the file (including file extension) to load game" << endl;
            getline(cin, loadFile);
            outputFileName = loadFile;

        } // end else
        //=============================================================================

    } // end else


    //===PlayingTheGame=====================================
    do
    {
        questionTree.ReadTreeFromFile(loadFile); // read tree

        currP = questionTree.GetRoot();          // set current node to root

        playGame(currP, questionTree, outputFileName);

    } while (playAgain()); // so long as playAgain == true
    //===GameFinished========================================

    // Game done and not playing again
    cout << "Bye Bye!" << endl;


    return 0;

} // end main

//===FUNCTIONS============================================================

//------------------------------
// print_GameHeader
//---------------------------------
void print_GameHeader()
{
    cout << "WELCOME TO 20 QUESTIONS" << endl;
    cout << "=======================" << endl;
    cout << "Would you like to play my instrument game? (Y or N)" << endl;

} // end print_GameHeader
//-----------------------------------------------------

//------------------------------
// answerIsYes
//----------------------------------
// Post: returns true or false based on if input answer is y or n
bool answerIsYes()
{
    string answer;  // string answer to store input

    getline(cin, answer);  // get and store user input
    // transform user input to lowercase
    transform(answer.begin(), answer.end(), answer.begin(), ::tolower);

    if(answer[FIRST_LETTER] == 'y')
    {
        return true;
    } // if y return true

    else
    {
        return false;
    } // otherwise false

} // end answerIsYes
//------------------------------------

//--------------------------------
// playAgain
//------------------------------------
// Post: returns true or false depening on user input
bool playAgain ()
{
    // ask question.....
    cout << "Would you like to play again? (Y or N): " << endl;

    // return bool based on answer
    return answerIsYes();

} // end playAgain
//-------------------------------------------

//-------------------------------------------
// playGame
//-------------------------------------------------
// Pre: assigned node pointer, assigned tree passed by reference, assigned file name for output
// Post: Game is played. Tree is possibly changed with new nodes added.
void playGame(/*in*/ Node* currP, /*inout*/ Tree &T, /*inout*/ string& outputFileName)
{
    short questionCounter = COUNTER_START;  // keeps track of how many questions asked
    currP = T.GetRoot();                    // point to current node

    while (!currP->IsLeaf())  // while currP lchild&&rchild != 0
    {
        cout << "Question #" << questionCounter << ": " << currP->GetText() << endl;

        if (answerIsYes())
        {
            currP = currP->LChild();
        } // move currP to LChild

        else
        {
            currP = currP->RChild();
        } // move currP to RChild

        questionCounter++; // increment

    } // end while

    //===ComputerGuess============================================
    cout << "You are thinking of a " << currP->GetText() << endl;
    cout << "Am I right?";
    //============================================================

    if (answerIsYes())
    {
        cout << "I win! Better luck next time!" << endl << endl;
        cout << "Would you like to save this game? (Y or N)" << endl;

        if (answerIsYes())
        {
            T.SaveTreeToFile(outputFileName);
        } // file saved

        else
        {
            cout << "Not saved" << endl;
        } // file not saved

    } // if answerIsYes

    else
    {
        // receive new thought
        string temp;
        cout << "What were you thinking of?" << endl;
        string userThought;
        getline(cin, userThought);

        // receive new question
        cout << "What question would give a yes?" << endl;
        string userQuestion;
        getline(cin, userQuestion);

        //===HelpfulDebugCOUTS===============================================================
        //cout << "THIS IS CURRP: " << currP->GetText() << endl;
        //cout << "THIS IS CURRP RCHILD: " << currP->RChild()->GetText() << endl;
        //cout << "THIS IS CURRP LCHILD: " << currP->LChild() << endl;
        //===EndDebug=========================================================================

        //===NewQuestionAndAnswer=============================================================
        temp = currP->GetText(); // store current nodes text into temp
        currP->StoreText(userQuestion); // put new question into the current node

        currP->AppendRight(new Node(temp)); // attach node to right of currP with temp
        currP->AppendLeft(new Node(userThought)); // attach node to left of currP with new thought
        //====================================================================================

        cout << "Would you like to save this game? (Y or N)" << endl;
        if (answerIsYes())
        {
            T.SaveTreeToFile(outputFileName);
        } // end if

        else
        {
            cout << "Not saved" << endl;
        } // end else

    } // end else

} // end playGame
//------------------------------------------------------------

//--------------------------EOF-------------------------------