#pragma once

namespace Math
{
    class Matrix{
        int rows,columns;
        double **data;
        public:
        Matrix(int rows,int columns);
        ~Matrix();
        Matrix(const Matrix &B);

        Matrix& add(const Matrix &B);
        Matrix& sub(const Matrix &B);
        /**
         * This does AxB
         * where A= invoked matrix
         * B= matrix in parameter
        */
        Matrix& mulWith(const Matrix &B);
        /**
         * This does BxA
         * where A= invoked matrix
         * B= matrix in parameter
        */
        Matrix& mulTo(const Matrix &B);
        Matrix operator+(const Matrix &B) const;
        Matrix operator-(const Matrix &B) const;
        Matrix operator*(const Matrix &B) const;
        
        Matrix& mul(const double &k);
        Matrix& div(const double &k);
        friend Matrix operator*(const Matrix &A,const double &k);
        friend Matrix operator/(const Matrix &A,const double &k);

        Matrix& transpose();
        static Matrix toTransposed(Matrix const &A);

        Matrix& normalize(double (*normalizingFun)(const double &));
        static Matrix toNormalized(const Matrix &A,double (*normalizingFun)(const double &));

        inline double * operator[](int row){
            return data[row];

        }
        inline int getRowCount() const{return rows;}
        inline int getColumnCount() const {return columns;}
    };
    //friend function declarations
    Matrix operator*(const Matrix &A,const double &k);
    Matrix operator/(const Matrix &A,const double &k);
} // namespace Matrix

