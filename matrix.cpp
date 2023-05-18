#include <iostream>
#include <vector>

using namespace std;

class Matrix{
    // instance vars
    public: vector<vector<double>> matrix;

    private: 
        int rows;
        int cols;

    // getters/setters/public methods
    public: 
        int getRows(){
            return rows;
        } 
        int getCols(){
            return cols;
        }
        double get(int row, int col){
            return matrix[row][col];
        }
        void set(int row, int col, double value){
            matrix[row][col] = value;
        }
        void print(){
            for(int i = 0; i < rows; i++){
                for(int j = 0; j < cols; j++){
                    cout << get(i, j) << " ";
                }
                cout << "\n";
            }
        }
        Matrix identity(){
            int size = cols;
            Matrix nm(size, size);
            for(int i = 0; i < size; i ++){
                nm.set(i, i, 1);
            }
            return nm;
        }
        Matrix submatrix(int startRow, int startCol, int endRow, int endCol){
            int h = endRow - startRow + 1;
            int w = endCol - startCol + 1;
            Matrix nm(h, w);
            for(int i = startRow; i <= endRow; i++){
                for(int j = startCol; j <= endCol; j++){
                    nm.set(i, j, get(i, j));
                }
            }
            return nm;
        }

    // public static methods
    public: 
        static Matrix add(Matrix m1, Matrix m2){
            Matrix nm(m1.rows, m1.cols);
            for(int i = 0; i < m1.rows; i++){
                for(int j = 0; j < m1.cols; j++){
                    nm.set(i, j, m1.get(i, j) + m2.get(i, j));
                }
            }
            return nm;
        }

        static Matrix multiply(Matrix m1, double scale){
            Matrix nm(m1.rows, m1.cols);
            for(int i = 0; i < m1.rows; i++){
                for(int j = 0; j < m1.cols; j++){
                    nm.set(i, j, m1.get(i, j) * scale);
                }
            }
            return nm;
        }

        static Matrix multiply(Matrix m1, Matrix m2){
            Matrix nm(m1.getRows(), m2.getCols());
            for(int i = 0; i < nm.getRows(); i++){
                for(int j = 0; j < nm.getCols(); j++){
                    double dot = 0;
                    for(int k = 0; k < m1.getCols(); k++){
                        dot += m1.get(i, k) * m2.get(k, j);
                    }
                    nm.set(i, j, dot);
                }
            }
            return nm;
        }
        static  Matrix inverse2x2(Matrix m){
            double det = m.get(0, 0) * m.get(1, 1) - m.get(0, 1) * m.get(1, 0);
            vector<vector<double>> flip = {{m.get(1, 1), (-1) * m.get(0, 1)}, {(-1) *  m.get(1, 0), m.get(0, 0)}};
            Matrix nm(flip);
            return multiply(nm, 1 / det);
        }

    // constructors
    public: 
        Matrix(int rows, int cols){
            this->rows = rows;
            this->cols = cols;
            matrix = vector<vector<double>>(rows, vector<double>(cols));
        }

        Matrix(vector<vector<double>> array){
            rows = array.size();
            cols = array[0].size();
            matrix = array;
        }
};

int main(){
    vector<vector<double>> array1 = {{6, 9}, {3, 12}};
    vector<vector<double>> array2 = {{128}, {341.6}};

    Matrix m1(array1);
    Matrix m2(array2);

    Matrix::multiply(m1, m2).print();
}