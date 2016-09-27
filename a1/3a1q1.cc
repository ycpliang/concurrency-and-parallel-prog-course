#include <iostream>
#include <cstdlib>
#include <vector>
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
vector <long int> alist;
int acounter = -1;
vector <long int> blist;
int bcounter = -1;
jmp_buf env;
jmp_buf * genv;

long int Ackermann4( long int m, long int n ) {
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
			int val = Ackermann4( m - 1, 1);
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
			int val = Ackermann4( m - 1, Ackermann4( m, n - 1));
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


long int Ackermann2( long int m, long int n ) {
	long int a;
	long int b;
//	cout << "p1" << " " << m << " " << n << endl;	
        if ( m == 0 ) {
//	cout << "p2" << " " << m << " " << n << endl;	
		acounter++;
//	cout << "value : " << alist[acounter] << endl;
		if ((a = random()) % freq == 0 ){ alist.push_back(a); 
//	cout << "value a: " << a << endl;
								throw E();}
//	cout << "value a: " << a << endl;
  //      cout << "a did not throw " << endl;
		alist.push_back(a);
  //      cout << "a did not throw " << endl;
		return n + 1;
        } else if ( n == 0 ) {
//	cout << "p3" << " " << m << " " << n << endl;	
		bcounter++;
//	cout << "value : " << blist[bcounter] << endl;
		if ((b = random()) % freq == 0 ){
//	cout << "value b: " << b << endl;
	blist.push_back(b); throw E();}
//	cout << "value b: " << b << endl;
//	cout << "did not throw b" << " " << m << " " << n << endl;	
//	cout << "p4" << " " << m << " " << n << endl;	
		blist.push_back(b);
//	cout << "did not throw b" << " " << m << " " << n << endl;	
                try {
//	cout << "p5" << " " << m << " " << n << endl;	
                        return Ackermann2( m - 1, 1 );
                } catch( E ) {
//	cout << "p6" << " " << m << " " << n << endl;	
                print( cout << "E1 " << m << " " << n << endl );
                } // try
//	cout << "p7" << " " << m << " " << n << endl;	
        } else {
//	cout << "p8" << " " << m << " " << n << endl;	
                try {
//	cout << "p9" << " " << m << " " << n << endl;	
                        return Ackermann2( m - 1, Ackermann2( m, n - 1 ) );
                } catch( E ) {
//	cout << "p10" << " " << m << " " << n << endl;	
                        print( cout << "E2 " << m << " " << n << endl );
                } // try
//	cout << "p11" << " " << m << " " << n << endl;	
        } // if
//	cout << "p12" << " " << m << " " << n << endl;	
        return 0; // recover by returning 0
}

int set;
jmp_buf base;

long int Ackermann3( long int m, long int n ) {
	jmp_buf localEnv;
		memcpy(localEnv, env, sizeof localEnv );
	cout << "p1" << " " << m << " " << n << endl;	
	if ( m == 0 ) {
	cout << "p2" << " " << m << " " << n << endl;	
		acounter++;
	cout << "value a: " << alist[acounter] << endl;
		if ( alist[acounter] % freq == 0 ) longjmp(env, 1);
        cout << "a did not throw " << endl;
		memcpy(env, base, sizeof base);		
		return n + 1;
	} else if ( n == 0 ) {
	cout << "p3" << " " << m << " " << n << endl;	
		bcounter++;
	cout << "value : " << blist[bcounter] << endl;
		if ( blist[bcounter] % freq == 0 ) longjmp(env, 1);
	cout << "did not throw b" << " " << m << " " << n << endl;	
	cout << "p4" << " " << m << " " << n << endl;	
		
		if(!setjmp(env)){
	cout << "p5" << " " << m << " " << n << endl;	
	//	try {
			return Ackermann3( m - 1, 1 );
		}else {
	cout << "p6" << " " << m << " " << n << endl;	
			print( cout << "E1 " << m << " " << n << endl );
			memcpy(env, localEnv, sizeof env);
		} // try
	cout << "p7" << " " << m << " " << n << endl;	
	} else {
	cout << "p8" << " " << m << " " << n << endl;	
		if(!setjmp(env)){
	cout << "p9" << " " << m << " " << n << endl;	
		//try {
			if(set == 0) { set = 1; memcpy(base, localEnv, sizeof localEnv);}
			return Ackermann3( m - 1, Ackermann3( m, n - 1 ) );	
		} else {
	cout << "p10" << " " << m << " " << n << endl;	
			print( cout << "E2 " << m << " " << n << endl );
			memcpy(env, localEnv, sizeof env);
		} // try
	cout << "p11" << " " << m << " " << n << endl;	
	} // if
	cout << "p12" << " " << m << " " << n << endl;	
	return 0; // recover by returning 0
}


long int Ackermann( long int m, long int n, jmp_buf cvn) {
	jmp_buf cvn2;
	long int a;
	long int b;
//	cout << "p1" << " " << m << " " << n << endl;	
	if ( m == 0 ) {
//	cout << "p2" << " " << m << " " << n << endl;	
		if ((a = random()) % freq == 0 ){ alist.push_back(a); 
//	cout << "value a: " << a << endl;
								longjmp(cvn,1);}
//	cout << "value a: " << a << endl;
  //      cout << "a did not throw " << endl;
		alist.push_back(a);
		return n + 1;
	} else if ( n == 0 ) {
//	cout << "p3" << " " << m << " " << n << endl;	
		if ((b = random()) % freq == 0 ){
//	cout << "value b: " << b << endl;
	blist.push_back(b); longjmp(cvn,1);}
//	cout << "value b: " << b << endl;
//	cout << "did not throw b" << " " << m << " " << n << endl;	
//	cout << "p4" << " " << m << " " << n << endl;	
		blist.push_back(b);
		if(!setjmp(cvn2)){
//	cout << "p5" << " " << m << " " << n << endl;	
			return Ackermann( m - 1, 1, cvn2);
		}else {
//	cout << "p6" << " " << m << " " << n << endl;	
		print( cout << "E1 " << m << " " << n << endl );
		} // try
//	cout << "p7" << " " << m << " " << n << endl;	
	} else {
//	cout << "p8" << " " << m << " " << n << endl;	
		if(!setjmp(cvn2)){
//		cout << "p9" << " " << m << " " << n << endl;	
			return Ackermann( m - 1, Ackermann( m, n - 1, cvn2), cvn2 );
		}else {
//		cout << "p10" << " " << m << " " << n << endl;	
			print( cout << "E2 " << m << " " << n << endl );
		} // try
//		cout << "p11" << " " << m << " " << n << endl;	
	} // if
//		cout << "p12" << " " << m << " " << n << endl;	
	return 0; // recover by returning 0
}


int main( int argc, const char * argv[ ] ) {
	long int Ackermann( long int m, long int n,jmp_buf cvn );
	long int Ackermann4( long int m, long int n);
	long int m = 4, n = 6, seed = getpid(); // default values
//	jmp_buf cvn;
	switch ( argc ) {
		case 5: freq = atoi( argv[4] );
		case 4: seed = atoi( argv[3] );
		case 3: n = atoi( argv[2] );
		case 2: m = atoi( argv[1] );
	} // switch
	srandom( seed );
	cout << m << " " << n << " " << seed << " " << freq << endl;
	if(!setjmp(env)){
//		cout << Ackermann( m, n, cvn) << endl;
		cout << Ackermann( m, n, env) << endl;
	}else {
		print( cout << "E3" << endl );
	} // try	
//	cout << random() << endl;
	 cout << m << " " << n << " " << seed << " " << freq << endl;
	jmp_buf c;
	 genv = &c;
        if(!setjmp(c)){
                cout << Ackermann4( m, n ) << endl;
        } else{
                print( cout << "E3" << endl );
        } // try

	for(int i = 0; i < alist.size(); i++){
		cout << "a list " << alist[i] << endl;
	}
	for(int i = 0; i < blist.size(); i++){
		cout << "b list " << blist[i] << endl;
	}
	cout << alist.size() + blist.size() << endl;
	cout << acounter << endl;
	cout << bcounter << endl;
}

