//-----------------------------------------------------------------------------------
// TallyVotes Program implementation of TallyVotes using uOwnerLock and uCondLock
// to synchronized votes
//-----------------------------------------------------------------------------------

//includes
#include "q2tallyVotes.h"
#include "printer.h"


//-----------------------------------------------------------------------------------
// TallyVotes::TallyVotes Constructor
//-----------------------------------------------------------------------------------
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : curMember(0), group(group),picOrStatue(0), printer(printer) {}

//-----------------------------------------------------------------------------------
// TallyVotes::vote Voting routine return the result of group's decision of Tour
//-----------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	//mutex lock acquire
	ownerLock.acquire();
	//check if barging queue is needed
	if(inuse){
		bLock.wait(ownerLock); //waiting queue
		if(bLock.empty()) inuse = 0;
	}
	//reset the groupvoteTally
	if(curMember == 0){
		picOrStatue = 0;
	}
	++curMember; //increase the number of people who voted
	printer.print(id, Voter::States::Vote, ballot); //print the voting for the voter

	//Add the vote to the group, subtract for Picture vote, Plus for Statue vote	
	if(ballot == Tour::Picture){
		--picOrStatue;
	}else{
		++picOrStatue;
	}

	//check if all members voted; if not all members voted, block.
	if(curMember == group){
		inuse = 1; //set inuse to be true, so new task wait in the barging lock
		printer.print(id, Voter::States::Complete); //print the complete statement
		//if not all members voted
	}else{
		printer.print(id, Voter::States::Block, curMember); //print the block 
		//signal a voter from the barging lock if it is not empty
		if(!bLock.empty()) bLock.signal(); 
		//block and wait
		tallyLock.wait(ownerLock);
		printer.print(id, Voter::States::Unblock, (curMember - 1));
	}
	--curMember; //subtract to reset it to zero
	//the last voter of the group does not wait and signals, another tallylock to wake up.
	//else if: if all the tallyLock have been signal, signal a voter from barging lock. 
	//If that is also empty, then set inuse to false so new task can go into tallyLock.
	if(!tallyLock.empty()){
		tallyLock.signal();
	}else if(!bLock.empty()){
		bLock.signal();
	}else{
		inuse = 0;
	}
	//mutex lock release
	ownerLock.release();
	
	//printer the finished result of voting
	printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
	
	//return the final tour decision
  	return (picOrStatue > 0) ? Tour::Statue : Tour::Picture;
}

