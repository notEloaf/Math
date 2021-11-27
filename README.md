# Math
## Matrix
Creating a matrix:
```
Matrix< type > mat( # of rows, # of columns );

or
int arr[10][10]
Matrix< type > mat = arr;
```

accessing elements in a matrix:
```
mat(1,2) = 2;
```

### Supported Functions
Addition, subtraction and multiplication are all supported, both for scalar and matrix operations. Additionaly division by a scalar is also supported.
Simply use +, - or * to use these functions.

#### Trace
```
mat.trace();
```
Returns the sum of the main diagonal (Returns same type as the matrix).

#### Transpose
```
mat.transpose();
```
Returns the transpose of the matrix as a new matrix.

#### Print
```
mat.print()
```
Outputs the matrix to cout formatted.
