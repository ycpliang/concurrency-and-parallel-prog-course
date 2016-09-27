#ifndef __TALLYVOTES_H__
#define __TALLYVOTES_H__

_Monitor Printer;


#if defined( IMPLTYPE_EXT )            // external scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    _Mutex void wait();//whether to accept more vote routine call
#elif defined( IMPLTYPE_INT )        // internal scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    uCondition tallyLock;
    // private declarations for this kind of vote-tallier
#elif defined( IMPLTYPE_INTB )        // internal scheduling monitor solution with barging
// includes for this kind of vote-tallier
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    uCondition bench;                // only one condition variable (you may change the variable name)
    unsigned int ticket;
    unsigned int signalling;
    void wait();                    // barging version of wait
    void signalAll();                // unblock all waiting tasks
#elif defined( IMPLTYPE_AUTO )        // automatic-signal monitor solution
// includes for this kind of vote-tallier
#include "AutomaticSignal.h"
_Monitor TallyVotes {
    // private declarations for this kind of vote-tallier
    AUTOMATIC_SIGNAL
    bool next;
#elif defined( IMPLTYPE_TASK )        // internal/external scheduling task solution
#include <queue>
_Task TallyVotes {
    // private declarations for this kind of vote-tallier
public:
    ~TallyVotes();//destructor to terminate task
private:
    bool finish; //terminating task condition
    uCondition queueEmpty;//whether queue is empty
    uCondition tallyCond;//whether there is enough voter
    std::queue<int> idQueue;//id queue to store voter id
    std::queue<int> ballotQueue;//ballot queue with matching index as id
    void main();//main task function
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
