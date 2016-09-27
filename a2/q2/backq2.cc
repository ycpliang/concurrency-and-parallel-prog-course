#include <iostream>
#include <sstream>
#include "q2.h"
using namespace std;

//static void Player::players (unsigned int num){
//}

void Player::play(unsigned int deck){
	cerr << "deck " << deck<<  "playing " << id << endl;
	Player::deck = deck;
	resume();
}

void Player::main(){
	suspend();
	for(;;){
//	cout << "inside " << id << endl;
	if(deck % DEATH_DECK_DIVISOR == 0){
//		cout << "got Death" << endl;
		lp->removeRight(rp);
		rp->removeLeft(lp);		
		subPlayer();
	}
	unsigned int taken = randomK(1,8);
	printer.prt(id, taken, nPlayer);
	if(nPlayer <= 1)return;
//	cout << "should terminate " << deck << " " << taken << " " <<  (deck <= taken) << endl;
	if(deck <= taken)return;
	deck -= taken;	
	if(deck % 2 == 0){
//		cout << "right going to play " << deck << endl;
		rp->play(deck);
	}else{
//		cout << "left going to play " << deck << endl;
		lp->play(deck);
	}
//	suspend();
	}

}


void Printer::prt( const unsigned int id, const unsigned int took, unsigned int PlayersRemaining){
//	cout << "printing" << took << endl;	
	std::ostringstream ss;
		if(PlayersRemaining <= 1){
			cnPlayers--;
			buffer[id] = 3;
		}else if(cnPlayers != PlayersRemaining){
			cnPlayers--;
		if(buffer[id] == 4){
			buffer[id] = 5;
		}else{
			buffer[id] = 2;
		}
		}
	
	if(buffer[id] != 1){
	if(cRemain <= took){
		buffer[id] = 4;
		cRemain = 0;
	}else{	
		cRemain -= took;
	}
//		ss << took << ":" << cRemain;
		Printer::took[id] = took;
		Printer::remaining[id] = cRemain;
	}
	if(buffer[id] == 0){
		buffer[id] = 1;
//		bufferStr[id] = ss.str();
	}else{
		for(unsigned int i = 0; i < NoOfPlayers; i++){	
			if(buffer[i] != 0){
				ss << Printer::took[i] << ":" << remaining[i];
				//if(i == id){
					if(remaining[i] % 2 == 0){
						ss << ":>";
					}else{
						ss << ":<";
					}
				if(id == i){
					ss << "*  ";
				}
				if(buffer[i] == 4){
					ss << "#";
				}else if(buffer[i] == 2){
					ss << "X";
				}else if(buffer[i] == 5){
					ss << "X#";
				}else if(buffer[i] == 3){
					ss << "#" << cRemain << "#";
				}
				ss << '\t';	
			
			}else{
				ss << '\t';
			}
			if(id != i){
			buffer[i] = 0;
			Printer::took[i] = 0;
			remaining[i] = 0;
			}
		}

		buffer[id] = 1;
		if(cRemain <= took){
			buffer[id] = 4;
			cRemain = 0;
		}else{	
			cRemain -= took;
		}
//		ss << took << ":" << cRemain;
		Printer::took[id] = took;
		Printer::remaining[id] = cRemain;
			
		cout << ss.str() << endl;			
	}	

//	cout << "done Printing " << endl;	
}

void uMain::main(){
        long int seed = getpid(); // default values
	int ngames = 5;

/*       	if(atoi(argv[2])  < 0 || seed < 0){
		cerr << "Invalid parameter input" << endl;
		return;
	}	*/
        switch ( argc ) {
                case 3: seed = atoi (argv[2]);
                case 2: ngames = atoi( argv[1] );
        } // switch
	randomK.seed(seed);	
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

}
