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


#ifndef TEXT_WRITER_HPP_
#define TEXT_WRITER_HPP_

#include <fstream>
#include <string>
#include <vector>

namespace n1graph {

/**
 * A utility class which writes text into files.
 */
class TextWriter {
 public:
	/**
	 * This method creates the a file whose each element of the
	 * vector will be a line of the file.
	 *
	 * @param location the output file location.
	 * @param lines the lines to be written into the file.
	 */
	static void Write(std::string location,
			const std::vector<std::string>& lines);
	/**
	 * This method creates the a file whose content will be the
	 * supplied string.
	 *
	 * @param location the output file location.
	 * @param text the text to be written into the file.
	 */
	static void Write(std::string location,
			const std::string& text);

};

}  // namespace n1graph
#endif /* TEXT_WRITER_HPP_ */
