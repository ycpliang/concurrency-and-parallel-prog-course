#include <iostream>
#include "q2.h"
using namespace std;

MPRNG randomK;

TallyVotes::Tour TallyVotes::vote(unsigned int id, Tour ballot) {
	ownerLock.acquire();
		if(inuse){
			bLock.wait(ownerLock);
//			cout << "releasing" << endl;
			if(bLock.empty()) inuse = 0;
		}
		if(curMember == 0){
			picOrStatue = 0;
		}
		++curMember;
		printer.print(id, Voter::States::Vote, ballot);
//		cout << "id " << id << " " << curMember << " " << ballot << endl;
		if(ballot == Tour::Picture){
			--picOrStatue;
		}else{
			++picOrStatue;
		}

		if(curMember == group){
//			cout << "release" << endl;
			inuse = 1;
		//	picOrStatue = 0;
			printer.print(id, Voter::States::Complete);
			printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
//			tallyLock.signal();
//			tallyLock.signal();
		//	bLock.signal();
		//	inuse = 0; 
		}else{
	//		inuse = 1;
			printer.print(id, Voter::States::Block, curMember);
			if(!bLock.empty()) bLock.signal();
			tallyLock.wait(ownerLock);
			printer.print(id, Voter::States::Unblock, (curMember - 1));
			//add finish print
			printer.print(id, Voter::States::Finished, TallyVotes::Tour(picOrStatue < 0 ? 0 : 1) );
		}
		--curMember;
	//	if(!tallyLock.empty()){
		//	tallyLock.signal();
	//	}else{
		if(!tallyLock.empty()){
			tallyLock.signal();
		}else if(!bLock.empty()){
			bLock.signal();
		}else{
			inuse = 0;
		}
	//	}
		ownerLock.release();
//	cout << "value " << picOrStatue << endl;
	if(picOrStatue == 0){
		cerr << "equal votes" << endl;
		return Tour::Picture;
	}
	if(picOrStatue > 0){
//		picOrStatue = 0;
		return Tour::Statue;
	}else{
//		picOrStatue = 0;
		return Tour::Picture; 
	}
}


void Voter::main(){
//	int startOrder = randomK() % 20;
	yield(randomK(19));
//	yield(startOrder);
	printer.print(id, States::Start);
	voteTallier.vote(id, TallyVotes::Tour(randomK() % 2));	
}

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

