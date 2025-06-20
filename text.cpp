#include <iostream>

#include <glm/gtc/matrix_transform.hpp>
#include <ft2build.h>
#include FT_FREETYPE_H

#include "text.h"
#include "shader.h"

TextRenderer::TextRenderer(unsigned int width, unsigned int height)
{
    // load and configure shader
    this->TextShader = Shader("./shaders/text.vert", "./shaders/text.frag");
    this->TextShader.use();
    this->TextShader.setMat4("projection", glm::ortho(0.0f, static_cast<float>(width), static_cast<float>(height), 0.0f));
    this->TextShader.setInt("text", 0);
    // configure VAO/VBO for texture quads
    glGenVertexArrays(1, &this->VAO);
    glGenBuffers(1, &this->VBO);
    glBindVertexArray(this->VAO);
    glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 6 * 4, NULL, GL_DYNAMIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), 0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void TextRenderer::Load(std::string font, unsigned int fontSize)
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
            glm::vec2(face->glyph->bitmap.width, face->glyph->bitmap.rows),
            glm::vec2(face->glyph->bitmap_left, face->glyph->bitmap_top),
            static_cast<unsigned int>(face->glyph->advance.x >> 6)
        };
        Characters.insert(std::pair<char, Character>(c, character));
    }
    glBindTexture(GL_TEXTURE_2D, 0);
    // destroy FreeType once we're finished
    FT_Done_Face(face);
    FT_Done_FreeType(ft);
}

void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
{
    this->TextShader.use();
    this->TextShader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->VAO);

    // Get ascent from reference character (e.g. 'H')
    float ascent = this->Characters['H'].Bearing.y * scale;
    float lineHeight = this->Characters['H'].Size.y * scale * 2.0f;

    std::istringstream stream(text);
    std::string line;
    float lineY = y + ascent;

    while (std::getline(stream, line)) {
        // Measure the width of the current line
        float lineWidth = 0.0f;
        for (char c : line) {
            Character ch = Characters[c];
            lineWidth += ch.Advance * scale;
        }

        float lineX = x; // Center this line horizontally

        for (char c : line) {
            Character ch = Characters[c];

            float xpos = lineX + ch.Bearing.x * scale;
            // float ypos = lineY - (ch.Bearing.y - ch.Size.y) * scale;
            float ypos = lineY + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f },
                { xpos,     ypos,       0.0f, 0.0f },

                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            lineX += ch.Advance * scale;
        }

        lineY += lineHeight;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

// void TextRenderer::RenderText(std::string text, float x, float y, float scale, glm::vec3 color)
// {
//     // activate corresponding render state	
//     this->TextShader.use();
//     this->TextShader.setVec3("textColor", color);
//     glActiveTexture(GL_TEXTURE0);
//     glBindVertexArray(this->VAO);

//     float startX = x;

//     for (std::string::const_iterator c = text.begin(); c != text.end(); c++)
//     {
//         if (*c == '\n') {
//             y += this->Characters['H'].Size.y * scale * 1.5f; // Move to next line
//             for (std::string::const_iterator c = text.begin(); c != text.end() && *c != '\n'; c++) {
//                 Character ch = Characters[*c];
//             }
//             x = startX;
//             continue;
//         }
    
//         Character ch = Characters[*c];
    
//         float xpos = x + ch.Bearing.x * scale;
//         float ypos = y + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;
//         // float ypos = baselineY - (ch.Bearing.y - ch.Size.y) * scale;

//         float w = ch.Size.x * scale;
//         float h = ch.Size.y * scale;
    
//         float vertices[6][4] = {
//             { xpos,     ypos + h,   0.0f, 1.0f },
//             { xpos + w, ypos,       1.0f, 0.0f },
//             { xpos,     ypos,       0.0f, 0.0f },
    
//             { xpos,     ypos + h,   0.0f, 1.0f },
//             { xpos + w, ypos + h,   1.0f, 1.0f },
//             { xpos + w, ypos,       1.0f, 0.0f }
//         };
    
//         glBindTexture(GL_TEXTURE_2D, ch.TextureID);
//         glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
//         glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
//         glBindBuffer(GL_ARRAY_BUFFER, 0);
//         glDrawArrays(GL_TRIANGLES, 0, 6);
    
//         x += ch.Advance * scale;
//     }
    
//     glBindVertexArray(0);
//     glBindTexture(GL_TEXTURE_2D, 0);
// }
void TextRenderer::RenderTextCentered(std::string text, float x, float y, float scale, glm::vec3 color)
{
    this->TextShader.use();
    this->TextShader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->VAO);

    // Get ascent from reference character (e.g. 'H')
    float ascent = this->Characters['H'].Bearing.y * scale;
    float lineHeight = this->Characters['H'].Size.y * scale * 2.0f;

    std::istringstream stream(text);
    std::string line;
    float lineY = y + ascent;

    while (std::getline(stream, line)) {
        // Measure the width of the current line
        float lineWidth = 0.0f;
        for (char c : line) {
            Character ch = Characters[c];
            lineWidth += ch.Advance * scale;
        }

        float lineX = x - lineWidth / 2.0f; // Center this line horizontally

        for (char c : line) {
            Character ch = Characters[c];

            float xpos = lineX + ch.Bearing.x * scale;
            // float ypos = lineY - (ch.Bearing.y - ch.Size.y) * scale;
            float ypos = lineY + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f },
                { xpos,     ypos,       0.0f, 0.0f },

                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            lineX += ch.Advance * scale;
        }

        lineY += lineHeight;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void TextRenderer::RenderTextRight(std::string text, float x, float y, float scale, glm::vec3 color)
{
    this->TextShader.use();
    this->TextShader.setVec3("textColor", color);
    glActiveTexture(GL_TEXTURE0);
    glBindVertexArray(this->VAO);

    // Get ascent from reference character (e.g. 'H')
    float ascent = this->Characters['H'].Bearing.y * scale;
    float lineHeight = this->Characters['H'].Size.y * scale * 2.0f;

    std::istringstream stream(text);
    std::string line;
    float lineY = y + ascent;

    while (std::getline(stream, line)) {
        // Measure the width of the current line
        float lineWidth = 0.0f;
        for (char c : line) {
            Character ch = Characters[c];
            lineWidth += ch.Advance * scale;
        }

        float lineX = x - lineWidth; // Center this line horizontally

        for (char c : line) {
            Character ch = Characters[c];

            float xpos = lineX + ch.Bearing.x * scale;
            // float ypos = lineY - (ch.Bearing.y - ch.Size.y) * scale;
            float ypos = lineY + (this->Characters['H'].Bearing.y - ch.Bearing.y) * scale;

            float w = ch.Size.x * scale;
            float h = ch.Size.y * scale;

            float vertices[6][4] = {
                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f },
                { xpos,     ypos,       0.0f, 0.0f },

                { xpos,     ypos + h,   0.0f, 1.0f },
                { xpos + w, ypos + h,   1.0f, 1.0f },
                { xpos + w, ypos,       1.0f, 0.0f }
            };

            glBindTexture(GL_TEXTURE_2D, ch.TextureID);
            glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
            glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
            glBindBuffer(GL_ARRAY_BUFFER, 0);
            glDrawArrays(GL_TRIANGLES, 0, 6);

            lineX += ch.Advance * scale;
        }

        lineY += lineHeight;
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}
