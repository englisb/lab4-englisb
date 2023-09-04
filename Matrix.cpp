
#include "Matrix.h"
#include <iostream>
#include <stdexcept>
#include <stdlib.h>
using namespace std;

Matrix::Matrix(){

	rowsNum=3;
	colsNum=3;
	matrixData=NULL;
	matrixData = (int**)malloc(rowsNum*sizeof(int*));

    // Allocate rows for fake "2D array":
    for (int i = 0 ; i < rowsNum ; ++i ){
       matrixData[i] = (int*) malloc(colsNum*sizeof(int));
    }

    for (int i = 0 ; i < rowsNum ; ++i ){
    	for (int j = 0 ; j < colsNum ; ++j ){
    		matrixData[i][j]=0;
		}

    }


}

Matrix::Matrix( int row, int col ){

	/*
	* constructs a row-by-col matrix with
	* all elements equal to 0; if row ≤ 0, the number of rows of the matrix is set to
	* 3; likewise, if col ≤ 0 the number of columns of the matrix is set to 3.
	*/

	rowsNum = (row <= 0? 3 : row);
	colsNum = (col <= 0? 3 : col);


	matrixData=NULL;
	matrixData = (int**)malloc(rowsNum*sizeof(int*));
    // Allocate rows for fake "2D array", setting entries to 0:
    for (int i = 0 ; i < rowsNum ; ++i )
    {
       matrixData[i] = (int*) calloc(colsNum,sizeof(int));
    }

}


Matrix::Matrix(int row, int col, int** table){

	/*
	* constructs a matrix out of the two dimensional array table, with the same number of rows, columns, and the same
	* element in each position as array table.
	*/

	rowsNum = row;
	colsNum = col;
	matrixData=NULL;

	matrixData = (int**)malloc(rowsNum*sizeof(int*));

	// Allocate rows for fake "2D array":
	for (int i = 0 ; i < rowsNum ; i++ ){
	   matrixData[i] = (int*) malloc(colsNum*sizeof(int));
	}

	for(int i = 0 ; i < rowsNum ; i++ ){		//go through each matrix entry and copy the values from table
	    for (int j = 0 ; j < colsNum ; j++ ){
	    	matrixData[i][j] = table[i][j];
	    }
	}

	

}

int Matrix::getElement(int i, int j){

	if(i >= rowsNum || i < 0 || j >= colsNum || j < 0){
		throw std::out_of_range( "Invalid indexes." );		//throw an exception if i or j out of matrix range
	}
		return matrixData[i][j];

}

bool Matrix::setElement(int x, int i, int j){

	if(i >= colsNum || i < 0 || j >= rowsNum || j < 0){
		return false;
	}


	matrixData[i][j] = x;			//if i and j are within matrix range set the entry at i,j to x
	return true;




}


Matrix Matrix::copy(){



    Matrix copy =  Matrix(rowsNum, colsNum, this->matrixData );
    //object "this" refers to object that method is being called on
    //create matrix copy using matrixData as a table and copying each entry over

    return copy;


}


void Matrix::addTo( Matrix m ){

	if(m.getsizeofcols() != this->getsizeofcols() || m.getsizeofrows() != this->getsizeofrows()){
		throw std::invalid_argument( "Invalid operation" );
		//throw an exception if "this" and "m" are not of the same dimensions
	}

	int i, j;

	for(i = 0; i < m.getsizeofrows(); i++){
		for(j = 0; j < m.getsizeofcols(); j++){
			this->matrixData[i][j] += m.getElement(i, j);	//add each corresponding entry of "m" to "this"
		}
	}
	
}


Matrix Matrix::subMatrix(int i, int j){

	//throw an exception if i or j are out of range of "this"
	if(i >= this->rowsNum || j >= this->colsNum || i <= 0 || j <= 0){
		throw std::out_of_range("Submatrix not defined");
	}

	Matrix subM = Matrix(i + 1,j + 1);

	int a, b;	//row and column variables for reiteration

	for(a = 0; a < i + 1; a++){									//going through each entry of subM, set it equal to the corresponding entry in "this" matrix
		for(b = 0; b < j + 1; b++){
			subM.setElement(this->matrixData[a][b], a, b);
		}
	}
    

    return  subM;
}


int Matrix::getsizeofrows(){

	
	return rowsNum;
}


int Matrix::getsizeofcols(){



    return colsNum;
}


bool Matrix::isUpperTr(){

	

	int i, j, currRow;


	for(j = 0, currRow = 1; j < colsNum && currRow < rowsNum; j++, currRow++){			//starting at row 0 check if every entry under the main diagonal is a 0
		for(i = currRow; i < rowsNum; i++){												//currentRow is the checkpoint and i iterates through the entries under it
			if(matrixData[i][j] != 0){													//if a non-zero is encountered return false
				return false;
			}
		}
	}


	return true;																		//if a non-zero is never encountered return true
}


string Matrix::toString(){

	int i, j;
	string output = "";																	//initialize an empty string

	for(i = 0; i < this->rowsNum; i++){
		for(j = 0; j < this->colsNum; j++){												//nested for loop for iteration through every matrixData entry
			output += to_string(this->matrixData[i][j]) + " ";							//to output, concatenate the string conversion of the matrixData entry and a space
		}
		output += "\n";																	//insert newline for every new row
	}


	return output;
}
