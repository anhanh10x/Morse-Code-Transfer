#include"Bll.h"
namespace Gui
{
	class TextToMor:private Bll::TextToMor
	{
	public:
		void TransferText(std::string,std::string);
	};
	class MorseToText :private Bll::MorseToTex
	{
	public:
		void TransferMorse(std::string, std::string);
	};
	class Statistic :private Bll::MorseToTex, Bll::TextToMor, Bll::Statistic
	{
	public:
		void GeneralMenu(Dto::TextAndMor);
		void MenuTextToMorse(std::string, std::string);
		void MenuMorseToText(std::string, std::string);
	};
	class Readme:private Bll::Readme
	{
	public:
		void ReadmeFile();
	};
	class MainMenu :private Gui::MorseToText, Gui::TextToMor, Gui::Statistic, Gui::Readme, Bll::MainMenu
	{
	public:
		void Decentralization(int, char*[]);
	};
}
