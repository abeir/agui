#ifndef GAME_ENGINE_GUI_EVENTHANDLER_H
#define GAME_ENGINE_GUI_EVENTHANDLER_H

#include "events/Event.h"
#include <cstdint>

namespace AGui {

    class EventHandler {
    public:
        virtual ~EventHandler() = default;
        virtual bool eventFilter(const Event &) = 0;
        virtual void eventHandle(const Event &) = 0;
    };

} // AGui
#endif //GAME_ENGINE_GUI_EVENTHANDLER_H
