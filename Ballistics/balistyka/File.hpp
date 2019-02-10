//
//  File.hpp
//  balistyka
//
//  Created by Matek on 10.01.2018.
//  Copyright © 2018 Matek. All rights reserved.
//

#ifndef File_hpp
#define File_hpp

#include <stdio.h>
#include <iostream>
#include <sstream>

class File{
public:
    std::ostringstream oss;
    void saveToFile(std::string rows);
    std::string removeDots(std::string rows);
};

#endif /* File_hpp */
