#include <iostream>
using namespace std;

volatile int N = 10000000, shared = 0;    // ignore volatile, prevent dead-code removal

_Task increment {
    void main() {
        for ( int i = 1; i <= N; i += 1 ) {
            shared += 1;    // no -O2 to prevent atomic increment instruction
        } // for
    }
};
void uMain::main() {
    if ( argc == 2 ) iterations = atoi( argv[1] );
#ifdef __U_MULTI__
    uProcessor p;                        // create 2nd kernel thread
#endif // __U_MULTI__
    {
        increment t[2];
    } // wait for tasks to finish
    cout << "shared:" << shared << endl;
}
