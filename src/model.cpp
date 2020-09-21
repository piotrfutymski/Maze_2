#include "model.h"

Model::Model(std::string objPath)
{
	std::vector<glm::vec3> v;
	std::vector<glm::vec2> vt;
	std::vector<glm::vec3> vn;
	v.reserve(1024);
	vt.reserve(1024);
	vn.reserve(1024);
	_mesh.reserve(1024);

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
				v.emplace_back(fx, fy, fz);
			}
			else if (data == "vt")
			{
				file >> fx >> fy;
				vt.emplace_back(fx, fy);

			}
			else if (data == "vn")
			{
				file >> fx >> fy >> fz;
				vn.emplace_back(fx, fy, fz);
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

GLuint Model::get() const
{
	return VAO;
}

GLsizei Model::count() const
{
	return _mesh.size() / vertexAttrSize;
}


void Model::processFace(std::string& line, std::vector<glm::vec3>& v, std::vector<glm::vec2>& vt, std::vector<glm::vec3>& vn)
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
	glm::vec3 pos[4];
	glm::vec2 uv[4];
	glm::vec3 nm[4];

	int vCount = temp.size() / 3;
	for (int i = 0; i < vCount; i++)
		pos[i] = v[temp[i * 3] - 1];
	for (int i = 0; i < vCount; i++)
		uv[i] = v[temp[i * 3 + 1] - 1];
	for (int i = 0; i < vCount; i++)
		nm[i] = v[temp[i * 3 + 2] - 1];

	if (vCount == 3)
		addTriangle(0, 1, 2, pos, uv, nm);
	else if (vCount == 4) //(need to split into two triangles [0,1,2] [0,2,3])
	{
		addTriangle(0, 1, 2, pos, uv, nm);
		addTriangle(0, 2, 3, pos, uv, nm);
	}

}

void Model::addTriangle(int off1, int off2, int off3, const glm::vec3* pos, const glm::vec2* uv, const glm::vec3* nm)
{
	glm::vec3 tan, btan;

	glm::vec3 dpos1 = pos[off2] - pos[off1];
	glm::vec3 dpos2 = pos[off3] - pos[off1];
	glm::vec2 duv1 = uv[off2] - uv[off1];
	glm::vec2 duv2 = uv[off3] - uv[off1];

	float f = 1.0f / (duv1.x * duv2.y - duv2.x * duv1.y);

	tan = (dpos1 * duv2.y - dpos2 * duv1.y) * f;
	btan = (dpos2 * duv1.x - dpos1 * duv2.x) * f;

	tan = glm::normalize(tan);
	btan = glm::normalize(btan);

	int offs[3] = { off1,off2,off3 };
	for (auto off : offs)
	{
		_mesh.push_back(pos[off].x);
		_mesh.push_back(pos[off].y);
		_mesh.push_back(pos[off].z);
		_mesh.push_back(uv[off].x);
		_mesh.push_back(uv[off].y);
		_mesh.push_back(nm[off].x);
		_mesh.push_back(nm[off].y);
		_mesh.push_back(nm[off].z);
		_mesh.push_back(tan.x);
		_mesh.push_back(tan.y);
		_mesh.push_back(tan.z);
		_mesh.push_back(btan.x);
		_mesh.push_back(btan.y);
		_mesh.push_back(btan.z);
	}

}

void Model::sendToGpu()
{
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, _mesh.size() * sizeof(GLfloat), _mesh.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexAttrSize * sizeof(GLfloat), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, vertexAttrSize * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, vertexAttrSize * sizeof(GLfloat), (void*)(5 * sizeof(GLfloat)));
	glEnableVertexAttribArray(2);

	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, vertexAttrSize * sizeof(GLfloat), (void*)(8 * sizeof(GLfloat)));
	glEnableVertexAttribArray(3);

	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, vertexAttrSize * sizeof(GLfloat), (void*)(11 * sizeof(GLfloat)));
	glEnableVertexAttribArray(4);
}