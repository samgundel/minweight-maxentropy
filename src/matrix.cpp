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


#include <matrix.hpp>
#include <algorithm>

namespace n1graph {

template<class T>
Matrix<T>::Matrix() :
		cols_(0), rows_(0), channels_(0), initialized_(false) {

}

template<class T>
Matrix<T>::Matrix(const Matrix<T>& original) {
	channels_ = original.channels();
	cols_ = original.cols();
	rows_ = original.rows();
	initialized_ = true;
	// Allocating the space for each channel.
	data_.reset(new std::unique_ptr<T[]>[channels_]);
	// Allocating the matrix in single array.
	for (int c = 0; c < channels_; ++c) {
		data_[c].reset(new T[cols_ * rows_]);
		for (int x = 0; x < cols_ * rows_; ++x) {
			data_[c][x] = original(x / cols_, x % cols_, c);
		}
	}
}

template<class T>
Matrix<T>::Matrix(int width, int height, int n_channels, T default_value) :
		cols_(width), rows_(height), channels_(n_channels) {
	Allocate(cols_, rows_, channels_, default_value);
}

template<class T>
void Matrix<T>::Allocate(int width, int height, int channels, T default_value) {
	rows_ = height;
	cols_ = width;
	channels_ = channels;
	initialized_ = true;
	CHECK_GE(width, 0);
	CHECK_GE(height, 0);
	CHECK_GE(channels, 1);
	// Allocating the space for each channel.
	data_.reset(new std::unique_ptr<T[]>[channels]);
	// Allocating the matrix in single array.
	for (int c = 0; c < channels_; ++c) {
		data_[c].reset(new T[cols_ * rows_]);
		for (int x = 0; x < cols_ * rows_; ++x) {
			data_[c][x] = default_value;
		}
	}
}

// Accessing single channel matrices.
template<class T>
T& Matrix<T>::operator()(const int row, const int col, const int channel) {
	CHECK_GE(row, 0);
	CHECK_GE(col, 0);
	CHECK_LT(row, rows_);
	CHECK_LT(col, cols_);
	return data_[channel][cols_ * row + col];
}

// Accessing single channel matrices in const mode.
template<class T>
T& Matrix<T>::operator()(const int row, const int col,
		const int channel) const {
	CHECK_GE(row, 0);
	CHECK_GE(col, 0);
	CHECK_LT(row, rows_);
	CHECK_LT(col, cols_);
	return data_[channel][cols_ * row + col];
}

template<class T>
T& Matrix<T>::operator()(const Vector<int>& coordinates) {
	CHECK_GT(coordinates.length(), 0);
	CHECK_LE(coordinates.length(), 3);
	int row = coordinates[0];
	int col = coordinates[1];
	int channel = 0;
	if (coordinates.length() == 3)
		channel = coordinates[2];
	CHECK_GE(row, 0);
	CHECK_GE(col, 0);
	CHECK_GE(channel, 0);
	CHECK_LT(row, rows_);
	CHECK_LT(col, cols_);
	CHECK_LT(channel, channels_);
	return data_[channel][cols_ * row + col];
}

template<class T>
T& Matrix<T>::operator()(const Vector<int>& coordinates) const {
	CHECK_GT(coordinates.length(), 0);
	CHECK_LE(coordinates.length(), 3);
	int row = coordinates[0];
	int col = coordinates[1];
	int channel = 0;
	if (coordinates.length() == 3)
		channel = coordinates[2];
	CHECK_GE(row, 0);
	CHECK_GE(col, 0);
	CHECK_GE(channel, 0);
	CHECK_LT(row, rows_);
	CHECK_LT(col, cols_);
	CHECK_LT(channel, channels_);
	return data_[channel][cols_ * row + col];
}

template<class T>
int Matrix<T>::rows() const {
	return rows_;
}

template<class T>
int Matrix<T>::channels() const {
	return channels_;
}

template<class T>
T Matrix<T>::min_row(int row) const {
	CHECK_LT(row, rows_);
	return *std::min_element(data_[row].get(), data_[row].get() + cols_);
}

template<class T>
T Matrix<T>::min_col(int col) const {
	CHECK_LT(col, cols_);
	T min_value = std::numeric_limits<float>::max();
	for (int i = 0; i < rows_; ++i) {
		min_value = std::min(min_value, (*this)(i, col));
	}
	return min_value;
}

template<class T>
int Matrix<T>::arg_min_row(int row) const {
	// TODO(sam): Implement this method.
}

template<class T>
int Matrix<T>::arg_min_col(int col) const {
	CHECK_LT(col, cols_);
	int arg_min = -1;
	T min_value = std::numeric_limits<float>::max();
	for (int i = 0; i < rows_; ++i) {
		T current_value = (*this)(i, col);
		if (current_value < min_value) {
			min_value = current_value;
			arg_min = i;
		}
	}
	return arg_min;
}


template<class T>
T Matrix<T>::col_sum(int col) const {
	CHECK_LT(col, cols_);
	T sum = 0;
	for (int i = 0; i < rows_; ++i) {
		sum += (*this)(i, col);
	}
	return sum;
}


template<class T>
T Matrix<T>::row_sum(int row) const {
	CHECK_LT(row, rows_);
	T sum = 0;
	for (int i = 0; i < cols_; ++i) {
		sum += (*this)(row, i);
	}
	return sum;
}

template<class T>
Matrix<T>& Matrix<T>::operator =(const Matrix<T>& original) {
	if (this != &original) {
		channels_ = original.channels();
		cols_ = original.cols();
		rows_ = original.rows();
		initialized_ = true;
		// Allocating the space for each channel.
		data_.reset(new std::unique_ptr<T[]>[channels_]);
		// Allocating the matrix in single array.
		for (int c = 0; c < channels_; ++c) {
			data_[c].reset(new T[cols_ * rows_]);
			for (int x = 0; x < cols_ * rows_; ++x) {
				data_[c][x] = original(x / cols_, x % cols_, c);
			}
		}
	}
	return *this;
}

template<class T>
std::string Matrix<T>::ToString() const {
	std::string output("\n");
	for (int c = 0; c < channels_; ++c) {
		for (int i = 0; i < rows_; ++i) {
			for (int j = 0; j < cols_; ++j) {
				const T value = (*this)(i, j, c);
				output += std::to_string(value);
				output += ",";
			}
			output += "\n";
		}
		output += "\n";
	}
	return output;

}



template<class T>
bool Matrix<T>::initialized() const {
	return initialized_;
}

template<class T>
int Matrix<T>::cols() const {
	return cols_;
}

template class Matrix<bool> ;
template class Matrix<int> ;
template class Matrix<long> ;
template class Matrix<float> ;
template class Matrix<double> ;

} /* namespace n1graph */
