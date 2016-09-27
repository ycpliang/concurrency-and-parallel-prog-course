//-----------------------------------------------------------------------------------
// TallyVotes Program implementation of TallyVotes using binary Semaphores
// to synchronized votes
//-----------------------------------------------------------------------------------

//includes
#include "q2tallyVotes.h"
#include "printer.h"

//-----------------------------------------------------------------------------------
// TallyVotes::TallyVotes Constructor
//-----------------------------------------------------------------------------------
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : ownerLock(1), tallyLock(0), bLock(1), curMember(0), group(group),picOrStatue(0), printer(printer) {}


//-----------------------------------------------------------------------------------
// TallyVotes::vote Voting routine return the result of group's decision of Tour
//-----------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	//mutex lock acquire
	bLock.P();//barging lock
	ownerLock.P();
	//reset the groupvoteTally
	if(curMember == 0){
		picOrStatue = 0;
	}
	++curMember;  //increase the number of people who voted
	printer.print(id, Voter::States::Vote, ballot);//print the voting for the voter

	//Add the vote to the group, subtract for Picture vote, Plus for Statue vote   
	if(ballot == Tour::Picture){
		--picOrStatue;
	}else{
		++picOrStatue;
	}

	//check if all members voted; if not all members voted, block.
	if(curMember == group){
		//print the complete statment
		printer.print(id, Voter::States::Complete);
	}else{
		printer.print(id, Voter::States::Block, curMember); //print the block
		bLock.V(); //barging lock acquire
		ownerLock.V(); // release the mutex lock
		tallyLock.P(); //wait for all vote to be casted
		ownerLock.P(); //reacquire the mutex lock
		printer.print(id, Voter::States::Unblock, (curMember - 1)); //print the unblock
	}
	--curMember;//subtract to reset it to zero

	//release another voter in the group unless it is the last person
	//last member will exit if and release one vote
	if(curMember != 0){
		tallyLock.V();
	}else{
		bLock.V(); //release the barging lock on the last person
	}
	//release the mutex lock
	ownerLock.V();	  
		
	//print the finished result of voting
	printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
	
	//return the final tour decision
  	return (picOrStatue > 0) ? Tour::Statue : Tour::Picture;
}

