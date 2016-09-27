#ifndef __VOTER_H__
#define __VOTER_H__
#include "MPRNG2.h"
#include "q2tallyVotes.h"
//#include "printer.h"

_Monitor printer;
extern MPRNG randomK;

_Task Voter {
  unsigned int id;
  TallyVotes & voteTallier;
  Printer & printer;
  void main();
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U',
                   Complete = 'C', Finished = 'F' };
    Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer ):
	id(id), voteTallier(voteTallier), printer(printer) {}
};


#endif
