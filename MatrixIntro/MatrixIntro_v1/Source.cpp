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
		// Triangle 1 (Front Face)
		-0.5f, -0.5f,  0.0f,
		-0.5f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		// Triangle 2 (Front Face)
		-0.5f,  0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		// Triangle 3 (Back Face)
		-0.5f, -0.5f, -1.0f,
		-0.5f,  0.5f, -1.0f,
		 0.5f, -0.5f, -1.0f,
		// Triangle 4 (Back Face)
		-0.5f,  0.5f, -1.0f,
		 0.5f,  0.5f, -1.0f,
		 0.5f, -0.5f, -1.0f,
		// Triangle 5 (Left Face)
		-0.5f,  0.5f, -1.0f,
		-0.5f,  0.5f,  0.0f,
		-0.5f, -0.5f,  0.0f,
		// Triangle 6 (Left Face)
		-0.5f,  0.5f, -1.0f,
		-0.5f, -0.5f, -1.0f,
		-0.5f, -0.5f,  0.0f,
		// Triangle 7 (Right Face)
		 0.5f,  0.5f, -1.0f,
		 0.5f,  0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f,
		// Triangle 8 (Right Face)
		 0.5f,  0.5f, -1.0f,
		 0.5f, -0.5f, -1.0f,
		 0.5f, -0.5f,  0.0f,
		// Triangle 9 (Top Face)
		-0.5f,  0.5f, -1.0f,
		 0.5f,  0.5f, -1.0f,
		 0.5f,  0.5f,  0.0f,
		// Triangle 10 (Top Face)
		-0.5f,  0.5f, -1.0f,
		-0.5f,  0.5f,  0.0f,
		 0.5f,  0.5f,  0.0f,
		// Triangle 11 (Bottom Face)
		-0.5f, -0.5f, -1.0f,
		 0.5f, -0.5f, -1.0f,
		 0.5f, -0.5f,  0.0f,
		// Triangle 12 (Bottom Face)
		-0.5f, -0.5f, -1.0f,
		-0.5f, -0.5f,  0.0f,
		 0.5f, -0.5f,  0.0f
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
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	// Initial Shader Call
	myShader.use();

	// RENDER LOOP
	while (!glfwWindowShouldClose(window))
	{
		// Input
		processInput(window);

		// Screen Color
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Render Calls
		myShader.use();
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
}