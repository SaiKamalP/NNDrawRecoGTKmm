#include "basicMathFunctions.h"

namespace Math
{
    double expo(double x){
        if(x<0) return 1/expo(-x);
        double result=0;
        double current=1;
        for(int i=1;i<=7;i++){
            result+=current;
            current*=x;
            current/=i;
        }
        return result;
    }
} // namespace Math
