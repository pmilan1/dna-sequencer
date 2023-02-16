#ifndef DNA_H
#define DNA_H

#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>
using namespace std;

struct Node {
  char m_data;
  Node *m_next;
};

class DNA {
 public:

  // Name: DNA() - Default Constructor
  // Desc: Used to build a new DNA sequence
  // Preconditions: None
  // Postconditions: Creates a new DNA where m_head and m_tail point to nullptr
  DNA();

  // Name: DNA(string) - Overloaded Constructor
  // Desc: Used to build a new DNA sequence with the name passed
  // Preconditions: None
  // Postconditions: Creates a new DNA where m_head and m_tail point to nullptr and name is passed
  DNA(string);

  // Name: ~DNA() - Destructor
  // Desc: Used to destruct a strand of DNA
  // Preconditions: There is an existing DNA strand with at least one node
  // Postconditions: DNA is deallocated (including all dynamically allocated nodes)
  //                 to have no memory leaks!
 ~DNA();

  // Name: InsertEnd
  // Preconditions: Takes in a char. Creates new node. 
  //                Requires a DNA strand
  // Postconditions: Adds the new node to the end of the DNA strand.
  void InsertEnd(char data);

  // Name: GetName()
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns m_name;
  string GetName();

  // Name: GetSize()
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns m_size;
  int GetSize();

  // Name: ReverseSequence
  // Preconditions: Reverses the DNA sequence
  // Postconditions: DNA sequence is reversed in place; nothing returned
  void ReverseSequence();

  // Name: CompareSequence
  // Preconditions: Requires two DNA sequence (suspect and passed evidence DNA)
  // Postconditions: Returns true if evidence sequence exists; else false
  bool CompareSequence(DNA &evidence);

  // Name: GetData
  // Desc: Returns the data at a specific location in the DNA sequence
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns a single char from a node
  char GetData(int nodeNum);

  // Name: operator<<
  // Desc: Overloaded << operator to return ostream from DNA
  // Preconditions: Requires a DNA sequence
  // Postconditions: Returns ostream populated from each node
  friend ostream &operator<< (ostream &output, DNA &myDNA);
  
 private:
  string m_name; //Name of the DNA (suspect or evidence)
  Node *m_head; //Front of the DNA
  Node *m_tail; //End of the DNA
  int m_size; //Total size of the DNA
};

#endif