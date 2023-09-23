#include <iostream>
#include "Value.h"
using namespace std;
int main(){
    Value x1(2,"x1",true);
    Value w1(5,"w1",true);
    Value x1w1=x1*w1;
    Value x2(1,"x2",true);
    Value w2(3,"w2",true);
    Value x2w2=x2*w2;
    Value b1(10,"b1",true);

    Value x1w1x2w2=x1w1+x2w2;
    Value n=x1w1x2w2+b1;
    Value r=n.tanh();
    Value O=r.reLu();
    O.setLabel("O");
    O.setGrad(1);
    O.backward();

    return 0;
}