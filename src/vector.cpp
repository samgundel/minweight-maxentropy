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


#include <vector.hpp>

#include <cmath>

#include <glog/logging.h>

namespace n1graph {

template<class T>
Vector<T>::Vector(const Vector<T>& v1) {
	if (&v1 != this) {
		length_ = v1.length();
		data_.reset(new T[v1.length_]);
		memcpy(data_.get(), v1.data(), length_ * sizeof(T));
	}
}

template<class T>
Vector<T>::Vector(T dim0) :
		length_(1) {
	data_.reset(new T[length_]);
	data_[0] = dim0;
}

template<class T>
Vector<T>::Vector(T dim0, T dim1) :
		length_(2) {
	data_.reset(new T[length_]);
	data_[0] = dim0;
	data_[1] = dim1;
}

template<class T>
Vector<T>::Vector(T dim0, T dim1, T dim2) :
		length_(3) {
	data_.reset(new T[length_]);
	data_[0] = dim0;
	data_[1] = dim1;
	data_[2] = dim2;
}

template<class T>
Vector<T>::Vector(T dim0, T dim1, T dim2, T dim3) :
		length_(4) {
	data_.reset(new T[length_]);
	data_[0] = dim0;
	data_[1] = dim1;
	data_[2] = dim2;
	data_[3] = dim3;
}

template<class T>
void Vector<T>::Resize(int length) {
	length_ = length;
	data_.reset(new T[length_]);
}

template<class T>
Vector<T> Vector<T>::operator -(const Vector<T>& v1) const {
	Vector<T> difference;
	difference.Resize(v1.length());
	for (int i = 0; i < v1.length(); ++i) {
		T d = data_[i] - v1[i];
		difference.Set(i, d);
	}
	return difference;
}

template<class T>
Vector<T> Vector<T>::operator +(const Vector<T>& v1) const {
	Vector<T> difference;
	difference.Resize(v1.length());
	for (int i = 0; i < v1.length(); ++i)
		difference.Set(i, data_[i] + v1[i]);
	return difference;
}

template<class T>
Vector<T>& Vector<T>::operator =(const Vector<T>& v1) {
	if (this != &v1) {
		length_ = v1.length();
		data_.reset(new T[v1.length_]);
		memcpy(data_.get(), v1.data(), length_ * sizeof(T));
	}
	return *this;
}

template<class T>
T& Vector<T>::operator [](int dim) {
	CHECK_LT(dim, length_);
	return data_[dim];
}

template<class T>
const T& Vector<T>::operator [](int dim) const {
	CHECK_LT(dim, length_);
	return data_[dim];
}

template<class T>
double Vector<T>::Norm() const {
	double sum = 0;
	for (int i = 0; i < length_; ++i) {
		sum += pow(data_[i], 2);
	}
	return sqrt(sum);
}

template<class T>
void Vector<T>::Set(int dim, T value) {
	CHECK_LT(dim, length_);
	data_[dim] = value;
}

template class Vector<int> ;
template class Vector<long> ;
template class Vector<long long> ;
template class Vector<float> ;
template class Vector<double> ;

} /* namespace n1graph */
