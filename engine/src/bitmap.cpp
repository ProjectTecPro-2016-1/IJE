#include "core/bitmap.h"
#include "core/rect.h"
#include "core/exception.h"
#include "core/environment.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

class Bitmap::Impl {
public:
// -------------------------------------------------------------
// Function: Impl()
// Description: Impl class builder where the initializations of the variables happen.
// Parameters:
//     void *data;        Description
//      int w;
//      int h;
//
// Return: void
// -------------------------------------------------------------
    Impl(void *data, int w, int h) : m_w(w), m_h(h) {
        m_bitmap = static_cast<SDL_Surface *>(data);
    }

// -------------------------------------------------------------
// Function: ~Impl()
// Description: Impl class destructor in which images files free themselves.
//
// Return: void
// -------------------------------------------------------------
    ~Impl() {
        if (m_bitmap) {
            SDL_FreeSurface(m_bitmap);
        } else {
            // Nothing to do
        }
    }

// -------------------------------------------------------------
// Function: w()
// Description:
//
// Return: int
// -------------------------------------------------------------
    int w() const  {
        return m_w;
    }

// -------------------------------------------------------------
// Function: h()
// Description:
//
// Return: int
// -------------------------------------------------------------
    int h() const {
        return m_h;
    }

    SDL_Surface * data() const {
        return m_bitmap;
    }

// -------------------------------------------------------------
// Function: pixels()
// Description:
//
// Return: void
// -------------------------------------------------------------
    void * pixels() const {
        return m_bitmap->pixels;
    }

// -------------------------------------------------------------
// Function: clear()
// Description:
//
// Return: void
// -------------------------------------------------------------
    void clear() {
        SDL_FillRect(m_bitmap, nullptr, 0);
    }

// -------------------------------------------------------------
// Function: fill()
// Description:
// Parameters:
//      const Rect&;        Description
//      Uint32 color;
//
// Return: void
// -------------------------------------------------------------
    void fill(const Rect& r, Uint32 color) {
        SDL_Rect rect { (int) r.x(), (int) r.y(), (int) r.w(), (int) r.h()
        };

        SDL_FillRect(m_bitmap, &rect, color);
    }

private:
    int m_w, m_h;
    SDL_Surface * m_bitmap;
};

// -------------------------------------------------------------
// Function:
// Description:
// Parameters:
//      int x;        Description
//
// Return: void
// -------------------------------------------------------------
Bitmap::Bitmap(void * data, int w, int h) : m_impl(new Impl(data, w, h)) {
}

// -------------------------------------------------------------
// Function:
// Description:
// Parameters:
//      int x;        Description
//
// Return: void
// -------------------------------------------------------------
Bitmap::Bitmap(Canvas * canvas) : m_impl(new Impl((void *) SDL_CreateRGBSurface(0, canvas->w(), canvas->h(), 32, 0, 0, 0, 0),
        canvas->w(), canvas->h())) {
}

// -------------------------------------------------------------
// Function:
// Description:
// Parameters:
//      int x;        Description
//
// Return: void
// -------------------------------------------------------------
Bitmap::~Bitmap() {
}

// -------------------------------------------------------------
// Function: data()
// Description:
//
// Return: void
// -------------------------------------------------------------
void * Bitmap::data() const {
    return m_impl->data();
}

// -------------------------------------------------------------
// Function: w()
// Description:
//
// Return: int
// -------------------------------------------------------------
int Bitmap::w() const {
    return m_impl->w();
}

// -------------------------------------------------------------
// Function: h()
// Description:
//
// Return: int
// -------------------------------------------------------------
int Bitmap::h() const {
    return m_impl->h();
}

Bitmap * Bitmap::from_file(const string& path) throw (Exception) {
    SDL_Surface *bitmap = IMG_Load(path.c_str());

    if (bitmap == nullptr) {
        throw Exception(SDL_GetError());
    } else {
            // Nothing to do
    }

    Bitmap * b = new Bitmap(bitmap, bitmap->w, bitmap->h);

    if (not b) {
        throw Exception("Out of memory for a new Bitmap");
    } else {
            // Nothing to do
    }

    return b;
}

// -------------------------------------------------------------
// Function: pixels()
// Description:
//
// Return: void
// -------------------------------------------------------------
void * Bitmap::pixels() const {
    return m_impl->pixels();
}

// -------------------------------------------------------------
// Function: clear()
// Description:
//
// Return: void
// -------------------------------------------------------------
void Bitmap::clear() {
    m_impl->clear();
}

// -------------------------------------------------------------
// Function:
// Description:
// Parameters:
//      int x;        Description
//
// Return: void
// -------------------------------------------------------------
Uint32 Bitmap::getpixel(SDL_Surface *surface, int x, int y) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 * p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        return * p;
        break;

    case 2:
        return * (Uint16 *)p;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            return p[0] << 16 | p[1] << 8 | p[2];
        } else {
            return p[0] | p[1] << 8 | p[2] << 16;
        }
        break;

    case 4:
        return * (Uint32 *)p;
        break;

    default:
        return 0;
    }
}

// -------------------------------------------------------------
// Function: putpixel()
// Description:
// Parameters:
//      SDL_Surface * surface;        Description
//      int x;
//      int y;
//      Uint32 pixel;
//
// Return: void
// -------------------------------------------------------------
void Bitmap::putpixel(SDL_Surface * surface, int x, int y, Uint32 pixel) {
    int bpp = surface->format->BytesPerPixel;
    Uint8 * p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

    switch (bpp) {
    case 1:
        * p = pixel;
        break;

    case 2:
        * (Uint16 *)p = pixel;
        break;

    case 3:
        if (SDL_BYTEORDER == SDL_BIG_ENDIAN) {
            p[0] = (pixel >> 16) & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = pixel & 0xff;
        } else {
            p[0] = pixel & 0xff;
            p[1] = (pixel >> 8) & 0xff;
            p[2] = (pixel >> 16) & 0xff;
        }
        break;

    case 4:
        * (Uint32 *)p = pixel;
        break;

    default:
        // Nothing to do
        break;
    }
}

// -------------------------------------------------------------
// Function: fill()
// Description:
// Parameters:
//      const Rect& r;        Description
//      Uint32 color;
//
// Return: void
// -------------------------------------------------------------
void Bitmap::fill(const Rect& r, Uint32 color) {
    m_impl->fill(r, color);
}
