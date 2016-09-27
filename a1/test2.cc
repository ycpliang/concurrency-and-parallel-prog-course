#include <iostream>
using namespace std;


struct E {};

long int freq = 5;

long int Ackermann( long int m, long int n ) {
	if ( m == 0 ) {
		if ( n % 5 == 0 ) throw E();
		return n + 1;
	} else if ( n == 0 ) {
		if ( m % 5 == 0 ) throw E();
		try {
			return Ackermann( m - 1, 1 );
		} catch( E ) {
			cout << "E1 " << m << " " << n << endl ;
		} // try
	} else {
		try {
			return Ackermann( m - 1, Ackermann( m, n - 1 ) );
		} catch( E ) {
			cout << "E2 " << m << " " << n << endl ;
		} // try
	} // if
	return 0; // recover by returning 0
}

int main() {
	long int Ackermann( long int m, long int n );
	long int m = 4, n = 6, seed = 10;
	cout << m << " " << n << " " << seed << endl;
	try {
		cout << Ackermann( m, n ) << endl;
	} catch( E ) {
		cout << "E3" << endl;
	} // try
}

