#include "test_generic.h"

void test_payload() {
	auto n = Payload::count();
	test_generic<Payload>();
	assert(Payload::count() == n);
	std::cout << "> Payload Counter: DONE." << std::endl;
}