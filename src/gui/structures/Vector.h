#ifndef GAME_ENGINE_GUI_VECTOR_H
#define GAME_ENGINE_GUI_VECTOR_H

namespace AGui {

    template<class T>
    class Vector2 {
        Vector2(T x, T y): x_{x}, y_{y} {}

        inline void setX(T x) { x_ = x; }
        inline void setY(T y) { y_ = y; }
        [[nodiscard]] inline T x() const { return x_;}
        [[nodiscard]] inline T y() const { return y_; }

    protected:
        T x_;
        T y_;
    };

    class IntVector2 : public Vector2<int> {
    };

    class FloatVector2 : public Vector2<float> {
    };

} // AGui

#endif //GAME_ENGINE_GUI_VECTOR_H
