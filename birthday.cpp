

//============================================================================
// Name        : bday.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include<stdlib.h>
using namespace std;
void fillUp(int birthdays [], int size)
{
    for (int i = 0; i < size; i++)
    {
        birthdays[i] = rand() % 365 + 1;
    }
}

int main(void) {
int birthdays[50];
int trials = 5000;
int flag;
double total;
int collisions[50];
   // number of people "in the room"
   for (int i = 2; i < 50; i++)
      {
      collisions[i] = 0;
      // do 5000 trials:
      for (int t = 0; t < trials; t++)
       {
        fillUp(birthdays, i);
        flag = 0;
        // compare all pairs (j,k):
        for (int j = 0; j < i - 1 && flag == 0; j++)
        {
          for (int k = j + 1; k < i && flag == 0; k++ )
          {
            if (birthdays[k] == birthdays[j])
            {
              collisions[i]++;
              flag = 1;
            }
          }
        }
      }
    total = collisions[i] / 5000.0;
    std::cout << "For " << i << " people in the room the probability is " << total << std::endl;
    }
return 0;
}
/*Output:
For 2 people in the room the probability is 0.0028
For 3 people in the room the probability is 0.0076
For 4 people in the room the probability is 0.0188
For 5 people in the room the probability is 0.0234
For 6 people in the room the probability is 0.0428
For 7 people in the room the probability is 0.0576
For 8 people in the room the probability is 0.075
For 9 people in the room the probability is 0.0916
For 10 people in the room the probability is 0.1152
For 11 people in the room the probability is 0.1396
For 12 people in the room the probability is 0.1734
For 13 people in the room the probability is 0.1912
For 14 people in the room the probability is 0.2118
For 15 people in the room the probability is 0.247
For 16 people in the room the probability is 0.2778
For 17 people in the room the probability is 0.3188
For 18 people in the room the probability is 0.335
For 19 people in the room the probability is 0.386
For 20 people in the room the probability is 0.42
For 21 people in the room the probability is 0.4414
For 22 people in the room the probability is 0.4838
For 23 people in the room the probability is 0.5082
For 24 people in the room the probability is 0.545
For 25 people in the room the probability is 0.5744
For 26 people in the room the probability is 0.617
For 27 people in the room the probability is 0.6182
For 28 people in the room the probability is 0.647
For 29 people in the room the probability is 0.6796
For 30 people in the room the probability is 0.71
For 31 people in the room the probability is 0.7212
For 32 people in the room the probability is 0.75
For 33 people in the room the probability is 0.7782
For 34 people in the room the probability is 0.795
For 35 people in the room the probability is 0.8208
For 36 people in the room the probability is 0.8264
For 37 people in the room the probability is 0.8538
For 38 people in the room the probability is 0.8644
For 39 people in the room the probability is 0.8782
For 40 people in the room the probability is 0.8974
For 41 people in the room the probability is 0.896
For 42 people in the room the probability is 0.9154
For 43 people in the room the probability is 0.9244
For 44 people in the room the probability is 0.9306
For 45 people in the room the probability is 0.9402
For 46 people in the room the probability is 0.9484
For 47 people in the room the probability is 0.9488
For 48 people in the room the probability is 0.9592
For 49 people in the room the probability is 0.9706
*/
