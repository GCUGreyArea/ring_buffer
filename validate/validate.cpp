#include <iostream>
#include <fstream>
#include <string>


int main(int argc, char ** argv) {
    if(argc ==1) {
        std::cerr << "please supply a valid file name" << std::endl;
        return 1;
    }

    std::ifstream file(argv[1]);

    std::string str;
    std::string tmp = "string: string:%d, slot %x"; 
    int invalid = 0;
    int entries = 0;
    if(file.is_open()) {
        while(file.good()) {
            std::getline(file,str);
            int stridx;
            unsigned int addr;

            int ret = sscanf(str.c_str(),tmp.c_str(),&stridx,&addr); 

            if( ret != 2) {
                printf("Invalid entry\n");
                invalid++;
            }
            else {
                entries++;
            }
        }

        printf("valid entries: %d\n",entries);
        printf("invalid entries: %d\n", invalid);

        return 0;
    }

    return 1;
}