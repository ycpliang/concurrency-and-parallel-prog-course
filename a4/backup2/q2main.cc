#include <iostream>
#include "printer.h"
#include "voter.h"
#include "q2tallyVotes.h"
using namespace std;

MPRNG randomK;

void uMain::main(){
  unsigned int vSizeOfTour = 6;
  unsigned int gSizeOfGroup = 3;
  long int seed = getpid();

  if(argc > 4){
  	cerr << "too many parameters" << endl;
  	return;
  }

  switch( argc ) {
  	case 4: seed = atoi(argv[3]);
  	case 3: gSizeOfGroup = atoi(argv[2]);
	case 2: vSizeOfTour = atoi(argv[1]);
  }
  randomK.seed(seed);
  //cout << "the Seed" << randomK.seed() << endl;
  Printer newPrinter(vSizeOfTour); 
  TallyVotes total(gSizeOfGroup, newPrinter);
  Voter * voters[vSizeOfTour];
  {
	for(unsigned int i = 0; i < vSizeOfTour; i++){
		voters[i] = new Voter(i,total, newPrinter); 
	}
  } 
  {
	for(unsigned int i = 0; i < vSizeOfTour; i++){
		delete voters[i];
	}
  }
}

