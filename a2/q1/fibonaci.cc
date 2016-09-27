#include <iostream>
using namespace std;

_Coroutine Fibonacci{
  int fn;
  void main(){
	int fn1, fn2;
	fn = 0; fn1 = fn;
	suspend();
	fn = 1; fn2 = fn1; fn1 = fn;
	suspend();
	for( ;; ){
		fn = fn1 + fn2; fn2 = fn1; fn1 = fn;
		suspend();
	}
  }
  public:
	int next(){
		resume();
		return fn;
	}
};
void uMain::main(){
    Fibonacci f1, f2;
    for(int i = 1; i <= 10; i+= 1){
	cout << f1.next() << " " << f2.next() << endl;
    }
}

