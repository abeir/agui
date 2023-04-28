#ifndef GAME_ENGINE_GUI_EVENT_H
#define GAME_ENGINE_GUI_EVENT_H


namespace AGui {
    class Event {
    public:
        enum EventType {
            None,
            Quit,
        };

        Event();
        explicit Event(EventType tp);

        inline void setType(EventType tp) { type_ = tp; }
        [[nodiscard]] inline EventType type() const { return type_; }

    private:
        EventType type_;
    };
}


#endif //GAME_ENGINE_GUI_EVENT_H
