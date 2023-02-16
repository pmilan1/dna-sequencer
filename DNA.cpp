//Title: DNA.cpp 
//Author: Milan Parmar
//Date: 4/3/2021
//Description: This is part of the DNA project in CMSC 202 @ UMBC

#include "DNA.h"
using namespace std;

  // Name: DNA() - Default Constructor
  // Desc: Used to build a new DNA sequence
  // Preconditions: None
  // Postconditions: Creates a new DNA where m_head and m_tail point to nullptr
DNA::DNA() {
    m_name = ""; //Name of the DNA (suspect or evidence)
    m_head = nullptr; //Front of the DNA
    m_tail = nullptr; //End of the DNA
    m_size = 0; //Total size of the DNA
}

  // Name: DNA(string) - Overloaded Constructor
  // Desc: Used to build a new DNA sequence with the name passed
  // Preconditions: None
  // Postconditions: Creates a new DNA where m_head and m_tail point to nullptr and name is passed
DNA::DNA(string name) {
    m_name = name;
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;    
}

  // Name: ~DNA() - Destructor
  // Desc: Used to destruct a strand of DNA
  // Preconditions: There is an existing DNA strand with at least one node
  // Postconditions: DNA is deallocated (including all dynamically allocated nodes)
  //                 to have no memory leaks!
DNA::~DNA() {
    Node *temp = m_head;

    while (m_head != nullptr) { // clears DNA sequence
        temp = m_head->m_next;
        delete m_head;
        m_head = temp;
    }
    m_head = nullptr;
    m_tail = nullptr;
    m_size = 0;
}

  // Name: InsertEnd
  // Preconditions: Takes in a char. Creates new node. 
  //                Requires a DNA strand
  // Postconditions: Adds the new node to the end of the DNA strand.
void DNA::InsertEnd(char data) {
    Node *temp = new Node();

    temp->m_data = data;
    temp->m_next = nullptr;

    if (m_head == nullptr) {
        m_head = temp;
	    m_tail = temp;
    }
    else {
        m_tail->m_next = temp;
        m_tail = temp;
    }
    m_size++;
}

  // Name: GetName()
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns m_name;
string DNA::GetName() {
    return m_name;
}

  // Name: GetSize()
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns m_size;
int DNA::GetSize() {
    return m_size;
}

  // Name: ReverseSequence
  // Preconditions: Reverses the DNA sequence
  // Postconditions: DNA sequence is reversed in place; nothing returned
void DNA::ReverseSequence() {
    Node *curr = m_head;
    Node *prev = nullptr;
    Node *next = nullptr;
    
    while (curr != nullptr) {
        next = curr->m_next;
        curr->m_next = prev;
        prev = curr;
        curr = next;    
    }
    m_tail = m_head;
    m_head = prev;
}

  // Name: CompareSequence
  // Preconditions: Requires two DNA sequence (suspect and passed evidence DNA)
  // Postconditions: Returns true if evidence sequence exists; else false
bool DNA::CompareSequence(DNA &evidence) {
    Node *evidenceTemp = evidence.m_head;
    Node *temp = m_head;
    int matchCounter = 0;
    int finalCount = 0;
    bool match = false;

    while (temp != nullptr && evidenceTemp != nullptr) {
        if (temp->m_next != nullptr && temp->m_next->m_next != nullptr && evidenceTemp != nullptr && evidenceTemp->m_next != nullptr // Checks for nullptr
            && evidenceTemp->m_next->m_next != nullptr) {
            if ((temp->m_data == temp->m_next->m_data && temp->m_next->m_data == temp->m_next->m_next->m_data) && (evidenceTemp->m_data != evidenceTemp->m_next->m_data
                || evidenceTemp->m_next->m_data != evidenceTemp->m_next->m_next->m_data)) { // Checks for matching repeated letters
                temp = temp->m_next;
            }
        }        
        if (temp->m_data == evidenceTemp->m_data) { //Moves evidence if chars match
            evidenceTemp = evidenceTemp->m_next;
            matchCounter++;

            if (matchCounter > finalCount) { // Updates finalCount to see how many letters in a row match 
                finalCount = matchCounter;
            }
        }
        else { // Resets evidenceTemp
            evidenceTemp = evidence.m_head;
            matchCounter = 0;
        }
        temp = temp->m_next;
    }
    if (finalCount == evidence.m_size) { // Determines if evidence matches
        match = true;
    }
    return match;   
}

  // Name: GetData
  // Desc: Returns the data at a specific location in the DNA sequence
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns a single char from a node
char DNA::GetData(int nodeNum) {
    Node *curr = m_head;
    char output = 'n';

    int nodeCounter = 0;

    while (curr != nullptr && nodeCounter <= nodeNum) {
        if (nodeCounter == nodeNum) {
            return curr->m_data;
        }
        curr = curr->m_next;
        nodeCounter++;
    }
    return output;
}

  // Name: operator<<
  // Desc: Overloaded << operator to return ostream from DNA
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns ostream populated from each node
ostream &operator<< (ostream &output, DNA &myDNA) {
    Node *temp = myDNA.m_head;

    while (temp != nullptr) {
        output << temp->m_data << "->";
        temp = temp->m_next;
    }
    return output;
}