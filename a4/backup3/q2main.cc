#include <iostream>
#include "printer.h" //the monitor printer
#include "voter.h" //the task voter
#include "q2tallyVotes.h" //the tallyVote class
#include <sstream>
using namespace std;

MPRNG randomK; //random generator



//--------------------------------------------------------------------------------------------------------------------
// Returns true if the given string can be considered an positive integer.
//--------------------------------------------------------------------------------------------------------------------
bool paramNumErrCheck(char * a){
	istringstream ss(a);
	int num;
	return (ss >> num) ? (num > 0) : false;
}


//--------------------------------------------------------------------------------------------------------------------
// Main driver for the program.  Reads in the commands, do error checking and start voter tasks
//--------------------------------------------------------------------------------------------------------------------
void uMain::main(){
  unsigned int vSizeOfTour = 6; //The total number of voters, default 6
  unsigned int gSizeOfGroup = 3; //The total number of voters in each group
  long int seed = getpid(); //the seed for random variable generator


  //check if there is too many parameters
  if(argc > 4){
	cerr << "wrong number of parameter" << endl;
	return;
  }

  //error check and get the commandline parameter
  switch( argc ) {
  	case 4: if(!paramNumErrCheck(argv[3])){
			cerr << "paramater 3 error" << endl;
			return;
		}
		seed = atoi(argv[3]);
  	case 3: if(!paramNumErrCheck(argv[2])){
			cerr << "paramater 2 error" << endl;
			return;
		}
		gSizeOfGroup = atoi(argv[2]);
		if(gSizeOfGroup % 2 != 1){
			cerr << "sizeOfGroup not odd" << endl;
			return;
		}
	case 2: if(!paramNumErrCheck(argv[1])){
			cerr << "paramater 1 error" << endl;
			return;
		}
		vSizeOfTour = atoi(argv[1]);
  }

  randomK.seed(seed); //set the seed of MPRNG
  
  
  //Initialize the necessary class, monitor and task
  Printer newPrinter(vSizeOfTour);  //monitor printer
  TallyVotes total(gSizeOfGroup, newPrinter); //tallyVotes 
  Voter * voters[vSizeOfTour]; //an array of pointers to task voters

  //create the all the tasks voters
  {
	for(unsigned int i = 0; i < vSizeOfTour; i++){
		voters[i] = new Voter(i,total, newPrinter); 
	}
  } 
  //wait and delete the all the tasks voters
  {
	for(unsigned int i = 0; i < vSizeOfTour; i++){
		delete voters[i];
	}
  }
}

