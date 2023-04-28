#include "Event.h"

namespace AGui {

    Event::Event() : type_{None} {
    }

    Event::Event(Event::EventType tp) : type_{tp} {
    }
}
