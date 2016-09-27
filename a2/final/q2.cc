#include <iostream>
#include <sstream>
#include "q2.h"
using namespace std;

//static void Player::players (unsigned int num){
//}

void Player::play(unsigned int deck){
	Player::deck = deck;
	resume();
}

void Player::main(){
	suspend();
	for(;;){
	//check if the current number of player is
	//one
	if(nPlayer <= 1){ 
		printer.prt(id, 0, nPlayer);	
		return;	
	}
	//check if the deck is a death deck
	if(deck % DEATH_DECK_DIVISOR == 0){
		//**this basically removes you from the linked list **//
		//change your left node neighbour's right pointer
		//to be your right pointer
		lp->removeRight(rp);
		//change your right node neighbour's left pointer
		//to be your left pointer
		rp->removeLeft(lp);		
		subPlayer(); //same as nPlayer--;
	}
	unsigned int taken = randomK(1,8);
	//go to printer to see if buffer need to be unloaded
	if(deck <= taken){
		printer.prt(id, deck, nPlayer);
	}else{
		printer.prt(id, taken, nPlayer);
	}
	//if there is no more cards
	if(deck <= taken){
		printer.prt(id, 2, nPlayer);	
		return;
	}
	deck -= taken;	
	//call the next player depending on even or odd
	//even right player goes 
	//odd left player goes
	if(deck % 2 == 0){
		rp->play(deck);
	}else{
		lp->play(deck);
	}
	}

}


void Printer::prt( const unsigned int id, const unsigned int took, unsigned int PlayersRemaining){
	std::ostringstream ss;
	unsigned int tmp = Printer::took[id];

	//unload the buffer
	if(tmp != 0 || took == 0){
		for(unsigned int i = 0; i < NoOfPlayers; i++){
			//check if it is terminatiing
			if(Printer::took[i] == 0){
				if(i == id){	
				if(cRemain <= 0){
					ss << "#";
				}
				if(PlayersRemaining <= 1){
					ss << "#" << cRemain << "#";
				}
				if(cRemain % 5 == 0){
					ss << "X";
				}
				}
			}
			if(Printer::took[i] != 0){
			//print out the entire line
				ss << Printer::took[i] << ":" << remaining[i];
				if(remaining[i] > 0){
				if(remaining[i] % 2 == 0){
					ss << ">";
				}else{
					ss << "<";
				}
				}else{
					ss << "#";
				}
				if((remaining[i] + Printer::took[i]) % 5 == 0){
					ss << "X";
				}
				if(i == id && (cRemain > 0)){
					ss << "*";
				}
			}
			ss << '\t';
			Printer::took[i] = 0;
			remaining[i] = 0;
		}	
		cout << ss.str() << endl;
	}
	//set the value to be unloaded later
	if(Printer::took[id] == 0){
		if(cRemain <= took){
			cRemain = 0;
		}else{
			cRemain -= took;
		}
		Printer::took[id] = took;
		Printer::remaining[id] = cRemain;
	}
	//recursive to print final results
	if(tmp != 0 && took == 0){
		prt(id,took,PlayersRemaining);
	}
}

void uMain::main(){
        long int seed = getpid(); // default values
	int ngames = 5;
	//reading in the command line arguments
        switch ( argc ) {
                case 3: seed = atoi (argv[2]);
                case 2: ngames = atoi( argv[1] );
        } // switch
	
	//error msg for command line input
	if(seed <= 0){
		cerr << "seed value too small" << endl;
		return;
	}
	if(ngames < 0){
		cerr << "game number is not valid" << endl;
		return;
	}
	randomK.seed(seed);//set seed	
	for(int gameNum = 0; gameNum < ngames; gameNum++){
	unsigned int nPlayers = randomK(2,10);
	unsigned int nCards = randomK(10,200);
	Printer printer(nPlayers, nCards);
	Player::players(nPlayers);
	Player * allPlayers[nPlayers];
	//initializing the players
	for(unsigned int i = 0; i < nPlayers; i++){
		allPlayers[i] = new Player(printer, i);
	}
	//set the first player's left to be the last player(linked list style)
	allPlayers[0]->start(*allPlayers[nPlayers - 1], *allPlayers[1]);
	for(unsigned int i = 1; i < nPlayers - 1; i++){
		allPlayers[i]->start(*allPlayers[i - 1], *allPlayers[i + 1]);
		
	}
	//set the last player's right to point to the first player
	allPlayers[nPlayers - 1]->start(*allPlayers[nPlayers - 2], *allPlayers[0]);
	unsigned int randStart = randomK((nPlayers - 1));
	
	//start playing
	allPlayers[randStart]->play(nCards);
	
	//delete the pointers (clean up)	
	for(unsigned int i = 0; i < nPlayers; i++){
		delete allPlayers[i];
	}
	if(ngames - 1 != gameNum){
		cout << endl << endl;
	}
	}

}
