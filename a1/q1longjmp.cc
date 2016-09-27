#include <iostream>
#include <cstdlib>
using namespace std;
#include <unistd.h> // getpid
#include <setjmp.h>
#include <string.h>

#ifdef NOOUTPUT
#define print( x )
#else
#define print( x ) x
#endif

struct E {};

long int freq = 5;

jmp_buf env;
int val;
bool ret;
long int Ackermann( long int m, long int n ) {
	jmp_buf localEnv;
		memcpy(localEnv, env, sizeof localEnv );
	cout << "p1" << " " << m << " " << n << endl;	
	if ( m == 0 ) {
	cout << "p2" << " " << m << " " << n << endl;	
		if ( random() % freq == 0 ) longjmp(env, 1);
	//	p = n + 1;
	//	longjmp(env, 2);
		//return n + 1;
	} else if ( n == 0 ) {
	cout << "p3" << " " << m << " " << n << endl;	
		if ( random() % freq == 0 ) longjmp(env, 1);
	cout << "p4" << " " << m << " " << n << endl;	
		val = setjmp(env);
		if(val == 0){
	cout << "p5" << " " << m << " " << n << endl;	
	//	try {
			return Ackermann( m - 1, 1 );
		} else if(val == 2){
			memcpy(env, localEnv, sizeof env);
			return p;
		}else {
	cout << "p6" << " " << m << " " << n << endl;	
			print( cout << "E1 " << m << " " << n << endl );
			memcpy(env, localEnv, sizeof env);
		} // try
	cout << "p7" << " " << m << " " << n << endl;	
	} else {
	cout << "p8" << " " << m << " " << n << endl;	
	cout << "p9" << " " << m << " " << n << endl;	
		val = setjmp(env);
		if(val == 0){
	cout << "p10" << " " << m << " " << n << endl;	
		//try {
			return Ackermann( m - 1, Ackermann( m, n - 1 ) );	
		}else if(val == 2){
			memcpy(env, localEnv, sizeof env);
			return p;
		} else {
	cout << "p11" << " " << m << " " << n << endl;	
			print( cout << "E2 " << m << " " << n << endl );
			memcpy(env, localEnv, sizeof env);
		} // try
	cout << "p12" << " " << m << " " << n << endl;	
	} // if
	cout << "p13" << " " << m << " " << n << endl;	
	return 0; // recover by returning 0
}

int main( int argc, const char * argv[ ] ) {
	long int Ackermann( long int m, long int n );
	long int m = 4, n = 6, seed = getpid(); // default values
	switch ( argc ) {
		case 5: freq = atoi( argv[4] );
		case 4: seed = atoi( argv[3] );
		case 3: n = atoi( argv[2] );
		case 2: m = atoi( argv[1] );
	} // switch
	srandom( seed );
	cout << m << " " << n << " " << seed << " " << freq << endl;
	if(!setjmp(env)) {
		cout << Ackermann( m, n ) << endl;
	}else {
		print( cout << "E3" << endl );
	} // try
}

