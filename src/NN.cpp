#include "NN.h"
#include "basicMathFunctions.h"
#include<stdexcept>
#include<fstream>
#include<iostream>
double NN::sigmoid(const double &d){
    double b=2;
    return 1/(1+expo(-b*d));
}
double NN::sigmoidDerivative(const double &d){
    double b=2;
    double sigmoidValue=sigmoid(d);
    return b*(sigmoidValue)*(1-sigmoidValue);
}
NN::NN(const vector<int> &nodesCount){
    if(nodesCount.empty()) throw std::runtime_error("Can't make a NN with no nodes");
    this->nodesCount=nodesCount;
    for(auto i:nodesCount){
        if(i==0) throw std::runtime_error("One of the layers is provided a node count 0.");
    }
    for(int i=0;i<nodesCount.size()-1;i++){
        weights.push_back(Matrix(nodesCount[i+1],nodesCount[i]));
    }
    input_size=nodesCount[0];
    output_size=nodesCount[nodesCount.size()-1];
}

void NN::randomizeWeights(double minR,double maxR){
    for(auto &weight:weights){
        for(int i=0;i<weight.getRowCount();i++){
            for(int j=0;j<weight.getColumnCount();j++){
                weight[i][j]=getRandom(minR,maxR);
            }
        }
    }
}

vector<double> NN::guess(const vector<double> &input) const{
    if(input.size()!=input_size){
        throw std::runtime_error("Size of the input dosen't match the nodes in layer first layer.");
    }
    Matrix processedInput(input.size(),1);
    for(int i=0;i<input.size();i++){
        processedInput[i][0]=2*input[i]-1;
    }
    processedInput.normalize(sigmoid);
    for(auto weight:weights){
        processedInput.mulTo(weight);
        processedInput.normalize(sigmoid);
    }
    vector<double> result(output_size);
    for(int i=0;i<output_size;i++){
        result[i]=processedInput[i][0];
    }
    return result;
}

void NN::train(const vector<double> &input,const vector<double> &expectedOutput){
    if(input.size()!=input_size){
        throw std::runtime_error("Size of the input dosen't match the nodes in layer first layer.");
    }
    if(expectedOutput.size()!=output_size){
        throw std::runtime_error("Size of the output doesn't match the nodes in layer last layer.");
    }
    //converting the input into a matrix
    Matrix inputMatrix(input_size,1);
    for(int i=0;i<input_size;i++){
        inputMatrix[i][0]=2*input[i]-1;
    }

    // finding out outputs, outputs without applying sigmoid at each layer
    vector<Matrix> outputs,unSigmoidedOutputs;
    unSigmoidedOutputs.push_back(inputMatrix);
    outputs.push_back(Matrix::toNormalized(inputMatrix,sigmoid));
    for(auto weight:weights){
        unSigmoidedOutputs.push_back(weight*(*outputs.rbegin()));
        outputs.push_back(Matrix::toNormalized((*unSigmoidedOutputs.rbegin()),sigmoid));
    }

    // find the error deltas at the last layer
    vector<double> errorDeltas(output_size);
    for(int i=0;i<output_size;i++){
        errorDeltas[i]=expectedOutput[i]-(*outputs.rbegin())[i][0];
    }

    //back propogation to adjust weights at each layer
    for(int k=outputs.size()-1;k>0;k--){
        // sigmoid derivatives of the outputs of the layer being processed.
        Matrix sigmoidDerivates=Matrix::toNormalized(unSigmoidedOutputs[k],sigmoidDerivative);
        
        //Index of weight matrix to be modified
        int current_weight_matrix_index=k-1;

        // calculation back propogation error delats for the before layer.
        vector<double> backPropogationDeltas(nodesCount[k-1],0);
        double learning_rate_backPropagationErrors_per_node=learning_rate_backPropagationErrors/nodesCount[k];
        for(int i=0;i<backPropogationDeltas.size();i++){
            for(int j=0;j<nodesCount[k];j++){
                backPropogationDeltas[i]+=learning_rate_backPropagationErrors_per_node
                                            * (errorDeltas[j])
                                            * sigmoidDerivates[j][0]
                                            * weights[current_weight_matrix_index][j][i];
            }
        }
        // adjusting weights of the current weight matrix
        for(int i=0;i<weights[current_weight_matrix_index].getColumnCount();i++){
            for(int j=0;j<weights[current_weight_matrix_index].getRowCount();j++){
                weights[current_weight_matrix_index][j][i]+=learning_rate_weights
                                                            * errorDeltas[j]
                                                            * sigmoidDerivates[j][0]
                                                            * outputs[k-1][i][0];
            }
        }

        // make the errors for before layer as the backPropogationDeltas for the next round
        errorDeltas=backPropogationDeltas;
        

    }
    
}

void NN::save(const string &filename) const{
    ofstream fout(filename);
    fout<<nodesCount.size()<<endl;
    for(auto i:nodesCount){
        fout<<i<<" ";
    }
    fout<<endl;
    fout<<endl;
    for(auto weight:weights){
        fout<<weight.getRowCount()<<" "<<weight.getColumnCount()<<endl;
        fout<<std::fixed;
        fout.precision(5);
        for(int i=0;i<weight.getRowCount();i++){
            for(int j=0;j<weight.getColumnCount();j++){        
                fout.width(16);
                fout.setf(ios::left);
                fout<<weight[i][j]<<" ";
            }
            fout<<endl;
        }
        fout<<endl;
    }
    fout.close();
}

NN NN::load(const string &fileName){
    ifstream fin(fileName);
    // Read the no of layers in NN
    int layersCount;
    fin>>layersCount;
    // Read the no of nodes in each layer
    vector<int> nodesCount(layersCount);
    for(int i=0;i<layersCount;i++){
        fin>>nodesCount[i];
    }
    // Make an NN with that nodes count
    NN loadedNN(nodesCount);
    for(auto &weight:loadedNN.weights){
        //read the no of rows and columns
        int rows,columns;
        fin>>rows>>columns;
        if(weight.getRowCount()!=rows || weight.getColumnCount()!=columns){
            throw std::runtime_error("Input file error, Matrix dimenstions in input files don't match the required dimensions.");
        }
        // read the corresponding values of the matrix
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                fin>>weight[i][j];
            }
        }
    }
    return loadedNN;
}