#include <iostream>
#include <string>
#include <fstream>

std::string makeSarcastic(std::string text) {
    std::string newText;
    int capUpLower;
    for(int i = 0; i < text.size(); i++) {
        int Ichar = text[i]-0;
        if ((Ichar >= 'a' && Ichar <= 'z') || (Ichar >= 'A' && Ichar <= 'Z')) {
            newText.push_back((capUpLower%2==1) ? tolower(text[i]):toupper(text[i]));
            capUpLower++;
        }else {
            if (('.' || '?' || '!')== Ichar) {
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
            the_file.close();
        }
    }
    // the_file is closed implicitly here
    return 0;
}