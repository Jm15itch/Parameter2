# Parameter2
An example of a game developed with ChatGPT's code generating ability. Essentially, I asked it questions such as: "Can you write me a C++ program that makes a sdl window" or "make a class that uses sdl functions to display a square with translation, rotation, and scale functions" and then copied and pasted the code it generated. I found that sometimes I had to fix up code (adding headers where the bot omitted them or changing some parts of the code to work together) but apart from that the AI generated almost all of it. The cmake folder contains stuff made by the community, and the CMakeLists.txt file was also made by the AI.

# GamePlay
Not fun. The game has a weird and broken movement probably because of a improperlly designed deltaTime variable. But for the most part, the game actually works. It's basically a really dumbed down version of one of those spaceship fighting games where it's top down and enemies spawn from the top and make their way down, akin to space invaders I suppose.

# Building

```
git clone https://github.com/Jm15itch/Parameter2
cd Parameter2
mkdir build
cd build
cmake ..
make
./parameter
```

you will also need sdl2 dev files
```
sudo apt install libsdl2-dev
```
