#ifndef __Q2TALLYVOTES_H__
#define __Q2TALLYVOTES_H__

_Monitor Printer; //forward declaration for printer

#if defined( IMPLTYPE_MC )            // mutex/condition solution
class TallyVotes {
    uOwnerLock ownerLock; //the mutex lock
    uCondLock  tallyLock; //the condition lcok
    bool inuse = false; //boolean flag to stop barging
    uCondLock bLock; //barging lock (wait channel)
    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_BAR )        // barrier solution
// includes for this kind of vote-tallier
#include "uBarrier.h"

_Cormonitor TallyVotes : public uBarrier { 
#elif defined( IMPLTYPE_SEM )        // semaphore solution
// includes for this kind of vote-tallier
#include "uSemaphore.h"

class TallyVotes {
    // private declarations for this kind of vote-tallier
    uSemaphore ownerLock; //ownerLock or mutex lock
    uSemaphore tallyLock; //tallyLock similar to condLock
#else
    #error unsupported voter type
#endif
    // common declarations
  unsigned int curMember; //the number of members that have voted
  unsigned int group; //the size of the group
  int picOrStatue; //negative for picture, positive for Statue
  Printer & printer;
  public:                            // common interface
    TallyVotes( unsigned int group, Printer &printer );
    enum Tour { Picture, Statue };
    Tour vote( unsigned int id, Tour ballot );
};

#endif
