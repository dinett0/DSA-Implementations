#include <iostream>
using namespace std;

//template <typename T>
struct element {
	int data;
	element* below;
};

//template <typename T>
class Stack {

public:
	element* head;
	int Size;

	Stack() {
		head = nullptr;
		Size = 0;
	}

	void push(const int x) {
		head = new element({ x, head });
		Size++;
	}

	void pop() {
		element* temp = head;
		head = head->below;
		delete temp;
		Size--;
	}

	bool empty() {
		return !Size;
	}

	int size() {
		return Size;
	}

	int top() {
		return head->data;
	}

	void print(element* node) {
		if (node == nullptr)
		{
			return;
		}
		print(node->below);
		cout << node->data << " ";
	}
};

int main() {
	Stack s;

	cout << sizeof(element) << '\n';

	for (size_t i = 0; i < 5; i++) {
		s.push(i);
		cout << s.top() << '\n';
		cout << s.head << '\n';
	}

	if (!s.empty()) {
		cout << s.top() << " sbeen popped\n";
		s.pop();
		cout << "new top " << s.top();
	}

	cout << '\n' << s.size();
}