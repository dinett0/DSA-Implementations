	//Well i just typed vector in cppreference 
	//and started to implement everything piece-by-piece

	//Implemented methods:
	//-push_back()
	//-shrink_to_fit()
	//-reserve()
	//-sort()(Bubble)
	//-pop()
	//-display
	//-plethora of minor methods

	//Future:
	// -All copy operations to move
	// -MyVector() : m_size(0), m_capacity(0), m_data(nullptr) {}
	// -Initializer-list
	// -Template

	//Features:
	// -Display using bit-shifting +
	// -Copy-Constructor +
	// -Index access +


#include <iostream>
#include <vector>
namespace Vector {

	class Vector {//just implement integer vector
		int* arr = nullptr;
		int m_size{};
		int m_capacity{};

	public:
		Vector()
		{
		}

		Vector(int size) {
			this->m_size = size;
			this->m_capacity = 2 * size;
			arr = new int[m_capacity] {};
		}

		Vector(const Vector& other) {//Copy-Constructor
			this->m_size = other.m_size;
			this->m_capacity = 2 * m_size;
			arr = new int[m_capacity] {};

			for (size_t i = 0; i < m_size; i++)
				this->arr[i] = other[i];
		}

		~Vector() {
			delete[] arr;
		}

		void shrink_to_fit() {
			if (m_size < m_capacity)
			{
				int* shrunck = new int[m_size];
				for (size_t i = 0; i < m_size; i++)
				{
					shrunck[i] = arr[i];
				}
				delete[] arr;
				arr = shrunck;
				m_capacity = m_size;
			}
		}

		void reserve(const int new_cap) {
			if (new_cap > m_capacity)
			{
				int* new_arr = new int[new_cap];
				for (size_t i = 0; i < m_size; i++)
				{
					new_arr[i] = arr[i];
				}
				delete[] arr;
				arr = new_arr;
				m_capacity = new_cap;
			}
		}

		void display() {
			for (size_t i = 0; i < m_size; i++)
				std::cout << arr[i] << ' ';
		}


		void push_back(int a) {
			if (m_size == m_capacity)
			{
				reserve(m_capacity == 0 ? 1 : m_capacity * 2);
			}
			arr[m_size++] = a;
		}

		void pop_back() {
			if (m_size > 0)
			{
				m_size--;
			}
		}

		void sort() {
			for (size_t i = 0; i < this->m_size - 1; i++)
			{
				bool swap = false;
				for (size_t j = 0; j < this->m_size - 1 - i; j++)
				{
					if (arr[j] > arr[j + 1]) {
						int temp = arr[j];
						arr[j] = arr[j + 1];
						arr[j + 1] = temp;
						swap = true;
					}
				}
				if (!swap)
				{
					return;
				}
			}
			return;
		}
////MINOR//METHODS/////////////////////////////////////////////////////////////////////////////////
		int size() const {
			return m_size;
		}

		int front() {
			return arr[0];
		}

		int back() {
			return arr[m_size];
		}

		bool empty() {
			return !m_size;
		}

		int* data() {
			return arr;
		}

		int& operator[](size_t i) const {
			return arr[i];
		}

		friend std::ostream& operator<<(std::ostream& stream, const Vector& vector);
///////////////////////////////////////////////////////////////////////////////////////////////////
	};

	std::ostream& operator<<(std::ostream& stream, const Vector& vector) {
		std::cout << "[ ";
		for (size_t i = 0; i < vector.size(); i++) {
			stream << vector[i] << " ";
		}
		std::cout << "]\n";
		return stream;
	}
}

int main() {

}
