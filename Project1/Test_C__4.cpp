#include <iostream>

using namespace std;

class A12 {
public:
	A12() { cout << "A" << endl;m_x = 0; }
	A12(int a) { cout << "A" << endl;m_x = a / 10; }
	A12(const A12&) { cout << "A->A" << endl; }
	~A12() { cout << "~A(" << m_x << ")" << endl; }
private:
	int m_x;
};

class B12 : public A12 {
public:
	B12() { cout << "B" << endl; }
	B12(const A12& a) :A12(47) { cout << "A->B" << endl; }
	B12(const B12&) { cout << "B->B" << endl; }
	virtual void do_some_stuff() { cout << "BBB" << endl; }
	virtual ~B12() { cout << "~B" << endl; }
};

class C12 : public B12 {
public:
	C12() : B12(m_f)    { cout << "C" << endl; m_pg = NULL; }
	C12(int a) : m_f(a) { cout << "C" << endl; m_pg = NULL; }
	~C12() { cout << "~C" << endl; if (m_pg != NULL) delete m_pg; }
	template <class T> void do_some_new_stuff(T ** output) {
		class D12 :public T {
		public:
			virtual void do_some_stuff() { cout << "T1" << endl; }
		};
		*output = new D12;
		m_pg = new C12(100);
	}
private:
	A12 m_f;
	C12 * m_pg;
};

int main() {
	C12 h;
	cout << "-------------"<<endl; 
	C12 *ph;
	cout << "-------------" << endl;
	h.do_some_new_stuff(&ph);
	cout << "-------------" << endl;
	ph->do_some_stuff();
	cout << "-------------" << endl;
	delete ph;
	cout << "-------------" << endl;
	h.~C12();
	return 0;
}