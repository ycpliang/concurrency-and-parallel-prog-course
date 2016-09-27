#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include "q1mergesort.h"
using namespace std;

template <typename T>
   void Mergesort<T>::recursive(int locall, int localh){
	if(locall >= localh){
		return;	
	}
        int mid = (localh - locall)/2 + locall;
	int lowL = locall; 
	int highL = mid; 
	int lowR = mid + 1;
	int highR = localh;
	recursive(lowL, highL);
	if(depth > 0){
		{Mergesort<T> t1(values, mid + 1, high, (depth-1), sortedValues);}
	}else{
		recursive(lowR, highR);
	}
	int counter = locall;
	while(lowL <= highL && lowR <= highR){
		if(values[lowL] < values[lowR]){
			sortedValues[counter] = values[lowL];
			lowL++;
		}else{
			sortedValues[counter] = values[lowR];
			lowR++;
		}
		counter++;
	}
	while(lowL <= highL){
		sortedValues[counter] = values[lowL];
		counter++;
		lowL++;
	}
	while(lowR <= highR){
		sortedValues[counter] = values[lowR];
		counter++;
		lowR++;	
	}
	for(int i = locall; i <= localh; i++){
		values[i] = sortedValues[i];
	}	
   }


template <typename T>
   void Mergesort<T>::main(){
   	recursive(low, high);
   }



void uMain::main(){
	string line;
	int length;
	char * outfile = NULL;
	char * infile = NULL;
	char * option = NULL;
	bool time = false;
	ostream * outStream = &cout;
	ofstream ofile;
	//error checking
	if(argc < 3){
		cerr << "too few parameters" << endl;
		return;
	}else if(argc > 4){
		cerr << "too many parameters" << endl;
		return;
	}
	//read in command line arguments
	switch(argc){
		case 4: outfile = argv[3]; 
		case 3: infile = argv[2];
		case 2: option = argv[1];
	}

	int depth = 0;
	int size;
	if(option[1] == 't'){
		time = true;
	}else if(option[1] == 's'){
		time = false;
	}else{
		cerr << "unknown command option " << option << endl;
		return;
	}

	if(time){
		if(!(istringstream(infile) >> size) || size < 0){
			cerr << "size is invalid" << endl;
			return;
		}	
		if(outfile != NULL && (!(istringstream(outfile) >> depth) || depth < 0)){ 
			cerr << "depth is invalid" << endl;
			return;
		}
		uProcessor p[ (1 << depth) - 1 ] __attribute__ (( unused )); // 2^depth-1 kernel threads
	        int * k = new int[size];
		for(int i = 0; i < size; i++){
			k[i] = size - i;
		} 
		{Mergesort<TYPE> merge(k, 0, size - 1, depth);}
		delete k;
	}else{
	//open output file if it is given
		if(outfile != NULL){
			try{
				ofile.open(outfile);
			}catch(...){
				cerr << "cannot open outfile" << endl;
				return;
			}
			if(ofile.is_open()){
				outStream = &ofile;
			}else{
				cerr << "cannot open file" << endl;
				return;
			}
		}
		ifstream myfile;
		try{
			myfile.open(infile);
		}catch(...){
			cerr << "input file incorrect" << endl; 
			return;
		}
		if(myfile.is_open()){
		while(getline(myfile, line)){
			istringstream buffer(line);
			buffer >> length;
			int * k = new int[length];
			//call sort for each number
			for(int i = 0; i < length; i++){
				buffer >> k[i];
				*outStream << k[i] << " ";
			}
			*outStream << endl;
	       	 	{Mergesort<TYPE> merge(k, 0, length - 1, depth);}
		
			//retrieve the values
			for(int i = 0; i < length; i++){
				*outStream << k[i] << " ";
			}
			*outStream << endl << endl;
			delete k;
		}
		myfile.close();
		}
	}
}
