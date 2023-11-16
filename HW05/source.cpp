#include <array>
#include <vector>
#include <string>
#include <iostream>

using namespace std;

int main(int argc, char const* argv[]) {
	
	//array
	cout << "=====array======" << endl;
	array<int, 8> arr1 = { 1, 2, 3 };
	
	cout << "elements of arr1 : ";
	for (int i= 0 ; i < arr1.size(); ++i) {
		cout << arr1[i] << " ";
	}
	cout << endl;

	cout << "elements of arr1 (reverse): ";
	array<int, 8>::reverse_iterator riter;
	for (riter = arr1.rbegin(); riter != arr1.rend(); ++riter) {
		cout << *riter << " ";
	}
	cout << endl;

	//array 2 dimention
	array<array<int, 8>, 4> arr2 = { 0 };
	array<array<int, 8>, 4>::iterator row;
	array<int, 8>::iterator col;
	cout << "elements of arr2" << endl;
	for (row = arr2.begin(); row != arr2.end(); ++row) {
		for (col = (*row).begin(); col != (*row).end(); ++col) {
			cout << *col << " ";
		}
		cout << endl;
	}
	cout << endl;

	int i = 0;
	for (row = arr2.begin(); row < arr2.end(); ++row) {
		(*row).fill(i++);
	}

	cout << "elements of arr2 (after fill)" << endl;
	for (int i=0; i < arr2.size(); i++) {
		for (int j = 0; j < arr2[i].size(); j++) {
			cout << arr2[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;

	cout << "value of arr2[0][7]: ";
	cout << (arr2.front()).back() << endl;
	cout << "value of arr2[3][4]: ";
	cout << (arr2.at(3)).at(4) << endl;
	cout << endl;

	//vector
	cout << "======vector======" << endl;
	vector<int> v1(5);

	if (v1.empty())
		cout << "v1 is empty" << endl;
	else
		cout << "v1 is not empty" << endl;

	cout << "size of v1: " << v1.size() << endl;
	cout << "capacity of v1: " << v1.capacity() << endl;
	cout << "elements of v1: ";
	for (int i = 0; i < v1.size(); ++i) { cout << v1[i] << " "; }
	cout << endl << endl;

	for (int i = 0; i < v1.size(); ++i) { v1[i] = i + 1; }
	for (int i = 10; i < 20; ++i) { v1.push_back(i); }

	cout << "--- After push_back ---" << endl;
	cout << "size of v1: " << v1.size() << endl;
	cout << "capacity of v1: " << v1.capacity() << endl;
	cout << "elements of v1: ";
	vector<int>::iterator it;
	for (it = v1.begin(); it != v1.end(); ++it) { cout << *it << " "; }
	cout << endl << endl;

	for (int i = 0; i < 5; i++)
		v1.pop_back();
	v1.shrink_to_fit();

	cout << "--- After pop_back ---" << endl;
	cout << "size of v1: " << v1.size() << endl;
	cout << "capacity of v1: " << v1.capacity() << endl;
	cout << "elements of v1: ";
	for (int i = 0; i < v1.size(); ++i) { cout << v1[i] << " "; }
	cout << endl;

	vector <int> v2(5, 3);
	cout << endl << "elements of v2: ";
	for (int i = 0; i < v2.size(); ++i) { cout << v2[i] << " "; }
	cout << endl << endl;

	v1.swap(v2);
	cout << "--- After swap v1, v2 ---" << endl;
	cout << "size of v1: " << v1.size() << endl;
	cout << "capacity of v1: " << v1.capacity() << endl;
	cout << "elements of v1: ";
	for (int i = 0; i < v1.size(); ++i) { cout << v1[i] << " "; }
	cout << endl;
	cout << "size of v2: " << v2.size() << endl;
	cout << "capacity of v2: " << v2.capacity() << endl;
	cout << "elements of v2: ";
	for (int i = 0; i < v2.size(); ++i) { cout << v2[i] << " "; }
	cout << endl << endl;

	//string
	cout << "======string======" << endl;
	string str1 = "Hello World!";
	cout << "str1: " << str1 << endl;
	string::reverse_iterator rit;
	cout << "str1 (reverse): ";
	for (rit = str1.rbegin(); rit != str1.rend(); ++rit) { cout << *rit; }
	cout << endl << endl;

	int n = str1.find("llo", 0);
	cout << "str1's 'llo' location : " << n << endl;
	str1.erase(2, 3);
	cout << "delte 'llo' in str1 : " << str1 << endl;

	string str2 = "Bye!";
	cout << "str2 : " << str2 << endl << endl;
	if (str1.compare(str2))
		cout << "str1 and str2 are not same" << endl;
	else
		cout << "str and str2 are same" << endl;

	return 0;
}