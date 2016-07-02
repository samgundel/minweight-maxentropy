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


#include <text_writer.hpp>

namespace n1graph {

void TextWriter::Write(std::string location, const std::string& text) {
	std::ofstream output_file;
	output_file.open(location.c_str());
	output_file << text;
	output_file.close();
}

void TextWriter::Write(std::string location,
		const std::vector<std::string>& lines) {
	std::ofstream output_file;
	output_file.open(location.c_str());
	for (const std::string& line : lines) {
		output_file << line << std::endl;
	}
	output_file.close();
}

} // namespace n1graph

