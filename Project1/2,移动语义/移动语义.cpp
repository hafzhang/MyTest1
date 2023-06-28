#include<iostream>
using namespace std;

class A {
public:
	int* m_data = nullptr;
	A() = default;
	
	void alloc() {   //给数据成员m_data分配内存空间
		m_data = new int;   
		memset(m_data, 0, sizeof(int));
	}
	A(const A& a) {
		cout << "拷贝构造函数。\n";
		if (m_data == nullptr) alloc();          //如果没有内存就分配内存
		memcpy(m_data, a.m_data, sizeof(int));   //将数据从源对象中拷贝过来

	}
	A& operator=(const A& a) {         //赋值函数
		cout << "赋值函数。\n";
		if (this == &a) return *this;   //避免自我赋值
		if (m_data == nullptr) alloc();
		memcpy(m_data, a.m_data, sizeof(int));
		return *this;
	}
	
	A(A&& a) noexcept {                       //移动构造函数
		cout << "using移动构造函数.\n";
		if (m_data != nullptr) delete m_data;  //如果已分配内存先释放掉
		m_data = a.m_data;                     //将资源从源对象中转移过来
		a.m_data = nullptr;                    //将源对象中的指针置空
	}
	A& operator=(A&& a) noexcept {             //移动赋值函数
		cout << "using移动赋值函数。\n";
		if (this == &a) return *this;         //避免自我赋值
		if (m_data != nullptr) delete m_data;  //如果已分配内存先释放掉
		m_data = a.m_data;                     //将资源从源对象中转移过来
		a.m_data = nullptr;                    //将源对象中的指针置空
		return *this;
	}

	~A()
	{
		if (m_data != nullptr) {
			delete m_data; m_data = nullptr;
		}
	}
};

void func(A param)
{
	cout << "using func.\n";
	A a1;
	a1 = std::move(param);  //调用移动赋值
}
void test()
{
	A a;
	// func(a); //error. 
	func(std::move(a)); //通过移动构造构建临时对象
}

int main() {
	/*
	    移动构造函数和拷贝构造函数调用时机是一样的，如果形参是左值，
	调用拷贝构造函数。如果是右值，调用移动构造函数。
	    移动赋值函数和普通赋值函数调用时机是一样的，如果形参是左值，
	调用普通赋值函数。如果是右值，调用移动赋值函数。
	    用std::move()函数把左值转换成右值是成功的。Move()告诉编译器，
	虽然我是左值，但是不要对我用拷贝构造函数，用移动构造函数。
	    左值对象被转移之后，不会立即析构，只有离开自己作用域的时候才
	会被析构，如果继续使用左值中的资源，可能会发生错误。
	*/
	A a1;
	a1.alloc();
	*a1.m_data = 3;     //给堆内存赋值
	cout << "a1.m_data=" << *a1.m_data << endl;

	A a2 = a1;         //调用拷贝构造
	cout << "a2.m_data=" << *a2.m_data << endl;

	A a3;
	a3 = a1;           //调用赋值函数
	cout << "a3.m_data=" << *a3.m_data << endl;


	A b1;
	b1.alloc();
	*b1.m_data = 3;     //给堆内存赋值
	cout << "b1.m_data=" << *b1.m_data << endl;

	A b2 = move(b1);         //调用移动构造函数
	cout << "b2.m_data=" << *b2.m_data << endl;

	A b3;
	b3 = move(b1);           //调用移动赋值函数
	cout << "b3.m_data=" << *b3.m_data << endl;

	system("pause");
	return EXIT_SUCCESS;

}