
/*-----------------------------------------------------------

Program: Unscrambler

Fall 2021. 

Description:
Unscramble a board containing randomly generated words which have been scrambled. You get to pick the difficulty, by choosing how big the board is and how many times it is initally scrambled. If you manage to rotate it back in place, you win!

------------------------------------------------------------*/


#include <iostream> //to print out statements
#include <fstream> // to open and close files
#include <vector> // to use vectors
#include <cassert> //to check if file opened
#include <cctype> //to make user input uppercase
#include <string> //to use string functions
using namespace std;


void readDictionaryFile(vector <string> &dictionaryFile);
void getRandomWords(int boardSize, vector <string> &dictionaryFile, vector <string> &randomWords);
void getRandomChars(vector <string> randomWords, vector <char> &randomChars, int boardSize);
void printBoard(int boardSize, vector <char> randomChars, vector <char> completedBoard, char option2);
void scrambleRow(int boardSize, vector <string> randomWords, vector <char> &randomChars);
void scrambleColumn(int boardSize, vector <char> &randomChars);
void displayCurrentChars(vector <char> randomChars);
void printCompletedBoard(int boardSize, vector <char> randomChars);
void scramble(int numTimesScrambled, int boardSize, vector <char> &randomChars);
void spellWords(vector <string> randomWords);
void scrambleColumn(int boardSize, vector <char> &randomChars);
void scrambleRow(int boardSize, vector <char> &randomChars);
void printMenuR(int boardSize);
void displayMenuR(int boardSize, vector <string> randomWords, vector <char> &randomChars, vector <char> completedBoard, vector <char> boardAfterScramble, vector <string> dictionaryFile, int numTimesScrambled, bool &win, char option2);
void scrambleSelectedRow(int boardSize, vector <char> &randomChars, int selectRow, int numTimesRotate);
void boardSpecializationMenus(int boardSize, vector <string> randomWords, vector <char> &randomChars, vector <char> &completedBoard, vector <char> &boardAfterScramble, vector <string> &dictionaryFile, int &numTimesScrambled, bool &win);
void scrambleSelectedColumn(int boardSize, vector <char> &randomChars, int SelectColumn, int numTimesRotate);
void checkForWin(vector <char> completedBoard, vector <char> randomChars, bool &win);
string printTheseWords();


int main() {
    srand(1);   //used to seed random number generators
    bool win = false;   //so we can keep prompting user thru while loop until win = true
    vector <string> dictionaryFile;     //vector containing words from dictionary file
    vector <string> randomWords;        //vector containing randomly found words that can fit on board
    vector <char> randomChars;      //vector containing each char of randomWords, along with needed spaces
    int numTimesScrambled = 0;      // the number of times the user wants the board to be scrambled
    vector <char> completedBoard;   //vector containing the randomChars chars of what the completed board should look like
    vector <char> boardAfterScramble; //vector containing the randomChars chars of what the board looked like after it was scrambled, but before it was rotated
    char option2 = 'b';   // the char containing the users input when they are selecting what to do to the board (rotating, restarting, generating new board, etc)

    cout << "Program 5: Unscrambler\nCS 141, Fall 2021, UIC\n"
            "You will be presented with a board that is filled with scrambled words. Rotate the rows and columns\n"
            "to get the words displayed in the right order.\n\n";

    readDictionaryFile(dictionaryFile);
    cout << dictionaryFile.size() << " words have been read in from the dictionary." << endl << endl;
    char option = 'a';
    cout << "Enter Q to quit or B to begin:  ";
    cin >> option;
    option = toupper(option);

    while(!(win)){
        if(option == 'B'){
INSTRUCTOR
| 12/05 AT 3:53 PM
Please remember to include comments for code blocks within functions!

            int boardSize = 0;
            cout << "Choose your board size (must be a number greater than or equal to 4): ";
            cin >> boardSize;
            if(!(boardSize >= 4)){
                cout << "The board size must be at least 4. Retry. ";
                continue;
            } else {
                while(!(numTimesScrambled >= 1)) {
                    cout << "Choose the number of times you would like the board to be scrambled (must be a single number >= 1): ";
                    cin >> numTimesScrambled;
                    if (!(numTimesScrambled >= 1)) {
                        cout << "The number of times you select must be at least 1. Retry.\n";
                        continue;

                    } else if (numTimesScrambled >= 1) {
                        cout << "These are the words that you should try to spell out using the board, in order:\n"
                             << "   ";
                    }
                    getRandomWords(boardSize, dictionaryFile, randomWords);
                    cout << endl;
                    getRandomChars(randomWords, randomChars, boardSize);
                    completedBoard = randomChars;
                    scramble(numTimesScrambled, boardSize, randomChars);
                    boardAfterScramble = randomChars;
                    printBoard(boardSize, randomChars, completedBoard, option2);
                    displayCurrentChars(randomChars);
                    while(!(win)){
                      checkForWin(completedBoard, randomChars, win);
                      if(win == true){
                        break;
                      }
      
                      cout << "Enter one of the following: \n"
                      "   R to rotate a row or column, \n"
                      "   C to view what the completed board should look like, \n"
                      "   B to reset the board back to the beginning, \n"
                      "   G to generate a new board with new random words, \n"
                      "   S to have the computer automatically solve a board that you enter (5 points extra credit), \n"
                      "   Q to quit. "
                      "\nYour choice: ";
                      cin >> option2;
                      option2 = toupper(option2);
                      if(option2 == 'R'){
                         bool whil = false;
                         char rOrC = ' ';
                         int whichOne = 0;
                         int numTimesRotated = 0;
                         printMenuR(boardSize);
                         while(whil != true){
                              cin >> rOrC >> whichOne >> numTimesRotated;
                              rOrC = toupper(rOrC);
                               if(!(rOrC == 'R' || rOrC == 'C')){
                                  cout << "First input must be 'R' or 'C'. Try again.";
                                  printMenuR(boardSize);
                                  continue;
                                } else if((whichOne < 0 || whichOne > (boardSize-1))){
                                  cout << "Number must be between 0 and " << boardSize-1 << ". "
                                  "Try again.\n";
                                  printMenuR(boardSize);
                                  continue;
                                } else {

                                    if(rOrC == 'R'){
                                        scrambleSelectedRow(boardSize, randomChars, whichOne, numTimesRotated);
                                    } else if (rOrC == 'C'){
                                        scrambleSelectedColumn(boardSize, randomChars, whichOne, numTimesRotated);
                                    }
                                    if(!(completedBoard == randomChars)){
                                        spellWords(randomWords);
                                    }
                                    printBoard(boardSize, randomChars, completedBoard, option2);
                                    displayCurrentChars(randomChars);
                                    checkForWin(completedBoard, randomChars, win);
                                    if(win == true){
                                        break;
                                    }
                                    whil = true;
                                }
                          }
                          continue;
                      } else if(option2 == 'C'){
                          printCompletedBoard(boardSize, completedBoard);
                          displayCurrentChars(completedBoard);
                          spellWords(randomWords);
                          printBoard(boardSize, randomChars, completedBoard, option2);
                          displayCurrentChars(randomChars);
                          continue;
                      } else if(option2 == 'B'){
                          spellWords(randomWords);
                          randomChars = boardAfterScramble;
                          printBoard(boardSize, randomChars, completedBoard, option2);
                          displayCurrentChars(randomChars);
                          continue;
                      } else if(option2 == 'G'){
                          cout << printTheseWords();
                          dictionaryFile.clear();
                          randomWords.clear();
                          randomChars.clear();
                          completedBoard.clear();
                          boardAfterScramble.clear();
                          readDictionaryFile(dictionaryFile);
                          getRandomWords(boardSize, dictionaryFile, randomWords);
                          getRandomChars(randomWords, randomChars, boardSize);
                          completedBoard = randomChars;
                          scramble(numTimesScrambled, boardSize, randomChars);
                          boardAfterScramble = randomChars;
                          printBoard(boardSize, randomChars, completedBoard, option2);
                          displayCurrentChars(randomChars);
                          continue;
                      } else if(option2 == 'Q'){
                          cout << "Thank you for playing! \n"
                                  "Exiting program... ";
                          exit(0);
                      }
                      break;
                    }
                }
            }
          //if user picked q when they first ran the program, return 0
        } else {
            cout << "Thank you for playing!\n"
                 << "Exiting program...";
            return 0;
        }
    }
    cout << "Congratulations, you won! Thank you for playing!\n"
            "Exiting program...";
    return 0;
}// end main()


//go through the dictionary file and read its words into vector dictionaryFile
void readDictionaryFile(vector <string> &dictionaryFile){
    ifstream inStream;  // Declare an input stream for reading
    inStream.open("dictionary-3to5-letters.txt");  // Open misspelled words file
    assert( inStream.fail() == false);   // Ensure file open worked

    string line;  //stores each line in the file
    while ( inStream >> line){   //While there is another word to be read
        //getline(inStream,line);
        dictionaryFile.push_back(line);    // add misspelled word to misspelled words vector
    }
    inStream.close(); // Close the misspelled words file

}


//prints the current board by displaying randomChars
void printBoard(int boardSize, vector <char> randomChars, vector <char> completedBoard, char option2){
    bool checkWin = (completedBoard==randomChars);
    if(!(checkWin)){
        cout << "\nCurrent board:";
    }
    
    cout << endl;
    cout << "    ";
    for(int k = 0; k < boardSize; k++){
        cout << k << "   ";
    }
    cout << endl;

    cout << "   ";
    for(int i = 0; i < ((boardSize*4)-1); i++){
        cout << "-";
    }
    cout << endl;

    for(int i = 0; i < boardSize; i++){
        cout << i << " ";
        for(int j = 0; j < (boardSize); j++){
            cout << " | ";
            cout << randomChars.at((i*boardSize)+j);
        }
        cout << " | ";
        cout << endl;
        cout << "   ";
        for(int k = 0; k < ((boardSize*4)-1); k++){
            cout << "-";
        }
        cout << endl;
    }

}


//prints the version of the board, of size boardSize*boardSize and that is unscrambled, that the user must attempt to get, by printing randomChars
void printCompletedBoard(int boardSize, vector <char> randomChars){
    cout << "The completed board should look like:";
    cout << endl;
    cout << "    ";
    for(int k = 0; k < boardSize; k++){
        cout << k << "   ";
    }
    cout << endl;

    cout << "   ";
    for(int i = 0; i < ((boardSize*4)-1); i++){
        cout << "-";
    }
    cout << endl;

    for(int i = 0; i < boardSize; i++){
        cout << i << " ";
        for(int j = 0; j < (boardSize); j++){
            cout << " | ";
            cout << randomChars.at((i*boardSize)+j);
        }
        cout << " | ";
        cout << endl;
        cout << "   ";
        for(int k = 0; k < ((boardSize*4)-1); k++){
            cout << "-";
        }
        cout << endl;
    }

}


//go through dictionaryFile and get a random word. if that word can fit on the board along with a space, add it to the vector randomWords, then print out the words
void getRandomWords(int boardSize, vector <string> &dictionaryFile, vector <string> &randomWords){
  int total = (boardSize*boardSize)+1;
  int wordLength = 0;
    while((total) > 3){
        int wordIndex = rand() % dictionaryFile.size();
        wordLength = (dictionaryFile.at(wordIndex).length());
        if((total-wordLength) > 0){
            randomWords.push_back(dictionaryFile.at(wordIndex));
            total = total - wordLength - 1;
            wordLength = 0;
        } else {
            continue;
        }
    }
    
  for(int j = 0; j < randomWords.size(); j++){
    if(j < randomWords.size()-1){
        cout << randomWords.at(j) << ", ";
    } else {
        cout << randomWords.at(j) << ". ";
    }
  }


}


//get each character in randomWords and add it to randomChars, adding a space after each word, and adding
// additional spaces if randomChars is not the size of the board
void getRandomChars(vector <string> randomWords, vector <char> &randomChars, int boardSize){
  for(int i = 0; i < randomWords.size(); i++){
    for(int j = 0; j < randomWords.at(i).length(); j++){
        randomChars.push_back(randomWords.at(i).at(j));
    }
    randomChars.push_back(' ');
  }

  if(randomChars.size() < (boardSize*boardSize)){
      randomChars.push_back(' ');
  }

}


//scramble a random row in randomChars
void scrambleRow(int boardSize, vector <char> &randomChars){
    int sizePerSide = boardSize;
    int randomRow = rand() % boardSize;

    int lastIndex = (randomRow + 1) * sizePerSide - 1;
    char lastChar = randomChars.at( lastIndex);

    int i;
    for( i=lastIndex; i>lastIndex - sizePerSide + 1; i--) {
        randomChars.at( i) = randomChars.at( i-1);
    }

    randomChars.at( i) = lastChar;
}


//rotate a specific row (selectRow) and rotate it numTimesRotate times, then add new column to randomChars
void scrambleSelectedRow(int boardSize, vector <char> &randomChars, int selectRow, int numTimesRotate){
    int sizePerSide = boardSize;
    int randomRow = selectRow;
    if(randomChars.size() < (boardSize*boardSize)){
      randomChars.push_back(' ');
    }

    int startIndex = boardSize*randomRow;
    int lastIndex = (randomRow + 1) * sizePerSide - 1;

    int i;
    if(numTimesRotate < 0){
        for(int j = 0; j > numTimesRotate; j--){
          char firstChar = randomChars.at(startIndex);
          for( i=startIndex; i<startIndex + sizePerSide-1; i++) {
            randomChars.at( i) = randomChars.at( i+1);
          }
          randomChars.at(i) = firstChar;
        }
        int i;
    } else if(numTimesRotate > 0){
      for(int k = 0; k < numTimesRotate; k++){
        char lastChar = randomChars.at( lastIndex);
        for( i=lastIndex; i>lastIndex - sizePerSide + 1; i--) {
            randomChars.at( i) = randomChars.at( i-1);
        }
        randomChars.at(i) = lastChar;
      }
    }

}


//scramble a random column and then update randomChars with the new column
void scrambleColumn(int boardSize, vector <char> &randomChars){
    int randColumn;
    randColumn = rand() % boardSize;

    int lastIndex = randColumn + (boardSize * (boardSize-1));
    char lastChar = randomChars.at( lastIndex);

    int i;
    for( i=lastIndex; i>randColumn; i-=boardSize) {
        randomChars.at(i) = randomChars.at( i-boardSize);
    }

    randomChars.at(i) = lastChar;
}


//get a specific column chosen by user (selectColumn) and then rotate it numTimesRotate times, then update randomChars with the new column
void scrambleSelectedColumn(int boardSize, vector <char> &randomChars, int selectColumn, int numTimesRotate){
    int randColumn = selectColumn;

    int startIndex = randColumn;
    int lastIndex = randColumn + (boardSize * (boardSize-1));


    int i;
    if(numTimesRotate < 0){
        for(int j = 0; j > numTimesRotate; j--){
          char firstChar = randomChars.at(startIndex);
            for( i=startIndex; i<lastIndex; i+=boardSize) {
            randomChars.at(i) = randomChars.at( i+boardSize);
            }
            randomChars.at(i) = firstChar;
          
        }
        

    } else if(numTimesRotate > 0){
        for(int k = 0; k < numTimesRotate; k++){
          char lastChar = randomChars.at(lastIndex);
            for( i=lastIndex; i>randColumn; i-=boardSize) {
            randomChars.at(i) = randomChars.at( i-boardSize);
            }
            randomChars.at(i) = lastChar;
        }
        
    }

}


//display the current characters on the board by printing each char in randomChars
void displayCurrentChars(vector <char> randomChars){
    cout << "Current board words: ";
    for(int i = 0; i < randomChars.size(); i++){
        cout << randomChars.at(i);
    }
    cout << endl << endl;
}


//print out the words that the user must try to spell, by unscrambling the board, by printing randomWords
void spellWords(vector <string> randomWords){
    cout << "These are the words that you should try to spell out using the board, in order:\n"
         << "   ";
    for(int j = 0; j < randomWords.size(); j++){
        if(j < randomWords.size()-1){
            cout << randomWords.at(j) << ", ";
        } else {
            cout << randomWords.at(j) << ". ";
        }
    }

}


//scrambles a randomly generated row and column, by calling scrambleRow and scrambleColumn numTimesScrambled times
void scramble(int numTimesScrambled, int boardSize, vector <char> &randomChars){
    for(int i = 0; i < numTimesScrambled; i++){
        scrambleRow(boardSize, randomChars);
        scrambleColumn(boardSize, randomChars);
    }
}


//prints the menu explanation for option R
void printMenuR(int boardSize){
    cout << "Enter the row/column you would like to rotate, and the number of positions to rotate by.\n"
            "   This should be in the format of <R or C> <row/column number> <number of positions to rotate>, \n"
            "   where valid row and column numbers are between 0 and " << boardSize-1 << ",\n"
            "   E.g. R 0 1 would rotate the top row (row 0) of the board to the right once, \n"
            "        c 1 -2 would rotate the second column (col 1) of the board upwards twice.\n";
    cout << "Your choice:";
}


//displays the options you get when you select menu R (rotating). Rotates by calling scrambleSelectedRow or scrambleSelectColumn, and calls that rotating function numTimesScrambled. Updates randomChars with changed row/column, and checks if current board is the winning one by comparing randomChars to completedBoard, and updating win as needed.
void displayMenuR(int boardSize, vector <string> randomWords, vector <char> &randomChars, vector <char> completedBoard, vector <char> boardAfterScramble, vector <string> dictionaryFile, int numTimesScrambled, bool &win, char option2){
    bool toHaveAWhileLoop = false;
    char rOrC = ' ';  //char containing user input, can be either a R (row) or a C (column)
    int whichRowOrColumn = 0; //int containing users selection of which row or column they want to rotate
    int numTimesRotated = 0;  //int containing users input of how many times to rotate
    printMenuR(boardSize);
    while(toHaveAWhileLoop != true){
        cin >> rOrC >> whichRowOrColumn >> numTimesRotated;
        rOrC = toupper(rOrC);
        if(!(rOrC == 'R' || rOrC == 'C')){
            cout << "First input must be 'R' or 'C'. Try again.";
            printMenuR(boardSize);
            continue;
        } else if((whichRowOrColumn < 0 || whichRowOrColumn > (boardSize-1))){
            cout << "Number must be between 0 and " << boardSize-1 << ". "
                    "Try again.\n";
            printMenuR(boardSize);
            continue;
        } else {
            spellWords(randomWords);
            if(rOrC == 'R'){
                scrambleSelectedRow(boardSize, randomChars, whichRowOrColumn, numTimesRotated);
            } else if (rOrC == 'C'){
                scrambleSelectedColumn(boardSize, randomChars, whichRowOrColumn, numTimesRotated);
            }
            printBoard(boardSize, randomChars, completedBoard, option2);
            displayCurrentChars(randomChars);
            checkForWin(completedBoard, randomChars, win);
            if(win == true){
              break;
            }
        }

    }
}


//checks if the user has managed to unscramble the board successfully by comparing completedBoard to randomChars, and updating win as needed
void checkForWin(vector <char> completedBoard, vector <char> randomChars, bool &win){
    if(completedBoard == randomChars){
        win = true;
    }
}


//returns a string announcing these are the words the user must try to spell out on the board
string printTheseWordsString(){
   return "These are the words that you should try to spell out using the board, in order:\n";
}
 dictionary-3to5-letters.txt
