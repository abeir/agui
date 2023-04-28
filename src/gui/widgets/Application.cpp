#include "Application.h"
#include "platform/SDLSupport.h"
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_opengl3.h>
#include <SDL.h>
#include <SDL_opengl.h>

namespace AGui {

    namespace Internal {

        class ApplicationPrivate {
        public:
            ApplicationPrivate() : backgroundColor{0.8,0.8,0.8,1} {}

            ~ApplicationPrivate() = default;

            NormalizedColor backgroundColor;

            bool quit = false;

            SDL_Window* window = nullptr;
            SDL_GLContext context = nullptr;
            ImGuiIO* io = nullptr;

            std::unique_ptr<EventHandler> eventHandler;
        };
    }


    Application::Application(const char *title, int w, int h)
        : Application(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, WindowShown) {
    }

    Application::Application(const char *title, int w, int h, Application::WindowFlags flags)
        : Application(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, flags) {
    }

    Application::Application(const char *title, int x, int y, int w, int h, Application::WindowFlags flags)
        : private_(new Internal::ApplicationPrivate) {

        // Setup SDL
        SDL_Init(SDL_INIT_EVERYTHING);

        // GL 3.0 + GLSL 130
        const char* glsl_version = "#version 130";
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, 0);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
        SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);

        // From 2.0.18: Enable native IME.
#ifdef SDL_HINT_IME_SHOW_UI
        SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
#endif

        // Create window with graphics context
        SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
        SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
        SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

        SDL_Window* window = SDL_CreateWindow(title, x, y, w, h, SDL_WINDOW_OPENGL | flags);
        SDL_GLContext gl_context = SDL_GL_CreateContext(window);
        SDL_GL_MakeCurrent(window, gl_context);
        SDL_GL_SetSwapInterval(1); // Enable vsync

        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // Setup Platform/Renderer backends
        ImGui_ImplSDL2_InitForOpenGL(window, gl_context);
        ImGui_ImplOpenGL3_Init(glsl_version);

        private_->window = window;
        private_->context = gl_context;
    }

    Application::~Application() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplSDL2_Shutdown();
        ImGui::DestroyContext();

        SDL_GL_DeleteContext(private_->context);
        SDL_DestroyWindow(private_->window);
        SDL_Quit();

        delete private_;
    }

    void Application::setEventHandler(std::unique_ptr<EventHandler> handler) {
        private_->eventHandler = std::move(handler);
    }

    Application &Application::setTitle(const char *title) {
        SDL_SetWindowTitle(private_->window, title);
        return *this;
    }

    Application &Application::setIcon(const char* file){
        // TODO SDL_SetWindowIcon
        return *this;
    }

    Application &Application::setPosition(int x, int y) {
        SDL_SetWindowPosition(private_->window, x, y);
        return *this;

    }

    Application &Application::setCenterd() {
        SDL_SetWindowPosition(private_->window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
        return *this;
    }

    Application &Application::setSize(int w, int h) {
        SDL_SetWindowSize(private_->window, w, h);
        return *this;
    }

    Application &Application::setMinimumSize(int w, int h) {
        SDL_SetWindowMinimumSize(private_->window, w, h);
        return *this;
    }

    Application &Application::setMaximumSize(int w, int h) {
        SDL_SetWindowMaximumSize(private_->window, w, h);
        return *this;
    }

    Application &Application::setBordered(bool border) {
        SDL_SetWindowBordered(private_->window, border ? SDL_TRUE : SDL_FALSE);
        return *this;
    }

    Application &Application::setResizable(bool resizable) {
        SDL_SetWindowResizable(private_->window, resizable ? SDL_TRUE : SDL_FALSE);
        return *this;
    }

    Application &Application::setAlwaysOnTop(bool onTop) {
        SDL_SetWindowAlwaysOnTop(private_->window, onTop ? SDL_TRUE : SDL_FALSE);
        return *this;
    }

    Application &Application::setWindowed() {
        SDL_SetWindowFullscreen(private_->window, 0);
        return *this;
    }

    Application &Application::setFullscreen() {
        SDL_SetWindowFullscreen(private_->window, SDL_WINDOW_FULLSCREEN);
        return *this;
    }

    Application &Application::setFullscreenDesktop() {
        SDL_SetWindowFullscreen(private_->window, SDL_WINDOW_FULLSCREEN_DESKTOP);
        return *this;
    }

    Application &Application::setBackgroundColor(const Color &color) {
        private_->backgroundColor = color.normalize();
        return *this;
    }

    Application &Application::setKeyboardGrab(bool grab) {
        SDL_SetWindowKeyboardGrab(private_->window, grab ? SDL_TRUE : SDL_FALSE);
        return *this;
    }

    Application &Application::setMouseGrab(bool grab) {
        SDL_SetWindowMouseGrab(private_->window, grab ? SDL_TRUE : SDL_FALSE);
        return *this;
    }

    Application &Application::setMouseRect(const Rect &r) {
        SDL_Rect rect {.x = r.x, .y = r.y, .w = r.w, .h = r.h};
        SDL_SetWindowMouseRect(private_->window, &rect);
        return *this;
    }

    Application &Application::setBrightness(float brightness) {
        SDL_SetWindowBrightness(private_->window, brightness);
        return *this;
    }

    Application &Application::setOpacity(float opacity) {
        SDL_SetWindowOpacity(private_->window, opacity);
        return *this;
    }

    Application &Application::setInputFocus() {
        SDL_SetWindowInputFocus(private_->window);
        return *this;
    }


    void Application::render() {
        ImGuiIO& io = ImGui::GetIO();

        while (!private_->quit)
        {
            SDL_Event event;
            while (SDL_PollEvent(&event))
            {
                ImGui_ImplSDL2_ProcessEvent(&event);
                if (event.type == SDL_QUIT){
                    quit();
                    continue;
                }
                if (event.type == SDL_WINDOWEVENT
                        && event.window.event == SDL_WINDOWEVENT_CLOSE
                        && event.window.windowID == SDL_GetWindowID(private_->window)){
                    quit();
                    continue;
                }
                if(private_->eventHandler){
                    Event e(SDLSupport::convertEventType(event.type));
                    if(private_->eventHandler->eventFilter(e)){
                        private_->eventHandler->eventHandle(e);
                    }
                }
            }

            // Start the Dear ImGui frame
            ImGui_ImplOpenGL3_NewFrame();
            ImGui_ImplSDL2_NewFrame();
            ImGui::NewFrame();

            update();

            // Rendering
            ImGui::Render();
            glViewport(0, 0, (int)io.DisplaySize.x, (int)io.DisplaySize.y);
            glClearColor(private_->backgroundColor.red(), private_->backgroundColor.green(), private_->backgroundColor.blue(), private_->backgroundColor.alpha());
            glClear(GL_COLOR_BUFFER_BIT);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            SDL_GL_SwapWindow(private_->window);
        }
    }

    void Application::update() {
        ImGui::Begin("Hello");

        ImGui::Text("This is some useful text.");

        ImGui::End();
    }

    void Application::quit() {
        private_->quit = true;
    }

} // AGui