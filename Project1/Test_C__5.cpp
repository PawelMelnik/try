#include <iostream>

using namespace std;

class A14 {
public:
	A14() { m_x = 0;cout << "A(" << m_x << ")" << endl; }
	A14(int a) { m_x = a*a / 10.0f + 4;cout << "A(" << m_x << ")" << endl; }
	A14(const A14&) { cout << "A->A" << endl; }
	~A14() { cout << "~A(" << m_x << ")" << endl; }
private:
	float m_x;
};

class B14 {
public:
	B14() { cout << "B" << endl; }
	B14(const A14& a) { cout << "A->B" << endl; }
	B14(const B14&) { cout << "B->B" << endl; }
	virtual void do_some_stuff() { cout << "BBB" << endl; }
	virtual ~B14() { cout << "~B"  << endl; }
};

class C14 : public B14, public A14 {
public:
	C14() : B14(m_f) { cout << "C" << endl; m_pg = NULL; }
	C14(int a) : m_f(a) { cout << "C" << endl; m_pg = NULL; }
	~C14() { cout << "~C" << endl; if (m_pg != NULL) delete m_pg; }
	template <class T> void do_some_new_stuff(T input) {
		m_pg = new C14(100);
	}
	template <class T> void do_some_new_stuff(T **output) const {
		*output = new C14(150);
	}
	template <class T> void do_some_new_stuff(const T *output) const {
		class D14 : public T {
		public:
			virtual void do_some_stuff() { cout << "T3" << endl; }
		private:
			T m_t;
		};
	}
	/*template <Ñ14*> void do_some_new_stuff(T input) const {
		class D14 :public C14 {
		public:
			D14() :n_t(0) { cout << "D" << endl; }
			virtual void do_some_stuff() { cout << "T3" << endl; }
			~D14() { cout << "~D" << endl; }
		private:
			C14 n_t
		};
		*output = new D14;
	}*/
private:
	A14 m_f;
	C14 * m_pg;
};

int main() {
	const C14 h;
	C14 * ph = NULL;
	cout << "------------" << endl;
	h.do_some_new_stuff(&ph);
	cout << "------------" << endl;
	h.do_some_new_stuff(&h);
	cout << "------------" << endl;
	ph->do_some_stuff();
	cout << "------------" << endl;
	delete ph;
}