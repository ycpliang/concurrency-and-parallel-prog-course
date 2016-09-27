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
	if(nPlayer <= 1){ 
		printer.prt(id, 0, nPlayer);	
		return;	
	}
	
	if(deck % DEATH_DECK_DIVISOR == 0){
		lp->removeRight(rp);
		rp->removeLeft(lp);		
		subPlayer();
	}
	unsigned int taken = randomK(1,8);
	if(deck <= taken){
		printer.prt(id, deck, nPlayer);
	}else{
		printer.prt(id, taken, nPlayer);
	}
	if(deck <= taken){
		printer.prt(id, 2, nPlayer);	
		return;
	}
	deck -= taken;	
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
	if(tmp != 0 || took == 0){
		for(unsigned int i = 0; i < NoOfPlayers; i++){
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
	if(Printer::took[id] == 0){
		if(cRemain <= took){
			cRemain = 0;
		}else{
			cRemain -= took;
		}
		Printer::took[id] = took;
		Printer::remaining[id] = cRemain;
	}
	if(tmp != 0 && took == 0){
		prt(id,took,PlayersRemaining);
	}
}

void uMain::main(){
        long int seed = getpid(); // default values
	int ngames = 5;

        switch ( argc ) {
                case 3: seed = atoi (argv[2]);
                case 2: ngames = atoi( argv[1] );
        } // switch
	
	if(seed <= 0){
		cerr << "seed value too small" << endl;
		return;
	}
	if(ngames < 0){
		cerr << "game number is not valid" << endl;
		return;
	}
	randomK.seed(seed);	
	for(int gameNum = 0; gameNum < ngames; gameNum++){
	unsigned int nPlayers = randomK(2,10);
	unsigned int nCards = randomK(10,200);
	Printer printer(nPlayers, nCards);
	Player::players(nPlayers);
	Player * allPlayers[nPlayers];
	for(unsigned int i = 0; i < nPlayers; i++){
		allPlayers[i] = new Player(printer, i);
	}
	allPlayers[0]->start(*allPlayers[nPlayers - 1], *allPlayers[1]);
	for(unsigned int i = 1; i < nPlayers - 1; i++){
		allPlayers[i]->start(*allPlayers[i - 1], *allPlayers[i + 1]);
		
	}
	allPlayers[nPlayers - 1]->start(*allPlayers[nPlayers - 2], *allPlayers[0]);
	unsigned int randStart = randomK((nPlayers - 1));
	allPlayers[randStart]->play(nCards);	
	for(unsigned int i = 0; i < nPlayers; i++){
		delete allPlayers[i];
	}
	if(ngames - 1 != gameNum){
		cout << endl << endl;
	}
	}

}
