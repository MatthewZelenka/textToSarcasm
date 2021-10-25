#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>

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

int main(int argc, char *argv[]) {
    if (argc > 1 && (argv[1] == (std::string)"--help")) {// argc should be 2 for correct execution
        std::cout<<"Usage: "<< argv[0] <<" <filename/filepath>\nThis will create a new file in sarcasm or leave arguments empty to put in text directly\n";
    } else if (argc == 1) {
        std::string text;
        std::cout << "Enter text: ";
        std::getline(std::cin, text);
        std::cout << "Sarcastic text:\n" << makeSarcastic(text)<<"\n";
    } else if (argc == 2){
        // We assume argv[1] is a filename to open
        std::ifstream the_file (argv[1]);
        // Always check to see if file opening succeeded
        if(!the_file.is_open()){
            std::cout<<"Could not open file use --help for help using the program\n";
        } else {
            std::cout<<"Could open file\n";
            std::string path = argv[1];
            std::string filename = std::filesystem::path(path).filename();
            std::string filepath = std::filesystem::path(path).remove_filename();
            std::string content((std::istreambuf_iterator<char>(the_file)),(std::istreambuf_iterator<char>()));
            the_file.close();
            // Makes file to store sarcastic text
            std::ofstream MyFile((std::string)(filepath+"sarcasm"+filename));

            // Write to the file
            MyFile << makeSarcastic(content);

            // Close the file
            MyFile.close();
        }
    }
    // the_file is closed implicitly here
    return 0;
}