#include "ui.h"


Button::Button(glm::vec2 pos, glm::vec2 scale, int layer, float angle, const Shader& shader)
    : GameObject(pos, scale, layer, angle, shader) {}

TexturedButton::TexturedButton(glm::vec2 pos, Texture2D tex, glm::vec2 scale, int layer, float angle)
    : Button(pos, scale, layer, angle, Shader("./shaders/main.vert", "./shader/texture.frag")), idleTex(tex), hoverTex(tex), pressTex(tex), mousePos(0.0, 0.0), hover(false), pressed(false){}
TexturedButton::TexturedButton(glm::vec2 pos, Texture2D idleTex, Texture2D pressTex, glm::vec2 scale, int layer, float angle)
    : Button(pos, scale, layer, angle, Shader("./shaders/main.vert", "./shader/texture.frag")), idleTex(idleTex), hoverTex(idleTex), pressTex(pressTex), mousePos(0.0, 0.0), hover(false), pressed(false){}
TexturedButton::TexturedButton(glm::vec2 pos, Texture2D idleTex, Texture2D hoverTex, Texture2D pressTex, glm::vec2 scale, int layer, float angle)
    : Button(pos, scale, layer, angle, Shader("./shaders/main.vert", "./shader/texture.frag")), idleTex(idleTex), hoverTex(hoverTex), pressTex(pressTex), mousePos(0.0, 0.0), hover(false), pressed(false){}

ColoredButton::ColoredButton(glm::vec2 pos, glm::vec3 col, glm::vec2 scale, int layer, float angle)
    : Button(pos, scale, layer, angle, Shader("./shaders/main.vert", "./shader/color.frag")), idleCol(col), hoverCol(col), pressCol(col), mousePos(0.0, 0.0), hover(false), pressed(false){}
ColoredButton::ColoredButton(glm::vec2 pos, glm::vec3 idleCol, glm::vec3 pressCol, glm::vec2 scale, int layer, float angle)
    : Button(pos, scale, layer, angle, Shader("./shaders/main.vert", "./shader/color.frag")), idleCol(idleCol), hoverCol(idleCol), pressCol(pressCol), mousePos(0.0, 0.0), hover(false), pressed(false){}
ColoredButton::ColoredButton(glm::vec2 pos, glm::vec3 idleCol, glm::vec3 hoverCol, glm::vec3 pressCol, glm::vec2 scale, int layer, float angle)
    : Button(pos, scale, layer, angle, Shader("./shaders/main.vert", "./shader/color.frag")), idleCol(idleCol), hoverCol(hoverCol), pressCol(pressCol), mousePos(0.0, 0.0), hover(false), pressed(false){}
