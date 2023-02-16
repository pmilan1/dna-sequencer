#ifndef SEQUENCER_H
#define SEQUENCER_H

#include "DNA.h"

#include <fstream>
#include <string>
#include <iostream>
#include <cstdlib>
#include <vector>
using namespace std;

class Sequencer {
 public:
  // Name: Sequencer (constructor)
  // Desc: Creates a Sequencer to hold multiple DNA strands from a file
  // Preconditions:  None
  // Postconditions: A sequencer created to populate m_suspects and m_evidence
  Sequencer(string fileName);

  // Name:  Sequencer (destructor)
  // Desc: Deallocates all dynamic aspects of a Sequencer
  // Preconditions: There is an existing DNA strand (linked list)
  // Postconditions: All vectors are cleared of DNA strands
  ~Sequencer();

  // Name:  DisplayStrands
  // Desc: Displays each strand in both m_suspects and m_evidence
  // Preconditions: At least one linked list is in either m_suspects or m_evidence
  // Postconditions: Displays DNA strand from one of the vectors
  void DisplayStrands();

  // Name:  ReadFile
  // Desc: Reads in a file that has the name on one line then the sequence on the next
  //       All sequences will be an indeterminate length. There are an indeterminate number of
  //       sequences in a file. Hint: Read in the entire sequence into a string then go char
  //       by char until you hit a new line break. Then insert to the correct vector
  // Preconditions: Valid file name of characters (Either A, T, G, or C)
  // Postconditions: Populates each DNA strand and puts in either m_suspects or m_evidence
  void ReadFile();
  
  // Name:  MainMenu
  // Desc: Displays the main menu and manages exiting
  // Preconditions: Populated m_suspects and m_evidence
  // Postconditions: None
  void MainMenu();

  // Name:  CheckSuspects
  // Desc: Iterates through each DNA strand in m_suspects to see if there is a match from
  //       m_evidence. Displays each suspect strand where the evidence matches
  // Preconditions: Populated m_suspects and m_evidence
  // Postconditions: Displays each suspect that has a match
  void CheckSuspects();

  // Name: ReverseSequence
  // Desc: User chooses a sequence from m_suspects or m_evidence and the sequence is reversed
  // Preconditions: Populated m_suspects and m_evidence
  // Postconditions: Reverses a specific sequence replacing in place
  void ReverseSequence();
  
private:
  vector<DNA*> m_suspects; //Stores all DNA from the suspects
  vector<DNA*> m_evidence; //Stores all DNA from the evidence
  string m_fileName; //File to read in
};

#endif
