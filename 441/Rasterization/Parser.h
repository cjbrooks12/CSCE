#ifndef PARSER_H
#define PARSER_H

#include <vector>
#include <fstream>
#include <sstream>
#include <iostream>
#include "Triangle.h"

class Parser {
public:
	static std::vector<Triangle> parseFile(std::string filename) {
		std::vector<Vertex*> points;
		std::vector<Triangle> faces;

		std::ifstream obj;
		obj.open(filename);
		if (obj.good()) {
			while (!obj.eof()) {
				std::string line;
				getline(obj, line);

				//line is empty
				if (line.size() == 0) continue;

				//line is a comment
				else if (line.at(0) == '#') continue;

				//line defines a vertex
				else if (line.at(0) == 'v') {
					float x, y, z;
					char v;
					std::stringstream ss(line);
					ss >> v >> x >> y >> z;
					points.push_back(new Vertex(x, y, z));
				}

				//line defines a face
				else if (line.at(0) == 'f') {
					int a, b, c;
					char f;
					std::stringstream ss(line);
					ss >> f >> a >> b >> c;

					//create the triangle face
					Triangle face;// = new Triangle();
					face.push_back(points[a - 1]);
					face.push_back(points[b - 1]);
					face.push_back(points[c - 1]);

					faces.push_back(face);
				}
			}
		}
		else {
			std::cout << filename << " does not exist\n";
		}
		
		obj.close();

		return faces;
	}
};

#endif