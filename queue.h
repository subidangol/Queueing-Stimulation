//QUEUEING SIMULATION

#include<iostream>
#include<stdlib.h>
#include<iomanip>
using namespace std;

class Queue
{
  public:
    // MEMBER CONSTANT
    typedef int Item;
    static const int CAPACITY = 100;
    
    // CONSTRUCTOR
    Queue( ) { front = 0; rear = CAPACITY - 1; count = 0; }

    // MODIFICATION MEMBER FUNCTIONS
    void enqueue ( Item entry );
    Item dequeue ( );

    // CONSTANT MEMBER FUNCTIONS
    int length() { return count; }
    bool empty( ) { return count == 0; }
      
    // FRIEND FUNCTION
    friend ostream& operator << (ostream& out_s, Queue q);

  private:
    // DATA MEMBERS
    Item data[CAPACITY];
    int front;
    int rear;
    int count;
    int next_index(int i) { return (i + 1) % CAPACITY; }
};
