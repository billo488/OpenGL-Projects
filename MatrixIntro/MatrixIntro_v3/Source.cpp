#include "shader.h"

// Function Definitions
void processInput(GLFWwindow* window);

int main() 
{
	// Window Settings
	const unsigned int SRC_WIDTH = 800;
	const unsigned int SRC_HEIGHT = 600;

	// GLFW Initialization
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	GLFWwindow* window = glfwCreateWindow(SRC_WIDTH, SRC_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create window" << std::endl;
		glfwTerminate();
		return -1;
	}

	// Set window to current context
	glfwMakeContextCurrent(window);

	// GLAD Initialization
	// (NOTE: GLAD can only be initialized after window creation + context!)
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	// Shader initialization
	Shader myShader("shader.vs", "shader.fs");

	// UNOPTIMIZED BOX:
	// 36 Vertices
	// 12 Triangles
	// 6 Faces
	float vertices[] =
	{
		// Triangle 1        //Tex Coords
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  // Bottom Left
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  // Upper Left
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 2 (Front)
		-0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  // Upper Left
		 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  // Upper Right
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 3 (Back)
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  // Bottom Left
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  // Upper Left
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 4 (Back)
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  // Upper Left
		 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  // Upper Right
		 0.5f, -0.5f, -0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 5 (Left)
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  // Upper Left
		-0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  // Upper Right
		-0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 6 (Left)
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  // Upper Left
		-0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  // Bottom Left
		-0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 7 (Right)
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  // Upper Left
		 0.5f,  0.5f,  0.5f,  1.0f,  1.0f,  // Upper Right
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 8 (Right)
		 0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  // Upper Left
		 0.5f, -0.5f, -0.5f,  0.0f,  0.0f,  // Bottom Left
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 9 (Top)
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  // Upper Left
		 0.5f,  0.5f, -0.5f,  1.0f,  1.0f,  // Upper Right
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 10 (Top)
		-0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  // Upper Left
		-0.5f,  0.5f,  0.5f,  0.0f,  0.0f,  // Bottom Left
		 0.5f,  0.5f,  0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 11 (Bottom)
		-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  // Upper Left
		 0.5f, -0.5f, -0.5f,  1.0f,  1.0f,  // Upper Right
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f,  // Bottom Right
		// Triangle 12 (Bottom)
		-0.5f, -0.5f, -0.5f,  0.0f,  1.0f,  // Upper Left
		-0.5f, -0.5f,  0.5f,  0.0f,  0.0f,  // Bottom Left
		 0.5f, -0.5f,  0.5f,  1.0f,  0.0f   // Bottom Right
	};

	// Vertex Buffer Object (VBO)
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Vertex Array Object (VAO)
	unsigned int VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	// TEXTURE INITIALIZATION

	// stbi settings
	stbi_set_flip_vertically_on_load(true);

	// Read texture file
	int width, height, nrChannels;
	unsigned char* data = stbi_load("heya.png", &width, &height, &nrChannels, 4);
	// Texture generation
	unsigned int texture0;
	glGenTextures(1, &texture0);
	// Bind texture
	glBindTexture(GL_TEXTURE_2D, texture0);
	// Configure texture wrapping
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Configure texture filtering
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// Generate texture
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture0" << std::endl;
	}
	// Free up memory from texture import
	stbi_image_free(data);

	// Initial Shader Call
	myShader.use();

	// Specify texture units to shader (only needs to be done once)
	myShader.setInt("texture0", 0);

	// Enable Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// COLORS:
	//red     =  (1.0f, 0.0f, 0.0f, 1.0f);
	//orange  =  (1.0f, 0.5f, 0.0f, 1.0f);
	//yellow  =  (1.0f, 1.0f, 0.0f, 1.0f);
	//green   =  (0.0f, 1.0f, 0.0f, 1.0f);
	//blue    =  (0.0f, 0.0f, 1.0f, 1.0f);
	//purple  =  (0.3f, 0.0f, 0.5f, 1.0f);
	//magenta =  (0.5f, 0.0f, 0.8f, 1.0f);

	// RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Screen Color
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Texture Activation
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, texture0);

		// Matrix Transformations
		// Create a transformation matrix initalized as an identity matrix
		glm::mat4 transform = glm::mat4(1.0f);
		// TRANSLATION:
		transform = glm::translate(transform, glm::vec3(0.0f, 0.0f, 0.0f));
		// ROTATION:
		transform = glm::rotate(transform, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
		// Render Calls
		myShader.use();
		// Update shader uniform
		unsigned int transformLoc = glGetUniformLocation(myShader.ID, "transform");
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transform));
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 36);
		// Swap buffers and poll events
		glfwSwapBuffers(window);
		glfwPollEvents();
	}


	return 0;
}

void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
	else if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
	{
		// RED
		glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
	{
		// ORANGE
		glClearColor(1.0f, 0.5f, 0.0f, 1.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
	{
		// YELLOW
		glClearColor(1.0f, 1.0f, 0.0f, 1.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
	{
		// GREEN
		glClearColor(0.0f, 1.0f, 0.0f, 1.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
	{
		// BLUE
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
	}
	else if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
	{
		// PURPLE
		glClearColor(0.3f, 0.0f, 0.5f, 1.0f);
	}
}