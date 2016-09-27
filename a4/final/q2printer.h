//----------------------------------------------------------
//Header file for the Monitor Printer
//----------------------------------------------------------

#ifndef __PRINTER_H__
#define __PRINTER_H__
//includes
#include <iostream>
#include "q2tallyVotes.h"
#include "q2voter.h"

_Task Voter; //forward declaration for voter

_Monitor Printer {   
  char * voteArray; //the state array
  int * resultArray; //stores the complimenting information to the state array Tour vote or number of blocked/unblocked
  unsigned int sizeOfGroup; //the number of voters in total
  _Mutex void printLine(bool); //helper routine to flush the result
  public:
    Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
    ~Printer();

};

#endif
