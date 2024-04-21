#include "default_theme.h"
#include "imgui.h"
#include "imgui_impl_sdl2.h"
#include "imgui_impl_sdlrenderer2.h"
#include <stdio.h>
#include <SDL.h>
#include <SDL_image.h>
#include "sbl_image.h"
#include "icons.h"
#include "canvas.h"

// Define constants for window resolution
const int WINDOW_WIDTH = 1280;
const int WINDOW_HEIGHT = 720;

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

    ImGui::SeparatorText("Colors");

    static float col1[3] = { 0.f, 0.0f, 0.0f };
    static float col2[3] = { 1.0f, 1.0f, 1.00f };
    ImGui::ColorEdit3("Primary", (float*)&col1);
    ImGui::ColorEdit3("Secondary", (float*)&col2);
    ImGui::End();
}

// Main code
int main(int, char**) {
    // Setup SDL
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER | SDL_INIT_GAMECONTROLLER) != 0) {
        printf("Error: %s\n", SDL_GetError());
        return -1;
    }

    // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

    // Create window with SDL_Renderer graphics context
    SDL_WindowFlags window_flags = (SDL_WindowFlags)(SDL_WINDOW_RESIZABLE | SDL_WINDOW_ALLOW_HIGHDPI);
    SDL_Window* window = SDL_CreateWindow("Sumi", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, window_flags);

    if (window == nullptr) {
        printf("Error: SDL_CreateWindow(): %s\n", SDL_GetError());
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        SDL_Log("Error creating SDL_Renderer!");
        return 0;
    }

    // Set window icon
    SDL_Surface* iconSurface = IMG_Load("../icons/icon.png");
    SDL_SetWindowIcon(window, iconSurface);
    SDL_FreeSurface(iconSurface);

    // Create a render target for the game itself
    SDL_Texture* texture = SDL_CreateTexture(renderer,
        SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
        300, 200);

    SDL_SetRenderTarget(renderer, texture);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_SetRenderTarget(renderer, NULL);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

    // Custom font/icons
    float baseFontSize = 22.0f; // 13.0f is the size of the default font. Change to the font size you use.
    io.Fonts->AddFontFromFileTTF("../icons/Proxima-Nova-Regular.ttf", baseFontSize);
    float iconFontSize = baseFontSize * 2.0f / 3.0f; // FontAwesome fonts need to have their sizes reduced by 2.0f/3.0f in order to align correctly

    // merge in icons from Font Awesome
    static const ImWchar icons_ranges[] = { ICON_MIN_FA, ICON_MAX_16_FA, 0 };
    ImFontConfig icons_config;
    icons_config.MergeMode = true;
    icons_config.PixelSnapH = true;
    icons_config.GlyphMinAdvanceX = iconFontSize;
    // use "fa-regular-400.ttf" if you want regular instead of solid
    io.Fonts->AddFontFromFileTTF("../icons/fa-solid-900.ttf", iconFontSize, &icons_config, icons_ranges);

    //Custom Theme
    Default::StyleColorsDefault();

    // Setup Platform/Renderer backends
    ImGui_ImplSDL2_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer2_Init(renderer);

    // Import background image
    SDL_Surface* surf = IMG_Load("../background/default.png");
    SDL_Texture* tex_background = SDL_CreateTextureFromSurface(renderer, surf);
    SDL_FreeSurface(surf);

    Canvas easel(renderer, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, 720, 480);

    bool done = false;

    while (!done) {

        // Handle user inputs and events
        SDL_Event event;

        while (SDL_PollEvent(&event)) {
            ImGui_ImplSDL2_ProcessEvent(&event);

            switch (event.type) {
            case SDL_QUIT:
                done = true;

            case SDL_MOUSEBUTTONDOWN:
                switch (event.button.button) {

                    // Drawing
                case SDL_BUTTON_LEFT:
                    int x = event.motion.x;
                    int y = event.motion.y;
                    break;
                }
                break;

            case SDL_MOUSEBUTTONUP:
                switch (event.button.button) {
                case SDL_BUTTON_LEFT:
                    //     drawing = false;
                    break;
                }
                break;
            }

            // Checks that window is open and when its closed
            if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(window))
                done = true;
        }

        // Check if the left mouse button is held down
        int x_off, y_off;
        Uint32 mouseState = SDL_GetRelativeMouseState(&x_off, &y_off);
        bool middleMouseButton = mouseState & SDL_BUTTON(SDL_BUTTON_MIDDLE);

        // Dragging the screen
        if (middleMouseButton) {
            easel.move(x_off, y_off);
        }


        // Start the Dear ImGui frame
        ImGui_ImplSDLRenderer2_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        DisplayMainMenuBar();
        DisplayToolbox(renderer);

        // Rendering
        ImGui::Render();
        ImGuiStyle& style = ImGui::GetStyle();
        ImVec4 clearColor = ImGui::ColorConvertU32ToFloat4(Default::GRAY100);

        style.WindowRounding = 6.0f;
        style.FrameRounding = 6.0f;
        style.PopupRounding = 6.0f;

        ImGui::Render();
        SDL_RenderSetScale(renderer, io.DisplayFramebufferScale.x, io.DisplayFramebufferScale.y);
        SDL_SetRenderDrawColor(renderer, (Uint8)(clearColor.x * 255), (Uint8)(clearColor.y * 255), (Uint8)(clearColor.z * 255), (Uint8)(clearColor.w * 255));
        SDL_RenderClear(renderer);

        // render the background image
        SDL_SetRenderTarget(renderer, tex_background);
        SDL_RenderClear(renderer);
        SDL_Rect drect{ 0, 0, WINDOW_WIDTH, WINDOW_HEIGHT };
        SDL_RenderCopy(renderer, tex_background, NULL, &drect);

        // Draw the canvas before imgui overlay, but on top of background
        easel.draw_self();

        ImGui_ImplSDLRenderer2_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }

    // Cleanup
    ImGui_ImplSDLRenderer2_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}