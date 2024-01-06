
# Snake game with C

I have written the famous snake game using the C language and a game library called SDL.

The game features many difficulty modes including a two player mode where two snakes compete against each other in order to attain the highest score.

## Acknowledgements

 - [Snake in C](https://www.youtube.com/watch?v=v6vn3qG_rwU&list=PLYLjKimBhcxHOOgGdbDBokN96KBMZGzJx)



## Installation

Before compiling, make sure you have installed the following dependencies:

- VCPKG: By following the installation steps in this [link](https://vcpkg.io/en/getting-started.html)

- SDL: By typing the following command depending on your OS:

    ```
    On Ubuntu: sudo apt-get install libsdl2-dev
    On Mac: brew install sdl
    On Windows in mingw64: pacman -S mingw-w64-x86_64-SDL2
    ```

Then compile the game, by typing 'make' in the terminal inside the project folder.

Finally, you can run the snake game by typing './snake' (or './snake.exe' on windows) followed by a game option choice.  

You can see the available option by typing './snake help' (or './snake.exe help' on windows).
## License

[MIT](https://choosealicense.com/licenses/mit/)


## Screenshots

- One player mode:
    [![image.png](https://i.postimg.cc/0QW7wGfW/image.png)](https://postimg.cc/sQWBFhb7)

- Two player mode:
    [![image.png](https://i.postimg.cc/52SgtCZG/image.png)](https://postimg.cc/xXqMxcjy)
