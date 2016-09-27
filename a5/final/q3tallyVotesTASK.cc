//-----------------------------------------------------------------------------------
// TallyVotes Program implementation of TallyVotes using uOwnerLock and uCondLock
// to synchronized votes
//-----------------------------------------------------------------------------------

//includes
#include "q3tallyVotes.h"
#include "q3printer.h"

//-----------------------------------------------------------------------------------
// TallyVotes::TallyVotes Destructor
//-----------------------------------------------------------------------------------
TallyVotes::~TallyVotes(){
	finish = 1;//set finish to true
	queueEmpty.signalBlock();//block and signal main
}


//-----------------------------------------------------------------------------------
// TallyVotes::TallyVotes Constructor
//-----------------------------------------------------------------------------------
TallyVotes::TallyVotes( unsigned int group, Printer &printer ) : finish(0),curMember(0), group(group),picOrStatue(0), printer(printer) {}

//-----------------------------------------------------------------------------------
// TallyVotes::TallyVotes main routine
//-----------------------------------------------------------------------------------
void TallyVotes::main(){
   int id;
   Tour ballot;
   while(true){
	//if there is no item in queue 
	if(idQueue.empty()){
		//wait until queue has a item
		queueEmpty.wait();						
	}
	//reset
	if(curMember == 0){
		picOrStatue = 0;
	}
	//terminate task
	if(finish) break;
	curMember++;
	//get the first one on the queue and pop it off the queue
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
		tallyCond.signal();//baton passing
	}
   }
}



//-----------------------------------------------------------------------------------
// TallyVotes::vote Voting routine return the result of group's decision of Tour
//-----------------------------------------------------------------------------------
TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	//push id and ballot on to queue
	idQueue.push(id);
	ballotQueue.push(ballot);
	//signal queue is not empty
	queueEmpty.signal();
	//wait until group all voted
	tallyCond.wait();
	//baton passing	
	if(!tallyCond.empty()) tallyCond.signal();
	--curMember; //subtract to reset it to zero

	printer.print(id, Voter::States::Unblock, (curMember));
	
	//printer the finished result of voting
	printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
	
	//return the final tour decision
  	return (picOrStatue > 0) ? Tour::Statue : Tour::Picture;	
}

