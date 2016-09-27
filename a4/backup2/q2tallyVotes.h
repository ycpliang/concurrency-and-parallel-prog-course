#ifndef __Q2TALLYVOTES_H__
#define __Q2TALLYVOTES_H__

_Monitor Printer;
#if defined( IMPLTYPE_MC )            // mutex/condition solution
// includes for this kind of vote-tallier
class TallyVotes {
    uOwnerLock ownerLock;
    uCondLock  tallyLock;
    bool inuse = false;
    uCondLock bLock; //barging lock
    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_BAR )        // barrier solution
// includes for this kind of vote-tallier
_Cormonitor TallyVotes : public uBarrier {
    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_SEM )        // semaphore solution
// includes for this kind of vote-tallier
class TallyVotes {
//   BinSem lock(0);
    // private declarations for this kind of vote-tallier
#else
    #error unsupported voter type
#endif
    // common declarations
  unsigned int curMember;
  unsigned int group;
  int picOrStatue; //negative for picture, positive for Statue
  Printer & printer;
  public:                            // common interface
    TallyVotes( unsigned int group, Printer &printer ) : curMember(0), group(group),picOrStatue(0), printer(printer) {}
    enum Tour { Picture, Statue };
    Tour vote( unsigned int id, Tour ballot );
};

#endif
