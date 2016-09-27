#include <iostream>
#include <stdlib.h>
#include <functional>
using namespace std;

#ifdef NOOUTPUT
#define print( x )
#else
#define print( x ) x
#endif

class E1 {
  public:
    int &i, &j;
    E1( int &i, int &j ) : i( i ), j( j ) {}
};
class E2 {
  public:
    int &i;
    E2( int &i ) : i( i ) {}
};
class E3 {
  public:
    int i;
    E3( int i ) : i( i ) {}
};

int C( int i, int j, function<void(E1)> fixup1, function<void(E2)> fixup2 , function<void(E3)> fixup3) {
    print( cout << i << " " << j << endl );
	fixup1(E1 (i , j));
    print( cout << i << " " << j << endl );
	fixup2(E2(j));
    print( cout << i << " " << j << endl );
	fixup3(E3(27));  
    return i;
}
int B( int i, int j, function<void(E1)> fixup1, function<void(E2)> fixup2 , function<void(E3)> fixup3) {
    if ( i > 0 ) B( i - 1, j, fixup1, fixup2, fixup3);
    return C( i, j, fixup1, fixup2, fixup3);
}
int A( int i, int j, int times ) {
    int k = 27, ret;
    function<void(E1)> fixup1 = [i, j](E1 e){ e.i = i; e.j = j;};
    function<void(E2)> fixup2 = [i, j, k](E2 e){ e.i = k;};
    function<void(E3)> fixup3 = [i, j](E3 e){print( cout << e.i << " " << j << endl );};
        
        for ( int i = 0; i < times; i += 1 ) {
            ret = B( i, j, fixup1, fixup2, fixup3);
        }
        return ret;
}
int main(int argc, const char * argv[] ) {
    long int m = 4, n = 6, times = 1;    // default values

    switch ( argc ) {
      case 4: times = atoi( argv[3] );
      case 3: n = atoi( argv[2] );
      case 2: m = atoi( argv[1] );
    } // switch
    cout << m << " " << n << " " << A( m, n, times ) << endl;
}
