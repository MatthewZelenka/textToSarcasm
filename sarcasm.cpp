#include <iostream>
#include <string>

int cTi(char i) {return (int)i;}

int main() {
    std::string text;
    std::string newText;
    int capUpLower;
    std::cout << "Enter text: ";
    std::getline(std::cin, text);
    for(int i = 0; i < text.size(); i++) {
        int Ichar = text[i]-0;
        if ((Ichar >= cTi('a') && Ichar <= cTi('z')) || (Ichar >= cTi('A') && Ichar <= cTi('Z'))) {
            newText.push_back((capUpLower%2==1) ? tolower(text[i]):toupper(text[i]));
            capUpLower++;
        }else {
            if (cTi('.') == Ichar) {
                capUpLower = 0;
            }
            newText.push_back(text[i]);
        }
    }
    std::cout << "Sarcastic text:\n" << newText;
    return 0;
}