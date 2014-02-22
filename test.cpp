#include <tensor.h>
#include <iostream>
#include <cstdlib>

using namespace tensor;
using namespace std;

int main() {
  const size_t o = 2;

  tensor<int,o> t(2,3);
  cout << t.size() << endl;
  cout << t.size(0) << endl;
  cout << t.size(1) << endl;

  for(int i = 0; i < t.size(0); ++i) {
    for(int j = 0; j < t.size(1); ++j) {
      t(i,j) = i*t.size(1)+j;
      cout << t(i,j) << '\t';
    }
    cout << endl;
  }

  tensor<double,o> a = t;
  cout << a.size() << endl;
  cout << a.size(0) << endl;
  cout << a.size(1) << endl;

  for(int i = 0; i < t.size(0); ++i) {
    for(int j = 0; j < t.size(1); ++j) {
      cout << a(i,j) << '\t';
    }
    cout << endl;
  }

  auto b = rotr<1>(a);

  cout << b.size() << endl;
  cout << b.size(0) << endl;
  cout << b.size(1) << endl;

  for(int i = 0; i < b.size(0); ++i) {
    for(int j = 0; j < b.size(1); ++j) {
      cout << b(i,j) << '\t';
    }
    cout << endl;
  }

  return 0;
}
