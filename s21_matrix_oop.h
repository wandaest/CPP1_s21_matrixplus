#include <cmath>
#include <iostream>

class S21Matrix {
 private:
  // Attributes
  int rows_, cols_;  // Rows and columns
  double** matrix_;  // Pointer to the memory where the matrix is allocated

 public:
  S21Matrix();  // Default constructor
  S21Matrix(int rows, int cols);
  S21Matrix(const S21Matrix& other);
  S21Matrix(S21Matrix&& other);

  // accessor
  int GetCols();
  int GetRows();

  void Resize(const int rows, const int cols);

  void SetCols(const int& cols);
  void SetRows(const int& rows);

  S21Matrix operator+(const S21Matrix& other);
  S21Matrix operator-(const S21Matrix& other);
  S21Matrix operator*(const S21Matrix& other);
  S21Matrix operator*(const double num);
  bool operator==(const S21Matrix& other) const;
  S21Matrix& operator=(S21Matrix&& other);
  S21Matrix& operator=(const S21Matrix& other);
  S21Matrix& operator+=(const S21Matrix& other);
  S21Matrix& operator-=(const S21Matrix& other);
  S21Matrix& operator*=(const S21Matrix& other);
  S21Matrix& operator*=(const double num);
  double& operator()(int row, int col);
  const double& operator()(int row, int col) const;

  ~S21Matrix();  // Destructor

  void ClearMatrix();
  void S21Swap(S21Matrix& other);

  void PrintMatrix() const;

  bool EqMatrix(const S21Matrix& other) const;
  void SumMatrix(const S21Matrix& other);
  void SubMatrix(const S21Matrix& other);
  void MulNumber(const double num);
  void MulMatrix(const S21Matrix& other);
  double Determinant();
  S21Matrix Transpose();
  S21Matrix GetMinor(int row, int col);
  S21Matrix CalcComplements();
  S21Matrix InverseMatrix();
};
