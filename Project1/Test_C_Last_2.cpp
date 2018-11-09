#include <iostream>

using namespace std;

class A9 {
public:
	A9() { m_x = 9;cout << "A" << endl; }
	A9(int x) { m_x = x;cout << m_x << "->A" << endl; }
	A9(const A9&) { m_x = 1;cout << "A->A" << endl; }
	A9& operator=(const A9& a) { cout << "A=A" << endl; return *this; }
	~A9() { cout << "~A" << endl; }
	void print() { cout << "NVI\n";v_print(); }
	void do_smth() { [this]() {cout << "do(A)\n";}; }
protected:
	int m_x;
	virtual void v_print() { cout << "A" << endl; }
};

class B9 :public A9 {
public:
	B9(int a) : A9(a) { cout << a << "->A" << endl; }
	B9() { cout << "B" << endl; }
	B9(const B9& b) { cout << "B->B" << endl; }
	B9& operator=(const B9 & a) { cout << "B=B" << endl;return *this; }
	virtual ~B9() { cout << "~B" << endl; }
	void do_smth() { cout << "do(B)\n"; }
protected:
	virtual void v_print() { cout << m_x << endl; }
};

class C9 :public B9 {
public:
	C9() :m_a(10) { cout << "C" << endl; }
	C9(const C9& b) { cout << "C->C" << endl; }
	C9& operator =(const A9 & a) { this->m_x = 99;cout << "C=A" << endl;return *this; }
	virtual ~C9() { cout << "~C" << endl; }
	void do_smth() { cout << "do(C)\n"; }
protected:
	void v_print() { cout << "C=" << m_x << endl; *this = m_a; }
	A9 m_a;
};

class D9 :public B9 {
public:
	D9() : B9(10) { cout << "D" << endl; }
	D9(const C9& c) : B9(c) { cout << "C->D" << endl; }
protected:
	virtual void v_print() { cout << "D=" << m_x << endl; [this]() {A9::v_print();}(); }
};

void main1() {
	A9 * a2 = new C9;
	cout << "----------------------" << endl;
	a2->print();
	cout << "----------------------" << endl;
	delete a2;
	cout << "----------------------" << endl;
	a2->do_smth();
	cout << "----------------------" << endl;
	C9 * b1 = new C9;
	cout << "----------------------" << endl;
	b1->do_smth();
	cout << "----------------------" << endl;
	A9 * b2 = new C9;
	cout << "----------------------" << endl;
	b2->do_smth();
	cout << "----------------------" << endl;
	b2->print();
	cout << "----------------------" << endl;
	D9 d;
	cout << "----------------------" << endl;
	d = *b1;
	cout << "----------------------" << endl;
	d.print();
	cout << "----------------------" << endl;
	delete b2;
	cout << "----------------------" << endl;
	system("pause");
}

void main() {
	main1();
}