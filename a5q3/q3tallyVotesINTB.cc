//-----------------------------------------------------------------------------------
// TallyVotes Program implementation of TallyVotes using uOwnerLock and uCondLock
// to synchronized votes
//-----------------------------------------------------------------------------------

//includes
#include "q3tallyVotes.h"
#include "q3printer.h"


//-----------------------------------------------------------------------------------
// TallyVotes::TallyVotes Constructor
//-----------------------------------------------------------------------------------
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : ticket(0), signalling(1), curMember(0), group(group),picOrStatue(0), printer(printer) {}

//-----------------------------------------------------------------------------------
// TallyVotes::vote Voting routine return the result of group's decision of Tour
//-----------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	unsigned int myTicket = ++ticket;
	//reset the groupvoteTally
	while(true){
		if(myTicket <= group * signalling) break;
		else printer.print(id, Voter::States::Barging);
		wait();
	}
	if(curMember == 0){
		picOrStatue = 0;
	//	signalling += 1;
	}
	++curMember; //increase the number of people who voted
	//Add the vote to the group, subtract for Picture vote, Plus for Statue vote	
	if(ballot == Tour::Picture){
		--picOrStatue;
	}else{
		++picOrStatue;
	}
	
	printer.print(id, Voter::States::Vote, ballot); //print the voting for the voter
	if(curMember < group){
		printer.print(id, Voter::States::Block, curMember); //print the block 
		while(true){
			wait();
			if(myTicket <= group * signalling) break;
		}
		printer.print(id, Voter::States::Unblock, (curMember - 1));
	}else{
		printer.print(id, Voter::States::Complete); //print the complete statement
		signalAll();	
	//	signalling += 1;
	//if not all members voted
	}
	
	--curMember; //subtract to reset it to zero
	if(curMember == 0){
		signalling += 1;
		signalAll();
	}

	//printer the finished result of voting
	printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
	
	//return the final tour decision
	return (picOrStatue > 0) ? Tour::Statue : Tour::Picture;
}

void TallyVotes::wait() {
    bench.wait();                            // wait until signalled
    while ( rand() % 5 == 0 ) {                // multiple bargers allowed
        _Accept( vote ) {                    // accept barging callers
        } _Else {                            // do not wait if no callers
        } // _Accept
    } // while
}

void TallyVotes::signalAll() {                // also useful
    while ( ! bench.empty() ) bench.signal();        // drain the condition
}
