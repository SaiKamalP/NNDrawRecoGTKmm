#include "basicMathFunctions.h"
#include<time.h>
#include<random>
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
    double getRandom(double minR,double maxR){
        static std::random_device randomDevice;
        static std::default_random_engine randomEngine(randomDevice());
        static std::uniform_real_distribution<long double> dist(0,1);
        return minR+(maxR-minR)*dist(randomEngine);
    }
} // namespace Math
