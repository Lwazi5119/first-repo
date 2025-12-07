#include "Matrix.h"


int main(){
    PPMatrix<int>A(3, 3);
    PPMatrix<int>B(2,2);
    cout<<A;
    cout<<"Please enter values for Matrix A: "<<endl;
    cin>>A;\
    cout<<A;
    cout<<endl;
    cout<<"Please enter values for B: "<<endl;
    cin>>B;
    cout<<B;
    cout<<endl;
    
    try{
        cout<<A+B;
    }
    catch (const char* error){
        cout<<"Error: "<<error;

    }

    
}

