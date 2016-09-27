#include <iostream>
using namespace std;

int main(){
unsigned long int a[] = {1 , 2 , 3 ,4 , 5 ,6};
cout << &a[0] << " " <<  &a[1] << " " <<  &a[2] << endl;
cout << (void * )&a[0] << " " << (void *)&a[1] << " " << (void *)&a[2] << endl;
}
