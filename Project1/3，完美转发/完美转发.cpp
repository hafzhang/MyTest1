#include<iostream>
using namespace std;

void func1(int& ii) {
	cout << "��������ֵ=" << ii << endl;
}
void func1(int&& ii) {
	cout << "��������ֵ=" << ii << endl;
}

void func2(int& ii) {  //��ֵ�汾
	func1(ii);
}
void func2(int&& ii) {  //��ֵ�汾
	func1(move(ii));
}
/*
1��ģ���к���������д��T&&����ô�����ȿ��Խ�����ֵ���ã��ֿ��Խ�����ֵ���á�
2���ṩģ�庯��std::forward<T>(����)������ת�����������������һ����ֵ��ת
   ����������ֵ���ã����������һ����ֵ��ת������Ȼ����ֵ���á�
*/
template<typename T>
void func3(T&& ii,int&& jj) {  //T&& ii���Խ�����ֵ����ֵ,int&& jjֻ�ܽ�����ֵ
	func1(forward<T>(ii));
}



int main() {
	int ii = 3;
	func1(ii);      //������ֵ����
	func1(4);       //������ֵ����

	int jj = 5;
	func2(jj);      //������ֵ����
	func2(6);       //������ֵ����
	
	int kk = 7;
	func3(kk,9);      //������ֵ����
	func3(8,9);       //������ֵ����
	system("pause");
	return EXIT_SUCCESS;
}