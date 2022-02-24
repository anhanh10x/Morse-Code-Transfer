#include"Gui.h"

//*******************************Graphic User Interface****************************

//Function for Text to Morse code.
void Gui::TextToMor::TransferText(std::string InputFile, std::string OutputFile)
{
	InputFile = Bll::returnFormatFile(InputFile);
	OutputFile = Bll::returnFormatFile(OutputFile);
	Dto::TextAndMor MorseCode;
	if (Bll::isFileExis(InputFile) == false)
	{
		std::cout << "Error E006: " << InputFile << " could not be opened" << std::endl;
		return;
	}
	Bll::TextToMor::TransferText(MorseCode, InputFile, OutputFile);
	std::list <std::string> ::iterator Head;
	for (Head = MorseCode.Morses.begin(); Head != MorseCode.Morses.end(); Head++)
	{
		std::cout << *Head << std::endl;
	}
	for (Head = MorseCode.Errors.begin(); Head != MorseCode.Errors.end(); Head++)
	{
		std::cout << *Head << std::endl;
	}
	if (Bll::isFileExis(OutputFile) == true)
	{
		std::cout << "Warning: " << OutputFile << " already exists.Do you wish to overwrite(y, n) ? : ";
		char c = _getch();
		std::cout << c;
		if (c == 'y')
		{
			Bll::SaveData(MorseCode.Morses,MorseCode.Errors, OutputFile);
		}
		else if (c == 'n')
		{
			std::cout << std::endl << OutputFile << " already exists. Nothing has been done." << std::endl;
		}
		else
		{
			std::cout << std::endl << "Invalid Value.";
			return;
		}
	}
	else
	{
		Bll::SaveData(MorseCode.Morses, MorseCode.Errors, OutputFile);
	}
}

//Function for Morse to Text code
void Gui::MorseToText::TransferMorse(std::string InputFile, std::string OutputFile)
{
	Dto::TextAndMor TextCode;
	InputFile = Bll::returnFormatFile(InputFile);
	OutputFile = Bll::returnFormatFile(OutputFile);
	if (Bll::isFileExis(InputFile) == false)
	{
		std::cout << "Error E006: " << InputFile << " could not be opened" << std::endl;
		return;
	}
	Bll::MorseToTex::TransferMorse(TextCode, InputFile, OutputFile);
	std::list <std::string> ::iterator Head;
	for (Head = TextCode.Sentences.begin(); Head != TextCode.Sentences.end(); Head++)
	{
		std::cout << *Head << std::endl;
	}
	for (Head = TextCode.Errors.begin(); Head != TextCode.Errors.end(); Head++)
	{
		std::cout << *Head << std::endl;
	}
	if (Bll::isFileExis(OutputFile) == true)
	{
		std::cout << "Warning: " << OutputFile << " already exists.Do you wish to overwrite(y, n) ? : ";
		char c = _getch();
		std::cout << c;
		if (c == 'y')
		{
			Bll::SaveData(TextCode.Sentences, TextCode.Errors, OutputFile);
		}
		else if (c == 'n')
		{
			std::cout << std::endl << OutputFile << " already exists. Nothing has been done." << std::endl;
		}
		else
		{
			std::cout << std::endl << "Invalid Value.";
			return;
		}
	}
	else
	{
		Bll::SaveData(TextCode.Sentences, TextCode.Errors, OutputFile);
	}
}

//Function for Statistic Menu
void Gui::Statistic::GeneralMenu(Dto::TextAndMor MorseCode)
{
	std::cout << "Time complete: " << MorseCode.CompletedTimeDate << std::endl;
	std::cout << "Duration[seconds]: " << MorseCode.Duration << std::endl;
	std::cout << "Word count in input file: " << MorseCode.TotalWord << std::endl;
	std::cout << "Word converted: " << MorseCode.SuccessedWord << std::endl;
	std::cout << "Word with errors: " << MorseCode.ErrorWord << std::endl;
	std::cout << "Total number of characters: " << MorseCode.TotalCharacter << std::endl;
	std::cout << "Number of characters have been converted: " << MorseCode.ConvertedCharacter << std::endl;
	std::cout << "Number of characters are NOT converted: " << MorseCode.ErrorCharacter << std::endl;
}
void Gui::Statistic::MenuTextToMorse(std::string InputFile, std::string OutputFile)
{
	Dto::TextAndMor MorseCode;
	InputFile = Bll::returnFormatFile(InputFile);
	OutputFile = Bll::returnFormatFile(OutputFile);
	if ( Bll::isFileExis(InputFile) == false)
	{
		std::cout << "Error E006: " << InputFile << " could not be opened" << std::endl;
		return;
	}
	Bll::TextToMor::TransferText(MorseCode, InputFile, OutputFile);
	std::cout << "Input file: " << InputFile << std::endl;
	std::cout << "Output file: " << OutputFile << std::endl;
	Gui::Statistic::GeneralMenu(MorseCode);
	if (Bll::isFileExis(OutputFile) == true)
	{
		std::cout << "Warning: " << OutputFile << " already exists.Do you wish to overwrite(y, n) ? : ";
		char c = _getch();
		std::cout << c;
		if (c == 'y')
		{
			Bll::SaveData(MorseCode.Morses, MorseCode.Errors, OutputFile);
		}
		else if (c == 'n')
		{
			std::cout << std::endl << OutputFile << " already exists. Nothing has been done." << std::endl;
		}
		else
		{
			std::cout << std::endl << "Invalid Value.";
			return;
		}
	}
	else
	{
		Bll::SaveData(MorseCode.Morses, MorseCode.Errors, OutputFile);
	}
	Dto::Statistic Statistic = MorseCode;
	Statistic.InputLink = InputFile;
	Statistic.OutputLink = OutputFile;
	Bll::Statistic::SaveStatistic(Statistic);
}
void Gui::Statistic::MenuMorseToText(std::string InputFile, std::string OutputFile)
{
	Dto::TextAndMor TextCode;
	InputFile = Bll::returnFormatFile(InputFile);
	OutputFile = Bll::returnFormatFile(OutputFile);
	if (Bll::isFileExis(InputFile) == false)
	{
		std::cout << "Error E006: " << InputFile << " could not be opened" << std::endl;
		return;
	}
	Bll::MorseToTex::TransferMorse(TextCode, InputFile, OutputFile);
	std::cout << "Input file: " << InputFile << std::endl;
	std::cout << "Output file: " << OutputFile << std::endl;
	Gui::Statistic::GeneralMenu(TextCode);
	if (Bll::isFileExis(OutputFile) == true)
	{
		std::cout << "Warning: " << OutputFile << " already exists.Do you wish to overwrite(y, n) ? : ";
		char c = _getch();
		std::cout << c;
		if (c == 'y')
		{
			Bll::SaveData(TextCode.Sentences, TextCode.Errors, OutputFile);
		}
		else if (c == 'n')
		{
			std::cout << std::endl << OutputFile << " already exists. Nothing has been done." << std::endl;
		}
		else
		{
			std::cout << std::endl << "Invalid Value.";
			return;
		}
	}
	else
	{
		Bll::SaveData(TextCode.Sentences, TextCode.Errors, OutputFile);
	}
	Dto::Statistic Statistic = TextCode;
	Statistic.InputLink = InputFile;
	Statistic.OutputLink = OutputFile;
	Bll::Statistic::SaveStatistic(Statistic);
}
//Function for Readme (for help)
void Gui::Readme::ReadmeFile()
{
	std::list<std::string> List;
	Bll::Readme::GetDataReadme(List);
	std::list <std::string> ::iterator Head;
	for (Head = List.begin(); Head != List.end(); Head++)
	{
		std::cout << *Head << std::endl;
	}
	Bll::Readme::SaveReadme(List);
}
//Function for Main Menu ( where other function is chose to run )
void Gui::MainMenu::Decentralization(int argc, char* argv[])
{
	/*
	* 1. Read for help
	* 2. Text to Morse
	* 3. Morse To Text
	* 4. Statistic for Text to Morse
	* 5. Statistic for Morse to Text
	* Notice: all Error can be found in Readme.txt or morse -h
	*/
	switch (Bll::MainMenu::returnOrderFunction(argc,argv))
	{
	case -1:
		std::cout << "Error E001: Unknown command. Type \"morse -h\" for help." << std::endl;
		break;
	case -2:
		std::cout << "Error E002: Unrecognized command. Type \"morse -h\" for help." << std::endl;
		break;
	case -4:
		std::cout << "Error E004: Missing arguments. Type \"morse -h\" for help." << std::endl;
		break;
	case -10:
		std::cout << "Error E010: File name could not be started with number." << std::endl;
		break;
	case -11:
		std::cout << "Error E011: File name just to have character, number, \".\" or \"_\"." << std::endl;
		break;
	case -12:
		std::cout << "Error E012: Input File and Output File is the same." << std::endl;
		break;
	case -6:
		std::cout << "Error E006: " << Bll::returnFormatFile(argv[1]) <<" could not be opened" << std::endl;
		break;
	case 1:
		Gui::Readme::ReadmeFile();
		break;
	case 2:
		Gui::TextToMor::TransferText(argv[1], argv[2]);
		break;
	case 3:
		Gui::MorseToText::TransferMorse(argv[1], argv[2]);
		break;
	case 4:
		Gui::Statistic::MenuTextToMorse(argv[1], argv[2]);
		break;
	case 5:
		Gui::Statistic::MenuMorseToText(argv[1], argv[2]);
		break;
	}
}