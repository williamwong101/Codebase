#include <utility>
#include <iostream>
class A
{
public:
    int x;
    A(int a) { x = a; std::cout << "ctor (int) \n"; }
	A(const A& a) {
		std::cout<<"ctor (const A&)\n";
		if (&a == this){
			return;
		}
		x = a.x;
		return;
	}
	A& operator=(A&& a) {
		this->swap(std::move(a));
		return *this;
	}
//	A(A&& a) {
//		std::cout<<"ctor (A&&)\n";
//		if (&a == this) {
//			return;
//		}
//		this->swap(std::move(a));
//	}
	
	int get_x(){ return x;}
private:
	void swap(A&& a) {
		this->x = a.x;
	}
};
A ret_a(A a) 
{
	std::cout<<"in ret_a\n";
    return a;
}
int main(void)
{
    std::cout<<ret_a(5).get_x()<<std::endl;
}
