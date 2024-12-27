#include <stdio.h>
#include <iostream> // cout, cerr
#include <fstream> // ifstream

using namespace std;

int main(){

   string line;
   ifstream myfile("Mishi.pgm");

   if (myfile.is_open()){
       while (myfile.good()){
         getline (myfile,line);
         cout << line;
       }
   }
   return 0;
}
