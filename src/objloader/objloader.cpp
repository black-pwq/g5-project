
#pragma once
#include "objloader.h"
void Objloader::loadcube(){
    
    _vertices.clear();
    _indices.clear();

    std::vector<glm::vec3> vert;
    std::vector<Vertex> verts;
    std::vector<uint32_t> inds;
    std::vector<int> ind = {1,2,4,3   ,3,4,6,5   ,5,6,8,7    ,7,8,2,1   ,2,8,6,4    ,7,1,3,5};
    vert.push_back(glm::vec3(-0.5,-0.5,0.5));
    vert.push_back(glm::vec3(0.5,-0.5,0.5));
    vert.push_back(glm::vec3(-0.5,0.5,0.5));
    vert.push_back(glm::vec3(0.5,0.5,0.5));
    vert.push_back(glm::vec3(-0.5,0.5,-0.5));
    vert.push_back(glm::vec3(0.5,0.5,-0.5));
    vert.push_back(glm::vec3(-0.5,-0.5,-0.5));
    vert.push_back(glm::vec3(0.5,-0.5,-0.5));
    
    for (int i = 0;i < 6;i++){

        glm::vec3 normal = glm::cross((vert.at(ind.at(4*i)-1)-vert.at(ind.at(4*i+1)-1)),  (vert.at(ind.at(4*i+1)-1)-vert.at(ind.at(4*i+2)-1)));
        inds.push_back(4*i);
        inds.push_back(4*i+2);
        inds.push_back(4*i+1);
        inds.push_back(4*i);
        inds.push_back(4*i+3);
        inds.push_back(4*i+2);
        for(int j = 0;j < 4;j++){
            Vertex temp;
            temp.SetPosition(vert.at(ind.at(4*i+j)-1));
            temp.SetNormal(normal);
            verts.push_back(temp);
            
        }

    }

    _vertices.swap(verts);
    _indices.swap(inds);

    
    
}
void Objloader::loadball(){
    _vertices.clear();
    _indices.clear();
    std::vector<Vertex> sphereVertices;
	std::vector<uint32_t> sphereIndices;
    float PI = 3.141592653589793;
	int Y_SEGMENTS = 50;
    int X_SEGMENTS = 50;
	for (int y=0;y<=Y_SEGMENTS;y++)
	{
		for (int x=0;x<=X_SEGMENTS;x++)
		{
            Vertex temp;
			float xSegment = (float)x / (float)X_SEGMENTS;
			float ySegment = (float)y / (float)Y_SEGMENTS;
			float xPos = std::cos(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			float yPos = std::cos(ySegment * PI);
			float zPos = std::sin(xSegment * 2.0f * PI) * std::sin(ySegment * PI);
			temp.SetPosition(glm::vec3(xPos,yPos,zPos));
            sphereVertices.push_back(temp);
		}
	}


	//生成球的Indices
	for (int i=0;i<Y_SEGMENTS;i++)
	{
		for (int j=0;j<X_SEGMENTS;j++)
		{

            glm::vec3 normal = glm::cross((sphereVertices.at(i * (X_SEGMENTS + 1) + j).position-sphereVertices.at((i + 1) * (X_SEGMENTS + 1) + j).position),(sphereVertices.at(i * (X_SEGMENTS + 1) + j).position-sphereVertices.at((i + 1) * (X_SEGMENTS + 1) + j+1).position));
            sphereVertices.at(i * (X_SEGMENTS + 1) + j).SetNormal(normal);
            sphereVertices.at((i + 1) * (X_SEGMENTS + 1) + j).SetNormal(normal);
            sphereVertices.at((i + 1) * (X_SEGMENTS + 1) + j+1).SetNormal(normal);
            sphereVertices.at(i* (X_SEGMENTS + 1) + j).SetNormal(normal);
            sphereVertices.at((i + 1) * (X_SEGMENTS + 1) + j + 1).SetNormal(normal);
            sphereVertices.at(i * (X_SEGMENTS + 1) + j + 1).SetNormal(normal);

			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j+1);
			sphereIndices.push_back(i* (X_SEGMENTS + 1) + j);
			sphereIndices.push_back((i + 1) * (X_SEGMENTS + 1) + j + 1);
			sphereIndices.push_back(i * (X_SEGMENTS + 1) + j + 1);
        
        }
	}
    _vertices.swap(sphereVertices);
    _indices.swap(sphereIndices);

}
void Objloader::loadcylinder(){

    _vertices.clear();
    _indices.clear();

    const int sectorCount = 36; 
    const float pierRadius = 2.0f;
    const float pierHeight = 5.0f;
    const float PI = 3.1415926f;
	float sectorStep = 2 * PI / sectorCount;
	float sectorAngle = 0.0f;
    std::vector<Vertex> unitVertices;
    std::cout <<" start build" << std::endl;

	{
        glm::vec3 position;
        glm::vec3 normal;
        Vertex tVertex;

        for (int i = 0; i <= sectorCount; ++i)
        {
            sectorAngle = i * sectorStep;
            position.x = pierRadius * cos(sectorAngle);
            position.y = 0.0f;
            position.z = pierRadius * sin(sectorAngle);

            normal.x = cos(sectorAngle);
            normal.y = 0.0f;
            normal.z = sin(sectorAngle);

            tVertex.position = position;
            tVertex.normal = normal;

            unitVertices.push_back(tVertex);
        }
    }
	
	// 获取上、下圆周点数组
	std::vector<Vertex> vctTop;
	std::vector<Vertex> vctBot;

	Vertex tVertex;
	for(int i = 0; i < unitVertices.size(); ++i)
	{
		tVertex.position = unitVertices[i].position;
		tVertex.position.y = pierHeight;
		tVertex.normal = unitVertices[i].normal;
		vctTop.push_back(tVertex);  

		tVertex.position.y = 0.0f;
		vctBot.push_back(tVertex);     
	}

	assert(vctTop.size() >= 2);
	assert(vctBot.size() >= 2);

	// 圆柱侧面
	for(int i = 0; i < vctTop.size() - 1; ++i)
	{
		// 左三角形
		_vertices.push_back(vctTop[i]);
		_vertices.push_back(vctBot[i]);
		_vertices.push_back(vctBot[i+1]);
		
		// 右三角形
		_vertices.push_back(vctTop[i]);
		_vertices.push_back(vctTop[i+1]);
		_vertices.push_back(vctBot[i+1]);
	}
	
	// 顶部圆形
	glm::vec3 position;
	for (int i = 0; i < vctTop.size() - 1; ++i)
	{
		glm::vec3 position(0.0f, pierHeight, 0.0f);
		glm::vec3 normal(0.0f, 1.0f, 0.0f);
		tVertex.position = position;
		tVertex.normal = normal;
		_vertices.push_back(tVertex);

		tVertex.position = vctTop[i].position;
		_vertices.push_back(tVertex);

		tVertex.position = vctTop[i+1].position;
		_vertices.push_back(tVertex);
	}

	// 底部圆形
	for (int i = 0; i < vctBot.size() - 1; ++i)
	{
		glm::vec3 position(0.0f, 0.0f, 0.0f);
		glm::vec3 normal(0.0f, -1.0f, 0.0f);
		tVertex.position = position;
		tVertex.normal = normal;
		_vertices.push_back(tVertex);

		tVertex.position = vctBot[i].position;
		_vertices.push_back(tVertex);

		tVertex.position = vctBot[i+1].position;
		_vertices.push_back(tVertex);
	}
    for(int i = 0;i < _vertices.size();i++){
        _indices.push_back(i);
    }
    std::cout <<_indices.size() << std::endl;

}



void Objloader::loadcone(){
    _vertices.clear();
    _indices.clear();
    const int sectorCount = 36; 
    const float pierRadius = 2.0f;
    const float pierHeight = 5.0f;
    const float PI = 3.1415926f;
	float sectorStep = 2 * PI / sectorCount;
	float sectorAngle = 0.0f;
    std::vector<Vertex> unitVertices;
    std::cout <<" start build" << std::endl;

	{
        glm::vec3 position;
        glm::vec3 normal;
        Vertex tVertex;

        for (int i = 0; i <= sectorCount; ++i)
        {
            sectorAngle = i * sectorStep;
            position.x = pierRadius * cos(sectorAngle);
            position.y = 0.0f;
            position.z = pierRadius * sin(sectorAngle);
            tVertex.position = position;
        
            unitVertices.push_back(tVertex);
        }

    }

}

void Objloader::loadMultisidedprisms(){
    _vertices.clear();
    _indices.clear();
}

void Objloader::exportobj(std::vector<Vertex> vertices,std::vector<uint32_t> indices,std::string &filename){
    std::cout<< "start export  " << std::endl;

    std::ofstream outfile("media/obj/exportobj/"+filename,std::ios::ate);
    if(outfile.is_open()){
        std::cout << "export file found" << std::endl;
        int isfour = 0;
        if(indices.size()*2 == vertices.size()*3){

            std::cout << "isfourv" << std::endl;
            
            std::vector<glm::vec3> vec;

            for(int i = 0;i < indices.size();i+=6){
                vec.push_back(glm::vec3((float)indices.at(i)+1,(float)indices.at(i)+1,(float)indices.at(i)+1));
                vec.push_back(glm::vec3((float)indices.at(i+1)+1,(float)indices.at(i+1)+1,(float)indices.at(i+1)+1));
                vec.push_back(glm::vec3((float)indices.at(i+4)+1,(float)indices.at(i+4)+1,(float)indices.at(i+4)+1));
                vec.push_back(glm::vec3((float)indices.at(i+5)+1,(float)indices.at(i+5)+1,(float)indices.at(i+5)+1));
            }
            
            for(int i = 0;i < vec.size();i++){
                // outfile << "v" + std::to_string(vertices.at(vec.at(i).x)) << std::endl;
                outfile << "v " + std::to_string(vertices.at(vec.at(i).x-1).position.x) +" " + std::to_string(vertices.at(vec.at(i).x-1).position.y)+" "+std::to_string(vertices.at(vec.at(i).x-1).position.z)<< std::endl;

            }

            for(int i = 0;i < vec.size();i++){
                // outfile << "v" + std::to_string(vertices.at(vec.at(i).x)) << std::endl;
                outfile << "vt " + std::to_string(vertices.at(vec.at(i).y-1).texCoord.x) +" " + std::to_string(vertices.at(vec.at(i).y-1).texCoord.y)<< std::endl;

            }

            for(int i = 0;i < vec.size();i++){
                // outfile << "v" + std::to_string(vertices.at(vec.at(i).x)) << std::endl;
                outfile << "vn " + std::to_string(vertices.at(vec.at(i).z-1).normal.x) +" " + std::to_string(vertices.at(vec.at(i).z-1).normal.y)+" "+std::to_string(vertices.at(vec.at(i).z-1).normal.z)<< std::endl;

            }
            for(int i = 0;i < vec.size();i+=4){
                // outfile << "v" + std::to_string(vertices.at(vec.at(i).x)) << std::endl;
                outfile << "f " + std::to_string((int)vec.at(i).x) +"/" + std::to_string((int)vec.at(i).y)+"/"+std::to_string((int)vec.at(i).z)+" "+std::to_string((int)vec.at(i+1).x) +"/" + std::to_string((int)vec.at(i+1).y)+"/"+std::to_string((int)vec.at(i+1).z) +" "+ std::to_string((int)vec.at(i+2).x) +"/" + std::to_string((int)vec.at(i+2).y)+"/"+std::to_string((int)vec.at(i+2).z)+" "+std::to_string((int)vec.at(i+3).x) +"/" + std::to_string((int)vec.at(i+3).y)+"/"+std::to_string((int)vec.at(i+3).z) +" "<< std::endl;

            }

        }
        else{
            std::cout << "isthreev" << std::endl;
            std::vector<int> v;
            std::vector<int> vt;
            std::vector<int> vn;
           
            std::vector<glm::vec3> vec;

            for(int i = 0;i < indices.size();i+=3){
                vec.push_back(glm::vec3((float)indices.at(i)+1,(float)indices.at(i)+1,(float)indices.at(i)+1));
                vec.push_back(glm::vec3((float)indices.at(i+1)+1,(float)indices.at(i+1)+1,(float)indices.at(i+1)+1));
                vec.push_back(glm::vec3((float)indices.at(i+2)+1,(float)indices.at(i+2)+1,(float)indices.at(i+2)+1));
            }
            
            for(int i = 0;i < vec.size();i++){
                // outfile << "v" + std::to_string(vertices.at(vec.at(i).x)) << std::endl;
                outfile << "v " + std::to_string(vertices.at(vec.at(i).x-1).position.x) +" " + std::to_string(vertices.at(vec.at(i).x-1).position.y)+" "+std::to_string(vertices.at(vec.at(i).x-1).position.z)<< std::endl;

            }

            for(int i = 0;i < vec.size();i++){
                // outfile << "v" + std::to_string(vertices.at(vec.at(i).x)) << std::endl;
                outfile << "vt " + std::to_string(vertices.at(vec.at(i).y-1).texCoord.x) +" " + std::to_string(vertices.at(vec.at(i).y-1).texCoord.y)<< std::endl;

            }

            for(int i = 0;i < vec.size();i++){
                // outfile << "v" + std::to_string(vertices.at(vec.at(i).x)) << std::endl;
                outfile << "vn " + std::to_string(vertices.at(vec.at(i).z-1).normal.x) +" " + std::to_string(vertices.at(vec.at(i).z-1).normal.y)+" "+std::to_string(vertices.at(vec.at(i).z-1).normal.z)<< std::endl;

            }
            for(int i = 0;i < vec.size();i+=3){
                // outfile << "v" + std::to_string(vertices.at(vec.at(i).x)) << std::endl;
                outfile << "f " + std::to_string((int)vec.at(i).x) +"/" + std::to_string((int)vec.at(i).y)+"/"+std::to_string((int)vec.at(i).z)+" "+std::to_string((int)vec.at(i+1).x) +"/" + std::to_string((int)vec.at(i+1).y)+"/"+std::to_string((int)vec.at(i+1).z) +" "+ std::to_string((int)vec.at(i+2).x) +"/" + std::to_string((int)vec.at(i+2).y)+"/"+std::to_string((int)vec.at(i+2).z)+" "<< std::endl;

            }

        }

        outfile.close();
    }
    std::cout <<  "fin export" << std::endl;

}

void Objloader::loadobj(std::string &fillpath)
{    
    _vertices.clear();
    _indices.clear();

    // std::cout << "try to load  " << std::endl;

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
    std::cout<< "fin load " << std::endl;
    return;
};


void Objloader::loadobjwithfullpath(std::string &fillpath)
{    
    _vertices.clear();
    _indices.clear();
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
        std::cout<< "fin load " << std::endl;


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



