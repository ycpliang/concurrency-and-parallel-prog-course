#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "q1binsertsort.h"
using namespace std;

template<typename T>
    void Binsertsort<T>::main(){
	pivot = value; //set pivot
	suspend();
	Binsertsort <T> less(Sentinel);
	Binsertsort <T> greater(Sentinel);
	while(value != Sentinel){
		if(value <= pivot){
			less.sort(value);
		}else{
			greater.sort(value);
		}
		suspend();
	}
	//check if left was initialized	
	if(less.getState() != 0) {
		less.sort(Sentinel);
		suspend(); 
		T k; 
		//retrieve value from left branch 
		//until sentinel is received
		while((k = less.retrieve()) != Sentinel){
			value = k;
			suspend();
		} 
	}else{
		suspend();
	}
	//return pivot value
	Binsertsort::value = pivot;
	//check if right was initialzed
	if(greater.getState() == 0){ 
		suspend();
	}else {
		greater.sort(Sentinel);
		suspend(); 
		T k; 
		//retrieve value from right branch
		//until sentinel is received
		while((k = greater.retrieve()) != Sentinel){
			value = k;
			suspend();
		} 
	}
	//set the value as sentinel to signal this node is done
	value = Sentinel; 
   }                     // YOU WRITE THIS ROUTINE



void uMain::main(){
	//int l;
	string line;
	int length;
	int k;
	char * outfile = NULL;
	char * infile = NULL;
	ostream * outStream = &cout;
	ofstream ofile;
	//error checking
	if(argc < 2){
		cerr << "unspecified input file" << endl;
		return;
	}
	//read in command line arguments
	switch(argc){
		case 3: outfile = argv[2]; 
		case 2: infile = argv[1];
	}
	
	//open output file if it is given
	if(outfile != NULL){
		ofile.open(outfile);
		if(ofile.is_open()){
			outStream = &ofile;
		}else{
			cerr << "cannot open file" << endl;
			return;
		}
	}
	ifstream myfile(infile);
	if(myfile.is_open()){
	while(getline(myfile, line)){
		Binsertsort <TYPE> base(SENTINEL);
		istringstream buffer(line);
		buffer >> length;
		//call sort for each number
		for(int i = 1; i <= length; i++){
			buffer >> k;
			*outStream << k << " ";
			base.sort(k);				
		}
		*outStream << endl;
		base.sort(SENTINEL);//signal the end of input
		
		//retrieve the values
		while((k = base.retrieve()) != SENTINEL){
			*outStream << k << " "; 
		}
		*outStream << endl << endl;
	}
	myfile.close();
	}
	if(outStream != &cout){
		ofile.close();
	}

}
