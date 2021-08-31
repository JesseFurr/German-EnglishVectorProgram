// Jesse Furr 8/2/2019 German/English dictionary vector program
#include <iostream>                // My friend asked me to make this program for him to help
#include <iomanip>                 // him learn German. 
#include <vector>                  //  
#include <iterator>                // 
#include <string>                  // 
#include <fstream>
#include <ctime>
#include <stdlib.h>
#include <algorithm>
#include <cctype>
using namespace std;
//function prtottypes
int menu1();
void addremove(vector<string>& engw, vector<string>& germw, vector<string>& gend);
void drawdict(vector<string>& engw, vector<string>& germw, vector<string>& gend);
void germantest(vector<string>& engw, vector<string>& germw, vector<string>& gend);
void englishtest(vector<string>& engw, vector<string>& germw, vector<string>& gend);

int main()
{
    fstream dictionary;            //Create filestream object
    int select1;                   //input for menu choice 1.   
    vector<string> englishw;              //Create 3 parallel vector arrays
    vector<string> germanw;               //to hold values for english,
    vector<string> gender;                //and german words with their genders

    cout << "\n       German Dictionary Program       " << endl;
    cout << "***************************************" << endl;
    cout << "\n\n This program allows the user to   " << endl;
    cout << "enter German words with their english  " << endl;
    cout << "translations as well as their gender   " << endl;
    cout << "specification and then tests the user. " << endl;
    char repeat = 'y';          //var to keep main switch repeating

    ifstream input_file1("gdictionary.txt");       //open filestream for input German
    if (input_file1) {                             //if file opened
        string line1;                              //create temp var to hold data from file.
        while (!input_file1.eof())                 //While not at the end of file
        {
            getline(input_file1, line1, '\n');     //Use getline to move data from input file object to line variable seperated by newline.
            germanw.push_back(line1);              //Use vector.push_back to add element from line1 to 
        }
        germanw.pop_back();                        //popback to remove element that is somehow getting added to the                                                    //vector arrays every program start 
    }
    input_file1.close();                           //close file
    ifstream input_file2("edictionary.txt");       //vector fill from fill and popback for english
    if (input_file2) {
        string line2;
        while (!input_file2.eof())
        {
            getline(input_file2, line2, '\n');
            englishw.push_back(line2);
        }
        englishw.pop_back();
    }
    input_file2.close();
    ifstream input_file3("gender.txt");            //vector fill from fill and popback for gender
    string line3;
    if (input_file3) {
        while (!input_file3.eof())
        {
            getline(input_file3, line3, '\n');
            gender.push_back(line3);
        }
        gender.pop_back();
    }
    input_file3.close();
    do {                                           //always on main switch menu loop       
        select1 = menu1();                         //function to display menu and take user input selection
        switch (select1) {
        case 1: {                //add/remove entries     
            addremove(englishw, germanw, gender);


            break;
        }
        case 2: {                //display dictionary                                              
            drawdict(englishw, germanw, gender);
        }
              break;
        case 3:                  //Tests
            int testmenu;        //var to hold test selection               
            cout << "\n****************************************" << endl;
            cout << "*                TESTS                 *" << endl;
            cout << "*              ---------               *" << endl;
            cout << "*  1. German Test: German words are    *" << endl;
            cout << "*  given and the user is asked for     *" << endl;
            cout << "*  gender specification and english    *" << endl;
            cout << "*  translation.                        *" << endl;
            cout << "*                                      *" << endl;
            cout << "*  2. English Test: English words are  *" << endl;
            cout << "*  given and the user is asked for     *" << endl;
            cout << "*  gender specification and german     *" << endl;
            cout << "*  translation.                        *" << endl;
            cout << "*                                      *" << endl;
            cout << "****************************************" << endl;
            cout << "Which test would you like to attempt?: ";
            cin >> testmenu;
            if (testmenu == 1 || testmenu == 2) {
                if (testmenu == 1) {           //german test
                    germantest(englishw, germanw, gender);   //call german test function passing vectors as parameters
                }
                else if (testmenu == 2) {
                    englishtest(englishw, germanw, gender);  //call English test function passing vectors as parameters
                }
            }
            else {
                break;
            }
            break;
        case 4:                 //exit
            exit(0);
            break;
        }
    } while (repeat == 'y');
}

void germantest(vector<string>& engw, vector<string>& germw, vector<string>& gend) {   //germantest function deffinition, accepting 3 vectors by referance for parameters
    system("CLS");                                                 //clear screan NO CHEATING!
    char again;                                                    //for do while loop     
    float score;                                                   //var to hold score
    do {
        cout << "\n German Test" << endl;
        auto seed = unsigned(time(0));                             //create random seed from clock
        srand(seed);                                               //set seed
        random_shuffle(engw.begin(), engw.end());                  //shuffle english vector
        srand(seed);
        random_shuffle(germw.begin(), germw.end());                  //shuffle german vector
        srand(seed);
        random_shuffle(gend.begin(), gend.end());                  //shuffle gender vector        
        double numquest;                                          //var to hold user input on number of questions for test
        if (size(germw) == 0) {                                   //make sure vector was filled
            cout << "There is no data yet within. Please fill dictionary first. ";
            break;
        }
        cout << "\nHow many entries would you like to be tested on?: " << endl;
        cout << "1 to " << size(germw) << ": ";                   //user can only enter max number of questions for num of elements in vector
        cin >> numquest;
        do {
            if (numquest > size(germw) || numquest < 0) {         //input validation
                cout << "Please enter value between 1 and " << size(germw) << ": ";
                cin >> numquest;
            }
        } while (numquest > size(germw) || numquest < 0);
        if (numquest < size(germw) || numquest >= 1) {             //if number of questions entered is less than the max size of the vector and greater than one
            double correctctr = 0;                                 //counter var for correctly answered questions           
            for (int i = 0; i < numquest; i++) {                   //counter loop, 2 questions per vector element                
                string tanswer, ganswer;                           //vars to hold anwsers            
                cout << "\n" << (i + 1) << ".       The German Word is        " << endl;
                cout << "\n" << setw(20) << right << germw[i] << endl;   //first parallel vect array german displayed
                cout << "************************************" << endl;;
                cout << "What is the gender specification? (Die, Der, Das?): ";          //gender specification question
                cin >> ganswer;
                if (ganswer == gend[i]) {                               //if answer is = to our 2nd gender parallel array
                    correctctr++;                                       //increment correct counter by 1
                    cout << "correct!" << endl;
                }
                else if (ganswer != gend[i]) {                          //if answer is not = to our 2nd gender parallel array

                    cout << "Incorrect." << endl;
                }
                cout << "What is the English Translation?: ";           //translation question
                cin >> tanswer;
                if (tanswer == engw[i]) {                               //if answer is = to our 3nd english parallel array
                    correctctr++;                                       //increment correct counter by 1
                    cout << "correct!" << endl;
                }
                else if (tanswer != engw[i]) {                          //if answer is not = to our 2nd gender parallel array
                    cout << "Incorrect." << endl;
                }
            }
            score = (correctctr / (numquest * 2) * 100);                 //calculate score
            cout << "\nYour score is " << setprecision(3) << score << "%." << endl;
            cout << "Would you like to run the German test again? Y or N: ";
            cin >> again;
        }
    } while (again == 'y' || again == 'Y');
}
void englishtest(vector<string>& engw, vector<string>& germw, vector<string>& gend) {  //see german test function
    system("CLS");
    char again;
    float score;
    do {
        cout << "\n English Test" << endl;
        auto seed = unsigned(time(0));
        srand(seed);
        random_shuffle(engw.begin(), engw.end());
        srand(seed);
        random_shuffle(germw.begin(), germw.end());
        srand(seed);
        random_shuffle(gend.begin(), gend.end());
        double numquest;
        if (size(engw) == 0) {
            cout << "There is no data yet within. Please fill dictionary first. ";
            break;
        }
        cout << "\nHow many entries would you like to be tested on?: " << endl;
        cout << "1 to " << size(engw) << ": ";

        cin >> numquest;
        do {
            if (numquest > size(engw) || numquest < 0) {
                cout << "Please enter value between 1 and " << size(germw) << ": ";
                cin >> numquest;
            }
        } while (numquest > size(engw) || numquest < 0);
        if (numquest < size(engw) || numquest >= 1) {
            double correctctr = 0;
            for (int i = 0; i < numquest; i++) {
                string tanswer, ganswer;
                cout << "\n" << (i + 1) << ".       The Engish Word is        " << endl;
                cout << "\n" << setw(20) << right << engw[i] << endl;
                cout << "************************************" << endl;;
                cout << "What is the German Translation?: ";
                cin >> tanswer;
                if (tanswer == germw[i]) {
                    correctctr++;
                    cout << "correct!" << endl;
                }
                else if (tanswer != germw[i]) {
                    cout << "Incorrect." << endl;
                }
                cout << "What is the gender specification?(Die, Der, Das?): ";
                cin >> ganswer;
                if (ganswer == gend[i]) {
                    correctctr++;
                    cout << "correct!" << endl;
                }
                else if (ganswer != gend[i]) {

                    cout << "Incorrect." << endl;
                }
            }
            score = (correctctr / (numquest * 2) * 100);
            cout << "\nYour score is " << setprecision(3) << score << "%." << endl;
            cout << "Would you like to run the English test again? Y or N: ";
            cin >> again;
        }
    } while (again == 'y' || again == 'Y');
}

void drawdict(vector<string>& engw, vector<string>& germw, vector<string>& gend) {   //draw dictionary function definition
    cout << "\n    GERMAN          GENDER         ENGLISH" << endl;
    cout << "******************************************" << endl;
    for (int i = 0; i < germw.size(); i++) {
        cout << setw(3) << left << (i + 1) << setw(16) << germw[i] << setw(6) << gend[i] << setw(16) << right << engw[i] << endl;
    }
}
void addremove(vector<string>& engw, vector<string>& germw, vector<string>& gend) {  //addremove function definition
    char again;
    do {                                                                 // loop1
        int choice;                                                      //user input choice variable       
        string eword, gword, gen;                                        //initialize 3 string holder variables for input
        cout << "\nWould you like to add (1) or remove (2) from the data base?: ";
        cin >> choice;
        do {                                                              //loop2
            if (choice < 1 || choice > 2) {                                  //input validation
                cout << "Please enter value 1 or 2: ";
                cin >> choice;
            }
        } while (choice < 1 || choice > 2);                               //loop2
        if (choice == 1) {                     //choice 1 input entry
            char again;
            do {                                                              //loop3
                cout << "\nEnter German word: ";
                cin >> gword;
                germw.push_back(gword);                      //push back user input within holder var to end of germanvector array
                cout << "Enter Gender female (F), male (M), neutral (N): ";
                cin >> gen;
                gend.push_back(gen);                         //push back user input within holder var to end of germanvector array
                cout << "Enter English word : ";
                cin >> eword;
                engw.push_back(eword);                       //push back user input within holder var to end of germanvector array                
                cout << "\nUpdating..." << endl;
                drawdict(engw, germw, gend);                 //display updated table
                cout << "\nEnter another Word?  Y or N: ";
                cin >> again;                               //loop
                ofstream output_file1("edictionary.txt");                             //open output file stream for english file
                ostream_iterator<string> output_iterator1(output_file1, "\n");        //create iterator for output file
                copy(engw.begin(), engw.end(), output_iterator1);                     //copy vector to output iterator
                output_file1.close();                                                 //close file stream
                ofstream output_file2("gdictionary.txt");                             //open output file stream for german file
                ostream_iterator<string> output_iterator2(output_file2, "\n");
                copy(germw.begin(), germw.end(), output_iterator2);
                output_file2.close();
                ofstream output_file3("gender.txt");                             //open output file stream for gender file
                ostream_iterator<string> output_iterator3(output_file3, "\n");        //create iterator for output file
                copy(gend.begin(), gend.end(), output_iterator3);                     //copy vector to output iterator
                output_file3.close();                                                 //close file stream
            } while (again == 'y' || again == 'Y');                    //loop3
        }
        else if (choice == 2) {                     //choice 2 remove entry                       
            drawdict(engw, germw, gend);            //call dictionary function, passing parameters of add remove to parameters of drawdict
            char isranged;             //char var to hold user input on ranged entry removal           
            char again;
            do {                      //loop4
                cout << "\nWould you like to delete a range of entries? Y or N: ";
                cin >> isranged;
                bool range = 0; //if ranged remove executes, bool range will change to 1, witch will skip non ranged removal below
                if (isranged == 'y' || isranged == 'Y') {                      //ranged removal
                    range = 1;                                                 //change range bool to 1
                    int entry1;
                    int entry2;
                    cout << "Enter first and last entry number of range to remove seperated by space. ex 3 10 (for 3 - 10) : ";
                    cin >> entry1 >> entry2;
                    entry1 = entry1 - 1;                                            //remove index                   
                    engw.erase(engw.begin() + entry1, engw.begin() + entry2);       //use public memeber function to erase a
                    germw.erase(germw.begin() + entry1, germw.begin() + entry2);    // range of entries from all 3 parallel arrays
                    gend.erase(gend.begin() + entry1, gend.begin() + entry2);
                    cout << "\nUpdating..." << endl;
                    drawdict(engw, germw, gend);
                    ofstream output_file1("edictionary.txt");                       //Update files. See lines 312-325 for more details
                    ostream_iterator<string> output_iterator1(output_file1, "\n");
                    copy(engw.begin(), engw.end(), output_iterator1);
                    output_file1.close();

                    ofstream output_file2("gdictionary.txt");
                    ostream_iterator<string> output_iterator2(output_file2, "\n");
                    copy(germw.begin(), germw.end(), output_iterator2);
                    output_file2.close();

                    ofstream output_file3("gender.txt");
                    ostream_iterator<string> output_iterator3(output_file3, "\n");
                    copy(gend.begin(), gend.end(), output_iterator3);
                    output_file3.close();
                }
                if (range == 0) {            //non ranged entry removal (same as above, just no range erase memeber function
                    int entry1;
                    cout << "\nWhich entry would you like to erase?: ";
                    cin >> entry1;
                    entry1 = entry1 - 1;
                    engw.erase(engw.begin() + entry1);
                    germw.erase(germw.begin() + entry1);
                    gend.erase(gend.begin() + entry1);
                    cout << "\nUpdating..." << endl;
                    drawdict(engw, germw, gend);
                    ofstream output_file1("edictionary.txt");
                    ostream_iterator<string> output_iterator1(output_file1, "\n");
                    copy(engw.begin(), engw.end(), output_iterator1);
                    output_file1.close();

                    ofstream output_file2("gdictionary.txt");
                    ostream_iterator<string> output_iterator2(output_file2, "\n");
                    copy(germw.begin(), germw.end(), output_iterator2);
                    output_file2.close();

                    ofstream output_file3("gender.txt");
                    ostream_iterator<string> output_iterator3(output_file3, "\n");
                    copy(gend.begin(), gend.end(), output_iterator3);
                    output_file3.close();
                }
                cout << "\nWould you like to remove another entry? Y or N: ";
                cin >> again;
            } while (again == 'y' || again == 'Y');                 //loop4
        }
        cout << "\nWould you like to edit any other entries? Y or N: ";
        cin >> again;
    } while (again == 'y' || again == 'Y');                  //loop1
}

int menu1() {                    //menu1 function definition
    int selection1;
    cout << "\n\n                 Menu                " << endl;
    cout << "***************************************" << endl;
    cout << "1. Add/Remove dictionary entries" << endl;
    cout << "2. Display Current Dictionary" << endl;
    cout << "3. Test" << endl;
    cout << "4. Exit\n" << endl;
    cin >> selection1;
    if (selection1 > 5 || selection1 < 0)         //input validation
    {
        cout << "Please enter value between 1 and 4: ";
        cin >> selection1;
        return selection1;
    }

    return selection1;
}




