#include <iostream>
#include "MultiMap.h"
#include "ExtendedTest.h"
#include "ShortTest.h"
#include "MultiMapIterator.h"

using namespace std;


int main() {
    test_operation();
    testAll();
	testAllExtended();
	cout << "End" << endl;
	system("pause");

}
