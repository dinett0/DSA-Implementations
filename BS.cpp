#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <iomanip>
using namespace std;

const int SIZE = 30;

template<typename T>
T random(T range_from, T range_to) {
	std::random_device                  rand_dev;
	std::mt19937                        generator(rand_dev());
	std::uniform_int_distribution<T>    distr(range_from, range_to);
	return distr(generator);
}

int binary_search(const vector<int> &v, int sample) {
	int l = 0, r = v.size() - 1, m = (l + r) / 2;
	int i = 0;
	while (l < r)//previous condition was l!=r, but it failed 
	{
		cout << i++ << ": " << l << " " << r << '\n';
		if (sample > v[m])
		{
			l = m + 1;
		}
		else if (sample <= v[m])
		{
			r = m - 1;
		}
		m = (l + r) / 2;//previously it was at the beginning of loop
	}
	cout << "m: " << m << '\n';
	return sample > v[m] ? m + 1 : m;
}

void test() {
	vector<int> v;

	for (size_t i = 0; i < SIZE; i++)
	{
		int buff = random(0, 50);
		v.push_back(buff);
	}

	std::sort(v.begin(), v.end());
	for (size_t i = 0; i < SIZE; i++)
	{
		cout << setw(2) << i << " ";
	}
	cout << '\n';
	for (auto& i : v)
	{
		cout << setw(2) << i << " ";
	}
	cout << '\n';

	int n;
	cin >> n;

	cout << binary_search(v, n);
}

int main() {
	test();
}