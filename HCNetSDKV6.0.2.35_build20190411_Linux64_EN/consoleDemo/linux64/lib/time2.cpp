#include <ctime>
#include <iostream>
#include <typeinfo>
#include <string> 
#include <stdio.h>
#include <sstream>
using namespace std;
int main()
{
	time_t current_time;
        // Stores time in current_time
	time(&current_time);
	cout << current_time << "\n";
	std::cout << typeid(current_time).name() << '\n';	


  //long test = 1234567890L;
  char strLong[1024];
  sprintf(strLong, "%ld", current_time);
  printf("%s\n",strLong);
std::cout << typeid(strLong).name() << '\n';
  return 0;


}
