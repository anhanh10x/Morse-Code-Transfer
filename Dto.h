#include<iostream>
#include<list>
#include<conio.h>
#include<fstream>
#include<string>
namespace Dto
{
	class TextAndMor
	{
	public:
		std::list<std::string> Sentences;
		std::list<std::string> Morses;
		std::list<std::string> Errors;
		std::string CompletedTime, CompletedDate,CompletedTimeDate;
		double Duration;
		int	TotalWord, SuccessedWord, ErrorWord;
		int TotalCharacter, ConvertedCharacter, ErrorCharacter;
		TextAndMor()
		{
			CompletedDate=CompletedTime = CompletedTimeDate="";
			Duration = 0;
			TotalWord = SuccessedWord = ErrorWord = 0;
			TotalCharacter=ConvertedCharacter = ErrorCharacter = 0;
		}
	};
	class Statistic:public Dto::TextAndMor
	{
	public:
		std::string InputFile;
		std::string OutputFile;
		std::string InputLink;
		std::string OutputLink;
		Statistic()
		{
			InputFile = "";
			OutputFile = "";
			InputLink = "";
			OutputLink = "";
		}
		//Copy contructor of Statistic object with TextandMorse
		Statistic(const Dto::TextAndMor& Old)
		{
			this->CompletedDate = Old.CompletedDate;
			this->CompletedTime = Old.CompletedTime;
			this->CompletedTimeDate = Old.CompletedTimeDate;
			this->ConvertedCharacter = Old.ConvertedCharacter;
			this->Duration = Old.Duration;
			this->ErrorCharacter = Old.ErrorCharacter;
			this->ErrorWord = Old.ErrorWord;
			this->SuccessedWord = Old.SuccessedWord;
			this->TotalCharacter = Old.TotalCharacter;
			this->TotalWord = Old.TotalWord;
		}
	};
}