#pragma once
#include <map>
#include <glad/glad.h>
#include <glm/glm.hpp>
#include "GameObject.h"
#include "texture.h"
#include "shader.h"

using namespace std;


/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    unsigned int TextureID; // ID handle of the glyph texture
    glm::ivec2   Size;      // size of glyph
    glm::ivec2   Bearing;   // offset from baseline to left/top of glyph
    unsigned int Advance;   // horizontal offset to advance to next glyph
};


// A renderer class for rendering text displayed by a font loaded using the 
// FreeType library. A single font is loaded, processed into a list of Character
// items for later rendering.
class UIRenderer
{
public:
    // holds a list of pre-compiled Characters
    std::map<char, Character> Characters;
    // constructor
    UIRenderer(unsigned int width, unsigned int height);
    ~UIRenderer();
    // pre-compiles a list of characters from the given font
    void load(string font, unsigned int fontSize);
    // renders a string of text using the precompiled list of characters
    void renderText(string text, Position pos, float scale, Color color = Color(1.0f));
    void renderImage(const Texture& texture, Position pos, Size size);
private:
    // render state
    void initRenderer();
    Shader TextShader;
    Shader ImageShader;
    unsigned int VAO;
};

