#include"Dto.h"
namespace Dal
{
	bool isFileExis(std::string);
	void GetData(std::list<std::string>& List, std::string);
	void SaveData(std::list<std::string>, std::list<std::string>, std::string);
	class TextToMor
	{
	public:
		void MorseHashTable(std::string[]);
	};
	class MorToText
	{
	public:
		void TextHashTable(std::string[]);
	};
	class Statistic
	{
	public:
		void SaveStatistic(Dto::Statistic);
	};
	class Readme
	{
	public:
		void GetReadme(std::list<std::string>&);
		void SaveReadme(std::list<std::string>);
	};
}