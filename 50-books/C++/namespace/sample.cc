#include <iostream>
#include "debug_lib/macro_print.h"



/* using - TEST_USING_USE_NAMESPACE*/
#ifdef TEST_USING_USE_NAMESPACE
using namespace std;
void test_using(){
	cout 
		<< __func__ << __LINE__ 
		<< endl;
}
#else
void test_using(){
	std::cout 
		<< __func__ << __LINE__ 
		<< std::endl;
}
#endif



/* nest - TEST_NAMESPACE_NEST_SELECT_INSIDE */
namespace ns1{
	int var_ns_int = __LINE__;
	namespace ns2{
		int var_ns_int = __LINE__;
	}
}
#ifdef TEST_NAMESPACE_NEST_SELECT_INSIDE
using namespace ns1::ns2;
#else
using namespace ns1;
#endif
void test_nss_var(){
	std::cout << "var_ns_int = " << var_ns_int <<std::endl;
	print_varname_d(ns1::var_ns_int);
	print_varname_d(ns1::ns2::var_ns_int);
}



int main(int argc, char **argv){

	test_using();

	test_nss_var();


	return __LINE__;
}
