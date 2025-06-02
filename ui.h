#ifndef UI_H
#define UI_H

#include "shader.h"
#include "texture.h"
#include "gameobject.h"
#include <glm/glm.hpp>

class Button : public GameObject{
    public:
        glm::vec2 mousePos;
        bool hover;
        bool pressed;
        static void defaultCallback() {}
        void (*pressCallback)() = &defaultCallback;
        void (*releaseCallback)() = &defaultCallback;
        void (*hoverCallback)() = &defaultCallback;
        void (*holdCallback)() = &defaultCallback;
        Button(glm::vec2 pos, glm::vec2 scale, int layer, float angle, const Shader& shader);
        Button();
        virtual void update(float dt);
        virtual void draw();
        
};
class TexturedButton : public Button{
    public:
        Texture2D idleTex;
        Texture2D hoverTex;
        Texture2D pressTex;
        TexturedButton(glm::vec2 pos, Texture2D tex, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        TexturedButton(glm::vec2 pos, Texture2D idleTex, Texture2D pressTex, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        TexturedButton(glm::vec2 pos, Texture2D idleTex, Texture2D hoverTex, Texture2D pressTex, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        void update(float dt);
        void draw();
};
class ColoredButton : public Button{
    public:
        glm::vec3 idleCol;
        glm::vec3 hoverCol;
        glm::vec3 pressCol;
        ColoredButton(glm::vec2 pos, glm::vec3 col, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        ColoredButton(glm::vec2 pos, glm::vec3 idleCol, glm::vec3 pressCol, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        ColoredButton(glm::vec2 pos, glm::vec3 idleCol, glm::vec3 hoverCol, glm::vec3 pressCol, glm::vec2 scale=glm::vec2(1.0f, 1.0f), int layer=0, float angle=0.0f);
        void update(float dt);
        void draw();
};

#endif