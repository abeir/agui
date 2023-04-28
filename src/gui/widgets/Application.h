#ifndef GAME_ENGINE_GUI_APPLICATION_H
#define GAME_ENGINE_GUI_APPLICATION_H

#include "structures/Color.h"
#include "structures/Rect.h"
#include "events/EventHandler.h"
#include <memory>

namespace AGui {

    namespace Internal {
        class ApplicationPrivate;
    }

    class Application {
    public:
        enum WindowFlag{
            WindowFullScreen = 0x00000001,/**< fullscreen window */
            WindowShown = 0x00000004, /**< window is visible */
            WindowHidden = 0x00000008, /**< window is not visible */
            WindowBorderless = 0x00000010, /**< no window decoration */
            WindowResizable = 0x00000020, /**< window can be resized */
            WindowMinimized = 0x00000040, /**< window is minimized */
            WindowMaximized = 0x00000080, /**< window is maximized */
            WindowMouseGrabbed = 0x00000100, /**< window has grabbed mouse input */
            WindowInputFocus = 0x00000200, /**< window has input focus */
            WindowMouseFocus = 0x00000400, /**< window has mouse focus */
            WindowFullScreenDesktop = ( WindowFullScreen | 0x00001000 ),
            WindowAllowHighDPI = 0x00002000, /**< window should be created in high-DPI mode if supported. */
            WindowMouseCapture = 0x00004000, /**< window has mouse captured (unrelated to MOUSE_GRABBED) */
            WindowAlwaysOnTop = 0x00008000, /**< window should always be above others */
            WindowSkipTaskbar = 0x00010000, /**< window should not be added to the taskbar */
            WindowUtility = 0x00020000, /**< window should be treated as a utility window */
            WindowTooltip = 0x00040000, /**< window should be treated as a tooltip */
            WindowPopupMenu = 0x00080000, /**< window should be treated as a popup menu */
            WindowKeyboardGrabbed = 0x00100000,   /**< window has grabbed keyboard input */
        };
        typedef uint32_t WindowFlags;

        explicit Application(const char* title, int w, int h);
        Application(const char* title, int w, int h, WindowFlags flags);
        Application(const char* title, int x, int y, int w, int h, WindowFlags flags);
        ~Application();

        void setEventHandler(std::unique_ptr<EventHandler> handler);

        Application& setTitle(const char* title);
        Application& setIcon(const char* file);
        Application& setPosition(int x, int y);
        Application& setCenterd();
        Application& setSize(int w, int h);
        Application& setMinimumSize(int w, int h);
        Application& setMaximumSize(int w, int h);
        Application& setBordered(bool);
        Application& setResizable(bool);
        Application& setAlwaysOnTop(bool);
        Application& setWindowed();
        Application& setFullscreen();
        Application& setFullscreenDesktop();
        Application& setBackgroundColor(const Color &);
        Application& setKeyboardGrab(bool);
        Application& setMouseGrab(bool);
        Application& setMouseRect(const Rect &);
        Application& setBrightness(float);
        Application& setOpacity(float);
        Application& setInputFocus();

        void render();
        void update();

        void quit();
    private:
        Internal::ApplicationPrivate* private_;
    };

} // AGui

#endif //GAME_ENGINE_GUI_APPLICATION_H
