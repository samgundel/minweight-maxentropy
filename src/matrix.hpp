/*
 * Copyright 2014 Samuel de Sousa
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef MATRIX_HPP_
#define MATRIX_HPP_

#include <memory>
#include <string>

#include <glog/logging.h>

#include <vector.hpp>

namespace n1graph {

/**
 * A Matrix class which is the core data structured we use.
 *
 * It accepts a parameter defining which type of data we are allocating.
 */
template<class T>
class Matrix {
public:
	/**
	 * The default constructor which creates a Matrix but it does not allocate
	 * any data in the heap. The current state of the Matrix after this method
	 * will be: not initialized.
	 */
	Matrix();

	/**
	 * It creates a copy of the provided object.
	 *
	 * @param original The object to be copied.
	 */
	Matrix(const Matrix<T>& original);

	/**
	 * The constructor of a matrix which already allocates the data in the heap.
	 * The current state of the matrix after this method will be initialized.
	 *
	 * @param width The number of columns in this matrix.
	 * @param height The number of rows in this matrix.
	 * @param n_channels The number of channels in this matrix. In case this
	 * argument is not provided, the matrix will be bidimentional.
	 * @param default_value The value used for initialization.
	 */
	Matrix(int width, int height, int n_channels = 1, T default_value = 0);

	/**
	 * This is the method which allocates data for this matrix and changes the
	 * state. The current state of the matrix after this method will be
	 * initialized.
	 *
	 * @param width The number of columns in this matrix.
	 * @param height The number of rows in this matrix.
	 * @param n_channels The number of channels in this matrix. In case this
	 * argument is not provided, the matrix will be bidimentional.
	 * @param default_value The value used for initialization.
	 */
	void Allocate(int width, int height, int channels = 1, T default_value = 0);

	/**
	 * Accessing cell location using explicit values for row, col, and channel.
	 *
	 * @param row The row of the matrix.
	 * @param col The column of the matrix.
	 * @param channel The channel of the matrix, the default value is zero.
	 * @return the reference to that matrix location.
	 */
	T& operator()(const int row, const int col, const int channel = 0);

	/**
	 * Accessing cell location using explicit values for row, col, and channel
	 * in const mode.
	 *
	 * @param row The row of the matrix.
	 * @param col The column of the matrix.
	 * @param channel The channel of the matrix, the default value is zero.
	 * @return the reference to that matrix location.
	 */
	T& operator()(const int row, const int col, const int channel = 0) const;

	/**
	 * Accessing cell location using a vector with 2 or 3 coordinates.
	 *
	 * @param coordinates the location of the matrix to be accessed.
	 * @return the reference to that matrix location.
	 */
	T& operator()(const Vector<int>& coordinates);

	/**
	 * Accessing cell location using a vector with 2 or 3 coordinates in const
	 * mode.
	 *
	 * @param coordinates the location of the matrix to be accessed.
	 * @return the reference to that matrix location.
	 */
	T& operator()(const Vector<int>& coordinates) const;

	/**
	 * The assignment operator which is useful during object copy.
	 *
	 * @param original The object to be copied.
	 * @return the reference to the object.
	 */
	Matrix<T>& operator=(const Matrix<T>& original);

	/**
	 * Finds the minimum value of a row.
	 *
	 * Time Complexity O(N) for N the number of columns.
	 *
	 * @param row the row index to be calculated.
	 * @return the minimum value.
	 */
	T min_row(int row) const;

	/**
	 * Finds the argmin of a row, i.e. the element whose value is the minimum.
	 * In case all values are the same and no minimum is found, then the return
	 * value is equal to -1.
	 *
	 * Time Complexity O(N) for N the number of columns.
	 *
	 * @param row The row index.
	 * @return the index of the column with minimum value in the specified row.
	 */
	int arg_min_row(int row) const;

	/**
	 * Finds the minimum value of a colunm.
	 *
	 * Time Complexity O(N) for N the number of rows.
	 *
	 * @param col the column index to be calculated.
	 * @return the minimum value.
	 */
	T min_col(int col) const;

	/**
	 * Finds the argmin of a cols, i.e. the element whose value is the minimum.
	 * In case all values are the same and no minimum is found, then the return
	 * value is equal to -1.
	 *
	 * Time Complexity O(N) for N the number of rows.
	 *
	 * @param col The col index.
	 * @return the argmin of that col.
	 */
	int arg_min_col(int col) const;

	/**
	 * It returns the sum of all elements in the column.
	 */
	T row_sum(int row) const;

	/**
	 * It returns the sum of all elements in the row.
	 */
	T col_sum(int col) const;

	/**
	 * Returns the number of rows in this matrix.
	 *
 	 * Time Complexity O(1).
	 *
	 * @return The number of rows.
	 */
	int rows() const;

	/**
	 * Returns the number of columns in this matrix.
	 *
 	 * Time Complexity O(1).
	 *
	 * @return The number of cols.
	 */
	int cols() const;

	/**
	 * Returns the number of channels in this matrix.
	 *
 	 * Time Complexity O(1).
	 *
	 * @return The number of channels.
	 */
	int channels() const;

	/**
	 * This method checks the state of the current matrix, i.e. if it has been
	 * initialized of not. Initialization means that data has been already
	 * dynamic allocated in memory, all methods which require operations in the
	 * matrix will check for initialization and throw and error in case it has
	 * not been yet initialized.
	 *
 	 * Time Complexity O(1).
	 *
	 * @return The number of cols.
	 */
	bool initialized() const;

	/**
	 * This method generates a string representation of all content of the
	 * matrix. It is useful for debug purposes.
	 *
	 * Time Complexity O(N^3). It has to iterate through all dimensions.
	 *
	 * @return The string representation of the matrix.
	 */
	std::string ToString() const;

	virtual ~Matrix() {
	}

private:

	// The number of rows, columns, and channels.
	int rows_;
	int cols_;
	int channels_;

	// It holds the state of this matrix: initialized or not.
	bool initialized_;

	// The actual data being stored as a smart pointer.
	std::unique_ptr<std::unique_ptr<T[]>[]> data_;
};

} /* namespace n1graph */
#endif /* MATRIX_HPP_ */
