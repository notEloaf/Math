#include <iostream>
#include <type_traits>

class Matrix{
public:
    float ** data;
    int _rows;
    int _cols;

    Matrix(int rows, int cols){
        _rows = rows;
        _cols = cols;
        data = new float*[_rows];
        for(int r = 0; r < _rows; r++){
            data[r] = new float[_cols]();
        }

    }
    //numeric Operators
    template<typename num, typename = typename std::enable_if<std::is_arithmetic<num>::value, num>::type>
    void operator+=(num a){
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                data[r][c] += a;
            }
        }
    }

    template<typename num, typename = typename std::enable_if<std::is_arithmetic<num>::value, num>::type>
    Matrix operator+(num a){
        Matrix m = Matrix(_rows,_cols);
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                m.data[r][c] = data[r][c] + a;
            }
        }
        return m;
    }

    template<typename num, typename = typename std::enable_if<std::is_arithmetic<num>::value, num>::type>
    void operator-=(num a){
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                data[r][c] -= a;
            }
        }
    }

    template<typename num, typename = typename std::enable_if<std::is_arithmetic<num>::value, num>::type>
    Matrix operator-(num a){
        Matrix m = Matrix(_rows,_cols);
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                m.data[r][c] = data[r][c] - a;
            }
        }
        return m;
    }

    template<typename num, typename = typename std::enable_if<std::is_arithmetic<num>::value, num>::type>
    void operator*=(num a){
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                data[r][c] *= a;
            }
        }
    }

    template<typename num, typename = typename std::enable_if<std::is_arithmetic<num>::value, num>::type>
    void operator*(num a){
        Matrix m = Matrix(_rows, _cols);
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                m.data[r][c] = data[r][c] * a;
            }
        }
    }

    //Matrix Operators
    void operator=(Matrix m){
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                data[r][c] = m.data[r][c];
            }
        }
    }

    Matrix operator*(Matrix m2){
        if(_cols != m2._rows){
            std::cerr << "Invalid Operation: (Multiply) rows and columns do not match" << std::endl;
            std::cerr << "Sizes: " << _rows << " : " << _cols << " != " << m2._rows << " : " << m2._cols << std::endl;
            return Matrix(0,0);
        }

        Matrix m = Matrix(_rows,m2._cols);

        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < m2._cols; c++){
                m.data[r][c] = 0;

                for(int x = 0; x < _cols; x++){
                    m.data[r][c] += data[r][x] * m2.data[x][c];
                }
            }
        }

        return m;
    }

    Matrix operator+(Matrix a){
        Matrix m = Matrix(_rows,_cols);
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                m.data[r][c] = data[r][c] + a.data[r][c];
            }
        }
        return m;
    }

    void operator+=(Matrix a){
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                data[r][c] += a.data[r][c];
            }
        }
    }

    float& operator()(int x,int y){
        return data[x][y];
    }

    Matrix transpose(){
        Matrix ret = Matrix(_cols,_rows);
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                ret.data[c][r] = data[r][c];
            }
        }
        return ret;
    }



    void printMatrix(){
        std::cout << "\n";
        for(int r = 0; r < _rows; r++){
            for(int c = 0; c < _cols; c++){
                std::cout << data[r][c] << " ";
            }
            std::cout << "\n";
        }
    }
};
