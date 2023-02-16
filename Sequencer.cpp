//Title: Sequencer.cpp 
//Author: Milan Parmar
//Date: 4/3/2021
//Description: This is part of the DNA project in CMSC 202 @ UMBC

#include "Sequencer.h"
using namespace std;

  // Name: Sequencer (constructor)
  // Desc: Creates a Sequencer to hold multiple DNA strands from a file
  // Preconditions:  None
  // Postconditions: A sequencer created to populate m_suspects and m_evidence
Sequencer::Sequencer(string fileName) {
    m_fileName = fileName; //File to read in
    ReadFile(); // Reads in the DNA strands
    MainMenu(); // Shows main interaction menu
}

  // Name:  Sequencer (destructor)
  // Desc: Deallocates all dynamic aspects of a Sequencer
  // Preconditions: There is an existing DNA strand (linked list)
  // Postconditions: All vectors are cleared of DNA strands
Sequencer::~Sequencer() {
    cout << "DNA removed from memory" << endl;
    cout << "Deleting Suspects" << endl;
    for (unsigned int i = 0; i < m_suspects.size(); i++) { // Deallocates m_suspects
        delete m_suspects[i];
    }
    cout << "Deleting Evidence" << endl;
    for (unsigned int x = 0; x < m_evidence.size(); x++) { // Deallocates m_evidence
        delete m_evidence[x];
    }
}

  // Name:  DisplayStrands
  // Desc: Displays each strand in both m_suspects and m_evidence
  // Preconditions: At least one linked list is in either m_suspects or m_evidence
  // Postconditions: Displays DNA strand from one of the vectors
void Sequencer::DisplayStrands() {
    cout << endl;
    for (unsigned int i = 0; i < m_suspects.size(); i++) { // Displays m_suspects strands
        cout << "Suspect " << i + 1 << endl;
	    cout << *m_suspects[i] << "END" << endl;
    }
    for (unsigned int i = 0; i < m_evidence.size(); i++) { // Displays m_evidence strands
        cout << "Evidence " << i + 1 << endl;
        cout << *m_evidence[i] << "END" << endl;
    }
    MainMenu();
}

  // Name:  ReadFile
  // Desc: Reads in a file that has the name on one line then the sequence on the next
  //       All sequences will be an indeterminate length. There are an indeterminate number of
  //       sequences in a file. Hint: Read in the entire sequence into a string then go char
  //       by char until you hit a new line break. Then insert to the correct vector
  // Preconditions: Valid file name of characters (Either A, T, G, or C)
  // Postconditions: Populates each DNA strand and puts in either m_suspects or m_evidence
void Sequencer::ReadFile() {
    string dummyString;
    string line;
    const char DELIMITER = ',';
    int dnaCount = 0;
    int strands = 0;
    bool suspect = false;

    ifstream myfile(m_fileName); // opens file
    if (myfile.is_open()) {
        cout << "Opened File" << endl;

        while (getline(myfile, line)) {
            if (line[0] == 'S') { // Decides where to put the DNA strand
                suspect = true;
                dnaCount++;
            }
            else if (line[0] == 'E') {
                suspect = false;
                dnaCount++;
            }
            DNA *newDNA = new DNA(line); // New DNA object

            getline(myfile, line); // Reads in DNA strand
            strands = line.size();

            for (int i = 0; i < strands; i++) { // Goes through each character and uses InsertEnd to add to DNA linked list
                if (line[i] != DELIMITER) {
                    newDNA->InsertEnd(line[i]);
                }
            }
            if (suspect == true) { // Uses suspect bool to determine where to put DNA object
                m_suspects.push_back(newDNA);
            }
            else {
                m_evidence.push_back(newDNA);
            }
        }
    }
    else {
        cout << "ERROR OPENING FILE" << endl;
    }
    myfile.close();

    cout << dnaCount << " strands loaded." << endl;
}

  // Name:  MainMenu
  // Desc: Displays the main menu and manages exiting
  // Preconditions: Populated m_suspects and m_evidence
  // Postconditions: None
void Sequencer::MainMenu() {
    int choice = 0;
    
    cout << endl;
    cout << "What would you like to do?" << endl; // Prompts user for input
    cout << "1. Display Strand" << endl << "2. Reverse Sequence" << endl << "3. Check Suspects" << endl << "4. Exit" << endl;
    cin >> choice;
    while (choice > 4 || choice < 1) {
        cout << "Invalid number, try again (between 1-4): ";
        cout << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> choice;
    }

    if (choice == 1) {
        DisplayStrands();
    }
    else if (choice == 2) {
        ReverseSequence();
    }
    else if (choice == 3) {
        CheckSuspects();
    }
}

  // Name:  CheckSuspects
  // Desc: Iterates through each DNA strand in m_suspects to see if there is a match from
  //       m_evidence. Displays each suspect strand where the evidence matches
  // Preconditions: Populated m_suspects and m_evidence
  // Postconditions: Displays each suspect that has a match
void Sequencer::CheckSuspects() {
    bool verify = false;
    
    cout << endl;
    cout << "Checking all suspects vs evidence" << endl;

    for (unsigned int i = 0; i < m_suspects.size(); i++) { // iterates through suspects
        int matches = 0; // used to tell how many evidence pieces the suspect matches
        for (unsigned int j = 0; j < m_evidence.size(); j++) { // iterates through evidence to see any matches
            verify = m_suspects[i]->CompareSequence(*m_evidence[j]);

            if (verify == true) {
	            cout << "Suspect " << i + 1 << " matches Evidence " << j + 1 << endl;
                matches++;
            }
            else {
	            cout << "Suspect " << i + 1 << " does NOT match Evidence " << j + 1 << endl;
            }
        }
        if (matches == int(m_evidence.size())) {
            cout << "Suspect " << i + 1 << " matches ALL evidence!" << endl;
        }
    }
    MainMenu();
}

  // Name: ReverseSequence
  // Desc: User chooses a sequence from m_suspects or m_evidence and the sequence is reversed
  // Preconditions: Populated m_suspects and m_evidence
  // Postconditions: Reverses a specific sequence replacing in place
void Sequencer::ReverseSequence() {
    int choice = 0;
    int choice2 = 0;
    
    cout << endl;
    cout << "Which type of sequence to reverse?" << endl << "1. Suspect" << endl << "2. Evidence" << endl;
    cin >> choice;
    while (choice > 2 || choice < 1) {
        cout << "Invalid number, try again (1 or 2): ";
        cout << endl;
        cin.clear();
        cin.ignore(256, '\n');
        cin >> choice;
    }    

    if (choice == 1) {
        if (m_suspects.size() > 1) {
            cout << "Choose 1 - " << m_suspects.size() << endl;
            cin >> choice2;
            while (choice > int(m_suspects.size()) || choice < 1) {
                cout << "Invalid number, try again (between 1-" << m_suspects.size() << ")";
                cout << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cin >> choice2;       
            }

            cout << "choice: " << choice << endl;
            m_suspects[choice2 - 1]->ReverseSequence();
            cout << endl;
            cout << "Done reversing Suspect " << choice2 << "'s sequence" << endl;
        }
        else {
            cout << endl;
            m_suspects[0]->ReverseSequence();
            cout << "Done reversing Suspect " << 1 << "'s sequence" << endl;            
        }
    }
    else {
        if (m_evidence.size() > 1) {
            cout << "Choose 1 - " << m_evidence.size() << endl;
            cin >> choice2;
            while (choice > int(m_evidence.size()) || choice < 1) {
                cout << "Invalid number, try again (between 1-" << m_evidence.size() << ")";
                cout << endl;
                cin.clear();
                cin.ignore(256, '\n');
                cin >> choice2;       
            }            
            m_evidence[choice2 - 1]->ReverseSequence();
            cout << "Done reversing Evidence " << choice2 << "'s sequence" << endl;
        }
        else {
            m_evidence[0]->ReverseSequence();
            cout << "Done reversing Evidence " << 1 << "'s sequence" << endl;
        }
    }
    MainMenu();
}