//-----------------------------------------------------------------------------------
// TallyVotes Program implementation of TallyVotes using Barrier to synchronized votes 
//-----------------------------------------------------------------------------------

//includes
#include "q2tallyVotes.h"
#include "q2printer.h"


//-----------------------------------------------------------------------------------
// TallyVotes::TallyVotes Constructor 
//-----------------------------------------------------------------------------------
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : uBarrier(group), curMember(0), group(group),picOrStatue(0), printer(printer) {}


//-----------------------------------------------------------------------------------
// TallyVotes::vote Voting routine return the result of group's decision of Tour 
//-----------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	//reset the groupVoteTally
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

	//check if all members voted
	if(curMember == group){
		printer.print(id, Voter::States::Complete);
		uBarrier::block(); //last person to block which release the other tasks
	}else{
		printer.print(id, Voter::States::Block, curMember);
		uBarrier::block(); //block and wait for all the task to vote
		printer.print(id, Voter::States::Unblock, (curMember - 1)); //print unblock statement
	}
	--curMember; //subtract to reset it to zero

	//print the finished result of voting
	printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) ); 
	
	//return the final tour decision
  	return (picOrStatue > 0) ? Tour::Statue : Tour::Picture;
}

