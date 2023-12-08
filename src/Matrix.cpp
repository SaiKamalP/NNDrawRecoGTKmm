#include "Matrix.h"
#include<stdexcept>
namespace Math
{
    Matrix::Matrix(int rows, int columns){
        this->rows=rows;
        this->columns=columns;
        data=new double*[rows];
        for(int i=0;i<rows;i++){
            data[i]=new double[columns]{};
        }
    }
    
    Matrix::~Matrix(){
        for(int i=0;i<rows;i++){
            delete [] data[i];
        }
        delete [] data;
    }
    Matrix::Matrix(const Matrix &B){
        this->rows=B.rows;
        this->columns=B.columns;
        data=new double*[rows];
        for(int i=0;i<rows;i++){
            data[i]=new double[columns];
        }
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                data[i][j]=B.data[i][j];
            }
        }
    }

    Matrix& Matrix::add(const Matrix &B){
        if(rows!=B.rows || columns!=B.columns){
            throw std::runtime_error("Can't add matrices of different dimensions. A:="
                + std::to_string(rows) + "x" + std::to_string(columns)
                + " with B:=" + std::to_string(B.rows) + "x" + std::to_string(B.columns));
        }
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                data[i][j]+=B.data[i][j];
            }
        }
        return *this;
    }
    Matrix& Matrix::sub(const Matrix &B){
        if(rows!=B.rows || columns!=B.columns){
            throw std::runtime_error("Can't subtract matrices of different dimensions. A:="
                + std::to_string(rows) + "x" + std::to_string(columns)
                + " with B:=" + std::to_string(B.rows) + "x" + std::to_string(B.columns));
        }
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                data[i][j]-=B.data[i][j];
            }
        }
        return *this;
    }
    Matrix& Matrix::mulWith(const Matrix &B){
        if(columns!=B.rows){
            throw std::runtime_error("Can't multiply matrices of incompatable dimensions. A:="
                + std::to_string(rows) + "x" + std::to_string(columns)
                + " with B:=" + std::to_string(B.rows) + "x" + std::to_string(B.columns));
        }
        int resultRows=rows;
        int resultColumns=B.columns;
        double **newData=new double*[resultRows];
        for(int i=0;i<resultRows;i++){
            newData[i]=new double[resultColumns]{};
        }
        for(int i=0;i<resultRows;i++){
            for(int j=0;j<resultColumns;j++){
                for(int k=0;k<columns;k++){
                    newData[i][j]+=data[i][k]*B.data[k][j];
                }
            }
        }
        this->~Matrix();
        data=newData;
        rows=resultRows;
        columns=resultColumns;
        return *this;
    }
    Matrix& Matrix::mulTo(const Matrix &B){
        if(B.columns!=rows){
            throw std::runtime_error("Can't multiply matrices of incompatable dimensions. A:="
                + std::to_string(B.rows) + "x" + std::to_string(B.columns)
                + " with B:=" + std::to_string(rows) + "x" + std::to_string(columns));
        }
        int resultRows=B.rows;
        int resultColumns=columns;
        double **newData=new double*[resultRows];
        for(int i=0;i<resultRows;i++){
            newData[i]=new double[resultColumns]{};
        }
        for(int i=0;i<resultRows;i++){
            for(int j=0;j<resultColumns;j++){
                for(int k=0;k<B.columns;k++){
                    newData[i][j]+=B.data[i][k]*data[k][j];
                }
            }
        }
        this->~Matrix();
        data=newData;
        rows=resultRows;
        columns=resultColumns;
        return *this;
    }
    Matrix Matrix::operator+(const Matrix &B) const{
        if(rows!=B.rows || columns!=B.columns){
            throw std::runtime_error("Can't add matrices of different dimensions. A:="
                + std::to_string(rows) + "x" + std::to_string(columns)
                + " with B:=" + std::to_string(B.rows) + "x" + std::to_string(B.columns));
        }
        Matrix result(rows,columns);
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                result.data[i][j]=data[i][j]+B.data[i][j];
            }
        }
        return result;
    }
    Matrix Matrix::operator-(const Matrix &B) const{
        if(rows!=B.rows || columns!=B.columns){
            throw std::runtime_error("Can't subtract matrices of different dimensions. A:="
                + std::to_string(rows) + "x" + std::to_string(columns)
                + " with B:=" + std::to_string(B.rows) + "x" + std::to_string(B.columns));
        }
        Matrix result(rows,columns);
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                result.data[i][j]=data[i][j]-B.data[i][j];
            }
        }
        return result;
    }
    Matrix Matrix::operator*(const Matrix &B) const{
        if(columns!=B.rows){
            throw std::runtime_error("Can't multiply matrices of incompatable dimensions. A:="
                + std::to_string(rows) + "x" + std::to_string(columns)
                + " with B:=" + std::to_string(B.rows) + "x" + std::to_string(B.columns));
        }
        int resultRows=rows;
        int resultColumns=B.columns;
        Matrix result(resultRows,resultColumns);
        for(int i=0;i<resultRows;i++){
            for(int j=0;j<resultColumns;j++){
                for(int k=0;k<columns;k++){
                    result.data[i][j]+=data[i][k]*B.data[k][j];
                }
            }
        }
        return result;
    }

    Matrix& Matrix::mul(const double &k){
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                data[i][j]*=k;
            }
        }
        return *this;
    }
    Matrix& Matrix::div(const double &k){
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                data[i][j]/=k;
            }
        }
        return *this;
    }

    Matrix& Matrix::transpose(){
        double **newData=new double*[columns];
        for(int i=0;i<columns;i++){
            newData[i]=new double[rows];
        }
        for(int i=0;i<columns;i++){
            for(int j=0;j<rows;j++){
                newData[i][j]=data[j][i];
            }
        }
        this->~Matrix();
        data=newData;
        int swapTemp=rows;
        rows=columns;
        columns=swapTemp;
        return *this;
    }

    Matrix Matrix::toTransposed(Matrix const &A){
        Matrix result(A.columns,A.rows);
        for(int i=0;i<A.columns;i++){
            for(int j=0;j<A.rows;j++){
                result.data[i][j]=A.data[j][i];
            }
        }
        return result;
    }

    Matrix& Matrix::normalize(double (*normalizingFun)(const double &)){
        for(int i=0;i<rows;i++){
            for(int j=0;j<columns;j++){
                data[i][j]=(*normalizingFun)(data[i][j]);
            }
        }
        return *this;
    }
    Matrix Matrix::toNormalized(const Matrix &A,double (*normalizingFun)(const double &)){
        Matrix result(A.rows,A.columns);
        for(int i=0;i<A.rows;i++){
            for(int j=0;j<A.columns;j++){
                result.data[i][j]=(*normalizingFun)(A.data[i][j]);
            }
        }
        return result;
    }
    Matrix operator*(const Matrix &A,const double &k){
        Matrix result(A.rows,A.columns);
        for(int i=0;i<A.rows;i++){
            for(int j=0;j<A.columns;j++){
                result.data[i][j]=A.data[i][j]*k;
            }
        }
        return result;
    }
    Matrix operator/(const Matrix &A,const double &k){
        Matrix result(A.rows,A.columns);
        for(int i=0;i<A.rows;i++){
            for(int j=0;j<A.columns;j++){
                result.data[i][j]=A.data[i][j]/k;
            }
        }
        return result;
    }

} // namespace Math
