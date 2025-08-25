#include "XORList.tpp"
#include <algorithm>

int main()
{
	XORLL<int> ll;
	for (int i : {1, 2, 3}) ll.push_back(i);
	for (int i : {6, 5}) ll.push_front(i);

	std::cout << ll << std::endl;

	for (int i : ll) std::cout << i << " ";
	std::cout << std::endl;
	
	
	for (auto it = ll.rbegin(); it != ll.rend(); --it) {
		*it += 10;
		std::cout << *it << " ";
	}
	std::cout << std::endl;


	auto l = [](int val) {
		std::cout << val << " ";
	};

    std::for_each(ll.begin(), ll.end(), l);

	std::cout<< "\nmoving\n";
	XORLL<int> mv{};
	mv = std::move(ll);
	std::cout << mv << std::endl;
	std::cout << ll << std::endl;
}