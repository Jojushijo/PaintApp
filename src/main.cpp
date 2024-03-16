#include "default_theme.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_opengl3.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>

#if defined(IMGUI_IMPL_OPENGL_ES2)
#include <SDL_opengles2.h>
#else
#include <SDL_opengl.h>
#endif
#include <iostream>

#include <SDL_image.h>

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
            if (ImGui::MenuItem("New")) {
                std::cout << "New File" << std::endl;
            }
            if (ImGui::MenuItem("Open", "Ctrl+O")) {
            }
            if (ImGui::BeginMenu("Open Recent")) {
                // Dynamically generate list in future
                ImGui::MenuItem("image_0.png");
                if (ImGui::MenuItem("ming_ma.jpg")) {
                    std::cout << "DO NOT OPEN" << std::endl;
                }
                ImGui::MenuItem("compsci.gif");
                ImGui::EndMenu();
            }
            if (ImGui::MenuItem("Save", "Ctrl+S")) {
            }
            if (ImGui::MenuItem("Save As..")) {
            }

            ImGui::Separator();
            if (ImGui::MenuItem("Quit", "Alt+F4")) {
                std::exit(0);
            }

            ImGui::EndMenu();
        }

        // Edit menu
        if (ImGui::BeginMenu("Edit")) {
            if (ImGui::MenuItem("Undo", "CTRL+Z")) {
            }
            if (ImGui::MenuItem("Redo", "CTRL+Y", false, false)) {
            } // Disabled item
            ImGui::Separator();
            if (ImGui::MenuItem("Cut", "CTRL+X")) {
            }
            if (ImGui::MenuItem("Copy", "CTRL+C")) {
            }
            if (ImGui::MenuItem("Paste", "CTRL+V")) {
            }
            ImGui::EndMenu();
        }

        // Filter menu
        if (ImGui::BeginMenu("Filter")) {
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
    ImGui::SetNextWindowSizeConstraints(ImVec2(200, 400), ImVec2(200, 400)); // Fixed size
    ImGui::Begin("Toolbox", NULL, ImGuiWindowFlags_NoResize);
    ImGui::Button("Paint");
    ImGui::Button("Line");
    ImGui::Button("Circle");
    ImGui::End();
}

// Main code
int main(int, char**) {
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // GL 3.0 + GLSL 130
    const char* glsl_version = "#version 130";
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

    // Create window with graphics context
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Sumi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, window_flags);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

    if (window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }

    SDL_GLContext gl_context = SDL_GL_CreateContext(window);
    SDL_GL_MakeCurrent(window, gl_context);
    SDL_GL_SetSwapInterval(1); // Enable vsync

    // Set window icon
    SDL_Surface* iconSurface = IMG_Load("../icons/icon.png");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls
    io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;     // Enable Docking
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;   // Enable Multi-Viewport / Platform Windows
    // io.ConfigViewportsNoAutoMerge = true;
    io.ConfigViewportsNoTaskBarIcon = true;

    //Custom Theme
    Default::StyleColorsDefault();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
    ImGui_ImplOpenGL3_Init(glsl_version);

    bool done = false;

    while (!done) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);
            if (event.type == SDL_QUIT)
                done = true;
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Start the Dear ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL2_NewFrame();

        ImGui::NewFrame();
        DisplayToolbox(renderer);
        DisplayMainMenuBar();

        // Rendering
        ImGui::Render();
        glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4 clearColor = style.Colors[ImGuiCol_FrameBg];
        glClearColor(clearColor.x, clearColor.y, clearColor.z, clearColor.w);
        glClear(GL_COLOR_BUFFER_BIT);
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        // Update and Render additional Platform Windows
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            SDL_Window* backup_current_window = SDL_GL_GetCurrentWindow();
            SDL_GLContext backup_current_context = SDL_GL_GetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            SDL_GL_MakeCurrent(backup_current_window, backup_current_context);
        }

        SDL_GL_SwapWindow(window);
    }

    // Cleanup
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_GL_DeleteContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}