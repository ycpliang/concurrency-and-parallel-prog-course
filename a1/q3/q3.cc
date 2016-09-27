#include <iostream>
#include <fstream>
using namespace std;

_Coroutine Utf8 {
  public:
    _Event Match {
      public:
        unsigned int unicode;
        Match( unsigned int unicode ) : unicode( unicode ) {}
    };
    _Event Error {};
  private:
    union UTF8 {
        unsigned char ch;                // character passed by cocaller
        struct {                         // types for 1st UTF-8 byte
            unsigned char dt : 7;        // data
            unsigned char ck : 1;        // check
        } t1;
        struct {
            unsigned char dt : 5;        // data
            unsigned char ck : 3;        // check
        } t2;
        struct {
            unsigned char dt : 4;
	    unsigned char ck : 4;
	    // YOU FIGURE IT OUT
        } t3;
        struct {
	    unsigned char dt : 3;
	    unsigned char ck : 5;
            // YOU FIGURE IT OUT
        } t4;
        struct {                 
	    unsigned char dt : 8;
	    unsigned char ck : 8;	        // type for extra UTF-8 bytes
            // YOU FIGURE IT OUT
        } dt;
    } utf8;
    // YOU MAY ADD PRIVATE MEMBERS
    bool check(){
	if(!utf8.t1.ck){
		cout << std::hex << (0 | utf8.t1.dt) << endl;
	}
	cout << std::hex << (110 | utf8.t2.dt) <<  endl;
	cout << std::hex << (1110 | utf8.t3.dt) <<  endl;
	}
    void main(){
	for(;;){
	for(;;){
		if( utf8.ch != '\n'){
			cout << "0x"<< std::hex << (unsigned int)(unsigned char)utf8.ch << " : ";
			check();
			suspend();
		}else{
			//suspend();
				break;
		}	
	}
	}
	cout << "hello" << endl;
	
    }
  public:
    // YOU MAY ADD CONSTRUCTOR/DESTRUCTOR IF NEEDED
    void next( unsigned char c ) {
        utf8.ch = c;                     // insert character into union for analysis
        resume();
    }
};



void uMain::main(){
	char nextChar;
	Utf8 translate;
	if(argc > 1){	
		ifstream is (argv[1]);
		while(is.read(&nextChar, 1)){
			translate.next(nextChar);
		}
		is.close();	
	}else{
		while(cin >> nextChar){
			translate.next(nextChar);
		}	
	}

}
