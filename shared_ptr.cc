#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>
#include <iostream>

struct S : boost::enable_shared_from_this<S>
{
	boost::shared_ptr<S> dangerous()
	{
		return shared_from_this();
	}
	~S()
	{
		std::cout << "going out" << std::endl;
	}
};

int main()
{
	boost::shared_ptr<S> sp1(new S);
	boost::shared_ptr<S> sp2 = sp1->dangerous();    // not dangerous
	return 0;
}
