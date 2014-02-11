#include <tensor.h>
#include <iostream>
#include <cstdlib>

using namespace tensor;
using namespace std;

int main() {
  const size_t o = 2;
  const size_t s = 2;

  Tensor<int,o> t(s,s);
  cout << t.size() << endl;
  cout << t.size(0) << endl;
  cout << t.size(1) << endl;

  for(int i = 0; i < t.size(0); ++i) {
    for(int j = 0; j < t.size(1); ++j) {
      t(i,j) = i*t.size(1)+j;
    }
  }

  Tensor<double,o> a(s,s);
  cout << a.size() << endl;
  cout << a.size(0) << endl;
  cout << a.size(1) << endl;

  for(int i = 0; i < a.size(0); ++i) {
    for(int j = 0; j < a.size(1); ++j) {
      a(i,j) = 0.75*(double)(i*a.size(1));
    }
  }

  int v = 1;
  a = a+a;

  cout << "Mod: " << (-1)%(a.order()) << endl;

  auto expr = a+rotl<1>(a);
  for(int i = 0; i < a.size(0); ++i) {
    for(int j = 0; j < a.size(1); ++j) {
      cout << expr(i,j) << '\t';
    }
    cout << endl;
  }
  cout << endl;

  cout << a(0,1) << endl;
  cout << rotr<1>(a)(1,0) << endl;
  //cout << rex(a)(0,0,1) << endl;

  cout << a.size() << endl;

  return 0;
}
