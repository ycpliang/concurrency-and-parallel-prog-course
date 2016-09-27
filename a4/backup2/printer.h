#ifndef __PRINTER_H__
#define __PRINTER_H__
#include <iostream>
#include "q2tallyVotes.h"
#include "voter.h"

/*
#if defined( IMPLTYPE_MC )            // mutex/condition solution
// includes for this kind of vote-tallier
class TallyVotes;
#elif defined( IMPLTYPE_BAR )        // barrier solution
// includes for this kind of vote-tallier
_Cormonitor TallyVotes : public uBarrier;
#elif defined( IMPLTYPE_SEM )        // semaphore solution
// includes for this kind of vote-tallier
class TallyVotes;
#else
    #error unsupported voter type
#endif
*/
_Task Voter;

_Monitor Printer {    // chose one of the two kinds of type constructor
  char * voteArray;
  int * resultArray; 
  unsigned int sizeOfGroup;
  _Mutex void printLine(bool);
  public:
    Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
    ~Printer();

};

#endif
