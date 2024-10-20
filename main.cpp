#include <iostream>
#include <string>
#include <fstream>
#include <thread>


class Frame {
        public:
                void clear() {
                        std::cout << "\e[H\e[2J"; 
                }
};

class Fill{
        public:
                static std::string test(std::string color, char c, int width){
                        std::string buffer="";
                        for (int i=0; i<width; i++){
                                buffer+=color+c;
                        }
                        return buffer;
                }
};


class Texture {
        public:
                std::string s;
                std::ifstream file;

                Texture(std::string filename) : file(filename) {
                        if (!file.is_open()) {
                                std::cerr << "Error opening file: " << filename << std::endl;
                        }
                }

                std::string nextline() {
                        std::getline(file, s);
                        return s;
                }
                void reset() {
                        file.clear();
                        file.seekg(0);
                }
                bool eof(){
                        return file.eof();
                }
};

int main(){
        Frame f;
        Texture t[2]={Texture("test.txt"),Texture("test1.txt")};
        int x=0;
        std::string reset="\e[0m";
        std::string bold="\e[5m";
        std::string red_fg="\e[38;2;255;0;0m";
        std::string green_fg="\e[38;2;0;255;0m";
        std::string blue_fg="\e[38;2;0;0;255m";
        std::string color[]={red_fg,green_fg,blue_fg};
        int test=0;
        while (1){
                std::string Outputbuffer="";
                while (1){
                        int count_space[10]={0};
                        int count_no_space[10]={0};
                        int i=0;
                        int j=0;
                        std::string next = t[test].nextline();
                        if (t[test].eof()){
                                t[test].reset();
                                break;
                        }
                        int length = next.length();
                        for (int k = 0; k < length; ++k) {
                                if (next[k] == ' ') {
                                        int space_count = 0;
                                        while (k < length && next[k] == ' ') {
                                                space_count++;
                                                k++;
                                        }
                                        count_space[i] = space_count;
                                        i++;
                                        k--;
                                } else {
                                        int non_space_count = 0;
                                        while (k < length && next[k] != ' ') {
                                                non_space_count++;
                                                k++;
                                        }
                                        count_no_space[j] = non_space_count;
                                        j++;
                                        k--;
                                }
                        }
                        for (int j=0; j<10; j++){
                                if (count_space[j]!=0){
                                        Outputbuffer+=Fill::test(bold+color[x],'\\',count_space[j]);
                                }
                                if (count_space[j]!=0){
                                        Outputbuffer+=Fill::test(bold+color[x],'-',count_no_space[j]);
                                }
                        }
                        Outputbuffer+=reset+"\n";
                        std::cout << reset << std::endl;
                }
                std::cout << Outputbuffer;
                test = (test == 0) ? 1 : 0;
                std::this_thread::sleep_for(std::chrono::milliseconds(100));
                f.clear();
        }
        return 0;
}


