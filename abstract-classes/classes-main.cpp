#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <fstream>
#include <cassert>
using namespace std;

struct Node{
   Node* next;
   Node* prev;
   int value;
   int key;
   Node(Node* p, Node* n, int k, int val):prev(p),next(n),key(k),value(val){};
   Node(int k, int val):prev(NULL),next(NULL),key(k),value(val){};
};

class Cache{

   protected: 
    map<int,Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

};

class LRUCache: public Cache {

   void reorder(Node* n) {
      // Base cases
      if (n == this->head) {
         return;
      } else if (n == this->tail) {
         n->prev->next = NULL;
         tail = n->prev;
      } else {
         n->prev->next = n->next;
         n->next->prev = n->prev;
      }

      // Set head node prev/nexts
      this->head->prev = n;
      n->prev = NULL;
      n->next = this->head;

      // New node is head
      this->head = n;

   }
   void insert(Node * n) {
      if (this->mp.size() == 0) { // Empty start - need to set heads
         this->head = n;
         this->tail = n;
         this->tail->next = NULL;
      } else if (this->mp.size() == this->cp) {
         // Delete last node and remove from map
         Node * t = this->tail->prev;
         t->next = NULL;
         this->mp.erase(tail->key);
         this->tail = t;
      } else {
         this->head->prev = n;
      }

      
      // If n is not the tail
      if (n != this->tail){
         n->next = this->head;
      }
       // Add to front of linked list and map
      this->head = n;
      this->mp[n->key] = n;
   }
   public:
      LRUCache(int capacity){
         this->cp = capacity;
      };
      void printlist() {
         Node * curr = this->head;
         while (curr != this->tail) {
            cout << "Key: " << curr->key << " Val: " << curr->value << endl;
            curr = curr->next;
         }
      }
      void set(int k, int v) {
         Node * n;
         try {
            n = mp.at(k);
            n->value = v;
            reorder(n);
         } catch (out_of_range) {
            n = new Node(k,v);
            insert(n);
         }
      }
      int get(int k) {
         try {
            return mp.at(k)->value;
         } catch (out_of_range) {
            return -1;
         }
      } 
};


int main() {
   ifstream testfile;
   testfile.open("output01.txt");


   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         int val;
         int expected_val;
         cin >> key;
         val = l.get(key);
         testfile >> expected_val;
         if (val != expected_val) {
            cout << val << endl;
            cout << expected_val << endl;
            exit(1);
         }
         cout << val << endl;
      }
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
