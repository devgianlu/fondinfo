/**
 * @author  Michele Tomaiuolo - http://www.ce.unipr.it/people/tomamic
 * @license This software is free - http://www.gnu.org/licenses/gpl.html
 */

#ifndef BOARDGAMEGUI_H
#define BOARDGAMEGUI_H

#include "boardgame.hpp"
#include "canvas.hpp"
#include <chrono>
#include <functional>

using namespace std::chrono_literals;
using namespace g2d;

namespace g2d {

auto W = 40, H = 40;
auto LONG_PRESS = 0.5s;

class BoardGameGui {
    BoardGame* g_;
    std::chrono::time_point<std::chrono::high_resolution_clock> downtime_;
    Size size_;

public:
    BoardGameGui(BoardGame* game) {
        g_ = game;
        size_ = Size{W*g_->cols(), H*g_->rows()};
        init_canvas(size_);
        update_buttons();

        main_loop([&]{ tick(); });
    }

    void tick() {
        if (key_pressed("LeftButton")) {
            downtime_ = std::chrono::high_resolution_clock::now();
        } else if (key_released("LeftButton")) {
            auto pos = mouse_position();
            auto now = std::chrono::high_resolution_clock::now();
            if (now - downtime_ > LONG_PRESS) {
                g_->flag_at(pos.x/W, pos.y/H);
            } else {
                g_->play_at(pos.x/W, pos.y/H);
            }
            update_buttons();
        }
    }

    void update_buttons() {
        clear_canvas();
        set_color({0, 0, 0});
        auto rows = g_->rows(), cols = g_->cols();
        for (auto y = 0; y < rows; ++y) {
            draw_line({0, y * H}, {cols * W, y * H});
        }
        for (auto x = 0; x < cols; ++x) {
            draw_line({x * W, 0}, {x * W, rows * H});
        }
        for (auto y = 0; y < rows; ++y) {
            for (auto x = 0; x < cols; ++x) {
                auto value = g_->value_at(x, y);
                auto center = Point{x * W + W/2, y * H + H/2};
                draw_text_centered(value, center, H/2);
            }
        }
        update_canvas();
        if (g_->finished()) {
            alert(g_->message());
            close_canvas();
        }
    }
    Size size() { return size_; }
};

void gui_play(BoardGame* game) {
    auto ui = BoardGameGui{game};
}

}

#endif