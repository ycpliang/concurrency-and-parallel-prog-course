/* longjmp example */
#include <iostream>      /* printf */
#include <setjmp.h>     /* jmp_buf, setjmp, longjmp */
#include <vector>
using namespace std;
int main()
{
  jmp_buf env;
//   jmp_buf temp;
//   setjmp(temp);
//    env.push_back(temp);
 int val;

  val=setjmp(env[0]);
//  cout << "val is " << val << endl;
//  val=setjmp(env[0]);
//  cout << "2 val is " << val << endl;

  if (val == 0){cout << "ran" << endl; longjmp(env, 1);}
  if (val == 1) longjmp(env, 7);
  if (val == 2) longjmp(env, 7);
 
  val=setjmp(env);
  cout << "endingggg" << endl;
  val=setjmp(env);
  if(val == 0){ cout << "still going" << endl;}
  if(val == 1){	longjmp(env,3);}
  cout << "end" << endl;
  

}
