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
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : curMember(0), group(group),picOrStatue(0), printer(printer) {}

//-----------------------------------------------------------------------------------
// TallyVotes::vote Voting routine return the result of group's decision of Tour
//-----------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
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
		printer.print(id, Voter::States::Complete); //print the complete statement
		//if not all members voted
		wait();
	}else{
		printer.print(id, Voter::States::Block, curMember); //print the block 
		wait();	
		printer.print(id, Voter::States::Unblock, (curMember - 1));
	}
	--curMember; //subtract to reset it to zero
	
	//printer the finished result of voting
	printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
	
	//return the final tour decision
  	return (picOrStatue > 0) ? Tour::Statue : Tour::Picture;
}

void TallyVotes::wait(){
if(curMember < group) _Accept(vote);
}
