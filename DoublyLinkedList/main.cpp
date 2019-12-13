#include <iostream>
#include "DList.h"
using namespace std;

int main()
{

	DList li;
	li.push_back(11);
	li.push_back(22);
	li.push_back(33);
	li.push_back(44);
	li.push_back(55);
	li.push_back(66);

	DList::Iterator it;
	for (it = li.begin(); it != li.end(); ++it) {
		cout << *it << "-> ";
	}
	cout << '\n';
	
	it = li.begin();
	++it;
	++it;

	it = li.insert(it, 4, 9);

	for (it = li.begin(); it != li.end(); ++it) {
		cout << *it << "-> ";
	}
	cout << '\n';

	DList li2;
	li2.push_back(7);
	li2.push_back(7);
	li2.push_back(11);
	li2.push_back(33);
	
	it = li.begin();
	++it;
	it = li.insert(it, li2.begin(), li2.end());
	for (it = li.begin(); it != li.end(); ++it) {
		cout << *it << "-> ";
	}
	cout << '\n';
	cout << "----------------------------------------------\n";

	DList::Iterator first = li.begin();
	DList::Iterator last = li.end();
	++first; ++first; ++first;
	--last; --last;
	first = li.erase(first, last);

	for (it = li.begin(); it != li.end(); ++it) {
		cout << *it << "-> ";
	}
	cout << '\n';
	cout << *first << '\n';
	cout << "개수 : " << li.size() << '\n' << '\n';

	cout << "Reverse 실행\n";
	li.reverse();
	for (it = li.begin(); it != li.end(); ++it) {
		cout << *it << "-> ";
	}
	cout << '\n';
	return 0;
}