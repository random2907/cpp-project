#include <iostream>
#include <string>
#include <fstream>
#include <unistd.h>
#include <thread>


class Frame {
        public:
                void clear() { std::cout << "\e[2J\e[H"; }
};

class Fill{
        public:
                Fill(std::string color, char c, int width){
                        for (int i=0; i<width; i++){
                                std::cout << color+c;
                        }
                }
};

class Texture{
        public:
                std::string s;
                std::ifstream file;
                Texture(std::string filename) : file(filename){
                }
                std::string nextline(){
                        if (std::getline(file, s)) {
                                return s;
                        } else {
                                file.clear();
                                file.seekg(0);
                                return nextline();
                        }
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
                while (1){
                        int count_space[10]={0};
                        int count_no_space[10]={0};
                        int i=0;
                        int j=0;
                        std::string next = t[test].nextline();
                        if (next.empty()){
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
                                        Fill(bold+color[x],' ',count_space[j]);
                                }
                                if (count_space[j]!=0){
                                        Fill(bold+color[x],'*',count_no_space[j]);
                                }
                        }
                        std::cout << reset << std::endl;
                }
                test==0? test=1 : test=0;
                f.clear();
                sleep(1);
        }
        return 0;
}


