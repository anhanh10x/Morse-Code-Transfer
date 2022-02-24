#define _CRT_SECURE_NO_WARNINGS
#include"Bll.h"
#include<ctime>
#include<cmath>
//*******************************Business Logic Layer*************************
//Function of Bll namespace (can be accessed by all classes)
bool Bll::isExistHashValue(std::string MorseHash[],int HashCode)
{
    if(HashCode<0)
        return false;
    if (MorseHash[HashCode] == "")
        return false;
    return true;
}
bool Bll::isMorseCode(std::string Text)
{
    for (int i = 0; i < Text.length(); i++)
    {
        if (Text[i] != ' ' && Text[i] != '/' && Text[i] != '-' && Text[i] != '.')
            return false;
    }
    return true;
}
std::string Bll::ToString(int Value)
{
    std::string Temp = std::to_string(Value);
    if (Value < 10)
        Temp = "0" + Temp;
    return Temp;
}
std::string Bll::DeleteExtraBlank(std::string Text)
{
    std::string Temp = "";
    while (true)
    {
        int Index = Text.find("  ");
        if (Index ==-1)
        {
            break;
        }
        Text = Text.substr(0, Index) + " " + Text.substr(Index + 2);
    }
    if (Text[0] == ' ')
        Text = Text.substr(1);
    if (Text[Text.length() - 1] == ' ')
        Text.pop_back();
    return Text;
}
std::string Bll::FixForm(std::string Text)
{
    int Length = Text.length();
    for (int i = 0; i < Length; i++)
    {
        if (Text[i] == '/')
        {
            Text = Text.substr(0, i) + " " + Text.substr(i);
            Text = Text.substr(0, i + 2) + " " + Text.substr(i + 2);
            i++;
        }
    }
    return Text;
}
std::string Bll::returnTime()
{
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    return ToString(ptr->tm_hour) + ToString(ptr->tm_min) + ToString(ptr->tm_sec);
}
std::string Bll::returnDate()
{
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    return ToString(ptr->tm_year + 1900) + ToString(ptr->tm_mon+1) + ToString(ptr->tm_mday);
}
std::string Bll::returnMonthString(int Month)
{
    switch(Month)
    {
    case 1:
        return "Jan";
    case 2:
        return "Feb";
    case 3:
        return "Mar";
    case 4:
        return "Apr";
    case 5:
        return "May";
    case 6:
        return "Jun";
    case 7:
        return "Jul";
    case 8:
        return "Agu";
    case 9:
        return "Sep";
    case 10:
        return "Oct";
    case 11:
        return "Nov";
    case 12:
        return "Dec";
    }
    return "";
}
std::string Bll::returnTimeDate()
{
    struct tm* ptr;
    time_t t;
    t = time(NULL);
    ptr = localtime(&t);
    return ToString(ptr->tm_year + 1900) + "-" + returnMonthString(ptr->tm_mon + 1) + "-" + ToString(ptr->tm_mday) + " " + ToString(ptr->tm_hour) + ":" + ToString(ptr->tm_min) + ":" + ToString(ptr->tm_sec);
}
std::string Bll::returnLowerCase(std::string Text)
{
    std::string Temp="";
    for (int i = 0; i < Text.length(); i++)
    {
        if (Text[i] <= 90 && Text[i] >= 65)
        {
            Temp.push_back((char)((int)Text[i] + 32));
            continue;
        }
        Temp.push_back(Text[i]);
    }
    return Temp;
}
void Bll::SaveData(std::list<std::string>List, std::list<std::string>Error, std::string OutputFile)
{
    Dal::SaveData(List, Error, OutputFile);
}
bool Bll::isFileExis(std::string FileName)
{
    FileName = Bll::returnFormatFile(FileName);
    if (Dal::isFileExis(FileName) == false)
    {
        return false;//Cannot open Input file
    }
    return true;
}
std::string Bll::returnFormatFile(std::string FileName)
{
    if (FileName.find(".") == -1)
    {
        return FileName + ".txt";
    }
    return FileName;
}
//Function for Text to Morse code
std::string Bll::TextToMor::returnTextError(char C, int Line)
{
    std::string Temp = "";
    Temp.append("Unrecognized character ");
    Temp.push_back(C);
    Temp.append(" on line ");
    Temp.append(ToString(Line));
    Temp.append(".");
    return Temp;
}


void Bll::TextToMor::TransferText(Dto::TextAndMor& MorseCode,std::string InputFile,std::string OutputFile)
{
    clock_t TimeStart, TimeEnd;
    TimeStart = clock();
    bool isInnerWord = false;
    int Line=0;
    std::string MorseHash[145]={};
    Dal::TextToMor::MorseHashTable(MorseHash);
    Dal::GetData(MorseCode.Sentences, InputFile);
	std::list <std::string> ::iterator Head;
    std::string MorseString="";
    std::string CorrectTextForm = "";
	for (Head = MorseCode.Sentences.begin(); Head != MorseCode.Sentences.end(); Head++)
	{
        Line++;
        isInnerWord = false;
        if ((*Head) == "")
            continue;
        CorrectTextForm = Bll::DeleteExtraBlank(*Head);
        CorrectTextForm = Bll::returnLowerCase(CorrectTextForm);
        for (int i = 0; i < CorrectTextForm.length(); i++)
        {
            if (CorrectTextForm[i] == ' ')
            {
                MorseString.push_back('/');
                MorseCode.TotalWord++;
                isInnerWord = false;
            }
            else
            {
                if (isExistHashValue(MorseHash,(int)CorrectTextForm[i]))
                {
                    MorseString.append(MorseHash[(int)CorrectTextForm[i]]);
                    MorseCode.ConvertedCharacter++;
                }
                else
                {
                    MorseCode.Errors.push_back(returnTextError(CorrectTextForm[i], Line));
                    MorseString.append("#");
                    MorseCode.ErrorCharacter++;
                    if (isInnerWord == false)
                        MorseCode.ErrorWord++;
                    isInnerWord = true;
                }
            }
            MorseString.push_back(' ');
        }
        MorseString.pop_back();
        MorseCode.Morses.push_back(MorseString);
        MorseString = "";
        MorseCode.TotalWord++;
	}
    TimeEnd = clock();
    MorseCode.Duration = (float)(TimeEnd*10 - TimeStart) / CLOCKS_PER_SEC;
    MorseCode.CompletedTime = Bll::returnTime();
    MorseCode.CompletedDate = Bll::returnDate();
    MorseCode.CompletedTimeDate = Bll::returnTimeDate();
    MorseCode.SuccessedWord = MorseCode.TotalWord - MorseCode.ErrorWord;
    MorseCode.TotalCharacter = MorseCode.ConvertedCharacter + MorseCode.ErrorCharacter;
}

//Function for Morse code to Text
int Bll::MorseToTex::CreateHashCode(std::string Text)
{
    int Hash = 0;
    for (int i = 0; i < Text.length(); i++)
    {
        if (Text[i] == '.')
            Hash += (int)pow(2, i);
        else if (Text[i] == '-')
            Hash += (int)pow(2, i + 1);
        else
            return 0;
    }
    return Hash;
}
std::string Bll::MorseToTex::returnMorseError(std::string Morse, int Line)
{
    std::string Temp = ""; 
    Temp.append("Invalid Morse code ");
    Temp.append(Morse);
    Temp.append(" on line ");
    Temp.append(ToString(Line));
    return Temp;
}
void Bll::MorseToTex::TransferMorse(Dto::TextAndMor& TextCode, std::string InputFile, std::string OutputFile)
{
    clock_t TimeStart, TimeEnd;
    TimeStart = clock();
    bool isInnerWord = false;
    int HashValue = 0;
    int Line = 0;
    int Begin = 0;
    std::string TextString = "";
    std::string Sub = "";
    std::string CorrectMorseForm = "";
    std::string TextHash[116] = {};
    Dal::MorToText::TextHashTable(TextHash);
    Dal::GetData(TextCode.Morses, InputFile);
    std::list <std::string> ::iterator Head;
    for (Head = TextCode.Morses.begin(); Head != TextCode.Morses.end(); Head++)
    {
        Line++;
        isInnerWord = false;
        if ((*Head) == "")
            continue;
        CorrectMorseForm = Bll::DeleteExtraBlank(Bll::FixForm(*Head));
        for (int i = 0; i <= CorrectMorseForm.length(); i++)
        {
            if (CorrectMorseForm[i] == '/' )
            {
                TextString.push_back(' ');
                i++;
                Begin = i + 1;
                TextCode.TotalWord++;
                isInnerWord = false;
                continue;
            }
            else
            {
                if (CorrectMorseForm[i] == ' ' || i==CorrectMorseForm.length())
                {
                    Sub = CorrectMorseForm.substr(Begin, i - Begin);
                    HashValue = CreateHashCode(Sub);
                    if (HashValue <= 114)
                    {
                        if (isExistHashValue(TextHash, HashValue))
                        {
                            TextString.append(TextHash[HashValue]);
                            TextCode.ConvertedCharacter++;
                            Begin = i + 1;
                            continue;
                        }
                    }
                    if (Sub.length() > 7 || Bll::isMorseCode(Sub)==false)
                    {
                        TextString.append("#");
                    }
                    else
                    {
                        TextString.append("*");
                    }
                    TextCode.Errors.push_back(returnMorseError(Sub, Line));
                    TextCode.ErrorCharacter++;
                    if (isInnerWord == false)
                        TextCode.ErrorWord++;
                    isInnerWord = true;
                    Begin = i + 1;
                }
            }
        }
        TextCode.Sentences.push_back(TextString);
        TextCode.TotalWord++;
        Begin = 0;
        Sub = "";
        TextString = "";
    }
    TimeEnd = clock();
    TextCode.Duration =(float)(TimeEnd*10 - TimeStart) / CLOCKS_PER_SEC;
    TextCode.CompletedTime = Bll::returnTime();
    TextCode.CompletedDate = Bll::returnDate();
    TextCode.CompletedTimeDate = Bll::returnTimeDate();
    TextCode.SuccessedWord = TextCode.TotalWord - TextCode.ErrorWord;
    TextCode.TotalCharacter = TextCode.ConvertedCharacter + TextCode.ErrorCharacter;
}

//Function for Statistic Menu
std::string Bll::Statistic::CutLink(std::string Text)
{
    for (int i = Text.length(); i >= 0; i--)
    {
        if (Text[i] == '\\')
            return Text.substr(i + 1);
    }
    return Text;
}
void Bll::Statistic::SaveStatistic(Dto::Statistic Statistic)
{
    Statistic.InputFile = CutLink(Statistic.InputLink);
    Statistic.OutputFile = CutLink(Statistic.OutputLink);
    Dal::Statistic::SaveStatistic(Statistic);
}

//Function for Readme (for help)
void Bll::Readme::GetDataReadme(std::list<std::string>& List)
{
    Dal::Readme::GetReadme(List);
}
void Bll::Readme::SaveReadme(std::list<std::string>List)
{
    Dal::Readme::SaveReadme(List);
}
//Function for Main Menu
bool Bll::MainMenu::isMorseInputFile(std::string InputFile)
{
    std::list<std::string> List;
    InputFile = Bll::returnFormatFile(InputFile);
    Dal::GetData(List, InputFile);
    std::list <std::string> ::iterator Head;
    for (Head = List.begin(); Head != List.end(); Head++)
    {
        if (isMorseCode(*Head) == false)
            return false;
    }
    return true;
}
int Bll::MainMenu::checkErrorFileName(std::string FileName)
{
    bool Check = false;
    if (FileName[0] >= '1' && FileName[0] <= '9')
        return 0;//File name could not be started with number
    if (FileName[0] == '-')
        return 1;//Missing Argument
    for (int i = 0; i < FileName.length(); i++)
    {
        Check = false;
        if (FileName[i] >= 'A' && FileName[i] <= 'z')
            Check = true;
        else if (FileName[i] >= '1' && FileName[i] <= '9')
            Check = true;
        else if (FileName[i] == '_')
            Check = true;
        else if (FileName[i] == '.')
            Check = true;
        else if (FileName[i] == '\\')
            Check = true;
        else if (FileName[i] == ':')
            Check = true;
        else {};
        if (Check == false)
            return 2;//File name just to have character, number, "." or "_" 
    }
    return 3;
}
int Bll::MainMenu::returnOrderFunction(int argc, char* argv[])
{
 //Notice: all Error id are presented in Readme.txt or morse -h

    if (argc > 4)
        return -2;//E002
    std::string Text[4];
    Text[0] = Text[1] = Text[2] = Text[3] = "";
    for (int i = 0; i < argc; i++)
    {
        Text[i].append(argv[i]);
    }
    if (argc == 1)
    {
        return -2;//E002
    }
    if (argc == 2)
    {
        if (Text[1] == "-h")
        {
            return 1;//Read for help
        }
        else
            return -1;//E001
    }
    if (Bll::MainMenu::checkErrorFileName(argv[1]) == 2)
        return -11;//E011
    else if (Bll::MainMenu::checkErrorFileName(argv[1]) == 1)
        return -4;//E004
    else {}
    if (Bll::MainMenu::checkErrorFileName(argv[2]) == 0)
        return -10;//E010
    else if (Bll::MainMenu::checkErrorFileName(argv[2]) == 1)
        return -4;//E004
    else if (Bll::MainMenu::checkErrorFileName(argv[2]) == 2)
        return -11;//E011
    else {}
    std::string Temp[2];
    Temp[0].append(argv[1]);
    Temp[1].append(argv[2]);
    if (Temp[1] == Temp[0])
        return -12;//E012
    if (argc == 3)
    {
        if (Bll::isFileExis(argv[1]) == false)
            return -6;//E006
        if (isMorseInputFile(argv[1]))
            return 5;//Statistic for Morse to Text 
        else
            return 4;//Statistic for Text to Morse
    }
    if (argc == 4)
    {
        if (Text[3] == "-t")
        {
            return 2;//Text to Morse
        }
        else if (Text[3] == "-m")
        {
            return 3;//Morse to Text
        }
        else if (Text[3] == "-c")
        {
            if (Bll::isFileExis(argv[1]) == false)
                return -6;//E006
            if (isMorseInputFile(argv[1]))
                return 5;//Statistic for Morse to Text 
            else
                return 4;//Statistic for Text to Morse
        }
        else
        {
            return -1; //E001
        }
    }
    return -1;//E001
}
