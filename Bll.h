#include"Dal.h"
namespace Bll
{
	bool isExistHashValue(std::string[], int);
	bool isFileExis(std::string);
	bool isMorseCode(std::string);
	std::string ToString(int);
	std::string DeleteExtraBlank(std::string);
	std::string FixForm(std::string);
	std::string returnTime();
	std::string returnDate();
	std::string returnMonthString(int);
	std::string returnTimeDate();
	std::string returnLowerCase(std::string);
	std::string returnFormatFile(std::string);
	void SaveData(std::list<std::string>,std::list<std::string>,std::string);
	class TextToMor:private Dal::TextToMor
	{
	public:
		std::string returnTextError(char, int);
		void TransferText(Dto::TextAndMor&,std::string,std::string);
	};
	class MorseToTex:private Dal::MorToText
	{
	public:
		std::string returnMorseError(std::string, int);
		int CreateHashCode(std::string);
		void TransferMorse(Dto::TextAndMor&,std::string,std::string);
	};
	class Statistic:private Dal::Statistic
	{
	public:
		std::string CutLink(std::string);
		void SaveStatistic(Dto::Statistic);
	};
	class Readme:public Dal::Readme
	{
	public:
		void SaveReadme(std::list<std::string>);
		void GetDataReadme(std::list<std::string>&);
	};
	class MainMenu
	{
	public:
		bool isMorseInputFile(std::string);
		int	checkErrorFileName(std::string);
		int returnOrderFunction(int,char*[]);
	};

}