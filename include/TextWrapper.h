#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <string>

class TextWrapper
{
public:
  TextWrapper(SDL_Renderer* renderer, TTF_Font* font, int x, int y, int w, int h)
    : renderer(renderer), font(font), x(x), y(y), w(w), h(h)
  {
    // Initialize the text surface and texture
    textSurface = TTF_RenderText_Blended_Wrapped(font, "", {255, 255, 255, 255}, w);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);

    // Initialize the text rect
    textRect.x = x;
    textRect.y = y;
    textRect.w = w;
    textRect.h = h;
  }

  ~TextWrapper()
  {
    // Free the font, text surface and texture
    TTF_CloseFont(font);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);
  }

  // Set the text
  void setText(const std::string& text)
  {
    // Free the old text surface and texture
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // Create a new text surface and texture
    textSurface = TTF_RenderText_Blended_Wrapped(font, text.c_str(), {255, 255, 255, 255}, w);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
  }


    void draw() const
  {
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
  }

private:
  SDL_Renderer* renderer; // The renderer
  TTF_Font* font; // The font to use for the text
  SDL_Surface* textSurface; // The text surface
  SDL_Texture* textTexture; // The text texture
  SDL_Rect textRect; // The rect representing the text
  int x, y; // The position of the text
  int w, h; // The size of the text
};
