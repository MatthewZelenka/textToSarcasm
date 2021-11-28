#include <iostream>
//#include <string>
#include <fstream>
#include <filesystem>

std::string makeSarcastic(std::string text) {
    std::string newText;
    int capUpLower;
    for(int i = 0; i < text.size(); i++) {
        int Ichar = text[i]-0;
        if ((Ichar >= 'a' && Ichar <= 'z') || (Ichar >= 'A' && Ichar <= 'Z') && Ichar != ' ') {
            newText.push_back((capUpLower%2==1) ? tolower(text[i]):toupper(text[i]));
            capUpLower++;
        }else {
            if (('.' == Ichar) || ('!' == Ichar) || ('?' == Ichar) || ('\n' == Ichar)) {
                capUpLower = 0;
            }
            newText.push_back(text[i]);
        }
    }
    return newText;
}

std::string removeSubString(std::string mainString, std::string subString) {
    // Search for the substring in string
    size_t pos = mainString.find(subString);
    if (pos != std::string::npos)
    {
        // If found then erase it from string
        mainString.erase(pos, subString.length());
    }
    return mainString;
}

void help() {
    std::cout<<"help function"<<std::endl;
}

int main(int argc, char *argv[]) { // add text input flag
    std::string filepathInput;
    std::string filepathOutput;
    std::string text;
    for (size_t argument = 1; argument < argc; argument++) {
        std::string param = argv[argument];
        if (param == "--help"){
            std::cout<<"help\n";
            break;
        } else if (param == "--input"){
            if (argc > argument+1) {
                std::cout<<"input with arg: "<<argv[argument+1]<<"\n";
                // Always check to see if file exists and not a directory
                if(!std::filesystem::is_directory(argv[argument+1]) && std::filesystem::exists(argv[argument+1])){
                    std::cout<<"Is file\n";
                    filepathInput = argv[argument+1];
                    argument++;
                } else {
                    std::cout<<"Input file does not exist\n";
                    break;
                }
            } else {
                std::cout<<"Not enought inputs for --input inclue file path: --input \"filepath\"" <<"\n";
            }
        } else if (param == "--output") {
            if (argc > argument+1) {
                std::cout<<"output with arg: "<<argv[argument+1]<<"\n";
                // Always check to see if file exists and not directory
                if(std::filesystem::is_directory(argv[argument+1]) || std::filesystem::exists(argv[argument+1])){
                    std::cout<<"Is directory or file\n";
                    filepathOutput = argv[argument+1];
                    argument++;
                } else {
                    std::cout<<"Output directory or file does not exist\n";
                    break;
                }
            } else {
                std::cout<<"Not enought inputs for --output inclue file path: --output \"filepath\"" <<"\n";
            }
        } else {
            std::cout<<argv[argument]<<" is not found" <<std::endl;
            break;
        }
    }
    if (filepathInput.empty()) {
        std::cout << "Enter text: ";
        std::getline(std::cin, text);
    } else {
        std::ifstream inputTextFile (filepathInput);
        text.assign( (std::istreambuf_iterator<char>(inputTextFile) ),
                (std::istreambuf_iterator<char>()    ) );
        inputTextFile.close();
    }
    if (filepathOutput.empty()) {
        std::cout << "Sarcastic text: \n"<<makeSarcastic(text)<<std::endl;
    } else {
        std::string newFileName;
        if(std::filesystem::is_directory(filepathOutput)) {
            newFileName = filepathOutput+"sarcasm"+".txt";
        } else {
            newFileName = filepathOutput;
        }
        std::ofstream MyFile(newFileName); //(std::string)(filepath+"sarcasm"+filename)
        // Write to the file
        MyFile << makeSarcastic(text);
        // Close the file
        MyFile.close();
    }
    // if (argc > 1 && (argv[1] == (std::string)"--help")) {// argc should be 2 for correct execution
    //     std::cout<<"Usage: "<< argv[0] <<" <filename/filepath>\nThis will create a new file in sarcasm or leave arguments empty to put in text directly\n";
    // } else if (argc == 1) {
    //     std::string text;
    //     std::cout << "Enter text: ";
    //     std::getline(std::cin, text);
    //     std::cout << "Sarcastic text:\n" << makeSarcastic(text)<<"\n";
    // } else if (argc == 2){
    //     // We assume argv[1] is a filename to open
    //     std::ifstream the_file (argv[1]);
    //     // Always check to see if file opening succeeded
    //     if(!the_file.is_open()){
    //         std::cout<<"Could not open file use --help for help using the program\n";
    //     } else {
    //         std::cout<<"Could open file\n";
    //         std::string path = argv[1];
    //         int found = path.find_last_of("/\\");
    //         std::string filename = path.substr(found+1);
    //         std::string filepath = (found!=-1) ? path.substr(0,found+1):"";
    //         std::string content((std::istreambuf_iterator<char>(the_file)),(std::istreambuf_iterator<char>()));
    //         the_file.close();
    //         // Makes file to store sarcastic text
    //         std::ofstream MyFile((std::string)(filepath+"sarcasm"+filename));

    //         // Write to the file
    //         MyFile << makeSarcastic(content);

    //         // Close the file
    //         MyFile.close();
    //     }
    // }
    // the_file is closed implicitly here
    return 0;
}