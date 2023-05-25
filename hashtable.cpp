//Unordered map is an associative container that contains key-value pairs with unique keys. 
//Search, insertion, and removal of elements have average constant-time complexity.

//Internally, the elements are not sorted in any particular order,
//but organized into buckets.


//Learned abt:  *CRT
//				*CDCDCDCDCDCDCDCD debug value
//				*Magic numbers


//v1.0	-Only supported type is int
//		-Trivial hash function implementation
//		-Rehash is not implemented
//		-Two constructors
//		-Methods: insert, remove, find, cap, size, empty

//v1.1 -Reimplemented constructors using init-list
//	   -Class members renaming('m_' prefix)

//v1.2 -A bit of refactoring and beautification
#include <iostream>
#include <iomanip>
#include <random>
using namespace std;

template<typename T>
T random(T range_from, T range_to) {
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<T>    distr(range_from, range_to);
	return distr(generator);
}

struct element {
	element* next = nullptr;
	int data{};
};

class hash_table {
	const double LOAD_FACTOR{ 0.75 };
	const int DEFAULT_CAPACITY{ 20 };//no magic numbers
	
	int m_size{}, m_capacity{};
	element** buckets{ nullptr };

	int hash_function(const int value) {
		return value % m_capacity;
	}

	element* find_internal(const int value) {//tested
		int hash = hash_function(value);
		//if (buckets[hash] == nullptr)
		//{
		//	cout << "no such element. insert?\n";
		//}
		//else
		//{
		//	element* tmp = buckets[hash];
		//	while (tmp != nullptr)
		//	{
		//		if (tmp->data == value)
		//		{
		//			cout << "found on bucket[" << hash << "]\n";
		//			return;
		//		}
		//		tmp = tmp->next;
		//	}
		//	cout << "no such element. insert?\n";
		//}
		if (buckets[hash])//DRY
		{
			element* tmp = buckets[hash];
			while (tmp != nullptr)
			{
				if (tmp->data == value) 
					return tmp;
				tmp = tmp->next;
			}
		}
		return nullptr;
		/*cout<< ".insert(Y / N) ? \n";
		char c;
		cin >> c;
		if (c == 'Y')
		{
			this->insert(value);
		}*/
	}

	int remove_internal(const int value) {
		int hash = hash_function(value);
		if (!buckets[hash])
			return 1;

		element* head = buckets[hash];
		element* prev = nullptr;
		while (head)
		{
			if (head->data == value)
			{
				element* tmp = head->next;
				delete head;
				prev->next = tmp;
				m_size--;
				return 0;
			}
			prev = head;
			head = head->next;
		}
		return 1;
	}

public:
	hash_table()
		: m_capacity(DEFAULT_CAPACITY), buckets(new element* [m_capacity] {})
	{}

	hash_table(const int m_capacity)
		:m_capacity(m_capacity), buckets(new element* [m_capacity] {})
	{}

	void insert(const int value) {//tested
		int hash = hash_function(value);
		if (buckets[hash])//if the bucket is occupied
		{
			element* tmp = buckets[hash];
			while (tmp -> next)//traverse to the end of chain
				tmp = tmp->next;
			
			tmp->next = new element{ nullptr, value };
		}
		else//else if its free
			buckets[hash] = new element{ nullptr, value };
		cout << "inserted on bucket[" << hash << "]\n";
		m_size++;//NO DUPLICATES HANDLING
	}

	//BADVERSIONBADVERSIONBADVERSIONBADVERSIONBADVERSIONBADVERSIONBADVERSIONBADVERSIONBADVERSIONBADVERSION
	// void remove(const int value) {
	//	element* pov = find_internal(value);//'pov' is a POV of the 'next' field of the previous element
	//	if (!pov) {
	//		cout << "no element \"" << value << "\" to remove\n";
	//	}
	//	else {
	//		if (pov->next == nullptr) {//if 'pov' is at the end of the chain
	//			delete pov;
	//		}
	//		else
	//		{
	//			//element* tmp = pov;
	//			//cout << "pov points to: " << pov << ", and that thing has " << pov->data;
	//			//cout << " and points to " << pov->next << '\n';
	//			//cout << "\ntmp now also points to " << tmp << '\n';
	//			//cout << "but now im assigning pov to " << pov->next << '\n';
	//			//pov = pov->next;
	//			//cout << "pov: " << pov << '\n';
	//			//delete tmp;
	//		}
	//		cout << "element \"" << value << "\" removed\n";
	//		si--;
	//	}
	//}

	void remove(const int value) {//wrapper
		cout << (!remove_internal(value)? "removed\n": "no such element\n");
	}

	void print() {//tested
		for (size_t i = 0; i < m_capacity; i++)
		{
			element* tmp = buckets[i];
			cout << "[" << setw(2) << i << "]";
			while (tmp != nullptr)
			{
				cout << "->" << setw(3) << tmp->data;
				tmp = tmp->next;
			}
			cout << '\n';
		}

	}

	void find(const int value) {//interface wrapper
		if (find_internal(value))
			cout << "element \"" << value << "\" found on bucket[" << hash_function(value) << "]\n";
		else
			cout << "no such element \"" << value << "\"\n";
	}

	int cap() {
		return m_capacity;
	}

	int size() {
		return m_size;
	}
	
	bool empty() {
		return !m_size;
	}
};

//void insert(element *predecessor, int value) {
//	predecessor->next = new element{ nullptr, value };
//}

void test_print() {
	hash_table ht;
	for (size_t i = 0; i < 50; i++)
	{
		ht.insert(random(0, 999));
	}

	ht.print();
}

void test_find() {
	hash_table ht;
	ht.insert(100);
	ht.print();
	ht.find(100);
	ht.find(101);
	ht.find(200);
}

void test_remove() {
	hash_table ht;
	ht.insert(101);
	ht.insert(121);
	ht.insert(141);
	ht.insert(81);
	ht.insert(0);
	ht.insert(100);
	ht.insert(102);

	ht.print();

	ht.remove(61);
	ht.remove(121);

	ht.print();
}

int main() {
	hash_table ht(40);
	for (size_t i = 0; i < ht.cap(); i++)
	{
		ht.insert(random(0, 999));
	}

	ht.print();
}
