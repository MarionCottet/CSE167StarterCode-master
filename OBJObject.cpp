#include "OBJObject.h"

OBJObject::OBJObject(const char *filepath) 
{
	toWorld = glm::mat4(1.0f);
	parse(filepath);
	this->angle = 0.0f;
	this->pointSize = 1.0f;
}

void OBJObject::parse(const char *filepath) 
{
	//TODO parse the OBJ file
	// Populate the face indices, vertices, and normals vectors with the OBJ Object data
	FILE* fp; //file pointer
	float x, y, z; //vertex coordinates
	float r, g, b; //vertex color
	int c1, c2; //charaters read from file

	fp = fopen(filepath, "rb");
	if (fp == NULL)
	{
		cerr << "Error loading file" << endl;
		exit(-1);
	}

	c1 = fgetc(fp);
	c2 = fgetc(fp);

	//Loop to read the file
	while (c1 != EOF)
	{
		if (c1 == 'v' && c2 == ' ') //vertex line
		{
			fscanf(fp, "%f %f %f %f %f %f", &x, &y, &z, &r, &g, &b);
			vertices.push_back(glm::vec3(x, y, z));
		}
		else if (c1 == 'v' && c2 == 'n') //vertex normal line
		{
			fscanf(fp, " %f %f %f", &x, &y, &z);
			normals.push_back(glm::normalize(glm::vec3(x, y, z)));
		}

		c1 = fgetc(fp);
		c2 = fgetc(fp);
	}

	fclose(fp);
}

void OBJObject::draw() 
{
	glMatrixMode(GL_MODELVIEW);

	// Push a save state onto the matrix stack, and multiply in the toWorld matrix
	glPushMatrix();
	glMultMatrixf(&(toWorld[0][0]));

	glBegin(GL_POINTS);
	// Loop through all the vertices of this OBJ Object and render them
	for (unsigned int i = 0; i < vertices.size(); ++i) 
	{
		glColor3f(normals[i].x*0.5f + 0.5f, normals[i].y*0.5f + 0.5f, normals[i].z*0.5f + 0.5f); //set the color
		glVertex3f(vertices[i].x, vertices[i].y, vertices[i].z); //draw
	}
	glEnd();

	// Pop the save state off the matrix stack
	// This will undo the multiply we did earlier
	glPopMatrix();
}

void OBJObject::update()
{
	spin(1.0f);
}

void OBJObject::spin(float deg)
{
	this->toWorld = this->toWorld * glm::rotate(glm::mat4(1.0f), deg / 180.0f * glm::pi<float>(), 
		glm::vec3(0.0f, 1.0f, 0.0f));
}

void OBJObject::changePointSize(float size)
{
	if (pointSize += size > 0) //Check is pointSize still positive
	{
		pointSize += size;
	}
	glPointSize(pointSize); //Apply new points size
}

void OBJObject::translate(float x, float y, float z) 
{
	this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(x, y, z)) * this->toWorld;
}

void OBJObject::scale(float size)
{
	this->toWorld = this->toWorld * glm::scale(glm::mat4(1.0f), glm::vec3(size));
}

void OBJObject::orbit(float deg, float direction)
{
	this->toWorld = glm::rotate(glm::mat4(1.0f), deg / 180.0f * glm::pi<float>(), 
		glm::vec3(0.0f, 0.0f, direction)) * this->toWorld;
}

void OBJObject::resetPosition()
{
	this->toWorld = glm::translate(glm::mat4(1.0f), 
		glm::vec3(-this->toWorld[3].x, -this->toWorld[3].y, -this->toWorld[3].z)) * this->toWorld;
}

void OBJObject::resetOrientationScale()
{
	//Save the translation coordinates
	float savedTX = this->toWorld[3].x;
	float savedTY = this->toWorld[3].y;
	float savedTZ = this->toWorld[3].z;

	//Set toWorld to an Identity Matrix
	this->toWorld = glm::mat4(1.0f);
	//Reapply the previously saved translation
	this->toWorld = glm::translate(glm::mat4(1.0f), glm::vec3(savedTX, savedTY, savedTZ)) * this->toWorld;
}