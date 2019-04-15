#include <list>
#include <iostream>

class B
{
public:
	B(int g) { std::cout << "New B" << std::endl; };
	~B() { std::cout << "Dest B" << std::endl; }
	B& Add(int a) {};
};

class A
{
public:
	std::list<B> list_;
	A(const B& n){list_.emplace_back(n);}
	A(B* b){list_.emplace_back(*b);};
};

void main()
{
	new A(B(10).Add(3).Add(4));
}