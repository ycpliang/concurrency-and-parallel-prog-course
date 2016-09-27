//-----------------------------------------------------------------------------------
// Voters Program implementation of Voter Task main
//-----------------------------------------------------------------------------------

//includes
#include "q3voter.h" //header file
#include "q3printer.h" //monitor printer for printing


void Voter::main(){
        yield(randomK(19)); //yield a random number of times between 0 and 19
        printer.print(id, States::Start); //print the start State
        voteTallier.vote(id, TallyVotes::Tour(randomK() % 2)); //state the voting with randomly calculated ballot( 0 for Picture, 1 for Statue)
}



