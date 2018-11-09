#include <iostream>

using namespace std;

class A6 {
public:
	A6() { cout << "A6" << endl;m_a = 5; }
	A6(const A6& a) { cout << "A6->A6" << endl;m_a = 5; }
	A6(int a) { cout << "0->A6" << endl;m_a = 0; }
	A6& operator= (const A6& a) { cout << "A6=A6" << endl;m_a = a.m_a;return *this; }
	~A6() { cout << "~A6" << endl; }
	void print() { cout << m_a << endl; }
private:
	int m_a;
};

class D6:public A6 {
public:
	D6() { cout << "D6" << endl;m_a = 5; }
	D6(int a) { cout << "int->D6" << endl;m_a = a; }
	D6& operator =(const D6& a) { cout << "D6=D6" << endl;m_a = a.m_a;return *this; }
	~D6() { cout << "~D6" << endl; }
	virtual void print() { cout << "D::print" << endl; }
protected:
	int m_a;
};

class B6 {
public:
	B6() { cout << "B6" << endl;}
	void operator =(A6& a_) { cout << "B6=A6" << endl;a = a_; }
	A6& do_some_stuff() {
		class C :public D6, private A6 {
		public:
			C(A6 a) : A6(D6::m_a), D6(15) { cout << "A6->C" << endl; }
			C() { cout << "C" << endl; }
			~C() { cout << "~C" << endl; }
			void print() { cout << "C::print" << endl; }
		};
		C c(a);
		return static_cast<D6&>(c);
	}
	~B6() { cout << "~B6" << endl; }
private:
	A6 a;
};

int main() {
	B6 b;
	cout << "-----------------" << endl;
	A6 * a = new A6;
	cout << "-----------------" << endl;
	*a = b.do_some_stuff();
	cout << "-----------------" << endl;
	[&b](A6*c) ->void {b = *c;c->print();} (a);
	cout << "-----------------" << endl;
	delete a;
	cout << "-----------------" << endl;
	b.~B6();
	return 0;
}