//
//  File.cpp
//  balistyka
//
//  Created by Matek on 10.01.2018.
//  Copyright © 2018 Matek. All rights reserved.
//

#include "File.hpp"
#include <iostream>
#include <fstream>

void File::saveToFile(std::string rows){
    std::fstream myfile;
    
    myfile.open("/Users/statekmatek/Desktop/myFile.txt",
                std::ios::in | std::ios::out | std::ios::trunc);
    
    myfile << rows;
    //(myfile.good()) ? std::cout << "ok" : std::cout << "nope";
    
    myfile.close();
}

std::string removeDots(std::string rows){
    for(int i=0; i<rows.length(); i++){
        if (rows[i] == '.') rows[i] = ',';
    }
    
    return rows;
}
