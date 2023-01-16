#pragma once
#include <memory> 
#include <vector>
#include <iostream>
#include <fstream> 

#include<iomanip>
#include <string>
#include <cstring>
#include <cstdio> 
#include "../common/vertex.h"


class Objloader {
public:
    void loadcylinder();
    void loadball();
    void loadcube();
    void loadcone();
    void loadMultisidedprisms();
	void exportobj(std::vector<Vertex> vertices,std::vector<uint32_t> indices,std::string &filename);

    void loadobj(std::string& fillpath);
    void loadobjwithfullpath(std::string& fillpath);
    std::vector<std::string> split(const std::string& str, const std::string& delim); 
        
    std::vector<Vertex> _vertices;

	std::vector<uint32_t> _indices;
};





