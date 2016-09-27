#include <iostream>
using namespace std;

_Coroutine Cons {
	int p1, p2, status; bool done;
	void main(){
		int money = 1;
		for( ;; ){
			if(done)break;
			cout << "receives:" << p1 << ", " << p2;
			cout << "and pays $" << money << endl;
			status += 1;
			suspend();
			money += 1;
		}
		cout << "consumer stoped" << endl;
	}
	public:
	 Cons(): status(0), done(false) {}
	 int delivery(int p1, int p2 ){
	   Cons::p1 = p1;  Cons::p2 = p2;
	   resume();
	   return status;
	 }
	 void stop() {done = true; resume(); }
};

_Coroutine Prod {
	Cons &c;
	int N;
	void main(){
		int i, p1, p2, status;
		for(i = 1; i <= N; i+= 1){
			p1 = rand() % 100;
			p2 = rand() % 100;
			cout << "delivers: " << p1 << ", " << p2 << endl;
			status = c.delivery(p1, p2);
			cout << "gets status: " << status << endl;
		}
		cout << "prod stops" << endl;
		c.stop();
	}
	public:
	  Prod(Cons & c) : c(c) {}
	  void start(int N) {
		Prod::N = N;
		resume();
	  }


};

void uMain::main(){
	Cons cons;
	Prod prod( cons );
	prod.start(5);
}
