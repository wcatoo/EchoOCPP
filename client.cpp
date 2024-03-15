#include "app/EndPointer/ChargePoint.hpp"
#include <source_location>
#include <iostream>
using namespace std;

struct A {
  A() {cout << "c A\n";}
  ~A() { cout << "A\n"; }
};
struct B {
  B() {cout << "c B\n";}
  ~B() { cout << "B\n"; }
};
struct C : A {
  C() {cout << "c C\n";}
  ~C() { cout << "C\n"; }
};
int main(int argc, char **argv) {
//    ChargePoint chargepoint;
//    chargepoint.init();
//
//    while (true) {
//      std::cout << "11" << std::endl;
//      std::this_thread::sleep_for(std::chrono::seconds(1));
//    }

//std::cout << std::source_location::current().function_name() << std::endl;

C c;




}




