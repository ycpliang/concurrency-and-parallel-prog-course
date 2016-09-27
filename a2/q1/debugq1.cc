#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
using namespace std;

int iglb =0;
template<typename T> _Coroutine Binsertsort {
    const T Sentinel;                // value denoting end of set
    T value; 
    T pivot;                        // communication: value being passed down/up the tree
    int number;
//    Binsertsort <T> * left;
    bool leftSet = false;
  //  Binsertsort <T> * right;
    bool rightSet = false;
    void main(){
	cout << "The numbered " << number << endl;
	pivot = value;
	cout << " 1pivot: " << pivot << "i: " <<  iglb << endl;
	iglb++;
	suspend();
	cout << "2 pivot: " << pivot << "i: " <<  iglb << endl;
	iglb++;
	cout << "booleans set" << leftSet << rightSet << endl;
	Binsertsort <T> less(Sentinel, (number + 1));
	Binsertsort <T> greater(Sentinel, (number + 2));
	while(value != Sentinel){
//	if(value != Sentinel){
	cout << "NOT SENTINEL" << endl;
	if(value <= pivot){
		cout << "less " << endl;
//		left = &less;
		leftSet = true;
		less.sort(value);
	}else{
		cout << "greater " << endl;
//		right = &greater;
		rightSet = true;
		greater.sort(value);
	}
	suspend();
	}	
//	suspend();
	cout << " 2 booleans set" << pivot << leftSet << rightSet << endl;
	cout << "sentinel " << endl;
	if(leftSet) {	
		less.sort(Sentinel);
	}
	cout << "signal done" << pivot << endl;
//	suspend();
	if(leftSet) {
		suspend(); 
		cout << "left sent" << endl; 
		cout << "pppl" << endl;
		T k; 
		while((k = less.retrieve()) != Sentinel){
			value = k;
			cout << "less K " << k << "number " << number << endl;
			suspend();
		} 
	//	do{ value = less.retrieve();  }while(value != Sentinel);
	}
	cout << "exit" << endl;
	if(!leftSet)suspend();
//	if(leftSet) { cout << "left " << endl; left->retrieve(); suspend();}
	Binsertsort::value = pivot;
	cout << "OWN VALUE" << pivot << "and # " << number << endl;
	if(!rightSet) suspend();
	if(rightSet){ greater.sort(Sentinel);}
	if(rightSet) {
		suspend(); 
		cout << "right sent" << endl; 
		cout << "pppr" << endl;
		T k; 
		while((k = greater.retrieve()) != Sentinel){
//			value = greater.retrieve();
			value = k;
			cout << "K " << k << " number " << number << endl;
			suspend();
		} 
	}
//	this->retrieve();	
//	if(rightSet) { cout << "right " << endl; right->retrieve(); suspend();}
//	Binsertsort::value = Sentinel;
//	this->retrieve();
	Binsertsort::value = Sentinel; 
	cout << "TERMINATING" << endl;
   }                     // YOU WRITE THIS ROUTINE
  public:
    Binsertsort( T Sentinel, int i ) : Sentinel( Sentinel ), number(i) {}
    void sort( T value ) {           // value to be sorted
        Binsertsort::value = value;
        cout << "sort" << number << endl;
	resume();
    }
    T retrieve() {                   // retrieve sorted value
        resume();
	cout << "retrieve#" << number << endl;
        return value;
    }
};


void uMain::main(){
	//int l;
	string line;
	int length;
	int k;
	char * outfile;
	char * infile;
	Binsertsort <int> base(SENTINEL,0);
	cout << SENTINEL << endl;
	switch(argc){
		case 3: outfile = argv[2]; 
		case 2: infile = argv[1];	
	}
	
	(void) outfile;
	ifstream myfile(infile);
	if(myfile.is_open()){
//	while(
	getline(myfile, line);
	istringstream buffer(line);
	buffer >> length;
	for(int i = 1; i <= length; i++){
		cout << "THE ITH" << endl;
		buffer >> k;
		base.sort(k);				
	}
	cout << "DONE SET" << endl;
	base.sort(SENTINEL);
	for(int i = 0; i <= length; i++){
		cout << "ITH RETRIEVE " << i << endl;
		int k = base.retrieve();
		cout << "retrieved: " << k << endl;
//		if(k == SENTINEL){
//			base.sort(SENTINEL);
//		}
	}

	myfile.close();
	}

}
