#ifndef GAME_H
#define GAME_H

#include <string>

class Game
{
public:
    virtual void play_at(int x, int y) = 0;
    virtual int cols() const = 0;
    virtual int rows() const = 0;
    virtual std::string get_val(int x, int y) const = 0;
    virtual bool is_finished() const = 0;
    virtual std::string get_message() const = 0;
};

#endif // GAME_H