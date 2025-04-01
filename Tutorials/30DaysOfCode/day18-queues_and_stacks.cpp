#include <iostream>

using namespace std;

/*-------------------------------------------------------------------*/
//	Day 18: Queues and Stacks
/*-------------------------------------------------------------------*/
class Node_
{	private:
		char m_data;
		Node_* m_next;
		Node_* m_prev;
	public:
		Node_(const Node_& other) { this->m_data = other.m_data; };
		Node_(char data) { this->m_data = data; m_next = NULL; m_prev = NULL; };
		void setNext(Node_* next) { this->m_next = next; };
		void setPrev(Node_* prev) { this->m_prev = prev; };
		Node_* getNext() { return this->m_next; };
		Node_* getPrev() { return this->m_prev; };
		char getData() { return m_data; };
};

class Queue
{
	protected:
		Node_* m_tail;
		Node_* m_head;

	public:
		Queue();
		~Queue();
		void enqueue(const char c);
		char dequeue();
};

Queue::Queue()
	: m_head(NULL),
	  m_tail(NULL)
{
}

Queue::~Queue()
{
	while(m_head)
	{
		Node_* node = m_head;
		m_head = m_head->getNext();

		delete node;
	}
}

void
Queue::enqueue(const char c)
{
	Node_* node_ = new Node_(c);

	if(!m_head)
	{
		m_head = m_tail = node_;
	}
	else
	{
		m_tail->setNext(node_);
		m_tail = node_;
	}
}

char
Queue::dequeue()
{
	if(m_head)
	{
		char c = m_head->getData();
		Node_* node = m_head;

		m_head = m_head->getNext();
		delete node;

		return c;
	}
	else
	{
		return '\0';
	}
}

class Stack
{
	protected:
		Node_* m_bottom;
		Node_* m_top;

	public:
		Stack();
		~Stack();
		void push(char c);
		char pop();
};

Stack::Stack()
	: m_top(NULL),
	  m_bottom(NULL)
{
}

Stack::~Stack()
{
	while(m_top)
	{
		Node_* node = m_top;
		m_top = m_top->getPrev();

		delete node;
	}
}

void
Stack::push(char c)
{
	Node_* node_ = new Node_(c);

	if(!m_top)
	{
		m_top = m_bottom = node_;
	}
	else
	{
		node_->setPrev(m_top);
		m_top = node_;
	}
}

char
Stack::pop()
{
	if(m_top)
	{
		char c = m_top->getData();
		Node_* top = m_top;

		m_top = m_top->getPrev();
		delete top;

		return c;
	}
	else
		return '\0';
}

class Solution: public Queue, Stack
{
	public: 
		void pushCharacter(char c) { push(c); };
		char popCharacter() { return pop(); };
		void enqueueCharacter(char c) { enqueue(c); };
		char dequeueCharacter() { return dequeue(); };
};
/*-------------------------------------------------------------------*/
int main() {
    // read the string s.
    string s;
    getline(cin, s);
    
  	// create the Solution class object p.
    Solution obj;
    
    // push/enqueue all the characters of string s to stack.
    for (int i = 0; i < s.length(); i++) {
        obj.pushCharacter(s[i]);
        obj.enqueueCharacter(s[i]);
    }
    
    bool isPalindrome = true;
    
    // pop the top character from stack.
    // dequeue the first character from queue.
    // compare both the characters.
    for (int i = 0; i < s.length() / 2; i++) {
        if (obj.popCharacter() != obj.dequeueCharacter()) {
            isPalindrome = false;
            
            break;
        }
    }
    
    // finally print whether string s is palindrome or not.
    if (isPalindrome) {
        cout << "The word, " << s << ", is a palindrome.";
    } else {
        cout << "The word, " << s << ", is not a palindrome.";
    }
    
    return 0;
}