#include <SDL2/SDL.h>
#include <cmath>

class Square
{
public:
  Square(SDL_Renderer* renderer, int x, int y, int width, int height)
  {
    mRenderer = renderer;
    mX = x;
    mY = y;
    mWidth = width;
    mHeight = height;
    mScaleX = 1.0;
    mScaleY = 1.0;
    mRotation = 0.0;
  }

  void setScale(double scaleX, double scaleY)
  {
    mScaleX = scaleX;
    mScaleY = scaleY;
  }

  void setRotation(double rotation)
  {
    mRotation = rotation;
  }

  void setPosition(int x, int y)
  {
    mX = x;
    mY = y;
  }

  // Get the x coordinate of the square
  int getX() const
  {
    return mX;
  }

  // Get the y coordinate of the square
  int getY() const
  {
    return mY;
  }

  // Get the x coordinate of the square
  int getSX() const
  {
    return mWidth;
  }

  // Get the y coordinate of the square
  int getSY() const
  {
    return mHeight;
  }

  // Check whether a specific square is intersecting with this square
  bool isIntersecting(const Square& other) const
  {
    return mX < other.getX() + other.getSX() &&
           mX + mWidth > other.getX() &&
           mY < other.getY() + other.getSY() &&
           mHeight + mY > other.getY();
  }



  void draw()
  {
    // Set the render color to white
  SDL_SetRenderDrawColor(mRenderer, 255, 255, 255, 255);


  // Create the transformed rect
  SDL_Rect rect = { mX, mY, mWidth, mHeight };

  // Scale the rect
  rect.w = static_cast<int>(rect.w * mScaleX);
  rect.h = static_cast<int>(rect.h * mScaleY);

  // Rotate the rect around the center
  int centerX = rect.x + rect.w / 2;
  int centerY = rect.y + rect.h / 2;
  int angle = static_cast<int>(mRotation * 180.0 / M_PI);
  SDL_Point center = { centerX, centerY };
  SDL_Point points[4];

    SDL_RenderFillRect(mRenderer, &rect);
  }

private:
  SDL_Renderer* mRenderer;
  int mX;
  int mY;
  int mWidth;
  int mHeight;
  double mScaleX;
  double mScaleY;
  double mRotation;
};
