#include "s21_matrix_oop.h"

S21Matrix::S21Matrix() : S21Matrix(2, 2) {}

S21Matrix::S21Matrix(int rows, int cols) : rows_(rows), cols_(cols) {
  if (rows <= 0 && cols <= 0) {
    throw std::invalid_argument("Invalid arguments");
  }
  matrix_ = new double*[rows_]();
  for (int i = 0; i < rows_; i++) {
    matrix_[i] = new double[cols_]();
  }
}

S21Matrix::S21Matrix(const S21Matrix& other)
    : S21Matrix(other.rows_, other.cols_) {
  for (int i = 0; i < other.rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      matrix_[i][j] = other.matrix_[i][j];
    }
  }
}

S21Matrix::S21Matrix(S21Matrix&& other)
    : rows_(other.rows_), cols_(other.cols_), matrix_(other.matrix_) {
  other.rows_ = 0;
  other.cols_ = 0;
  other.matrix_ = nullptr;
}

S21Matrix& S21Matrix::operator=(S21Matrix&& other) {
  if (this != &other) {
    ClearMatrix();
    rows_ = other.rows_;
    cols_ = other.cols_;
    matrix_ = other.matrix_;
    other.rows_ = 0;
    other.cols_ = 0;
    other.matrix_ = nullptr;
  }

  return *this;
}

S21Matrix& S21Matrix::operator=(const S21Matrix& other) {
  if (this != &other) {
    S21Matrix copy = other;
    S21Swap(copy);
  }
  return *this;
}

S21Matrix::~S21Matrix() { ClearMatrix(); }

int S21Matrix::GetCols() { return cols_; }
int S21Matrix::GetRows() { return rows_; }

void S21Matrix::Resize(const int rows, const int cols) {
  S21Matrix tmpMatrix(rows, cols);
  for (int i = 0; i < std::min(rows, rows_); i++) {
    for (int j = 0; j < std::min(cols, cols_); j++) {
      tmpMatrix.matrix_[i][j] = matrix_[i][j];
    }
  }
  *this = std::move(tmpMatrix);
}

void S21Matrix::SetCols(const int& cols) { Resize(rows_, cols); }
void S21Matrix::SetRows(const int& rows) { Resize(rows, cols_); }

void S21Matrix::ClearMatrix() {
  for (int i = 0; i < rows_; i++) {
    delete[] matrix_[i];
  }
  rows_ = 0;
  cols_ = 0;
  delete[] matrix_;
}

void S21Matrix::S21Swap(S21Matrix& other) {
  std::swap(rows_, other.rows_);
  std::swap(cols_, other.cols_);
  std::swap(matrix_, other.matrix_);
}

void S21Matrix::PrintMatrix() const {
  std::cout << "rows = " << rows_ << ", cols = " << cols_ << std::endl;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      std::printf("%lf ", matrix_[i][j]);
    }
    std::cout << std::endl;
  }
}

bool S21Matrix::EqMatrix(const S21Matrix& other) const {
  if (rows_ != other.rows_ && cols_ != other.cols_) return false;
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      if (fabs(matrix_[i][j] - other.matrix_[i][j]) > 0.0000001) return false;
    }
  }
  return true;
}

void S21Matrix::SumMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Invalid arguments: matrices must be the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] += other.matrix_[i][j];
    }
  }
}

void S21Matrix::SubMatrix(const S21Matrix& other) {
  if (rows_ != other.rows_ || cols_ != other.cols_) {
    throw std::invalid_argument(
        "Invalid arguments: matrices must be the same size");
  }
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] -= other.matrix_[i][j];
    }
  }
}

void S21Matrix::MulNumber(const double num) {
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      matrix_[i][j] *= num;
    }
  }
}

void S21Matrix::MulMatrix(const S21Matrix& other) {
  if (cols_ != other.rows_) {
    throw std::invalid_argument(
        "Invalid arguments: matrices must be the same size");
  }
  S21Matrix resultMatrix(rows_, other.cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < other.cols_; j++) {
      for (int k = 0; k < cols_; k++) {
        resultMatrix.matrix_[i][j] += matrix_[i][k] * other.matrix_[k][j];
      }
    }
  }
  *this = std::move(resultMatrix);
}

S21Matrix S21Matrix::GetMinor(int row, int col) {
  S21Matrix res(rows_ - 1, cols_ - 1);
  int res_i = 0;
  for (auto i = 0; i < rows_; i++) {
    if (i != row) {
      int res_j = 0;
      for (auto j = 0; j < cols_; j++) {
        if (j != col) {
          res.matrix_[res_i][res_j] = matrix_[i][j];

          res_j++;
        }
      }
      res_i++;
    }
  }
  return res;
}

double S21Matrix::Determinant() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Invalid arguments: matrix must be square");
  }
  double matrixDeterminant = 0;

  if (rows_ == 1)
    matrixDeterminant = matrix_[0][0];
  else if (rows_ == 2) {
    matrixDeterminant =
        matrix_[0][0] * matrix_[1][1] - matrix_[0][1] * matrix_[1][0];
  } else {
    for (int i = 0; i < rows_; i++) {
      S21Matrix minorMatrix = GetMinor(0, i);
      double minorDeterminant = minorMatrix.Determinant();
      matrixDeterminant +=
          matrix_[0][i] * minorDeterminant * (i % 2 == 0 ? 1 : -1);
    }
  }
  return matrixDeterminant;
}

S21Matrix S21Matrix::Transpose() {
  S21Matrix resultMatrix(cols_, rows_);
  for (int i = 0; i < resultMatrix.rows_; i++) {
    for (int j = 0; j < resultMatrix.cols_; j++) {
      resultMatrix.matrix_[i][j] = matrix_[j][i];
    }
  }
  return resultMatrix;
}

S21Matrix S21Matrix::CalcComplements() {
  if (rows_ != cols_) {
    throw std::invalid_argument("Invalid arguments: matrix must be square");
  }

  S21Matrix resultMatrix(rows_, cols_);
  for (int i = 0; i < rows_; i++) {
    for (int j = 0; j < cols_; j++) {
      S21Matrix minorMatrix = GetMinor(i, j);
      resultMatrix.matrix_[i][j] = pow(-1, i + j) * minorMatrix.Determinant();
    }
  }

  return resultMatrix;
}

S21Matrix S21Matrix::InverseMatrix() {
  if (fabs(Determinant()) < 0.00000001) {
    throw std::logic_error("Matrix is not invertible");
  }

  S21Matrix resultMatrix;

  if (cols_ == 1) {
    resultMatrix(1, 1);
    resultMatrix.matrix_[0][0] = 1 / Determinant();
  } else {
    resultMatrix = CalcComplements();
    resultMatrix = resultMatrix.Transpose();
    resultMatrix.MulNumber(1 / Determinant());
  }

  return resultMatrix;
}

S21Matrix S21Matrix::operator+(const S21Matrix& other) {
  S21Matrix resultMatrix(*this);
  resultMatrix.SumMatrix(other);
  return resultMatrix;
}

S21Matrix S21Matrix::operator-(const S21Matrix& other) {
  S21Matrix resultMatrix(*this);
  resultMatrix.SubMatrix(other);
  return resultMatrix;
}

S21Matrix S21Matrix::operator*(const double num) {
  S21Matrix resultMatrix(*this);
  resultMatrix.MulNumber(num);
  return resultMatrix;
}

S21Matrix S21Matrix::operator*(const S21Matrix& other) {
  S21Matrix resultMatrix(*this);
  resultMatrix.MulMatrix(other);
  return resultMatrix;
}

bool S21Matrix::operator==(const S21Matrix& other) const {
  return EqMatrix(other);
}

S21Matrix& S21Matrix::operator+=(const S21Matrix& other) {
  SumMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator-=(const S21Matrix& other) {
  SubMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const S21Matrix& other) {
  MulMatrix(other);
  return *this;
}

S21Matrix& S21Matrix::operator*=(const double num) {
  MulNumber(num);
  return *this;
}

double& S21Matrix::operator()(int row, int col) {
  if (row >= rows_ || col >= cols_) {
    throw std::invalid_argument("Index out of range");
  }
  return matrix_[row][col];
}

const double& S21Matrix::operator()(int row, int col) const {
  if (row >= rows_ || col >= cols_) {
    throw std::invalid_argument("Index out of range");
  }
  return matrix_[row][col];
}
