#include <stdio.h>
#include <time.h>
#include <fstream>
using namespace std;

int main ()
{
  time_t rawtime;
  struct tm * timeinfo;

  time ( &rawtime );
  timeinfo = localtime( &rawtime);
  printf ("%s", asctime(timeinfo));
  //string x = "abc";
  //char nm = asctime(timeinfo);
  std::ofstream file{"Hello.txt"};
  return 0;
} 
