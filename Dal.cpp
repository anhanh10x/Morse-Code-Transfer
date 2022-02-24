#include"Dal.h"

//****************************Data Layer**********************************

//Function for Dal namespace (can be accessed by all classes)
bool Dal::isFileExis(std::string InputFile)
{
	std::ifstream f;
	f.open(InputFile.c_str(), std::ios::in);
	if (f.is_open() == false)
		return false;
	return true;
}
void Dal::GetData(std::list<std::string>& List, std::string FileName)
{
	std::ifstream f;
	char c;
    std::string temp="";
	f.open(FileName.c_str(), std::ios::in | std::ios::binary); 
	while (true)
    {
        f.read(&c,sizeof(c));
        if(f.eof())
        {
            List.push_back(temp);
            break;
        }
        if(c=='\n')  
        {
			temp.pop_back();
            List.push_back(temp);
			temp = "";
			continue;
        }
        temp.push_back(c);
    }
	f.close();
}
void Dal::SaveData(std::list<std::string>List,std::list<std::string>Error, std::string FileName)
{
	std::ofstream f;
	f.open(FileName.c_str(), std::ios::out);
	std::list <std::string> ::iterator Head;
	for (Head = List.begin(); Head != List.end(); Head++)
	{
		f << *Head << std::endl;
	}
	for (Head = Error.begin(); Head != Error.end(); Head++)
	{
		f << *Head << std::endl;
	}
	f.close();
}

//Function for Text to Morse code
void Dal::TextToMor::MorseHashTable(std::string MorseHash[])
{
	MorseHash[43] = ".-.-.";
	MorseHash[97] = ".-";
	MorseHash[98] = "-...";
	MorseHash[99] = "-.-.";
	MorseHash[100] = "-..";
	MorseHash[101] = ".";
	MorseHash[102] = "..-.";
	MorseHash[103] = "--.";
	MorseHash[104] = "....";
	MorseHash[105] = "..";
	MorseHash[106] = ".---";
	MorseHash[107] = "-.-";
	MorseHash[108] = ".-..";
	MorseHash[109] = "--";
	MorseHash[110] = "-.";
	MorseHash[111] = "---";
	MorseHash[112] = ".--.";
	MorseHash[113] = "--.-";
	MorseHash[114] = ".-.";
	MorseHash[115] = "...";
	MorseHash[116] = "-";
	MorseHash[117] = "..-";
	MorseHash[118] = "...-";
	MorseHash[119] = ".--";
	MorseHash[120] = "-..-";
	MorseHash[121] = "-.--";
	MorseHash[122] = "--..";
	MorseHash[48] = "-----";
	MorseHash[49] = ".----";
	MorseHash[50] = "..---";
	MorseHash[51] = "...--";
	MorseHash[52] = "....-";
	MorseHash[53] = ".....";
	MorseHash[54] = "-....";
	MorseHash[55] = "--...";
	MorseHash[56] = "---..";
	MorseHash[57] = "----.";
	MorseHash[46] = ".-.-.-";
	MorseHash[44] = "--..--";
	MorseHash[58] = "---...";
	MorseHash[63] = "..--..";
	MorseHash[39] = ".----.";
	MorseHash[45] = "-....-";
	MorseHash[47] = "-..-.";
	MorseHash[40] = "-.--.";
	MorseHash[41] = "-.--.-";
	MorseHash[34] = ".-..-.";
	MorseHash[61] = "-...-";
	MorseHash[64] = ".--.-.";
}

//Function for Morse code to Text
void Dal::MorToText::TextHashTable(std::string TextHash[])
{
	TextHash[5] = "a";
	TextHash[16] = "b";
	TextHash[20] = "c";
	TextHash[8] = "d";
	TextHash[1] = "e";
	TextHash[19] = "f";
	TextHash[10] = "g";
	TextHash[15] = "h";
	TextHash[3] = "i";
	TextHash[29] = "j";
	TextHash[12] = "k";
	TextHash[17] = "l";
	TextHash[6] = "m";
	TextHash[4] = "n";
	TextHash[14] = "o";
	TextHash[21] = "p";
	TextHash[26] = "q";
	TextHash[9] = "r";
	TextHash[7] = "s";
	TextHash[2] = "t";
	TextHash[11] = "u";
	TextHash[23] = "v";
	TextHash[13] = "w";
	TextHash[24] = "x";
	TextHash[28] = "y";
	TextHash[18] = "z";
	TextHash[62] = "0";
	TextHash[61] = "1";
	TextHash[59] = "2";
	TextHash[55] = "3";
	TextHash[47] = "4";
	TextHash[31] = "5";
	TextHash[32] = "6";
	TextHash[34] = "7";
	TextHash[38] = "8";
	TextHash[46] = "9";
	TextHash[105] = ".";
	TextHash[114] = ",";
	TextHash[70] = ":";
	TextHash[75] = "?";
	TextHash[93] = "'";
	TextHash[96] = "-";
	TextHash[40] = "/";
	TextHash[44] = "(";
	TextHash[108] = ")";
	TextHash[81] = "\"";
	TextHash[48] = "=";
	TextHash[85] = "@";
	TextHash[41] = "+";
}

//Function for Statistic Menu
void Dal::Statistic::SaveStatistic(Dto::Statistic Statistic)
{
	std::ofstream f;
	std::string OutputFile = Statistic.InputFile + "_" + Statistic.OutputFile + "_" + Statistic.CompletedDate + "_" + Statistic.CompletedTime + ".log";
	f.open(OutputFile.c_str(), std::ios::out);
	f << "Input file: " << Statistic.InputLink << std::endl;
	f << "Output file: " << Statistic.OutputLink << std::endl;
	f << "Time complete: " << Statistic.CompletedTimeDate << std::endl;
	f << "Duration[seconds]: " << Statistic.Duration << std::endl;
	f << "Word count in input file: " << Statistic.TotalWord << std::endl;
	f << "Word converted: " << Statistic.SuccessedWord << std::endl;
	f << "Word with errors: " << Statistic.ErrorWord << std::endl;
	f << "Total number of characters: " << Statistic.TotalCharacter << std::endl;
	f << "Number of characters have been converted: " << Statistic.ConvertedCharacter << std::endl;
	f << "Number of characters are NOT converted: " << Statistic.ErrorCharacter << std::endl;
	f.close();
}
//Function for Readme (for help)
void Dal::Readme::GetReadme(std::list<std::string>& List)
{
	List.push_back("Format for a command: Morse* Input* Output* Command");
	List.push_back("Input: single input file name or path together (Exp D:\\Filename.txt)");
	List.push_back("Output: single output file name or path together (Exp D:\\Filename.txt)");
	List.push_back("Command: \"-t\" Text to Morse, \"-m\" Morse to Text, \"-c\" print a statistic menu");
	List.push_back("Notice: \"*\" is compulsory.");
	List.push_back("Error E001: Unknown command. Type \"morse -h\" for help.");
	List.push_back("Error E002: Unrecognized command. Type \"morse -h\" for help.");
	List.push_back("Error E003: Do not allow more than 4 arguments in the same command. Type \"morse -h\" for help.");
	List.push_back("Error E004: Missing arguments. Type \"morse -h\" for help.");
	List.push_back("Error E005: Changing order of appearance. Type \"morse -h\" for help.");
	List.push_back("Error E006: (File name) could not be opened.");
	List.push_back("Error E007: (File name) already exists. Nothing has been done.");
	List.push_back("Error E008: Unrecognized character (C) on line (D).");
	List.push_back("Error E009: Invalid Morse code (C) on line (D).");
	List.push_back("Error E010: File name could not be started with number.");
	List.push_back("Error E011: File name just to have character, number, \".\" or \"_\".");
	List.push_back("Error E012: Input File and Output File is the same.");
}
void Dal::Readme::SaveReadme(std::list<std::string>List)
{
	std::ofstream f;
	f.open("Readme.txt", std::ios::out);
	std::list <std::string> ::iterator Head;
	for (Head = List.begin(); Head != List.end(); Head++)
	{
		f << *Head << std::endl;
	}
}