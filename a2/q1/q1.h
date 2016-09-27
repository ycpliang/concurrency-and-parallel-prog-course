#ifndef __q1_h__
#define __q1_h__

template<typename T> _Coroutine Binsertsort {
    const T Sentinel;                // value denoting end of set
    T value; 
    T pivot;                        // communication: value being passed down/up the tree
    void main();                     // YOU WRITE THIS ROUTINE
  public:
    Binsertsort( T Sentinel) : Sentinel( Sentinel ){}
    void sort( T value ) {           // value to be sorted
        Binsertsort::value = value;
	resume();
    }
    T retrieve() {                   // retrieve sorted value
        resume();
        return value;
    }
};
#endif
