#include "default_theme.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "sbl_image.h"


#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif
#include <iostream>

bool LoadTextureFromFile(const char* filename, SDL_Texture** texture_ptr, int& width, int& height, SDL_Renderer* renderer) {
    SDL_Surface* surface = IMG_Load(filename);

    if (surface == nullptr) {
        fprintf(stderr, "Failed to load image: %s\n", IMG_GetError());
        return false;
    }

    *texture_ptr = SDL_CreateTextureFromSurface(renderer, surface);

    if (*texture_ptr == nullptr) {
        fprintf(stderr, "Failed to create SDL texture: %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        return false;
    }

    width = surface->w;
    height = surface->h;

    SDL_FreeSurface(surface);
    return true;
}


// Top Menu
static void DisplayMainMenuBar() {
    if (ImGui::BeginMainMenuBar()) {
        // File menu
        if (ImGui::BeginMenu("File")) {
            if (ImGui::MenuItem(ICON_FA_FILE " New")) {
                std::cout << "New File" << std::endl;
            }
            if (ImGui::MenuItem(ICON_FA_FOLDER_OPEN " Open", "Ctrl+O")) {
            }
            if (ImGui::BeginMenu(ICON_FA_BOX_ARCHIVE " Open Recent")) {
                // Dynamically generate list in future
                ImGui::MenuItem("image_0.png");
                if (ImGui::MenuItem("ming_ma.jpg")) {
                    std::cout << "DO NOT OPEN" << std::endl;
                }
                ImGui::MenuItem("compsci.gif");
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem(ICON_FA_FLOPPY_DISK " Save", "Ctrl+S")) {
            }
            if (ImGui::MenuItem(ICON_FA_FLOPPY_DISK " Save As..")) {
            }

            ImGui::Separator();
            if (ImGui::MenuItem(ICON_FA_X " Quit", "Alt+F4")) {
                std::exit(0);
            }

            ImGui::EndMenu();
        }

        // Edit menu
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem(ICON_FA_ARROW_ROTATE_LEFT " Undo", "CTRL+Z")) {
            }
            if (ImGui::MenuItem(ICON_FA_ARROW_ROTATE_RIGHT " Redo", "CTRL+Y", false, false)) {
            } // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem(ICON_FA_SCISSORS " Cut", "CTRL+X")) {
            }
            if (ImGui::MenuItem(ICON_FA_COPY " Copy", "CTRL+C")) {
            }
            if (ImGui::MenuItem(ICON_FA_PASTE " Paste", "CTRL+V")) {
            }
            ImGui::EndMenu();
        }

        // Filter menu
        if (ImGui::BeginMenu(ICON_FA_WAND_MAGIC_SPARKLES " Filter")) {
            if (ImGui::MenuItem("Blur")) {
            }
            ImGui::EndMenu();
        }

        // Filter menu
        /* if (ImGui::BeginMenu("Help"))
        {
            if (ImGui::MenuItem("Docs"))
            {
            }

            if (ImGui::MenuItem("About"))
            {
            }
        }*/
        ImGui::EndMainMenuBar();
    }
}

// ToolBox
static void DisplayToolbox(SDL_Renderer* renderer) {
    ImGui::SetNextWindowSizeConstraints(ImVec2(250, 175), ImVec2(250, 175)); // Fixed size
    ImGui::Begin("Toolbox", NULL, ImGuiWindowFlags_NoResize);

    // Draw Tool
    ImGui::Button(ICON_FA_PENCIL);
    ImGui::SetItemTooltip("Paint | CTRL+D");

    // Fill Tool
    ImGui::SameLine();
    ImGui::Button(ICON_FA_BUCKET);
    ImGui::SetItemTooltip("Fill | CTRL+B");

    // Line Tool
    ImGui::SameLine();
    ImGui::Button(ICON_FA_PEN_NIB);
    ImGui::SetItemTooltip("Draw Line | CTRL+L");

    // Circle Tool
    ImGui::SameLine();
    ImGui::Button(ICON_FA_COMPASS_DRAFTING); // ICON_FA_CIRCLE_NOTCH, ICON_FA_CIRCLE_DOT
    ImGui::SetItemTooltip("Draw Ellipse | CTRL+E");
    
    // Square tool
    ImGui::SameLine();
    ImGui::Button(ICON_FA_PEN_NIB);
    ImGui::SetItemTooltip("Draw Square | CTRL+Q");

    ImGui::SeparatorText("Colors");

    static float col1[3] = { 0.f, 0.0f, 0.0f };
    static float col2[3] = { 1.0f, 1.0f, 1.00f };
    ImGui::ColorEdit3("Primary", (float*)&col1);
    ImGui::ColorEdit3("Secondary", (float*)&col2);
    ImGui::End();
}
class dot {
public:
    dot() : posX(0.0f), posY(0.0f), radius(5.0f), color(1.0f, 0.0f, 0.0f) {}

    void draw() const {
        // Draw dot using OpenGL
        glColor3f(color.x, color.y, color.z);
        glBegin(GL_TRIANGLE_FAN);
        for (int i = 0; i < 360; i++) {
            float angle = i * 3.1415926f / 180;
            float x = posX + radius * cos(angle);
            float y = posY + radius * sin(angle);
            glVertex2f(x, y);
        }
        glEnd();
    }

    void setPosition(float x, float y) {
        posX = x;
        posY = y;
    }

    void setColor(const ImVec4& col) {
        color = col;
    }

private:
    float posX, posY;
    float radius;
    ImVec4 color;
};

int main(int, char**) {
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Create window
    SDL_Window* window = SDL_CreateWindow("Dot Drawing", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    if (!window) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Setup OpenGL context
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

    // Create OpenGL context
    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // Initialize OpenGL loader
    if (gladLoadGLLoader(SDL_GL_GetProcAddress) == 0) {
        printf("Failed to initialize OpenGL loader!\n");
        return -1;
    }

    // Setup ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;

    // Setup ImGui backends
    ImGui_ImplSDL2_InitForOpenGL(window, glContext);
    ImGui_ImplOpenGL3_Init("#version 330");

    Dot dot;

    bool done = false;
    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT) {
                done = true;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN && event.button.button == SDL_BUTTON_LEFT) {
                // Get mouse position
                int mouseX, mouseY;
                SDL_GetMouseState(&mouseX, &mouseY);
                // Convert mouse coordinates to OpenGL coordinates
                float glX = (mouseX / (float)800) * 2 - 1;
                float glY = ((600 - mouseY) / (float)600) * 2 - 1;
                dot.setPosition(glX, glY);
            }
        }

        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame(window);
        ImGui::NewFrame();

        // Render ImGui components
        ImGui::Begin("Toolbox");
        if (ImGui::Button("Select Dot")) {
            // Activate dot selection mode
        }
        ImGui::End();

        // Render dot
        dot.draw();

        // Rendering
        ImGui::Render();
        SDL_GL_MakeCurrent(window, glContext);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
