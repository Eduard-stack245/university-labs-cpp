#include <iostream>
#include <list>
#include <functional>

int main()
{
	// quick sort
	std::list<int> list;
	const int N = 20;
	for (int i = 0; i < N; i++)
	{
		if (i % 2 == 0)
			list.push_back(N - i);
		else
			list.push_front(N - i);
	}
	std::cout << std::endl;
	list.sort();
	for (std::list<int>::iterator it = list.begin(); it != list.end(); it++) {
		std::cout << (*it) << " ";
	}
	//quick sort end
	std::cout << std::endl;
	//sort greater
	list.sort(std::greater<int>());
	for (std::list<int>::iterator it = list.begin(); it != list.end(); it++) {
		std::cout << (*it) << " ";
	}
	std::cout << std::endl;
	//sort greater end

	std::cin.ignore();
}