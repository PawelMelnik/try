#include <iostream>
#include <list>

class A15 {
public:
	static std::list<A15*> my_list;
	A15() { m_x = 0;std::cout << "A(" << m_x << ")" << std::endl;
			A15::my_list.push_back(this);}
	A15(int a) { m_x = a / 10;std::cout << "A(" << m_x << ")" << std::endl;
			A15::my_list.push_back(this);}
	A15(const A15&) { std::cout << "A->A" << std::endl; A15::my_list.push_back(this);}
	~A15() { std::cout << "~A(" << m_x << ")" << std::endl; A15::my_list.remove(this); }
	template <typename functor>
	static void iterate_over(functor f) {
		for(auto it = A15::my_list.begin();it != A15::my_list.end();++it)
		{ f(*it); }
	}
	int get_val() { return m_x; }
private:
	int m_x;
};

class B15 :public A15 {
public:
	B15() { std::cout << "B" << std::endl; }
	B15(const A15&a):A15(47){ std::cout << "A->B" << std::endl; }
	B15(const B15&){ std::cout << "B->B" << std::endl; }
	virtual ~B15() { std::cout << "~B" << std::endl; }
};

class C15 :public B15 {
public:
	template<typename Base, typename functor>
	void f(functor func) {
		class D15 :public Base {
		public:
			D15() { std::cout << "D\n"; }
			~D15() { A15::my_list.push_back(new A15); std::cout << "~D\n";}
		};
		int sz = 2;
		D15 * d = new D15;
		sz = func(sz);
		A15::iterate_over([&sz](A15 * val) {std::cout << val->get_val() + sz << std::endl;});
	}
};

std::list<A15*> A15::my_list;
int main(void)
{
	A15 * a1 = new A15(15);
	std::cout << "-----------------------" << std::endl;
	B15 * b = new B15(*a1);
	std::cout << "-----------------------" << std::endl;
	C15 * c = new C15;
	std::cout << "-----------------------" << std::endl;
	c->f<A15>([](int a) {return a / 2;});
	std::cout << "-----------------------" << std::endl;
	return 0;
}