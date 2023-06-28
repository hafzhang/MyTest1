#include<iostream>
using namespace std;

class A {
public:
	int* m_data = nullptr;
	A() = default;
	
	void alloc() {   //�����ݳ�Աm_data�����ڴ�ռ�
		m_data = new int;   
		memset(m_data, 0, sizeof(int));
	}
	A(const A& a) {
		cout << "�������캯����\n";
		if (m_data == nullptr) alloc();          //���û���ڴ�ͷ����ڴ�
		memcpy(m_data, a.m_data, sizeof(int));   //�����ݴ�Դ�����п�������

	}
	A& operator=(const A& a) {         //��ֵ����
		cout << "��ֵ������\n";
		if (this == &a) return *this;   //�������Ҹ�ֵ
		if (m_data == nullptr) alloc();
		memcpy(m_data, a.m_data, sizeof(int));
		return *this;
	}
	
	A(A&& a) noexcept {                       //�ƶ����캯��
		cout << "using�ƶ����캯��.\n";
		if (m_data != nullptr) delete m_data;  //����ѷ����ڴ����ͷŵ�
		m_data = a.m_data;                     //����Դ��Դ������ת�ƹ���
		a.m_data = nullptr;                    //��Դ�����е�ָ���ÿ�
	}
	A& operator=(A&& a) noexcept {             //�ƶ���ֵ����
		cout << "using�ƶ���ֵ������\n";
		if (this == &a) return *this;         //�������Ҹ�ֵ
		if (m_data != nullptr) delete m_data;  //����ѷ����ڴ����ͷŵ�
		m_data = a.m_data;                     //����Դ��Դ������ת�ƹ���
		a.m_data = nullptr;                    //��Դ�����е�ָ���ÿ�
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
	a1 = std::move(param);  //�����ƶ���ֵ
}
void test()
{
	A a;
	// func(a); //error. 
	func(std::move(a)); //ͨ���ƶ����칹����ʱ����
}

int main() {
	/*
	    �ƶ����캯���Ϳ������캯������ʱ����һ���ģ�����β�����ֵ��
	���ÿ������캯�����������ֵ�������ƶ����캯����
	    �ƶ���ֵ��������ͨ��ֵ��������ʱ����һ���ģ�����β�����ֵ��
	������ͨ��ֵ�������������ֵ�������ƶ���ֵ������
	    ��std::move()��������ֵת������ֵ�ǳɹ��ġ�Move()���߱�������
	��Ȼ������ֵ�����ǲ�Ҫ�����ÿ������캯�������ƶ����캯����
	    ��ֵ����ת��֮�󣬲�������������ֻ���뿪�Լ��������ʱ���
	�ᱻ�������������ʹ����ֵ�е���Դ�����ܻᷢ������
	*/
	A a1;
	a1.alloc();
	*a1.m_data = 3;     //�����ڴ渳ֵ
	cout << "a1.m_data=" << *a1.m_data << endl;

	A a2 = a1;         //���ÿ�������
	cout << "a2.m_data=" << *a2.m_data << endl;

	A a3;
	a3 = a1;           //���ø�ֵ����
	cout << "a3.m_data=" << *a3.m_data << endl;


	A b1;
	b1.alloc();
	*b1.m_data = 3;     //�����ڴ渳ֵ
	cout << "b1.m_data=" << *b1.m_data << endl;

	A b2 = move(b1);         //�����ƶ����캯��
	cout << "b2.m_data=" << *b2.m_data << endl;

	A b3;
	b3 = move(b1);           //�����ƶ���ֵ����
	cout << "b3.m_data=" << *b3.m_data << endl;

	system("pause");
	return EXIT_SUCCESS;

}