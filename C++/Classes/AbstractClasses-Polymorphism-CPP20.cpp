#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
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
   map<int,Node*> key_to_node_map_; //map the key to the node in the linked list
   int capacity_;  //capacity
   Node* tail_; // double linked list tail__ pointer
   Node* head_; // double linked list head_ pointer
   virtual void set(int, int) = 0; //set function
   virtual int get(int) = 0; //get function
};

class LRUCache : public Cache {
public:
   LRUCache(int capacity) {
      this->capacity_ = capacity;
      head_ = new Node(0, 0);
      tail_ = new Node(0, 0);
      head_->next = tail_;
      tail_->prev = head_;
   }

    ~LRUCache() {
        Node* current = head_;
        while (current) {
            Node* nextNode = current->next;
            delete current;
            current = nextNode;
        }
    }

    // check if the cache is full
    bool IsCacheFull() {
        return key_to_node_map_.size() >= capacity_;
    }

    // check if the key exists in the cache
    bool IsKeyInCache(int key) {
        return key_to_node_map_.find(key) != key_to_node_map_.end();
    }

    bool HandleCacheHit(int key, int value) {
         Node* node = key_to_node_map_[key];
         removeNode(node);
         node->value = value;
         addNode(node);
         key_to_node_map_[key] = node;

         return true;
    }

    // if it is full, remove the least recently used item
    bool HandleCacheFull() {
         Node* lru = tail_->prev;
         removeNode(lru);
         key_to_node_map_.erase(lru->key);
         delete lru;

         return true;
   }

    // add the new item to the cache
    bool HandleNewKey(int key, int value) {
         Node* newNode = new Node(key, value);
         addNode(newNode);
         key_to_node_map_[key] = newNode;

        return true;
    }

   void set(int key, int value) override {
        // If the key is present in the cache
        if(IsKeyInCache(key)) {
            HandleCacheHit(key, value);
        } else {
            if(IsCacheFull()) {
                HandleCacheFull();
            }
            HandleNewKey(key, value);
        }
   }

   int get(int key) override {
      if(IsKeyInCache(key)) {
         Node* node = key_to_node_map_[key];
         removeNode(node);
         addNode(node);
         return node->value;
      }
      return -1;
   }

private:
   void addNode(Node* node) {
      node->prev = head_;
      node->next = head_->next;
      head_->next->prev = node;
      head_->next = node;
   }

   void removeNode(Node* node) {
      node->prev->next = node->next;
      node->next->prev = node->prev;
   }
};

int main() {
   int n, capacity,i;
   cin >> n >> capacity;
   LRUCache l(capacity);
   for(i=0;i<n;i++) {
      string command;
      cin >> command;
      if(command == "get") {
         int key;
         cin >> key;
         cout << l.get(key) << endl;
      } 
      else if(command == "set") {
         int key, value;
         cin >> key >> value;
         l.set(key,value);
      }
   }
   return 0;
}
