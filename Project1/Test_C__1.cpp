#include <iostream>
#include <conio.h>
class A6
{
public:
	A6()
	{
		std::cout << "A6" << std::endl;
		m_a = 5;
	}
	A6(const A6& a)
	{
		std::cout << "A6->A6" << std::endl;
		m_a = a.m_a;
	}
	A6& operator = (const A6& a)
	{
		std::cout << "A6 = A6" << std::endl;
		m_a = a.m_a;
		return *this;
	}
	 ~A6() { std::cout << "~A6" << std::endl; }

	void print() { std::cout << m_a << std::endl; }

private:
	int m_a;
};

class B6: public A6
{
public:
	B6() { std::cout << "B6" << std::endl; }
	virtual ~B6() { std::cout << "~B6" << std::endl; }
	A6& do_some_stuff()
	{
		class C : public A6
		{
		public:
			C (A6 a) { std::cout << "A6->C" << std::endl; }
			C() { std::cout << "C" << std::endl; }
			~C(){ std::cout << "~C" << std::endl; }
		};
		C c(a);
		return c;
	}
private:
	A6 a;
};

int main()
{
	B6 b;
	A6 *a = new B6;
	delete a;
	_getch();
}