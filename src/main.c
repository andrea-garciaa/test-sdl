#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>

#ifdef _WIN32
#include <GL/glew.h>
#endif
#include <GL/gl.h>

#include "mymath.h"

// -- Constants ---------------------------------
#define DEFAULT_WIDTH 800
#define DEFAULT_HEIGHT 600

// -- Function declarations ---------------------
static void processInput(void);
static void onWindowEvent(SDL_WindowEvent winevent);
static void onMouseMotion(SDL_MouseMotionEvent motion);
static void onMouseScroll(SDL_MouseWheelEvent whevent);
static void onMouseButton(SDL_MouseButtonEvent btnevent);
static int loadShaderFromFile(const char* filename, unsigned int shadertype);
static int loadShaderFromBuffer(const char* buffer, unsigned int shadertype, int len);
static void render();
static void updateCamera();

// -- Globals -----------------------------------
static SDL_Window* window;
static bool canwarp;
static int warpx;
static int warpy;
static int width;
static int height;
static float deltatime;
static float lastframe;
static int shaderprog;
static unsigned int vbo;
static unsigned int vao;
static struct vec3 position;
static struct vec3 front;
static struct vec3 up;
static struct vec3 right;
static struct vec3 worldup;
static float yaw;
static float pitch;
static float movementspeed;
static float mousesensitivity;
static float zoom;

//-----------------------------------------------
int main(int argc, char** argv)
{
    if (0 > SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTS | SDL_INIT_TIMER)) {
        SDL_Quit();
        return 1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

    window = SDL_CreateWindow("testgl", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, DEFAULT_WIDTH, DEFAULT_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        SDL_Quit();
        return 1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);

#ifdef WIN32
    glewExperimental = true;
    if (!context || glewInit() != GLEW_OK) {
#else
    if (!context) {
#endif
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

    SDL_Event ev;
    bool keeprunning = true;

    // set the viewport size
    ev.type = SDL_WINDOWEVENT;
    ev.window.event = SDL_WINDOWEVENT_RESIZED;
    ev.window.data1 = DEFAULT_WIDTH;
    ev.window.data2 = DEFAULT_HEIGHT;

    SDL_PushEvent(&ev);


    // prepare data to draw
    float vertices[] = {
        // positions            // colors
        -0.5f, -0.5f, 0.0f,     1.0f, 0.0f, 0.0f,
        0.5f, -0.5f, 0.0f,      0.0f, 1.0f, 0.0f,
        0.0f,  0.5f, 0.0f,       1.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &vao);
    glGenBuffers(1, &vbo);
    glBindVertexArray(vao);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // position attribute is 3 float sized, but we jump 6 floats to reach the next position attribute, because there is color attribute inbetween
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), NULL);
    glEnableVertexAttribArray(0);

    // color attribute, same semantic as before, but last argument is first offset inside attrib array
    // it is 3 float sized because there is 3 floats (position attribute) before our color attribute we specify herein
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    // prepare shaders
    int success, vertshader, fragshader;

    vertshader = loadShaderFromFile("vertex.glsl", GL_VERTEX_SHADER);

    if (vertshader) {
        glGetShaderiv(vertshader, GL_COMPILE_STATUS, &success);

        if (success == GL_TRUE) {
            fragshader = loadShaderFromFile("fragment.glsl", GL_FRAGMENT_SHADER);

            if (fragshader) {
                glGetShaderiv(fragshader, GL_COMPILE_STATUS, &success);

                if (success == GL_TRUE) {
                    // link shader objects into a shader program
                    char infolog[512];

                    shaderprog = glCreateProgram();
                    glAttachShader(shaderprog, vertshader);
                    glAttachShader(shaderprog, fragshader);
                    glLinkProgram(shaderprog);
                    glGetProgramiv(shaderprog, GL_LINK_STATUS, &success);

                    if (success == GL_FALSE) {
                        glGetProgramInfoLog(shaderprog, sizeof(infolog), NULL, infolog);
                        fprintf(stderr, "shader program linking failed:\n%s\n", infolog);
                        keeprunning = false;
                    }

                    // no longer needed once linked
                    glDeleteShader(vertshader);
                    glDeleteShader(fragshader);
                }
                else {
                    char infolog[512];
                    glGetShaderInfoLog(fragshader, sizeof(infolog), NULL, infolog);
                    fprintf(stderr, "fragment shader compilation failed:\n%s\n", infolog);

                    keeprunning = false;
                }
            }
            else {
                fprintf(stderr, "%s\n", "failed to load fragment.glsl");
                keeprunning = false;
            }
        }
        else {
            char infolog[512];
            glGetShaderInfoLog(vertshader, sizeof(infolog), NULL, infolog);
            fprintf(stderr, "vertex shader compilation failed:\n%s\n", infolog);

            keeprunning = false;
        }
    }
    else {
        fprintf(stderr, "%s\n", "failed to load vertex.glsl");
        keeprunning = false;
    }


    // properties
    //------------------------
    lastframe = 0.0f;
    canwarp = false; // mouse capture is initialized later (here after first click to virtually give focus to the camera and fix mouse at center, otherwise first mouse motion will find the mouse far from the center and camera will abnormally shift its target)
    front.x = 0.0f;
    front.y = 0.0f;
    front.z = -1.0f;
    position.x = 0.0f;
    position.y = 0.0f;
    position.z = 3.0f;
    worldup.x = 0.0f;
    worldup.y = 1.0f;
    worldup.z = 0.0f;
    yaw = -90.0f;
    pitch = 0.0f;
    movementspeed = 2.5f;
    mousesensitivity = 0.1f;
    zoom = 45.0f;
    updateCamera();
    //------------------------

    while (keeprunning) {
        float currentframe = (double)SDL_GetTicks() / 1000;
        deltatime = currentframe - lastframe;
        lastframe = currentframe;

        while (SDL_PollEvent(&ev)) {
            switch (ev.type) {
            case SDL_QUIT:
                keeprunning = false;
                break;
            case SDL_WINDOWEVENT:
                onWindowEvent(ev.window);
                break;
            case SDL_MOUSEMOTION:
                onMouseMotion(ev.motion);
                break;
            case SDL_MOUSEWHEEL:
                onMouseScroll(ev.wheel);
                break;
            case SDL_MOUSEBUTTONDOWN:
            case SDL_MOUSEBUTTONUP:
                onMouseButton(ev.button);
                break;
            default:
                break;
            }
        }

        processInput();
        render();

        SDL_GL_SwapWindow(window);
    }

    glDeleteVertexArrays(1, &vao);
    glDeleteBuffers(1, &vbo);

    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}


//-----------------------------------------------
void processInput(void)
{
    int numkeys = 0;
    const Uint8* state = SDL_GetKeyboardState(&numkeys);

    if (numkeys) {
        if (state[SDL_SCANCODE_UP]) {
            struct vec3 tmp = { front.x, front.y, front.z };
            vec3_mulf(&tmp, movementspeed * deltatime);
            vec3_sub(&position, &tmp);
        }

        if (state[SDL_SCANCODE_DOWN]) {
            struct vec3 tmp = { front.x, front.y, front.z };
            vec3_mulf(&tmp, movementspeed * deltatime);
            vec3_add(&position, &tmp);
        }

        if (state[SDL_SCANCODE_LEFT]) {
            struct vec3 tmp = { right.x, right.y, right.z };
            vec3_mulf(&tmp, movementspeed * deltatime);
            vec3_sub(&position, &tmp);
        }

        if (state[SDL_SCANCODE_RIGHT]) {
            struct vec3 tmp = { right.x, right.y, right.z };
            vec3_mulf(&tmp, movementspeed * deltatime);
            vec3_add(&position, &tmp);
        }

        if (state[SDL_SCANCODE_ESCAPE])
            canwarp = false;

        //printf("x:%f y:%f z:%f yaw:%f pitch:%f deltatime:%f\n", position.x, position.y, position.z, yaw, pitch, deltatime);
    }
}


//-----------------------------------------------
void onWindowEvent(SDL_WindowEvent winevent)
{
    switch (winevent.event) {
    case SDL_WINDOWEVENT_RESIZED:
        width = winevent.data1;
		warpx = width / 2;
        height = winevent.data2;
		warpy = height / 2;
        glViewport(0, 0, width, height);
        printf("window resized to %dx%d\n", width, height);
        break;
    default:
        break;
    }
}


//-----------------------------------------------
void onMouseMotion(SDL_MouseMotionEvent motion)
{
	int xoffset = (motion.x - warpx);
	int yoffset = (motion.y - warpy);

    if (canwarp && (xoffset || yoffset)) {
		SDL_WarpMouseInWindow(window, warpx, warpy);

		yaw -= xoffset * mousesensitivity;
		pitch += yoffset * mousesensitivity;

		if (pitch > 89.0f)
			pitch = 89.0f;
		if (pitch < -89.0f)
			pitch = -89.0f;

		updateCamera();
    }
}


//-----------------------------------------------
void onMouseScroll(SDL_MouseWheelEvent whevent)
{
    if (zoom > 1.0f && zoom < 45.0f) zoom -= whevent.y;
    else if (zoom <= 1.0f) zoom = 1.0f;
    else if (zoom >= 45.0f) zoom = 45.0f;

    updateCamera();
}


//-----------------------------------------------
void onMouseButton(SDL_MouseButtonEvent btnevent)
{
    if (btnevent.state == SDL_PRESSED) {
        switch (btnevent.button) {
        case SDL_BUTTON_LEFT:
			SDL_WarpMouseInWindow(window, warpx, warpy);
            canwarp = true;
            break;
        case SDL_BUTTON_RIGHT:
            canwarp = false;
        default:
            break;
        }
    }
}


//-----------------------------------------------
int loadShaderFromFile(const char* filename, unsigned int shadertype)
{
    FILE* f = fopen(filename, "rb");
    if (f)
    {
        fseek(f, 0, SEEK_END);
        int size = ftell(f);
        fseek(f, 0, SEEK_SET);

        char* buffer = (char*)malloc(size);
        if (buffer && fread(buffer, size, 1, f)) {
            int shader = loadShaderFromBuffer(buffer, shadertype, size);
            free(buffer);
            return shader;
        }
    }

    return 0;
}


//-----------------------------------------------
int loadShaderFromBuffer(const char* buffer, unsigned int shadertype, int len)
{
    unsigned int shader = glCreateShader(shadertype);
    glShaderSource(shader, 1, &buffer, &len);
    glCompileShader(shader);
    return shader;
}


//-----------------------------------------------
void render()
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(shaderprog);

    float projection[4][4];
    mat4_perspective(projection, deg2rad(zoom), width / height, 0.1f, 100.0f);
    glUniformMatrix4fv(glGetUniformLocation(shaderprog, "projection"), 1, GL_FALSE, (const float*)projection);

    float view[4][4];
    struct vec3 target = { position.x, position.y, position.z };
    vec3_add(&target, &front);
    mat4_lookat(view, &position, &target, &up);
    glUniformMatrix4fv(glGetUniformLocation(shaderprog, "view"), 1, GL_FALSE, (const float*)view);

    glBindVertexArray(vao);

    float model[4][4];
    mat4_ident(model);
    glUniformMatrix4fv(glGetUniformLocation(shaderprog, "model"), 1, GL_FALSE, (const float*)model);

    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void updateCamera()
{
    front.x = cosf(deg2rad(yaw)) * cosf(deg2rad(pitch));
    front.y = sinf(deg2rad(pitch));
    front.z = sinf(deg2rad(yaw)) * cosf(deg2rad(pitch));
    vec3_normalize(&front);
    vec3_cross(&right, &front, &worldup);
    vec3_normalize(&right);
    vec3_cross(&up, &right, &front);
    vec3_normalize(&up);
}