#ifndef GAME_ENGINE_GUI_SDLSUPPORT_H
#define GAME_ENGINE_GUI_SDLSUPPORT_H

#include "events/Event.h"
#include <SDL_events.h>

namespace AGui {

    class SDLSupport {
    public:
        static Event::EventType convertEventType(Uint32 tp);
    };
}
#endif //GAME_ENGINE_GUI_SDLSUPPORT_H
