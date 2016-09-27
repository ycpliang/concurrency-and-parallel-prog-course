//-----------------------------------------------------------------------------------
// TallyVotes Program implementation of TallyVotes using uOwnerLock and uCondLock
// to synchronized votes
//-----------------------------------------------------------------------------------

//includes
#include "q3tallyVotes.h"
#include "q3printer.h"

TallyVotes::~TallyVotes(){
	finish = 1;
	queueEmpty.signalBlock();
}


//-----------------------------------------------------------------------------------
// TallyVotes::TallyVotes Constructor
//-----------------------------------------------------------------------------------
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : finish(0),curMember(0), group(group),picOrStatue(0), printer(printer) {}


void TallyVotes::main(){
   int id;
   Tour ballot;
   while(true){
	if(idQueue.empty()){
		queueEmpty.wait();						
	}
	if(curMember == 0){
		picOrStatue = 0;
	}
	if(finish) break;
	curMember++;
	id = idQueue.front();
	idQueue.pop();
	ballot = TallyVotes::Tour(ballotQueue.front());
	ballotQueue.pop();
	printer.print(id, Voter::States::Vote, ballot); //print the voting for the voter

	//Add the vote to the group, subtract for Picture vote, Plus for Statue vote	
	if(ballot == Tour::Picture){
		--picOrStatue;
	}else{
		++picOrStatue;
	}

	printer.print(id, Voter::States::Block, curMember); //print the block 
	//check if all members voted; if not all members voted, block.
	if(curMember == group){
		printer.print(id, Voter::States::Complete); //print the complete statement
		tallyCond.signal();
	}
   }
}



//-----------------------------------------------------------------------------------
// TallyVotes::vote Voting routine return the result of group's decision of Tour
//-----------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	idQueue.push(id);
	ballotQueue.push(ballot);
	queueEmpty.signal();
	tallyCond.wait();	
	if(!tallyCond.empty()) tallyCond.signal();
	--curMember; //subtract to reset it to zero

	printer.print(id, Voter::States::Unblock, (curMember));
	
	//printer the finished result of voting
	printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
	
	//return the final tour decision
  	return (picOrStatue > 0) ? Tour::Statue : Tour::Picture;	
}

