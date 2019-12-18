#include "node_parser.hpp"
#include "platform/filesystem/path.hpp"
#include "base/object.hpp"

std::string dotth::node_parser::read_file(const char * file_path)
{
	std::string path = dotth::path(file_path);
	// ���̴� �ڵ带 ���Ͽ��� �б�
	std::string contents;
	std::ifstream stream(path.c_str(), std::ios::in);
	if (stream.is_open()) {
		std::stringstream sstr;
		sstr << stream.rdbuf();
		contents = sstr.str();
		stream.close();
	}
	else 
	{
		printf("���� %s �� ���� �� ����. ��Ȯ�� ���丮�� ��� ���Դϱ� ? FAQ �� �켱 �о�� �� ���� ������!\n", path.c_str());
		getchar();
		return "";
	}

	return contents;
}

std::shared_ptr<dotth::object> dotth::node_parser::parse(const std::string& contents)
{
	tinyxml2::XMLDocument XmlDoc;
	auto enError = XmlDoc.Parse(contents.c_str());
	if (enError != tinyxml2::XML_SUCCESS)
	{
		printf("[%s] parse error : %s", __FUNCTION__, std::to_string(enError).c_str());
		return nullptr;
	}
	return nullptr;
}
