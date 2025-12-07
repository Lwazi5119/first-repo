#ifndef Matrix_h
#define Matrix_h
#include <iostream>
using namespace std;


template<class T>
class PPMatrix{
private:
    T**data;
    int rows;
    int cols;
public:
    PPMatrix(int r, int c );
    PPMatrix(): rows(0), cols(0){}
    PPMatrix(const PPMatrix<T> & other);
    ~PPMatrix();
    
    int getRows() const;
    int getCols() const;
    bool sameSize(const PPMatrix& other) const;
    bool canMultiply(const PPMatrix& other) const;
 
    void printMatrix() const;
    void addtoMatrix(int row, int colum, T value);
    
    PPMatrix<T>& operator=(const PPMatrix<T>& other);
    
    PPMatrix<T> operator+(const PPMatrix<T>& other);
    PPMatrix<T> operator+(const T& value);
    PPMatrix<T> operator-(const PPMatrix<T>& other);
    PPMatrix<T> operator-(const T& value);
    PPMatrix<T> operator*(const PPMatrix<T>& other);
    PPMatrix<T> operator*(const T& value);
    
    bool operator==(const PPMatrix<T>& other) const;
    
    T* operator[](int index);
    const T* operator[](int index) const;
 
    PPMatrix<T>& operator++();//pre increment
    PPMatrix<T> operator++(int);//post increment
    
//friend functions: cout and cin
    friend ostream& operator<<(std::ostream& os, const PPMatrix<T>& other){
        for (int i=0; i<other.rows; i++) {
            for(int j=0; j<other.cols; j++){
                os<<"["<<other.data[i][j]<<"] ";
            }
            os<<endl;
        }
        return os;
    }

    friend istream& operator>>(std::istream& is, PPMatrix<T>& other){
        for(int i=0; i<other.rows; i++){
            for(int j=0; j<other.cols; j++){
                is>>other.data[i][j];
            }
        }
        return is;
    }

};
    
#endif /* Matrix_h */


template<class T>
PPMatrix<T>::PPMatrix(int r, int c) : rows(r), cols(c){
    data = new T*[rows];
    for(int i=0; i<rows; i++){
        data[i]= new T[cols];
    }
    //creating values that are 0
    for(int i=0; i<rows;i++){
        for(int j=0; j<cols; j++){
            data[i][j] = 0;
        }
    }
}

template<class T>
PPMatrix<T>::PPMatrix(const PPMatrix<T>& other){
    //copy dimensions
    rows = other.rows;
    cols = other.cols;
    //alloacte memory
    data = new T*[rows];
    for(int i=0; i<rows; i++){
        data[i]=new T[cols];
    }
    //copy each value to new Matrix
    for(int i=0;i<rows;i++){
        for(int j=0; j<cols; j++){
            data[i][j]= other.data[i][j];
        }
    }
}

template<class T>
PPMatrix<T>::~PPMatrix(){
    for(int i=0; i<rows; i++){
        delete[] data[i];
    }
    delete[] data;
    data = NULL;
    std::cout<<"Pointer Pointer Matrix memory freed and Nullified:)"<<std::endl;
}

template<class T>
int PPMatrix<T>::getRows() const{return rows;}

template<class T>
int PPMatrix<T>::getCols() const{return cols;}

template<class T>
bool PPMatrix<T>::sameSize(const PPMatrix<T> &other) const{
    if((rows == other.rows) && (cols == other.cols))
        return true;
    else
        return false;
}
template<class T>
bool PPMatrix<T>::canMultiply(const PPMatrix<T> &other) const{
    if(cols == other.rows)
        return true;
    else
        return false;
}

template<class T>
void PPMatrix<T>::printMatrix() const{
    for (int i=0; i<rows; i++) {
        for(int j=0; j<cols; j++){
            cout<<data[i][j]<<" ";
        }
        cout<<endl;
    }
}

template<class T>
void PPMatrix<T>::addtoMatrix(int row, int colum, T value){
    data[row][colum] = value;
}

template<class T>
PPMatrix<T>& PPMatrix<T>::operator=(const PPMatrix<T> &other){
    if(this == &other) return *this;
    //deleting the current values
    for(int i=0; i<rows; i++){
        delete[] data[i];
    }
    delete[] data;
    //chnaging values
    rows = other.rows;
    cols = other.cols;
    //alocating new data
    data = new T*[rows];
    for(int i=0; i<rows; i++){
        data[i]=new T[cols];
        for(int j=0; j<cols; j++){
            data[i][j]= other.data[i][j];
        }
    }
    return *this;
}

template<class T>
PPMatrix<T> PPMatrix<T>::operator+(const PPMatrix<T>& other){
    if(sameSize(other)==false)
        throw "Matrices are not the same size, can't perform Matrix addition.";
    else{
        PPMatrix<T> result(rows, cols);
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                result.data[i][j] = data[i][j] + other.data[i][j];
            }
        }
        return result;
    }
}

template<class T>
PPMatrix<T> PPMatrix<T>::operator+(const T& value){
    PPMatrix<T> result(rows, cols);
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            result.data[i][j] = data[i][j] + value;
        }
    }
    return result;
}

template<class T>
PPMatrix<T> PPMatrix<T>::operator-(const PPMatrix<T>& other){
    if(sameSize(other)==false)
        throw "Matrices are not the same size, can't perform Matrix subtraction.";
    else{
        PPMatrix<T> result(rows, cols);
        for(int i=0; i<rows; i++){
            for(int j=0; j<cols; j++){
                result.data[i][j] = data[i][j] - other.data[i][j];
            }
        }
        return result;
    }
}

template<class T>
PPMatrix<T> PPMatrix<T>::operator-(const T& value){
    PPMatrix<T> result(rows, cols);
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            result.data[i][j] = data[i][j] - value;
        }
    }
    return result;
}
template<class T>
PPMatrix<T> PPMatrix<T>::operator*(const PPMatrix<T> &other){
    if(canMultiply(other)==false)
        throw "Matrices are not a match for Matrix Multiplication, can't perform action.";
    else{
        //create a new result matrix
        PPMatrix<T> result(rows, other.cols);
        //triple nested
        for(int i=0; i<result.rows; i++){
            for(int j=0; j<result.cols; j++){
                for(int k=0; k<cols; k++){
                    result.data[i][j] += data[i][k] * other.data[k][j];
                }
            }
        }
        return result;
    }
}

template<class T>
PPMatrix<T> PPMatrix<T>::operator*(const T& value){
    PPMatrix<T> result(rows, cols);
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            result.data[i][j] = data[i][j] * value;
        }
    }
    return result;
}

template<class T>
bool PPMatrix<T>::operator==(const PPMatrix<T> &other) const{

    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            if (data[i][j] != other.data[i][j])
                return false;
        }
    }
    return true;
}

template<class T>
T* PPMatrix<T>::operator[](int index){
    return data[index];
}

template<class T>
const T* PPMatrix<T>::operator[](int index) const{
    return data[index];
}

template<class T>
PPMatrix<T>& PPMatrix<T>::operator++(){
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            ++data[i][j];
        }
    }
    return *this;
}

template<class T>
PPMatrix<T> PPMatrix<T>::operator++(int){
    PPMatrix<T> temp = *this;
    for(int i=0; i<rows; i++){
        for(int j=0; j<cols; j++){
            ++data[i][j];
        }
    }
    return temp;
}

