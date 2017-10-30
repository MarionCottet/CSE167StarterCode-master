#include "Window.h"

const char* window_title = "GLFW Starter Project";
Cube cube(5.0f);
OBJObject bunny("bunny.obj");
OBJObject dragon("dragon.obj");
OBJObject bear("bear.obj");

int Window::width;
int Window::height;
float* Window::pixels = new float[Window::width * Window::height * 3];

int objectNumber = 1;
bool rasterizerMode = false;

struct Color    // generic color class
{
	float r, g, b;  // red, green, blue
};

void Window::initialize_objects()
{
}

void Window::clean_up()
{
}

// Clear frame buffer
void Window::clearBuffer()
{
	Color clearColor = { 0.0, 0.0, 0.0 };   // clear color: black
	for (int i = 0; i<Window::width*Window::height; ++i)
	{
		pixels[i * 3] = clearColor.r;
		pixels[i * 3 + 1] = clearColor.g;
		pixels[i * 3 + 2] = clearColor.b;
	}
}

// Draw a point into the frame buffer
void Window::drawPoint(int x, int y, float r, float g, float b)
{
	int offset = y*Window::width * 3 + x * 3;
	Window::pixels[offset] = r;
	Window::pixels[offset + 1] = g;
	Window::pixels[offset + 2] = b;
}

void Window::rasterize()
{
	// Put your main rasterization loop here
	// It should go over the point model and call drawPoint for every point in it
	
	//Calculate camera matrix (C-1)
	glm::mat4 cameraMatrix = glm::lookAt(glm::vec3(0, 0, 20), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
	//Calculate Projection Matrix (P)
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(60.0f), 
		(float)Window::width / (float)Window::height, 1.0f, 1000.0f);
	//Create Image matrix (D)
	glm::mat4 imageMatrix = glm::mat4(glm::vec4(Window::width/2, 0, 0, 0), glm::vec4(0, Window::height/2, 0, 0), 
		glm::vec4(0, 0, 1.0/2.0, 0), glm::vec4(Window::width/2, Window::height/2, 1.0/2.0, 1));

	switch (objectNumber)
	{
		case 1 : //Bunny
			for (int i = 0; i < bunny.vertices.size(); i++)
			{
				//Calculate point vector with coordinates from vertices (p)
				glm::vec4 pointObject = glm::vec4(bunny.vertices[i].x, bunny.vertices[i].y, bunny.vertices[i].z, 1.0f);
			
				//Apply the formula : p' = D*P*C-1*M*p
				glm::vec4 newPointObject = imageMatrix * projectionMatrix * cameraMatrix * bunny.toWorld * pointObject;
				
				//Draw the new point after normalization (double loop to draw a square or pixels according to the pointSize)
				for (int j = 0 ; j <= bunny.pointSize ; j++) 
				{
					for (int k = 0 ; k <= bunny.pointSize ; k++)
					{
						//Check if the pixel is in the window and in the camera view
						if ((newPointObject[0] / newPointObject[3] + j > 0) 
							&& (newPointObject[0] / newPointObject[3] + j < Window::width)
							&& (newPointObject[1] / newPointObject[3] + k > 0)
							&& (newPointObject[1] / newPointObject[3] + k < Window::height)
							&& (newPointObject[2] / newPointObject[3] > 0)
							&& (newPointObject[2] / newPointObject[3] < 1))
						{
							//Draw the pixel
							Window::drawPoint(newPointObject[0] / newPointObject[3] + j,
								newPointObject[1] / newPointObject[3] + k,
								bunny.normals[i].x*0.5f + 0.5f,
								bunny.normals[i].y*0.5f + 0.5f,
								bunny.normals[i].z*0.5f + 0.5f);
						}
					}
				}
			}
			break;

		case 2 : //Dragon
			for (int i = 0; i < dragon.vertices.size(); i++)
			{
				//Calculate point vector with coordinates from vertices (p)
				glm::vec4 pointObject = glm::vec4(dragon.vertices[i].x, dragon.vertices[i].y, dragon.vertices[i].z, 1.0f);

				//Apply the formula : p' = D*P*C-1*M*p
				glm::vec4 newPointObject = imageMatrix * projectionMatrix * cameraMatrix * dragon.toWorld * pointObject;

				//Draw the new point after normalization (double loop to draw a square or pixels according to the pointSize)
				for (int j = 0; j <= dragon.pointSize; j++)
				{
					for (int k = 0; k <= dragon.pointSize; k++)
					{
						//Check if the pixel is in the window and in the camera view
						if ((newPointObject[0] / newPointObject[3] + j > 0)
							&& (newPointObject[0] / newPointObject[3] + j < Window::width)
							&& (newPointObject[1] / newPointObject[3] + k > 0)
							&& (newPointObject[1] / newPointObject[3] + k < Window::height)
							&& (newPointObject[2] / newPointObject[3] > 0)
							&& (newPointObject[2] / newPointObject[3] < 1))
						{
							//Draw the pixel
							Window::drawPoint(newPointObject[0] / newPointObject[3] + j,
								newPointObject[1] / newPointObject[3] + k,
								dragon.normals[i].x*0.5f + 0.5f,
								dragon.normals[i].y*0.5f + 0.5f,
								dragon.normals[i].z*0.5f + 0.5f);
						}
					}
				}
			}
			break;

		case 3 : //Bear
			for (int i = 0; i < bear.vertices.size(); i++)
			{
				//Calculate point vector with coordinates from vertices (p)
				glm::vec4 pointObject = glm::vec4(bear.vertices[i].x, bear.vertices[i].y, bear.vertices[i].z, 1.0f);

				//Apply the formula : p' = D*P*C-1*M*p
				glm::vec4 newPointObject = imageMatrix * projectionMatrix * cameraMatrix * bear.toWorld * pointObject;

				//Draw the new point after normalization (double loop to draw a square or pixels according to the pointSize)
				for (int j = 0; j <= bear.pointSize; j++)
				{
					for (int k = 0; k <= bear.pointSize; k++)
					{
						//Check if the pixel is in the window and in the camera view
						if ((newPointObject[0] / newPointObject[3] + j > 0)
							&& (newPointObject[0] / newPointObject[3] + j < Window::width)
							&& (newPointObject[1] / newPointObject[3] + k > 0)
							&& (newPointObject[1] / newPointObject[3] + k < Window::height)
							&& (newPointObject[2] / newPointObject[3] > 0)
							&& (newPointObject[2] / newPointObject[3] < 1))
						{
							//Draw the pixel
							Window::drawPoint(newPointObject[0] / newPointObject[3] + j,
								newPointObject[1] / newPointObject[3] + k,
								bear.normals[i].x*0.5f + 0.5f,
								bear.normals[i].y*0.5f + 0.5f,
								bear.normals[i].z*0.5f + 0.5f);
						}
					}
				}
			}
			break;

		default:
			break;
	}
	
}

GLFWwindow* Window::create_window(int width, int height)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return NULL;
	}

	// 4x antialiasing
	glfwWindowHint(GLFW_SAMPLES, 4);

	// Create the GLFW window
	GLFWwindow* window = glfwCreateWindow(width, height, window_title, NULL, NULL);

	// Check if the window could not be created
	if (!window)
	{
		fprintf(stderr, "Failed to open GLFW window.\n");
		glfwTerminate();
		return NULL;
	}

	// Make the context of the window
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Call the resize callback to make sure things get drawn immediately
	Window::resize_callback(window, width, height);

	return window;
}

void Window::resize_callback(GLFWwindow* window, int width, int height)
{
	Window::width = width;
	Window::height = height;

	// Set the viewport size
	glViewport(0, 0, width, height);
	// Set the matrix mode to GL_PROJECTION to determine the proper camera properties
	glMatrixMode(GL_PROJECTION);
	// Load the identity matrix
	glLoadIdentity();
	// Set the perspective of the projection viewing frustum
	gluPerspective(60.0, double(width) / (double)height, 1.0, 1000.0);
	// Move camera back 20 units so that it looks at the origin (or else it's in the origin)
	glTranslatef(0, 0, -20);

	delete[] Window::pixels;
	Window::pixels = new float[Window::width * Window::height * 3];
}

void Window::idle_callback()
{
	// Perform any updates as necessary. Here, we will spin the cube slightly.
	bunny.update();
	dragon.update();
	bear.update();
}

void Window::display_callback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	// Set the matrix mode to GL_MODELVIEW
	glMatrixMode(GL_MODELVIEW);
	// Load the identity matrix
	glLoadIdentity();

	Window::clearBuffer();
	Window::rasterize();

	switch (rasterizerMode)
	{
		case true : //Rasterization mode
			// glDrawPixels writes a block of pixels to the framebuffer
			glDrawPixels(Window::width, Window::height, GL_RGB, GL_FLOAT, Window::pixels);
			break;

		case false : //OpenGL mode
			// Render objects
			switch (objectNumber)
			{
			case 1:
				bunny.draw();
				break;
			case 2:
				dragon.draw();
				break;
			case 3:
				bear.draw();
				break;
			default:
				break;
			}
			break;

		default:
			break;
	}

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();
	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	// Check for a key press
	if (action == GLFW_PRESS)
	{
		// Check if escape was pressed
		if (key == GLFW_KEY_ESCAPE)
		{
			// Close the window. This causes the program to also terminate.
			glfwSetWindowShouldClose(window, GL_TRUE);
		}
		// Check if F1 was pressed
		else if (key == GLFW_KEY_F1)
		{
			objectNumber = 1;
		}
		// Check if F2 was pressed
		else if (key == GLFW_KEY_F2)
		{
			objectNumber = 2;
		}
		// Check if F3 was pressed
		else if (key == GLFW_KEY_F3)
		{
			objectNumber = 3;
		}
		// Check if P was pressed
		else if (key == GLFW_KEY_P && mods == GLFW_MOD_SHIFT)
		{
			//Increase the size of the points
			bunny.changePointSize(1.0f);
			dragon.changePointSize(1.0f);
			bear.changePointSize(1.0f);
		}
		// Check if p was pressed
		else if (key == GLFW_KEY_P)
		{
			//Decrease the size of the points
			bunny.changePointSize(-1.0f);
			dragon.changePointSize(-1.0f);
			bear.changePointSize(-1.0f);
		}
		// Check if X was pressed
		else if (key == GLFW_KEY_X && mods == GLFW_MOD_SHIFT)
		{
			//Move the object to the right
			bunny.translate(1.0f, 0.0f, 0.0f);
			dragon.translate(1.0f, 0.0f, 0.0f);
			bear.translate(1.0f, 0.0f, 0.0f);
		}
		// Check if x was pressed
		else if (key == GLFW_KEY_X)
		{
			//Move the object to the left
			bunny.translate(-1.0f, 0.0f, 0.0f);
			dragon.translate(-1.0f, 0.0f, 0.0f);
			bear.translate(-1.0f, 0.0f, 0.0f);
		}
		// Check if Y was pressed
		else if (key == GLFW_KEY_Y && mods == GLFW_MOD_SHIFT)
		{
			//Move the object up
			bunny.translate(0.0f, 1.0f, 0.0f);
			dragon.translate(0.0f, 1.0f, 0.0f);
			bear.translate(0.0f, 1.0f, 0.0f);
		}
		// Check if y was pressed
		else if (key == GLFW_KEY_Y)
		{
			//Move the object down
			bunny.translate(.0f, -1.0f, 0.0f);
			dragon.translate(.0f, -1.0f, 0.0f);
			bear.translate(.0f, -1.0f, 0.0f);
		}
		// Check if Z was pressed
		else if (key == GLFW_KEY_Z && mods == GLFW_MOD_SHIFT)
		{
			//Move the object out of the screen
			bunny.translate(0.0f, 0.0f, 1.0f);
			dragon.translate(0.0f, 0.0f, 1.0f);
			bear.translate(0.0f, 0.0f, 1.0f);
		}
		// Check if z was pressed
		else if (key == GLFW_KEY_Z)
		{
			//Move the object into the screen
			bunny.translate(.0f, .0f, -1.0f);
			dragon.translate(.0f, .0f, -1.0f);
			bear.translate(.0f, .0f, -1.0f);
		}
		// Check if S was pressed
		else if (key == GLFW_KEY_S && mods == GLFW_MOD_SHIFT)
		{
			//Scale up the object
			bunny.scale(1.5f);
			dragon.scale(1.5f);
			bear.scale(1.5f);
		}
		// Check if s was pressed
		else if (key == GLFW_KEY_S)
		{
			//Scale down the object
			bunny.scale(0.5f);
			dragon.scale(0.5f);
			bear.scale(0.5f);
		}
		// Check if O was pressed
		else if (key == GLFW_KEY_O && mods == GLFW_MOD_SHIFT)
		{
			//Orbit the object clockwise
			bunny.orbit(5.0f, 1.0f);
			dragon.orbit(5.0f, 1.0f);
			bear.orbit(5.0f, 1.0f);
		}
		// Check if o was pressed
		else if (key == GLFW_KEY_O)
		{
			//Orbit the object counterclockwise
			bunny.orbit(5.0f, -1.0f);
			dragon.orbit(5.0f, -1.0f);
			bear.orbit(5.0f, -1.0f);
		}
		// Check if R was pressed
		else if (key == GLFW_KEY_R && mods == GLFW_MOD_SHIFT)
		{
			//Reset orientation and scale
			bunny.resetOrientationScale();
			dragon.resetOrientationScale();
			bear.resetOrientationScale();
		}
		// Check if r was pressed
		else if (key == GLFW_KEY_R)
		{
			//Reset position
			bunny.resetPosition();
			dragon.resetPosition();
			bear.resetPosition();
		}
		// Check if m was pressed
		else if (key == GLFW_KEY_M)
		{
			//Switch mode between OpenGL and rasterization
			rasterizerMode = !rasterizerMode;
		}
	}
}
