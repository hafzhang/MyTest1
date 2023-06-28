#include<iostream>
using namespace std;

void func1(int& ii) {
	cout << "参数是左值=" << ii << endl;
}
void func1(int&& ii) {
	cout << "参数是右值=" << ii << endl;
}

void func2(int& ii) {  //左值版本
	func1(ii);
}
void func2(int&& ii) {  //右值版本
	func1(move(ii));
}
/*
1，模板中函数参数书写成T&&，那么函数既可以接收左值引用，又可以接受右值引用。
2，提供模板函数std::forward<T>(参数)，用于转发参数，如果参数是一个右值，转
   发后仍是右值引用；如果参数是一个左值，转发后仍然是左值引用。
*/
template<typename T>
void func3(T&& ii,int&& jj) {  //T&& ii可以接收左值和右值,int&& jj只能接受右值
	func1(forward<T>(ii));
}



int main() {
	int ii = 3;
	func1(ii);      //调用左值函数
	func1(4);       //调用右值函数

	int jj = 5;
	func2(jj);      //调用左值函数
	func2(6);       //调用右值函数
	
	int kk = 7;
	func3(kk,9);      //调用左值函数
	func3(8,9);       //调用右值函数
	system("pause");
	return EXIT_SUCCESS;
}