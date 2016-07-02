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


#ifndef VECTOR_HPP_
#define VECTOR_HPP_

#include <cstdlib>
#include <memory>
#include <string>

namespace n1graph {

template<class T>
class Vector {
public:
	Vector() :
			length_(0) {

	}

	Vector(const Vector<T>& copy);
	Vector(T dim1);
	Vector(T dim1, T dim2);
	Vector(T dim1, T dim2, T dim3);
	Vector(T dim1, T dim2, T dim3, T dim4);

	double Norm() const;
	void Resize(int length);
	void Set(int dim, T value);

	T& operator[](int dim);
	const T& operator[](int dim) const;
	Vector<T> operator-(const Vector<T>& v1) const;
	Vector<T> operator+(const Vector<T>& v1) const;
	Vector<T>& operator=(const Vector<T>& v1);

	const T* data() const {
		return data_.get();
	}

	const std::string ToString() const {
		std::string output;
		for (int j = 0; j < length_; ++j) {
			output += std::to_string(data_[j]);
			output += ",";
		}
		return output;
	}
	virtual ~Vector() {
	}

	int length() const {
		return length_;
	}

private:
	int length_;
	std::unique_ptr<T[]> data_;

};

} /* namespace n1graph */
#endif /* VECTOR_HPP_ */
