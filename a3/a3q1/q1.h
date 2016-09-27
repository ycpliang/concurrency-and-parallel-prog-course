template<typename T> _Task Mergesort {
  T * values;
  T * sortedValues;
  unsigned int depth;
  unsigned int low;
  unsigned int high;
  bool remove;
  void recursive(int localh, int locall);
  Mergesort( T values[], unsigned int low, unsigned int high, unsigned int depth, T * sortedValues ): values(values), sortedValues(sortedValues),depth(depth), low(low), high(high), remove(false){} 
  void main();
  public:
    Mergesort( T values[], unsigned int low, unsigned int high, unsigned int depth ): values(values), depth(depth), low(low), high(high), remove(true){ 	 
		 this->sortedValues = new int[high - low + 1];
	} 
    ~Mergesort(){
	if(remove){
		delete sortedValues;	
   	}
    }
};

unsigned int uDefaultStackSize() {
    return 512 * 1000;        // set task stack-size to 512K
}

