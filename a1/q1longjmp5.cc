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

jmp_buf env;
jmp_buf * genv;

long int Ackermann( long int m, long int n ) {
	jmp_buf env;
	jmp_buf * old_env;
	old_env = genv;
	if ( m == 0 ) {
		if ( random() % freq == 0 ) longjmp(*genv, 1);
		return n + 1;
	} else if ( n == 0 ) {
		if ( random() % freq == 0 ) longjmp(*genv, 1);
//		memcpy(old_env, env, sizeof env);
		if(!setjmp(env)) {
			genv = &env;
			int val = Ackermann( m - 1, 1);
			genv = old_env;
			//memcpy(&genv, old_env, sizeof old_env);
			return val;
		} else {
			print( cout << "E1 " << m << " " << n << endl );
			genv = old_env;
			//memcpy(&genv, old_env, sizeof old_env);
		} // try
	} else {
//		memcpy(old_env, env, sizeof env);
		if(!setjmp(env)) {
			genv = &env;
			int val = Ackermann( m - 1, Ackermann( m, n - 1));
			//memcpy(&genv, old_env, sizeof old_env);
			genv = old_env;
			return val;
		}else {
			print( cout << "E2 " << m << " " << n << endl );
			genv = old_env;
	//		memcpy(&genv, old_env, sizeof old_env);
		} // try
	} // if
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
	jmp_buf mainEnv;
	genv = &mainEnv;
	if(!setjmp(mainEnv)){
		cout << Ackermann( m, n ) << endl;
	} else {
		print( cout << "E3" << endl );
	} // try
}

