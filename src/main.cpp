#include "D:\MakeFileTemplate-main\C++\_SFML\include\Game.h"
#include <time.h>
#include <SFML/Audio.hpp>

using namespace sf;
int main()
{
    Sound lagucok;
    SoundBuffer soundbuffcok;
    soundbuffcok.loadFromFile("D:\\MakeFileTemplate-main\\C++\\_SFML\\sound\\Rick-Astley-Never-Gonna-Give-You-Up-_Instrumental_-HD-Audio.wav");
    lagucok.setBuffer(soundbuffcok);
    lagucok.setVolume(100);
    lagucok.play();
    lagucok.setLoop(true);
    srand(time(static_cast<unsigned>(0)));
    Game game;
    game.run();

    return 0;
}