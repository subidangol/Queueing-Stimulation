#include<iostream>
#include<stdlib.h>
#include<iomanip>
#include "queue1.h"
#include "function.cxx"
using namespace std;

//prototype
int total(Queue q[], int, int&);
//precondition – an object and an integer has been passed
//postcondition – returns the sum of all the transactions

int find(Queue q[], int [], int);
//precondition – an object, an array and an integer has been passed
//postcondition – returns the shortest line number

int main()
{
  int time, entry_time, seed, max_trans_time, duration, arv_prov, ave_wt, servers, new_time,
  shortest_line; //integer declarations for the simulation
  int wait_time = 0, count = 0, c_count = 0, wait_sum = 0; //initializes four integers to zero
  cout << "Enter the number of queue/server pairs: ";
  cin >> servers; //store the number of tellers
  Queue line[servers]; //new object that is an array
  int teller[servers];  //array for teller time
  for(int k = 0; k < servers; ++k)
    teller[k] = 0; //initializes the array of time to zero
  cout << "\nEnter the probability that a customer arrives in one tick (%): ";
  cin >> arv_prov; //probability for a customer to arrive
  cout << "\nEnter the maximum duration of a transaction in ticks: ";
  cin >> max_trans_time; //max transaction time for each transaction
  cout << "\nEnter the duration of the simulation in ticks: ";
  cin >> duration; //time for simulation
  cout << "\nEnter a random number seed: ";
  cin >> seed; //for randomizing customer arrival and transaction time
  srand(seed); //calls a random number
  for(time = 0; time < duration; ++time) //for every tick of the time
  {
    if(rand() % 100 < arv_prov) //if customer arrives
    {
      shortest_line = find(line, teller, servers); //find shortest line
      line[shortest_line].enqueue(time); //add to the line
    }
    for(int i = 0; i < servers; i++) //for every teller line
    {
      if(teller[i] == 0) //if the teller is free
      {
        if(!line[i].empty()) //the line is empty
        {
          entry_time = line[i].dequeue(); //start the next transaction by the teller
          wait_sum += (time - entry_time); //add the time of transaction
          ++count; //increment the customer total
          teller[i] = (rand() % max_trans_time) + 1; //have a random transaction time
          new_time = time - entry_time;
          if(new_time > wait_time) //for the maximum wait time
            wait_time = new_time;
        }
      }
      else
        --teller[i]; //if the teller is in a transaction, reduce the time for the transaction
    }
    //SNAPSHOT – display the simulation for that time
    cout << endl << setw(3) << time+1 << setw(6) << teller[0] << "   " << line[0] << endl;
    if(servers > 1)
      for(int j = 1; j < servers; ++j)
        cout << setw(9) << teller[j] << "   " << line[j] << endl;
  }

  //report the statistics
  ave_wt = wait_sum/count;
  total(line, servers, c_count);
  cout << count << " customers waited an average of " << ave_wt << " ticks." << endl;
  cout << "The longest time a customer waited was " << wait_time << " ticks." << endl;
  cout << c_count << " customers remain in the lines." << endl;
}

int total(Queue q[], int servers, int &sum)
{
  sum += q[servers-1].length();
  if(servers > 1)
    total(q, servers-1, sum);
}

int find(Queue q[], int teller[], int servers)
{
  int shortest_line = 0;
  for(int i = 0; i < servers; ++i)
  {
    if(teller[i] == 0 && q[i].length() == 0)
      return i;
    else if (q[i].length() < q[shortest_line].length())
      shortest_line = i;
  }
  return shortest_line;
}
