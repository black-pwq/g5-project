#pragma once
#include <memory> 
#include <vector>
#include <iostream>
#include <fstream> 
#include <string>
#include <cstring>
#include <cstdio> 
#include "../common/vertex.h"


class Objloader {
public:
	
    void loadobj(std::string& fillpath);

    std::vector<std::string> split(const std::string& str, const std::string& delim); 
        
    std::vector<Vertex> _vertices;

	std::vector<uint32_t> _indices;
};




