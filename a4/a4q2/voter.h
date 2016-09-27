//----------------------------------------------------------
//Header file for the Voter
//----------------------------------------------------------

#ifndef __VOTER_H__
#define __VOTER_H__
#include "MPRNG2.h"  //random generator
#include "q2tallyVotes.h" //tallyVote class

_Monitor printer;
extern MPRNG randomK;

_Task Voter {
  unsigned int id; //the voter id (unique)
  TallyVotes & voteTallier; //TallyVotes voteTallier
  Printer & printer; //printer reference 
  void main(); //main routine
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U',
                   Complete = 'C', Finished = 'F' };
    Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer ):
	id(id), voteTallier(voteTallier), printer(printer) {}
};


#endif
