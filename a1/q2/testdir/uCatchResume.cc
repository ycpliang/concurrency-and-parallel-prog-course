#include <iostream>
using namespace std;

//_Event E{};
_Event E2 {
 public:
	int i;
	E2 (int i) : i(i){}
};

_Event E1 {
  public:
	int i;
	E1(int i) : i( i) {}

};


void f(int i){
_Resume E1 (3);
cout << "Finish" << i << endl;
_Resume E2 (5);
cout << "E2 Finish" << i << endl;
}

void uMain::main(){
try {
	f(4);
}_CatchResume(E1 e){
	e.i = 1;
	cout << "handler 1" << endl;
}_CatchResume(E2 e){
	e.i = 2;
	cout << "handler 3" << endl;
}

}
