#include <tensor.h>
#include <iostream>
#include <cstdlib>

using namespace std;

int main() {
  const size_t o = 2;

  tensor::tensor<int,o> t(2,3);
  cout << "t(2,3)" << endl;
  cout << "t.size(): " << t.size() << endl;
  cout << "t.size(0): " << t.size(0) << endl;
  cout << "t.size(1): " << t.size(1) << endl;

  for(int i = 0; i < t.size(0); ++i) {
    for(int j = 0; j < t.size(1); ++j) {
      t(i,j) = i*t.size(1)+j;
      cout << t(i,j) << '\t';
    }
    cout << endl;
  }
  cout << endl;

  tensor::tensor<double,o> a = t;
  cout << "a = t" << endl;
  cout << "a.size(): " << a.size() << endl;
  cout << "a.size(0): " << a.size(0) << endl;
  cout << "a.size(1): " << a.size(1) << endl;

  for(int i = 0; i < t.size(0); ++i) {
    for(int j = 0; j < t.size(1); ++j) {
      cout << a(i,j) << '\t';
    }
    cout << endl;
  }
  cout << endl;

  auto b = tensor::rotl<1>(a);
  cout << "b = tensor::rotl<1>(a)" << endl;
  cout << "b.size(): " << b.size() << endl;
  cout << "b.size(0): " << b.size(0) << endl;
  cout << "b.size(1): " << b.size(1) << endl;

  for(int i = 0; i < b.size(0); ++i) {
    for(int j = 0; j < b.size(1); ++j) {
      cout << b(i,j) << '\t';
    }
    cout << endl;
  }
  cout << endl;

  auto c = tensor::extl<1,tensor::Side::Right>(a);
  cout << "c = tensor::extl<1>(a)" << endl;
  cout << "c.size(): " << c.size() << endl;
  cout << "c.size(0): " << c.size(0) << endl;
  cout << "c.size(1): " << c.size(1) << endl;

  for(int i = 0; i < c.size(0); ++i) {
    for(int j = 0; j < c.size(1); ++j) {
      cout << c(0,i,j) << '\t';
    }
    cout << endl;
  }
  cout << endl;

  return 0;
}
