//-----------------------------------------------------------------------------------
// TallyVotes Program implementation of printer to
// print the states and votes
//-----------------------------------------------------------------------------------

#include "q2printer.h"  //header for printer

//-----------------------------------------------------------------------------------
// Printer::~Printer is used to free up the voteArray and resultArray and also to print
// final cout statements
//-----------------------------------------------------------------------------------
Printer::~Printer(){
        std::cout << "=================" << std::endl;
        std::cout << "All tours started" << std::endl;
        delete voteArray;
        delete resultArray;
}

//-----------------------------------------------------------------------------------
// Printer::Printer Constructor which allocate voterArray and resultArray on heap and 
// then print the initial statements
//-----------------------------------------------------------------------------------
Printer::Printer( unsigned int voters ){
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



//-----------------------------------------------------------------------------------
//Printer::printLine Helper routine to flush the line of output, the boolean parameter
//is to determine whether the current state is Finished.
//-----------------------------------------------------------------------------------
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


//-----------------------------------------------------------------------------------
//Printer::print put state on the buffer. If buffer is full, flush the buffer and then store
//the state
//-----------------------------------------------------------------------------------
void Printer::print( unsigned int id, Voter::States state){
        if(voteArray[id] != '.'){
                printLine(false);
        }
        voteArray[id] = state;
}

//-----------------------------------------------------------------------------------
//Printer::print put state and vote on the buffer. If buffer is full, flush the buffer and then store
//the state and vote 
//-----------------------------------------------------------------------------------
void Printer::print( unsigned int id, Voter::States state, TallyVotes::Tour vote){
        if(voteArray[id] != '.'){
                printLine(false);
        }
        voteArray[id] = state;
        resultArray[id] = vote;
        if(state == Voter::States::Finished) printLine(true);
}

//-----------------------------------------------------------------------------------
//Printer::print put state and number of blocked on the buffer. If buffer is full, flush the buffer and then store
//the state and number of blocked
//-----------------------------------------------------------------------------------
void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked){
        if(voteArray[id] != '.'){
                printLine(false);
        }
        voteArray[id] = state;
        resultArray[id] = numBlocked;

}


