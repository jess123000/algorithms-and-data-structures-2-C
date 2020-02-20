// main.cpp
// Alex Harris
// 9/4/19

#include <iostream>
#include "List.hpp"
#include <cassert>

using std::cout;
using std::cerr;
using std::endl;

int main() {
	List testList;
	for (int i = 0; i < 10; ++i) {
		testList.append(i);
	}
	for (int j = 0; j < 10; ++j) {
		assert(testList[j] == j);
	}
	cout << "Append test and [] operator test 1 passed." << endl;
	testList.append(10);
	assert(testList.size() == 11);
	cout << "Size test passed." << endl;
	assert(testList[testList.size() - 1] == 10);
	cout << "Resize test passed." << endl;
	List testList2;
	List testList3;
	testList3 = testList2 = testList;
	for (size_t k = 0; k < testList.size(); ++k) {
		assert(testList2[k] == testList[k]);
		assert(testList3[k] == testList[k]);
	}
	cout << "Assignment operator test and [] operator test2  passed." << endl;
	cout << "All tests have passed." << endl;
	return 0;
}