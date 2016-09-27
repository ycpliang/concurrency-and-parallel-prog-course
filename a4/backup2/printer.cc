//#include "q2tallyVotes.h"
//#include "voter.h"
#include "printer.h"


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

Printer::~Printer(){
        std::cout << "=================" << std::endl;
        std::cout << "All tours started" << std::endl;
        delete voteArray;
        delete resultArray;
}


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


