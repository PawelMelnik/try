#include <iostream>
class A4 {
public:
	A4() { m_x = 4;std::cout << "A" << std::endl; }
	A4(int x) { m_x = x;std::cout << m_x << "->A" << std::endl; }
	A4(const A4&) { m_x = 1;std::cout << "A->A" << std::endl;}
	A4& operator=(const A4& a){std::cout <<"A = A" << std::endl;return *this;}
	~A4() { std::cout << "~A" << std::endl;}
	void print() { std::cout << "NVI\n";v_print(); }
	void do_smth() { std::cout << "do(A)\n"; }
protected:
	int m_x;
	virtual void v_print() { std::cout << "A" << std::endl; } };
class B4 :public A4 {
public:
	B4(int a) :A4(a) { std::cout << a << "->A" << std::endl; }
	B4() { std::cout << "B" << std::endl; }
	B4(const B4& b) { std::cout << "B->B" << std::endl; }
	B4& operator = (const B4&a){ std::cout << "B = B" << std::endl;return *this; }
	virtual ~B4() { std::cout << "~B" << std::endl; }
	void do_smth() { std::cout << "do(B)\n"; }
protected:
	virtual void v_print() { std::cout << m_x << std::endl; } };
class C4 :public B4 {
public:
	C4() :m_a(10) { std::cout << "C" << std::endl; }
	C4(const C4&b) { std::cout << "C->C" << std::endl; }
	C4& operator = (const A4& a) { this->m_x = 44; std::cout << "C = A" << std::endl;return *this; }
	virtual ~C4() { std::cout << "~C" << std::endl; }
	void do_smth() { std::cout << "do(C)\n"; }
protected:
	virtual void v_print() { std::cout << "C = " << m_x << std::endl;*this = m_a; }
	A4 m_a; };
class D4 :public B4 {
public:
	D4() :B4(10) { std::cout << "D" << std::endl; }
	D4(const C4 &c) :B4(c) { std::cout << "C->D" << std::endl; }
protected:
	virtual void v_print() { std::cout << "D = " << m_x << std::endl;A4::v_print(); } };
int main() {
	B4 a1; // A B
	a1.print(); // NVI 4
	A4 a = a1; // A->A 
	a.print(); // NVI A
	A4*a2 = new C4; // A B 10->A C
	a2->print(); // NVI C=4 C=A
	delete a2; // ~A
	a2->do_smth(); // do(C)
	C4 *b1 = new C4; // A B 10->A C
	b1->do_smth(); // do(C)
	A4 *b2 = new C4; // A B 10->A C
	b2->do_smth(); // do(C) 
	b2->print(); // NVI C=4 C=A
	b2->print(); // NVI C=44 C=A
	*b2 = B4(); // A B A=A(C=A) ~B ~A
	b2->do_smth(); // do(C) 
	b2->print(); // NVI C=44 C=A
	D4 d(*b1); // A B->B C->D
	delete b1; // ~C ~A ~B ~A
	d.print(); // NVI D=4 A
	delete b2; // ~A(~C) ~A ~B ~A
	return 0;
} // 