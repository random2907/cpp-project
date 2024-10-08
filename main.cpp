#include <iostream>
#include <unistd.h>

class Frame{
        public:
                void clear(){
                        std::cout << "\e[2J\e[H";
                }
};

class Fill{
        public:
                Fill(int height, int width){
                        for (int i=0; i<height; i++){
                                for (int i=0; i<width; i++){
                                        std::cout << "-";
                                }
                                std::cout << std::endl;
                        }
                }
};

int main(){
        Frame f;
        std::string s;
        s = "     _    ____   ____ ___ ___      _         _        _             _     _           \n \
   / \\  / ___| / ___|_ _|_ _|    / \\   _ __| |_     / \\   _ __ ___| |__ (_)_   _____ \n\
   / _ \\ \\___ \\| |    | | | |    / _ \\ | '__| __|   / _ \\ | '__/ __| '_ \\| \\ \\ / / _ \\ \n\
  / ___ \\ ___) | |___ | | | |   / ___ \\| |  | |_   / ___ \\| | | (__| | | | |\\ V /  __/ \n\
 /_/   \\_\\____/ \\____|___|___| /_/   \\_\\_|   \\__| /_/   \\_\\_|  \\___|_| |_|_| \\_/ \\___|";
        std::string bold="\e[5m";
        std::string red_fg="\e[38;2;255;0;0m";
        std::string green_fg="\e[38;2;0;255;0m";
        std::string blue_fg="\e[38;2;0;0;255m";
        std::string reset="\e[0m";
        std::string color[]={red_fg,green_fg,blue_fg};
        int x=0;
        while (1){
                Fill(4,5);
                std::cout << color[x];
                std::cout << bold;
                std::cout << s;
                std::cout << reset << std::endl;
                if (x!=2){
                        x++;
                }else{
                        x=0;
                }
                f.clear();
                sleep(1);
        }

        return 0;

}
                
        
