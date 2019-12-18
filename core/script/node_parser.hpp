#ifndef __DOTTH_NODE_PARSER_HPP__
#define __DOTTH_NODE_PARSER_HPP__

#include "dotth.hpp"

namespace dotth {
	class node_parser : public utility::singleton<node_parser> {
	public:
		std::string read_file(const char* file_path);
		std::shared_ptr<class object> parse(const std::string& contents);
	};
};

#endif // __DOTTH_NODE_PARSER_HPP__
