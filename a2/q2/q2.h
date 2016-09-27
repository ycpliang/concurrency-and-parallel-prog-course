#ifndef __PlAYER_H__
#define __PlAYER_H__
#include "prng.h"

class Printer;
PRNG randomK;
_Coroutine Player {
    // YOU MAY ADD PRIVATE MEMBERS
  Printer & printer;
  unsigned int id;
  Player *lp;
  Player *rp;
  unsigned int deck;
  static unsigned int nPlayer; 
  	void main();
	static void subPlayer(){ nPlayer = nPlayer - 1;}
	void removeRight(Player * rp){ Player::rp = rp; }
	void removeLeft(Player * lp) { Player::lp = lp; }
  public:
    enum { DEATH_DECK_DIVISOR = 5 };
    static void players( unsigned int num ){nPlayer = num;}
    Player( Printer &printer, unsigned int id ): printer(printer), id(id){}
    void start( Player &lp, Player &rp ){
        Player::lp = &lp;
        Player::rp = &rp;
        resume();
    }
    void play( unsigned int deck);
};

unsigned int Player::nPlayer = 2;

class Printer {
   const unsigned int NoOfPlayers;
   const unsigned int NoOfCards;
   unsigned int cRemain; 
   unsigned int cnPlayers;
   unsigned int * took;
   unsigned int * remaining;    
   // YOU MAY ADD PRIVATE MEMBERS
  public:
    Printer( const unsigned int NoOfPlayers, const unsigned int NoOfCards ) : NoOfPlayers(NoOfPlayers), NoOfCards(NoOfCards), cRemain(NoOfCards), cnPlayers(NoOfPlayers){
		took = new unsigned int[NoOfPlayers];
		remaining = new unsigned int[NoOfPlayers];

		std::cout << "Players: " << NoOfPlayers << "    " << "Cards: " << NoOfCards << std::endl;
		for(unsigned int i = 0; i < NoOfPlayers; i++){	
			took[i] = 0;
			remaining[i] = 0;
	//		buffer[i] = 0;
			std::cout << "P" << i << '\t';
		}
		std::cout << std::endl;
	}
    void prt( const unsigned int id, const unsigned int took, unsigned int PlayersRemaining );
   ~Printer(){
	delete took;
	delete remaining;
   }
};

#endif
