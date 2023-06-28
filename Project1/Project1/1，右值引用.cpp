#include<iostream>
using namespace std;

class AA{
public:
	int m_a=9;
};
AA getTemp() {
	return AA();
}

int main() {
	int a = 3;
	int b = 8;

	int && c = b + 5;
	AA&& aa = getTemp();

	cout << "a=" << a << endl;
	cout << "c=" << c << endl;
	cout << "aa.m_a=" << aa.m_a << endl;

	system("pause");
	return EXIT_SUCCESS;

}