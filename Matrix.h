#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>

template <typename T>
class Matrix{
public:
    int rows, cols;
    T ** data;
    Matrix() : rows(0), cols(0){}

    template<size_t R, size_t C>
    Matrix(T (&a)[R][C]){
        set_mem(R,C);
        for(int r = 0; r < R; r++){
            for(int c = 0; c < C; c++){
                data[r][c] = a[r][c];
            }
        }
    }

    Matrix(int r, int c){
        set_mem(r,c);
    }

    void clear(){
    	// Clean up memory
    	for(int i = 0; i < rows; i++){
    		delete[] data[i];
    	}
    	delete data;
    }

// Operator Overloads
    //Scalar Addition Operators
    void operator+=(T a){
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                data[r][c] += a;
            }
        }
    }

    Matrix operator+(T a){
        Matrix<T> m;
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                m.data[r][c] = data[r][c] + a;
            }
        }
        return m;
    }

    //Scalar Subtraction operators
    void operator-=(T a){
        *this += -a;
    }

    Matrix operator-(T a){
        return *this + (-a);
    }

    //Scalar multipication operators
    void operator*=(T a){
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                data[r][c] *= a;
            }
        }
    }

    Matrix operator*(T a){
        Matrix<T> m;
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                m.data[r][c] = data[r][c] * a;
            }
        }
        return m;
    }

    //Scalar division operators
    void operator/=(T a){
        *this *= 1/a;
    }

    Matrix operator/(T a){
        return *this * (1/a);
    }

    //Sets matrix equal to another (must be the same size)
    void operator=(Matrix a){
        if(!isEqualSize(a)){
            std::cerr << "Error: Matrix add - matrices are not equal size." << std::endl;
            return;
        }
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                data[r][c] = a.data[r][c];
            }
        }
    }

    void operator=(T **a){
        data = a;
    }

    //Equals function for a 2d array of size (R,C)
    template<size_t R, size_t C>
    void operator=(T (&a)[R][C]){
        set_mem(R,C);
        for(int r = 0; r < R; r++){
            for(int c = 0; c < C; c++){
                data[r][c] = a[r][c];
            }
        }
    }

    //Matrix Addition Operations
    void operator+=(Matrix a){
        if(!isEqualSize(a)){
            std::cerr << "Error: Matrix add - matrices are not equal size." << std::endl;
            return;
        }
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                data[r][c] += a(r,c);
            }
        }
    }

    Matrix operator+(Matrix a){
        if(!isEqualSize(a)){
            std::cerr << "Error: Matrix add - matrices are not equal size." << std::endl;
            return Matrix<T>(0,0);
        }
        Matrix m = Matrix(rows, cols);
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                m(r,c) = data[r][c] + a(r,c);
            }
        }
        return m;
    }


    //Matrix Subtraction Operations
    void operator-=(Matrix a){
        *this += (-a);
    }

    Matrix operator-(Matrix a){
        return *this + (-a);
    }

    //Multiplies two matrices together and returns the result
    Matrix operator*(Matrix a){
        if(cols != a.rows){
            std::cerr << "Error: Matrix multiply - rows do not match columns {" << cols << " != " << a.rows << "}." << std::endl;
            return Matrix<T>(0,0);
        }

        Matrix m = Matrix(rows,a.cols);

        for(int r = 0; r < rows; r++){
            for(int c = 0; c < a.cols; c++){
                m.data[r][c] = 0;

                for(int x = 0; x < cols; x++){
                    m.data[r][c] += data[r][x] * a.data[x][c];
                }
            }
        }

        return m;
    }


    //Returns the Trace of the given matrix(sum of main diagonal)
    inline T trace() const{
        int sum = 0;
        for(int i = 0; i < std::min(rows, cols); i++){
            sum += data[i][i];
        }
        return sum;
    }

    //Returns the transposed version of this matrix
    Matrix transpose(){
        Matrix<T> ret(cols,rows);
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                ret.data[c][r] = data[r][c];
            }
        }
        return ret;
    }

    // T determinant(){
    //     //Go across top row
    //     //Create submatrix excluding the column we are currently at
    //     //Return current_pos * determinant of sub matrix (recursive)
    // }


    //Prints out a formatted version of the matrix
    void print(){
        for(int r = 0; r < rows; r++){
            for(int c = 0; c < cols; c++){
                std::cout << data[r][c] << " ";
            }
            std::cout << "\n";
        }
        std::cout << "\n";
    }

    //Operators for easy element access
    float& operator()(int x,int y){
        return data[x][y];
    }

    float& operator()(int x,int y) const{
        return data[x][y];
    }



private:
    
	//Initialises memory for matrix on creation
    void set_mem(int _r, int _c){
        rows = _r;
        cols = _c;
        data = new T*[rows];
        for(int r = 0; r < rows; r++){
            data[r] = new T[cols]();
        }
    }

    //Returns if two matrices is equal
    bool isEqualSize(Matrix &m){
        return (m.rows == rows && m.cols == cols);
    }
};

//Operation: number * matrix
template <typename T>
inline Matrix<T> operator*(const T n, const Matrix<T> &m){
    Matrix<T> ret;
    for(int r = 0; r < m.rows; r++){
        for(int c = 0; c < m.cols; c++){
            ret(r, c) = m(r,c) * n;
        }
    }
    return ret;
}


#endif