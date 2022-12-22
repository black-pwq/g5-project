
#pragma once
#include "objloader.h"

void Objloader::loadobj(std::string &fillpath)
{    

    std::cout << "try to load  " << std::endl;

    std::fstream fin;

    fin.open("media/obj/"+fillpath, std::ios::in);

    if (!fin.is_open())
    {
        std::cout << "no obj files found !" << std::endl;
    };
    std::string buff;
    int vsum = 0;
    int vtsum = 0;
    int vnsum = 0;
    int truevsum = 0;
    std::vector<glm::vec3> pos;
    std::vector<glm::vec3> vn;
    std::vector<glm::vec2> vt;

    std::cout << "start load " << _vertices.size() << std::endl;

    while (getline(fin, buff))
    {

        std::vector<std::string> temp = split(buff, " ");
        // std::cout  << "  " <<temp.size() <<std::endl;

        if (temp.size() > 0)
        {
            if (temp.at(0) == "v")
            {
                pos.push_back(glm::vec3(std::stof(temp.at(1)), std::stof(temp.at(2)), std::stof(temp.at(3))));

                vsum++;
                // std::cout <<temp.size()<< " "<<buff << std::endl;
            }
            else if (temp.at(0) == "vn")
            {
                vn.push_back(glm::vec3(std::stof(temp.at(1)), std::stof(temp.at(2)), std::stof(temp.at(3))));

                vtsum++;
            }

            else if (temp.at(0) == "vt")
            {
                vt.push_back(glm::vec2(std::stof(temp.at(1)), std::stof(temp.at(2))));

                vnsum++;
            }

            else if (temp.at(0) == "f")
            {

                if (temp.size() == 5)
                {

                    for (int i = 0; i < 4; i++)
                    {
                        Vertex vertex;
                        std::vector<std::string> vvtvn = split(temp.at(i + 1), "/");

                        if (vvtvn.size() == 1)
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 3)
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SettexCoord(vt.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                                else if (j == 2)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetNormal(vn.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 2 && temp.at(i).at(vvtvn.at(0).size() + 1) == '/')
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }

                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetNormal(vn.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 2 && temp.at(i).at(vvtvn.at(0).size() + 1) != '/')
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }

                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SettexCoord(vt.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }

                        _vertices.push_back(vertex);
                        truevsum++;
                    }
                    _indices.push_back(truevsum - 4);
                    _indices.push_back(truevsum - 3);
                    _indices.push_back(truevsum - 2);
                    _indices.push_back(truevsum - 4);
                    _indices.push_back(truevsum - 2);
                    _indices.push_back(truevsum - 1);
                }

                else if (temp.size() == 4)
                {
                    for (int i = 0; i < temp.size() - 1; i++)
                    {
                        Vertex vertex;
                        std::vector<std::string> vvtvn = split(temp.at(i + 1), "/");
                        if (vvtvn.size() == 1)
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 3)
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SettexCoord(vt.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                                else if (j == 2)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetNormal(vn.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 2)
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }

                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetNormal(vn.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 2 && temp.at(i).at(vvtvn.at(0).size() + 1) != '/')
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }

                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SettexCoord(vt.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }

                        _vertices.push_back(vertex);

                        truevsum++;
                    }
                    _indices.push_back(truevsum - 3);
                    _indices.push_back(truevsum - 2);
                    _indices.push_back(truevsum - 1);
                }
            }
        }
    }
    // std::cout <<vsum<< " "<<vtsum << " "<< vnsum << " "<< std::endl;

    // for (int i = 0; i < _vertices.size(); i++) {
    //     std::cout << _vertices.at(i).position.x<< "  "<< _vertices.at(i).position.y<< "  "<< _vertices.at(i).position.z << std::endl;
    //     std::cout << _vertices.at(i).normal.x<< "  "<< _vertices.at(i).normal.y<< "  "<< _vertices.at(i).normal.z << std::endl;

    // }

    // for (int i = 0; i < _indices.size(); i++) {
    //     std::cout << _indices.at(i) << std::endl;
    // }
    fin.close();

    return;
};


void Objloader::loadobjwithfullpath(std::string &fillpath)
{    

    std::cout << "try to load  " << std::endl;

    std::fstream fin;

    fin.open(fillpath, std::ios::in);

    if (!fin.is_open())
    {
        std::cout << "no obj files found !" << std::endl;
    };
    std::string buff;
    int vsum = 0;
    int vtsum = 0;
    int vnsum = 0;
    int truevsum = 0;
    std::vector<glm::vec3> pos;
    std::vector<glm::vec3> vn;
    std::vector<glm::vec2> vt;

    std::cout << "start load " << _vertices.size() << std::endl;

    while (getline(fin, buff))
    {

        std::vector<std::string> temp = split(buff, " ");
        // std::cout  << "  " <<temp.size() <<std::endl;

        if (temp.size() > 0)
        {
            if (temp.at(0) == "v")
            {
                pos.push_back(glm::vec3(std::stof(temp.at(1)), std::stof(temp.at(2)), std::stof(temp.at(3))));

                vsum++;
                // std::cout <<temp.size()<< " "<<buff << std::endl;
            }
            else if (temp.at(0) == "vn")
            {
                vn.push_back(glm::vec3(std::stof(temp.at(1)), std::stof(temp.at(2)), std::stof(temp.at(3))));

                vtsum++;
            }

            else if (temp.at(0) == "vt")
            {
                vt.push_back(glm::vec2(std::stof(temp.at(1)), std::stof(temp.at(2))));

                vnsum++;
            }

            else if (temp.at(0) == "f")
            {

                if (temp.size() == 5)
                {

                    for (int i = 0; i < 4; i++)
                    {
                        Vertex vertex;
                        std::vector<std::string> vvtvn = split(temp.at(i + 1), "/");

                        if (vvtvn.size() == 1)
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 3)
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SettexCoord(vt.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                                else if (j == 2)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetNormal(vn.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 2 && temp.at(i).at(vvtvn.at(0).size() + 1) == '/')
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }

                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetNormal(vn.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 2 && temp.at(i).at(vvtvn.at(0).size() + 1) != '/')
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }

                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SettexCoord(vt.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }

                        _vertices.push_back(vertex);
                        truevsum++;
                    }
                    _indices.push_back(truevsum - 4);
                    _indices.push_back(truevsum - 3);
                    _indices.push_back(truevsum - 2);
                    _indices.push_back(truevsum - 4);
                    _indices.push_back(truevsum - 2);
                    _indices.push_back(truevsum - 1);
                }

                else if (temp.size() == 4)
                {
                    for (int i = 0; i < temp.size() - 1; i++)
                    {
                        Vertex vertex;
                        std::vector<std::string> vvtvn = split(temp.at(i + 1), "/");
                        if (vvtvn.size() == 1)
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 3)
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SettexCoord(vt.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                                else if (j == 2)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetNormal(vn.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 2)
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }

                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetNormal(vn.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }
                        else if (vvtvn.size() == 2 && temp.at(i).at(vvtvn.at(0).size() + 1) != '/')
                        {
                            for (int j = 0; j < vvtvn.size(); j++)
                            {

                                if (j == 0)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SetPosition(pos.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }

                                else if (j == 1)
                                {
                                    if (vvtvn.at(j).length() > 0)
                                    {
                                        vertex.SettexCoord(vt.at(std::stoi(vvtvn.at(j)) - 1));
                                    }
                                }
                            }
                        }

                        _vertices.push_back(vertex);

                        truevsum++;
                    }
                    _indices.push_back(truevsum - 3);
                    _indices.push_back(truevsum - 2);
                    _indices.push_back(truevsum - 1);
                }
            }
        }
    }
    // std::cout <<vsum<< " "<<vtsum << " "<< vnsum << " "<< std::endl;

    // for (int i = 0; i < _vertices.size(); i++) {
    //     std::cout << _vertices.at(i).position.x<< "  "<< _vertices.at(i).position.y<< "  "<< _vertices.at(i).position.z << std::endl;
    //     std::cout << _vertices.at(i).normal.x<< "  "<< _vertices.at(i).normal.y<< "  "<< _vertices.at(i).normal.z << std::endl;

    // }

    // for (int i = 0; i < _indices.size(); i++) {
    //     std::cout << _indices.at(i) << std::endl;
    // }
    fin.close();

    return;
};

std::vector<std::string> Objloader::split(const std::string &str, const std::string &delim)
{
    std::vector<std::string> res;
    if ("" == str)
        return res;
    // 先将要切割的字符串从string类型转换为char*类型
    char *strs = new char[str.length() + 1]; // 不要忘了
    strcpy(strs, str.c_str());

    char *d = new char[delim.length() + 1];
    strcpy(d, delim.c_str());

    char *p = strtok(strs, d);
    while (p)
    {
        std::string s = p; // 分割得到的字符串转换为string类型
        res.push_back(s);  // 存入结果数组
        p = strtok(NULL, d);
    }

    return res;
}

