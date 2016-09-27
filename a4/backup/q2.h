#include "MPRNG2.h"


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


_Task Voter {
  unsigned int id;
  TallyVotes & voteTallier;
  Printer & printer;
  void main();
  public:
    enum States { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U',
                   Complete = 'C', Finished = 'F' };
    Voter( unsigned int id, TallyVotes &voteTallier, Printer &printer ):
	id(id), voteTallier(voteTallier), printer(printer) {}
};


_Monitor Printer {    // cihose one of the two kinds of type constructor
  char * voteArray;
  int * resultArray; 
  unsigned int sizeOfGroup;
  _Mutex void printLine(bool);
  public:
    Printer( unsigned int voters ){
	voteArray = new char[voters];
	resultArray = new int[voters];
	sizeOfGroup = voters;
	for(unsigned int i = 0;; i++){
		std::cout << "Voter" << i; 
		voteArray[i] = '.';
		resultArray[i] = 0;
		if(i + 1 >= sizeOfGroup) break;
		std::cout << '\t';
	}
	std::cout << std::endl;
	for(unsigned int i = 0; i < voters; i++){
		std::cout << "=======";
		if(i + 1 >= sizeOfGroup) break;
		std::cout << '\t';
	 
	}
	std::cout << std::endl;
    }
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
    ~Printer(){
	std::cout << "=================" << std::endl;
	std::cout << "All tours started" << std::endl;
  	delete voteArray;
	delete resultArray;
    }
};

void Printer::printLine(bool finishGroup){
	for(unsigned int i = 0; i < sizeOfGroup; i++){
		if(voteArray[i] == '.'){
			if(finishGroup){
				std::cout << "..."; 
			}
		}else{
			std::cout << voteArray[i];
		}
		if(voteArray[i] == Voter::States::Vote){
			std::cout << " " << ((resultArray[i] == 0) ? 'p' : 's');
		}else if(voteArray[i] == Voter::States::Unblock || voteArray[i] == Voter::States::Block || voteArray[i] == Voter::States::Finished){
			std::cout << " " << resultArray[i];
		}
		voteArray[i] = '.';
		resultArray[i] = -1;
		std::cout << '\t';
	} 
	std::cout << std::endl;

}

void Printer::print( unsigned int id, Voter::States state){
	if(voteArray[id] != '.'){
		printLine(false);
	}
	voteArray[id] = state;
}

void Printer::print( unsigned int id, Voter::States state, TallyVotes::Tour vote){
	if(voteArray[id] != '.'){
		printLine(false);		
	}	
	voteArray[id] = state;
	resultArray[id] = vote;
	if(state == Voter::States::Finished) printLine(true);
}

void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked){
	if(voteArray[id] != '.'){
		printLine(false);		
	}	
	voteArray[id] = state;
	resultArray[id] = numBlocked;

}
