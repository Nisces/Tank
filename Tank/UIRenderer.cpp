#include "UIRenderer.h"
#include <iostream>
#include "ResourceManager.h"
#include <glm/glm.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

UIRenderer::UIRenderer(unsigned int width, unsigned int height)
{
    // load and configure shader
    this->TextShader = ResourceManager::loadShader("text.vs", "text.fs", nullptr, "text");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f);
    this->TextShader.SetMatrix4("projection", projection, true);
    this->TextShader.SetInteger("text", 0);
    this->ImageShader = ResourceManager::loadShader("image.vs", "image.fs", nullptr, "image");
    this->ImageShader.SetMatrix4("projection", projection, true);
    this->ImageShader.SetInteger("image", 0);
    this->initRenderer();
}

UIRenderer::~UIRenderer()
{
    glDeleteVertexArrays(1, &this->VAO);
}

void UIRenderer::initRenderer()
{
    unsigned int VBO;
    unsigned int EBO;
    float vertices[] = {
        // pos      // tex
        0.0f, 0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
    };

    unsigned int indices[] = {
        0, 1, 2,
        0, 2, 3
    };

    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(this->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void UIRenderer::load(std::string font, unsigned int fontSize)
{
    // first clear the previously loaded Characters
    this->Characters.clear();
    // then initialize and load the FreeType library
    FT_Library ft;
    if (FT_Init_FreeType(&ft)) // all functions return a value different than 0 whenever an error occurred
        std::cout << "ERROR::FREETYPE: Could not init FreeType Library" << std::endl;
    // load font as face
    FT_Face face;
    if (FT_New_Face(ft, font.c_str(), 0, &face))
        std::cout << "ERROR::FREETYPE: Failed to load font" << std::endl;
    // set size to load glyphs as
    FT_Set_Pixel_Sizes(face, 0, fontSize);
    // disable byte-alignment restriction
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    // then for the first 128 ASCII characters, pre-load/compile their characters and store them
    for (GLubyte c = 0; c < 128; c++) // lol see what I did there 
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        unsigned int texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            face->glyph->bitmap.width,
            face->glyph->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            face->glyph->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        // now store character for later use
        Character character = {
            texture,
            glm::ivec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::ivec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            face->glyph->advance.x
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void UIRenderer::renderText(string text, Position pos, float scale, Color color)
{
    // Prepare transformations
    this->TextShader.use();
    glBindVertexArray(this->VAO);
    this->TextShader.SetVector3f("textColor", color);
    std::string::const_iterator c;
    for (c = text.begin(); c != text.end(); c++)
    {
        Character ch = Characters[*c];
        Size size(ch.Size.x * scale, ch.Size.y * scale);
        float xpos = pos.x + ch.Bearing.x * scale;
        float ypos = pos.y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;
        glm::mat4 model(1.0f);
        model = glm::translate(model, glm::vec3(Position(xpos, ypos), 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)
        model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

        this->TextShader.SetMatrix4("model", model);
        glBindTexture(GL_TEXTURE_2D, ch.TextureID);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
        pos.x += (ch.Advance >> 6) * scale;
    }
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void UIRenderer::renderImage(const Texture& texture, Position pos, Size size)
{
    // Prepare transformations
    this->ImageShader.use();
    glm::mat4 model(1.0f);
    model = glm::translate(model, glm::vec3(pos, 0.0f));  // First translate (transformations are: scale happens first, then rotation and then finall translation happens; reversed order)

    model = glm::scale(model, glm::vec3(size, 1.0f)); // Last scale

    this->ImageShader.SetMatrix4("model", model);

    glActiveTexture(GL_TEXTURE0);
    texture.bind();

    glBindVertexArray(this->VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

