#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <sstream>

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

class Model
{
public:

	GLuint get() const
	{
		return VAO;
	}

	GLsizei count() const
	{
		return _mesh.size() / 8;
	}

	void loadMesh(std::string objPath, size_t iniAlloc=32000)
	{
		std::vector<GLfloat> v;
		std::vector<GLfloat> vt;
		std::vector<GLfloat> vn;
		v.reserve(iniAlloc);
		vt.reserve(iniAlloc);
		vn.reserve(iniAlloc);
		_mesh.reserve(iniAlloc*8);

		std::fstream file;
		file.open(objPath, std::ios::in);
		if (file.is_open())
		{

			std::string data;
			float fx, fy, fz;
			while (file >> data)
			{
				if (data == "v")
				{
					file >> fx >> fy >> fz;
					v.push_back(fx);
					v.push_back(fy);
					v.push_back(fz);
				}
				else if (data == "vt")
				{
					file >> fx >> fy;
					vt.push_back(fx);
					vt.push_back(fy);

				}
				else if (data == "vn")
				{
					file >> fx >> fy >> fz;
					vn.push_back(fx);
					vn.push_back(fy);
					vn.push_back(fz);
				}
				else if (data == "f")
				{
					std::getline(file, data);
					processFace(data, v, vt, vn);
				}
				else
				{
					getline(file, data);	//ignore line
				}
			}
			file.close();
		}
		sendToGpu();
	}

private:
	void processFace(std::string& line, std::vector<GLfloat>& v, std::vector<GLfloat>& vt, std::vector<GLfloat>& vn)
	{
		int index;
		std::stringstream s;
		s << line;
		std::vector<GLuint> temp;

		while (s)
		{
			s >> index;
			temp.push_back(index);
			s.ignore(1);
		}

		if (temp.size() == 9)
		{
			for (int i = 0; i < 9; i++)
			{
				if (i % 3 == 0)
					for (int j = 0; j < 3; j++)
						_mesh.push_back(v[(temp[i] - 1) * 3 + j]);
				else if (i % 3 == 1)
					for (int j = 0; j < 2; j++)
						_mesh.push_back(vt[(temp[i] - 1) * 2 + j]);
				else if (i % 3 == 2)
					for (int j = 0; j < 3; j++)
						_mesh.push_back(vn[(temp[i] - 1) * 3 + j]);
			}
		}
		else
		{
			for (int i = 0; i < 9; i++)
			{
				if (i % 3 == 0)
					for (int j = 0; j < 3; j++)
						_mesh.push_back(v[(temp[i] - 1) * 3 + j]);
				else if (i % 3 == 1)
					for (int j = 0; j < 2; j++)
						_mesh.push_back(vt[(temp[i] - 1) * 2 + j]);
				else if (i % 3 == 2)
					for (int j = 0; j < 3; j++)
						_mesh.push_back(vn[(temp[i] - 1) * 3 + j]);
			}
			for (int i = 3; i < 12; i++)
			{
				if (i % 3 == 0)
					for (int j = 0; j < 3; j++)
						_mesh.push_back(v[(temp[i] - 1) * 3 + j]);
				else if (i % 3 == 1)
					for (int j = 0; j < 2; j++)
						_mesh.push_back(vt[(temp[i] - 1) * 2 + j]);
				else if (i % 3 == 2)
					for (int j = 0; j < 3; j++)
						_mesh.push_back(vn[(temp[i] - 1) * 3 + j]);
			}
		}

	}

	void sendToGpu()
	{
		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);
		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, _mesh.size()*sizeof(GLfloat), _mesh.data(), GL_STATIC_DRAW);

		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3*sizeof(GLfloat)));
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(5*sizeof(GLfloat)));
		glEnableVertexAttribArray(2);
	}

	GLuint VBO, VAO;
	std::vector<GLfloat> _mesh;
};