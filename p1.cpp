//=====================================================
// Name			: Class Assignment
// Author		: Dinh Tran
// Date			: Sep 16, 2020
// Purpose		: Record purposes only
// Description		: Small program that refresh the Link list
//=====================================================

#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>


using namespace std;

struct Node
{
  int data;
  Node* next;
};


void printList(Node* head, ostream &outFile);
// print Node list
// in: head of the list, output stream

void deleteList(Node* &head);
// deallocate node list
// in: pass by reference node list

void insertInOrder(Node* &head,int input);
// insert node to node list
// in:        pass by reference node list and value want to insert
// function:  it will add the node to node list in increasing order

void selectDelete(Node* &head, int value);
// delete the selected value
// in:          pass by reference head and value want to delete
// function:    delete the node contain value want to delete
// condition:   increasing order list


// constant variable
const int SIZE = 60;
const int WIDTH = 5;
const int NUM_COLS = 10;
const int MAX_VALUE = 100;
const string OUTFILE1 = "OutputA.txt";
const string OUTFILE2 = "OutputB.txt";

int main()
{
  int random;

  // output File
  ofstream outFile;

  srand(time(0));
  Node* head = nullptr;

  // create Node list
  for (int i = 0; i < SIZE; i++){
    insertInOrder(head,(rand() % MAX_VALUE));
  }

  // output file A
  cout << "\n\n-------------------------------------------------" << endl;
  cout << "Output file A" << endl;
  outFile.open(OUTFILE1);
  printList(head, cout);
  printList(head, outFile);
  outFile.close();

  // delete min
  cout << "------------------delete min---------------------" << endl;
  selectDelete(head, head->data);

  // delete max
  cout << endl;
  cout << "------------------delete max---------------------" << endl;

  Node* max = head;
  while (max->next != nullptr){
    max = max->next;
  }
  selectDelete(head, max->data);
  cout << endl;

  // delete random
  cout << "--------------delete random value----------------" << endl;
  random = rand() % MAX_VALUE;
  cout << "The random delete number is: " << random << endl;
  selectDelete(head, random);

  // output file B
  cout << "Output file B" << endl;
  outFile.open(OUTFILE2);
  printList(head, cout);
  printList(head, outFile);
  outFile.close();

  cout << "\n------------------Program End--------------------\n" << endl;
  // deallocate linked list
  deleteList(head);
  return 0;
}


void printList(Node* head, ostream &out)
{
  int count;
  while (head != nullptr){
    out << setw(WIDTH) << head->data;
    head = head->next;
    count ++;
    if (count == NUM_COLS){
        out << endl;
        count = 0;
    }
  }
}


void deleteList(Node* &head)
{
  Node* temp = nullptr;

  while(head != nullptr){
    temp = head;
    head = head->next;
    delete temp;
  }
}

void insertInOrder(Node* &head, int input)
{
  Node* temp = new Node;
  temp->data = input;
  if (head == nullptr || temp->data <= head->data){
    temp->next = head;
    head = temp;
  }else{
    Node *ptr = head;
    while (ptr->next != nullptr && ptr->next->data < temp->data){
      ptr = ptr->next;
    }
    temp->next = ptr->next;
    ptr->next = temp;
  }
}

void selectDelete(Node* &head, int value)
{
  Node* temp = new Node;
  Node* remove = new Node;

  // delete single node
  if(head->data == value){
    remove = head;
    head = head->next;
    delete remove;
  }else{
    temp = head;
    remove = head->next;
    while(remove->data < value && remove->next != nullptr){
      temp = remove;
      remove = remove->next;
    }
    if (remove->data == value){
      temp->next = temp->next->next;
      delete remove;
    }
  }
}
