/*
Licensed under the MIT License <http://opensource.org/licenses/MIT>.
Copyright (c) 2019 jaefunk <https://github.com/jaefunk/dotth>.

Permission is hereby  granted, free of charge, to any  person obtaining a copy
of this software and associated  documentation files (the "Software"), to deal
in the Software  without restriction, including without  limitation the rights
to  use, copy,  modify, merge,  publish, distribute,  sublicense, and/or  sell
copies  of  the Software,  and  to  permit persons  to  whom  the Software  is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE  IS PROVIDED "AS  IS", WITHOUT WARRANTY  OF ANY KIND,  EXPRESS OR
IMPLIED,  INCLUDING BUT  NOT  LIMITED TO  THE  WARRANTIES OF  MERCHANTABILITY,
FITNESS FOR  A PARTICULAR PURPOSE AND  NONINFRINGEMENT. IN NO EVENT  SHALL THE
AUTHORS  OR COPYRIGHT  HOLDERS  BE  LIABLE FOR  ANY  CLAIM,  DAMAGES OR  OTHER
LIABILITY, WHETHER IN AN ACTION OF  CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE  OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#ifndef __DOTTH_IO_HPP__
#define __DOTTH_IO_HPP__

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

namespace dotth {
	namespace io {
		const std::string read_text(const std::string& path) {
			FILE* hFile;
			hFile = fopen(path.c_str(), "rt");
			fseek(hFile, 0, SEEK_END);
			auto size = ftell(hFile);
			fseek(hFile, 0, SEEK_SET);
			std::string strRet;
			strRet.resize(size);
			auto bSuccess = fread((void*)strRet.data(), 1, static_cast<int>(size), hFile);
			fclose(hFile);
			return strRet;
		}
		const std::string read_binary(const std::string& path) {
			FILE* hFile;
			hFile = fopen(path.c_str(), "rb");
			fseek(hFile, 0, SEEK_END);
			auto size = ftell(hFile);
			fseek(hFile, 0, SEEK_SET);
			
			std::vector<char> ret;
			ret.resize(size);
			auto bSuccess = fread((void*)ret.data(), 1, static_cast<int>(size), hFile);
			fclose(hFile);
			return "";
		}
	}
};

#endif // __DOTTH_IO_HPP__
