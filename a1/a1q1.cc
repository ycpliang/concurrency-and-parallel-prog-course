#include <iostream>
#include <cstdlib>
using namespace std;
#include <unistd.h> // getpid
#include <setjmp.h>
#ifdef NOOUTPUT
#define print( x )
#else
#define print( x ) x
#endif

struct E {};

long int freq = 5;
int stackcount = 0;
jmp_buf cvn;
jmp_buf cvn2;
long int Ackermann( long int m, long int n) {
//	jmp_buf cvn2;
	int val;
	val = setjmp(cvn2);
	if(val == 1 && stackcount == 0) longjmp(cvn,1); 
	if ( m == 0 ) {
		if ( random() % freq == 0 ) longjmp(cvn2,1);
		return n + 1;
	} else if ( n == 0 ) {
		if ( random() % freq == 0 ) longjmp(cvn2,1);
		if(!setjmp(cvn2)){
			return Ackermann( m - 1, 1, cvn2);
		}else {
		print( cout << "E1 " << m << " " << n << endl );
		} // try
	} else {
		if(!setjmp(cvn2)){
			return Ackermann( m - 1, Ackermann( m, n - 1, cvn2), cvn2 );
		}else {
			print( cout << "E2 " << m << " " << n << endl );
		} // try
	} // if
	return 0; // recover by returning 0
}

int main( int argc, const char * argv[ ] ) {
	long int Ackermann( long int m, long int n,jmp_buf cvn );
	long int m = 4, n = 6, seed = getpid(); // default values
	switch ( argc ) {
		case 5: freq = atoi( argv[4] );
		case 4: seed = atoi( argv[3] );
		case 3: n = atoi( argv[2] );
		case 2: m = atoi( argv[1] );
	} // switch
	srandom( seed );
	cout << m << " " << n << " " << seed << " " << freq << endl;
	if(!setjmp(cvn)){
		cout << Ackermann( m, n, cvn) << endl;
	}else {
		print( cout << "E3" << endl );
	} // try	
}

