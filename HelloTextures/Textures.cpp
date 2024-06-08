// -------------------------------------------------------------------------------
// PROJECT: Textures
// AUTHOR: willo488
// DATE: 6/6/2024
// DESCRIPTION: This is a modification of the HelloRectangle project to 
// allow for a texture to be applied. Additionally, a new Shader header file
// is included to simplify the initialization of shader source code.
// -------------------------------------------------------------------------------

#include "shader.h"
#include "stb_image.h"

void processInput(GLFWwindow* window);

int main()
{
	// Error Check Variables
	int success;
	char infoLog[512];

	// WINDOW SETTINGS
	const unsigned int SRC_WIDTH = 800;
	const unsigned int SRC_HEIGHT = 600;

	// Initialize GLFW
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create Window
	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set window to current context
	glfwMakeContextCurrent(window);

	// GLAD: Load all OpenGL function pointers
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Shader initialization
	Shader myShader("shader.vs", "shader.fs");

	// Triangle Vertices
	float vertices[] =
	{
		  // Coordinates	   // Color			    // Texture Coordinates     
		  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,  0.0f,	1.0f,  1.0f,  // Top Right
		  0.5f, -0.5f,  0.0f,  0.0f,  1.0f,  0.0f,  1.0f,  0.0f,  // Bottom Right
		 -0.5f, -0.5f,  0.0f,  0.0f,  0.0f,  1.0f,  0.0f,  0.0f,  // Bottom Left
		 -0.5f,  0.5f,  0.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f   // Top Left
	};
	unsigned int indices[] = {
		0, 1, 3,  // first triangle
		1, 2, 3   // second triangle
	};

	// stbi settings
	stbi_set_flip_vertically_on_load(true);

	// ------------------------------ TEXTURE 1 ------------------------------
	// Texture file reading
	int width, height, nrChannels;
	unsigned char* data = stbi_load("container.jpg", &width, &height, &nrChannels, 0);

	// Texture generation (currently empty)
	unsigned int texture0;
	glGenTextures(1, &texture0);

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, texture0);

	// Configure texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generate texture
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// Free up memory from texture import
	stbi_image_free(data);

	// ------------------------------ TEXTURE 2 ------------------------------
	// Texture file reading
	data = stbi_load("awesomeface.png", &width, &height, &nrChannels, 0);

	// Texture generation (currently empty)
	unsigned int texture1;
	glGenTextures(1, &texture1);

	// Bind texture
	glBindTexture(GL_TEXTURE_2D, texture1);

	// Configure texture wrapping parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);	// set texture wrapping to GL_REPEAT (default wrapping method)
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// set texture filtering parameters
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	// Generate texture
	if (data)
	{	
		// (.PNG image uses RGBA, not RGB)
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}

	// Free up memory from texture import
	stbi_image_free(data);

	// Create VAO, VBO, and EBO
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	unsigned int EBO;
	glGenBuffers(1, &EBO);

	// Bind VAO
	glBindVertexArray(VAO);
	

	// Bind and set VBO
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Bind and set EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set vertex attribute pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// Use shader program
	myShader.use();

	// Specifiy texture units to shader samplers
	myShader.setInt("texture0", 0);
	myShader.setInt("texture1", 1);

	// RENDER LOOP
	while (!glfwWindowShouldClose(window)) {

		// Input
		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Texture activation
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);
		glActiveTexture(GL_TEXTURE1);
		glBindTexture(GL_TEXTURE_2D, texture1);

		// Render container
		myShader.use();
		glBindVertexArray(VAO);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}