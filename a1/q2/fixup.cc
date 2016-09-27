#include <iostream>
using namespace std;

#ifdef NOOUTPUT
#define print( x )
#else
#define print( x ) x
#endif

_Event E1 {
  public:
    int &i, &j;
    E1( int &i, int &j ) : i( i ), j( j ) {}
};
_Event E2 {
  public:
    int &i;
    E2( int &i ) : i( i ) {}
};
_Event E3 {
  public:
    int i;
    E3( int i ) : i( i ) {}
};

/*
void fixup1(int& i, int& j){
//cout << "1" << endl;
e.i = i;
e.j = j;
}

void fixup2(int& j, int& k){
//cout << "2" << endl;
E2 e(j);
e.i = k;
}

void fixup3(int i, int &j){
//cout << "3" << endl;
E3 e(i);
print( cout << e.i << " p4p " << j << endl );

}*/

int C( int & i, int & j, void (*fixup1)(int &, int &), void (*fixup2)(int &, int &), void (*fixup3)(int, int &), int & k ) {
    print( cout << i << " p1p " << j << endl );
  //  _Resume E1( i, j );	
	E1 e(i,j);
	fixup1(i, j);
    print( cout << i << " p2p " << j << endl );
	fixup2(j, k);
//    _Resume E2( j );
    print( cout << i << " p3p " << j << endl );
  	fixup3(27, j);
	//_Resume E3( 27 );
    return i;
}
int B( int i, int j, void (*fixup1)(int &, int &), void (*fixup2)(int &, int &),void (*fixup3)(int, int &), int k, int m, int n ) {
    if ( i > 0 ) B( i - 1, j, fixup1, fixup2, fixup3, k);
    return C( i, j, fixup1, fixup2, fixup3, k);
}
int A( int i, int j, int times ) {
    int k = 27, ret;
//  try {
        for ( int i = 0; i < times; i += 1 ) {
            ret = B( i, j, fixup1, fixup2, fixup3,k, i ,j );
        }
        return ret;
 //   } _CatchResume( E1 e ) {
   //     e.i = i;
    //    e.j = j;
   // } _CatchResume( E2 e ) {
    //    e.i = k;
   // } _CatchResume( E3 e ) {
    //    print( cout << e.i << " " << j << endl );
   // }
}
void uMain::main() {
    long int m = 4, n = 6, times = 1;    // default values

    switch ( argc ) {
      case 4: times = atoi( argv[3] );
      case 3: n = atoi( argv[2] );
      case 2: m = atoi( argv[1] );
    } // switch
    cout << m << " " << n << " " << A( m, n, times ) << endl;
}
