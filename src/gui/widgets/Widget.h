#ifndef GAME_ENGINE_GUI_WIDGET_H
#define GAME_ENGINE_GUI_WIDGET_H

namespace AGui {

    class Widget {

    public:
        virtual ~Widget();

        virtual void update() = 0;
    };

} // AGui

#endif //GAME_ENGINE_GUI_WIDGET_H
