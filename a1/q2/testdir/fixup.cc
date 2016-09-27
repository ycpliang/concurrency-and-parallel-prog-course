#include <iostream> 
using namespace std;

void f(void (*fixup1)(), void (*fixup2) () ){
	fixup1();
	cout << "finish" << endl;
	fixup2();
	cout << "finish" << endl;
}

void fixup1(){
	cout << "handler 1" << endl;
}

void fixup2(){
	cout << "handler 3 " << endl;
}

int main(){
	f( fixup1, fixup2);
//	f( fixup2);
}
