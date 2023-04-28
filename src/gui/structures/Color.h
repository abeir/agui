#ifndef GAME_ENGINE_GUI_COLOR_H
#define GAME_ENGINE_GUI_COLOR_H

namespace AGui {

    class NormalizedColor {
    public:
        NormalizedColor() = default;
        NormalizedColor(float r, float g, float b, float a);

        [[nodiscard]] inline float red() const { return r_; }
        [[nodiscard]] inline  float green() const { return g_; }
        [[nodiscard]] inline float blue() const { return b_; }
        [[nodiscard]] inline float alpha() const { return a_; }
    private:
        float r_;
        float g_;
        float b_;
        float a_;
    };;

    class Color {
    public:
        Color() = default;
        Color(int r, int g, int b, int a);

        [[nodiscard]] NormalizedColor normalize() const;

        [[nodiscard]] inline int red() const { return r_; }
        [[nodiscard]] inline  int green() const { return g_; }
        [[nodiscard]] inline int blue() const { return b_; }
        [[nodiscard]] inline int alpha() const { return a_; }

    private:
        int r_;
        int g_;
        int b_;
        int a_;
    };

} // AGui

#endif //GAME_ENGINE_GUI_COLOR_H
