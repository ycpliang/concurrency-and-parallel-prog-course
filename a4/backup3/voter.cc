#include "voter.h"
//#include "q2tallyVotes.h"
#include "printer.h"


void Voter::main(){
//      int startOrder = randomK() % 20;
        yield(randomK(19));
//      yield(startOrder);
        printer.print(id, States::Start);
        voteTallier.vote(id, TallyVotes::Tour(randomK() % 2));
}



