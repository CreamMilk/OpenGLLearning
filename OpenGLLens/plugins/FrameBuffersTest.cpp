#include <glad/glad.h>
#include "FrameBuffersTest.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <array>

#include "VertexBufferLayout.h"

namespace OpenGLLens
{
	namespace cube {
        constexpr std::array<float, 180> cubeVertices = {
            // positions          // texture Coords
             -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
              0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
              0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
              0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
             -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,

             -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
              0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
              0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
              0.5f,  0.5f,  0.5f,  1.0f, 1.0f,
             -0.5f,  0.5f,  0.5f,  0.0f, 1.0f,
             -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,

             -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
             -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             -0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

              0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
              0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
              0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
              0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
              0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
              0.5f,  0.5f,  0.5f,  1.0f, 0.0f,

             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,
              0.5f, -0.5f, -0.5f,  1.0f, 1.0f,
              0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
              0.5f, -0.5f,  0.5f,  1.0f, 0.0f,
             -0.5f, -0.5f,  0.5f,  0.0f, 0.0f,
             -0.5f, -0.5f, -0.5f,  0.0f, 1.0f,

             -0.5f,  0.5f, -0.5f,  0.0f, 1.0f,
              0.5f,  0.5f, -0.5f,  1.0f, 1.0f,
              0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
              0.5f,  0.5f,  0.5f,  1.0f, 0.0f,
             -0.5f,  0.5f,  0.5f,  0.0f, 0.0f,
             -0.5f,  0.5f, -0.5f,  0.0f, 1.0f
        };

        constexpr std::array<float, 30> planeVertices = {
            // positions          // texture Coords 
             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f,  5.0f,  0.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,

             5.0f, -0.5f,  5.0f,  2.0f, 0.0f,
            -5.0f, -0.5f, -5.0f,  0.0f, 2.0f,
             5.0f, -0.5f, -5.0f,  2.0f, 2.0f
        };

        constexpr std::array<float, 24> quadVertices = { // vertex attributes for a quad that fills the entire screen in Normalized Device Coordinates.
            // positions   // texCoords
            -1.0f,  1.0f,  0.0f, 1.0f,
            -1.0f, -1.0f,  0.0f, 0.0f,
             1.0f, -1.0f,  1.0f, 0.0f,

            -1.0f,  1.0f,  0.0f, 1.0f,
             1.0f, -1.0f,  1.0f, 0.0f,
             1.0f,  1.0f,  1.0f, 1.0f
        };
	}

    unsigned int loadTexture(char const* path)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
    }

    FrameBuffersTest::FrameBuffersTest()
    {

        cubeShader = std::make_shared<Shader>("shaders/framebuffers.vs", "shaders/framebuffers.fs");
        screenShader = std::make_shared<Shader>("shaders/framebuffers_screen.vs", "shaders/framebuffers_screen.fs");

        // cube VAO
		m_cubeVAO = std::make_shared<VertexArray>();
        m_cubeVAO->bind();
		m_cubeVBO = std::make_shared<VertexBuffer>((void *)cube::cubeVertices.data(), sizeof(cube::cubeVertices));
		VertexBufferLayout cubeLayout;
		cubeLayout.push<float>(3);
		cubeLayout.push<float>(2);
		m_cubeVAO->addBuffer(*m_cubeVBO, cubeLayout);


        // plane VAO
		m_planeVAO = std::make_shared<VertexArray>();
		m_planeVAO->bind();
		m_planeVBO = std::make_shared<VertexBuffer>((void*)cube::planeVertices.data(), sizeof(cube::planeVertices));
		VertexBufferLayout planeLayout;
		planeLayout.push<float>(3);
		planeLayout.push<float>(2);
		m_planeVAO->addBuffer(*m_planeVBO, planeLayout);

        // screen quad VAO
        m_quadVAO = std::make_shared<VertexArray>();
		m_quadVAO->bind();
		m_quadVBO = std::make_shared<VertexBuffer>((void*)cube::quadVertices.data(), sizeof(cube::quadVertices));
		VertexBufferLayout quadLayout;
		quadLayout.push<float>(2);
		quadLayout.push<float>(2);
		m_quadVAO->addBuffer(*m_quadVBO, quadLayout);



        cubeTexture = loadTexture("D:/code/OpenGLLens/OpenGLLens/resources/images/container.jpg");
        floorTexture = loadTexture("D:/code/OpenGLLens/OpenGLLens/resources/images/wall.jpg");


        // shader configuration
        // --------------------
        cubeShader->use();
        cubeShader->setInt("texture1", 0);

        screenShader->use();
        screenShader->setInt("screenTexture", 0);

        m_frameBufferObject = std::make_shared<FrameBufferObject>();
  //      m_frameBufferObject->init(1280, 800);
  //      m_frameBufferObject->initColor(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_TEXTURE_2D);
		//m_frameBufferObject->initDepth();
    }

	FrameBuffersTest::~FrameBuffersTest() 
	{

	}

	void FrameBuffersTest::onUpdate(float delaTime) 
	{

	}

	void FrameBuffersTest::onRender(const DrawContext* drawContext)
	{
        if(m_initialized == false ||
            m_screenWidth != (unsigned int)drawContext->glWidth ||
            m_screenHeight != (unsigned int)drawContext->glHeight)
        {
            m_screenWidth = drawContext->glWidth;
            m_screenHeight = drawContext->glHeight;
            m_frameBufferObject->init(m_screenWidth, m_screenHeight);
            m_frameBufferObject->initColor(GL_RGB, GL_RGB, GL_UNSIGNED_BYTE, GL_LINEAR, GL_TEXTURE_2D);
            m_frameBufferObject->initDepth();
            m_initialized = true;
			std::cout << "FrameBuffersTest::onRender resize framebuffer to " << m_screenWidth << "x" << m_screenHeight << std::endl;
		}

        if (!m_frameBufferObject->start())
        {
            return;
        }

        glEnable(GL_DEPTH_TEST);

		glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        cubeShader->use();
		glm::mat4 model = glm::mat4(1.0f);
		/*glm::vec3 pos = glm::vec3(0.0f, 0.0f, 8.0f);
		glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
		glm::vec3 front = glm::vec3(0.0f, 0.0f, -1.0f);*/
        glm::mat4 view = drawContext->viewMatrix;//glm::lookAt(pos, pos + front, up);
		float aspectRatio = drawContext->glWidth / (float)drawContext->glHeight;
        glm::mat4 projection = glm::perspective(glm::radians(45.0f), aspectRatio, 0.1f, 100.0f);
		cubeShader->setMat4("view", view);
		cubeShader->setMat4("projection", projection);

        //glBindVertexArray(cubeVAO);
		m_cubeVAO->bind();
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, cubeTexture);
        model = glm::translate(model, glm::vec3(-1.0f, 0.0f, -1.0f));
        cubeShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        model = glm::mat4(1.0f);
        model = glm::translate(model, glm::vec3(2.0f, 0.0f, 0.0f));
        cubeShader->setMat4("model", model);
        glDrawArrays(GL_TRIANGLES, 0, 36);

        //glBindVertexArray(planeVAO);
		m_planeVAO->bind();
        glBindTexture(GL_TEXTURE_2D, floorTexture);
        cubeShader->setMat4("model", glm::mat4(1.0f));
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glBindVertexArray(0);

        m_frameBufferObject->stop();

        glDisable(GL_DEPTH_TEST);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        screenShader->use();
       // glBindVertexArray(quadVAO);
		m_quadVAO->bind();
        glBindTexture(GL_TEXTURE_2D, m_frameBufferObject->getColorTexture());
        glDrawArrays(GL_TRIANGLES, 0, 6);
	}	

	void FrameBuffersTest::onImGuiRender() 
	{

	}

    unsigned int FrameBuffersTest::loadTexture(const char* path)
    {
        unsigned int textureID;
        glGenTextures(1, &textureID);

        int width, height, nrComponents;
        unsigned char* data = stbi_load(path, &width, &height, &nrComponents, 0);
        if (data)
        {
            GLenum format;
            if (nrComponents == 1)
                format = GL_RED;
            else if (nrComponents == 3)
                format = GL_RGB;
            else if (nrComponents == 4)
                format = GL_RGBA;

            glBindTexture(GL_TEXTURE_2D, textureID);
            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);

            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

            stbi_image_free(data);
        }
        else
        {
            std::cout << "Texture failed to load at path: " << path << std::endl;
            stbi_image_free(data);
        }

        return textureID;
	}
}