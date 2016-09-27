#ifndef __VOTER_H__
#define __VOTER_H__
#include "MPRNG2.h"
#include "q2tallyVotes.h"
//#include "printer.h"

_Monitor printer;

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
