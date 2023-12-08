#pragma once
#include "Matrix.h"
#include<vector>
#include<string>
using namespace std;
using namespace Math;
class NN{
    int input_size;
    int output_size;
    vector<int> nodesCount;
    vector<Matrix> weights;
    
    static double sigmoid(const double &value);
    static double sigmoidDerivative(const double &value);

    const double learning_rate_weights=0.01;
    const double learning_rate_backPropagationErrors=1;
    public:
    NN(const vector<int> &nodesCount);
    void randomizeWeights(double minR,double maxR);
    vector<double> guess(const vector<double> &input) const;

    void train(const vector<double> &input,const vector<double> &expectedOutput);
    
    void save(const string &fileName) const;

    static NN load(const string &fileName);
};
