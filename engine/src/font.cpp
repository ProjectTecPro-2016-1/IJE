#include "core/environment.h"
#include "core/font.h"
#include "core/settings.h"

class Font::Impl {
    public:
                
        // -------------------------------------------------------------  
        // Function: Impl()  
        // Description: Implements a loaded font of a file.
        // Parameters:
        //      TTF_Font *font;         Font from file
        //      const string& path;     
        //      int size;               Font size
        // -------------------------------------------------------------   
        Impl(TTF_Font *font, const string& path, int size)
            : m_font(font), m_path(path), m_size(size), m_style(NORMAL) {
        }


        // -------------------------------------------------------------  
        // Function: ~Impl()
        // Description: Destructor of Impl class.
        // -------------------------------------------------------------   
        ~Impl() {
            if (m_font) {
                TTF_CloseFont(m_font);
            }else {
                // Nothing to do
            }
        }

        // -------------------------------------------------------------  
        // Function: font()  
        // Description: Returns the font file.
        // Return: m_font
        // -------------------------------------------------------------   
        TTF_Font * font() const {
            return m_font;
        }

        
        // -------------------------------------------------------------  
        // Function: size()  
        // Description: Returns the font size.
        // Return: m_size
        // -------------------------------------------------------------   
        int size() const {
            return m_size;
        }

        
        // -------------------------------------------------------------  
        // Function: style()  
        // Description: Returns the font style.
        // Return: m_style
        // -------------------------------------------------------------   
        Style style() const {
            return m_style;
        }

        
        // -------------------------------------------------------------  
        // Function: set_size()  
        // Description: Set the font size.
        // Parameters:
        //      int size;         Escrever aqui
        // Return: void
        // -------------------------------------------------------------   
        void set_size(int size) {
            Environment *env = Environment::get_instance();
            shared_ptr<Settings> settings = env->resources_manager->get_settings(env->m_settings_path);
            double k = settings->read<double>("Game", "scale", 1);

            change_size(size * k);
        }

        
        // -------------------------------------------------------------  
        // Function: set_style()  
        // Description: Set the font style.
        // Parameters:
        //      Style style;         Type of font, like bold, italic or
        //                           normal.
        // Return: void
        // -------------------------------------------------------------   
        void set_style(Style style) {
            switch (style) {
                case BOLD:
                    TTF_SetFontStyle(m_font, TTF_STYLE_BOLD);
                    break;

                case ITALIC:
                    TTF_SetFontStyle(m_font, TTF_STYLE_ITALIC);
                    break;

                default:
                    TTF_SetFontStyle(m_font, TTF_STYLE_NORMAL);
                    break;
            }
        }

    private:
        TTF_Font *m_font;
        string m_path;
        int m_size;
        Style m_style;

        // -------------------------------------------------------------  
        // Function: change_size()  
        // Description: Change the font size.
        // Parameters:
        //      int size;         Font size.
        // Return: void
        // -------------------------------------------------------------   
        void change_size(int size) {
            if (m_size == size) {
                return;
            } else {
                // Nothing to do
            }

            TTF_Font *font = TTF_OpenFont(m_path.c_str(), size);

            if (not font) {
                return;
            } else {
                // Nothing to do
            }

            TTF_CloseFont(m_font);
            m_font = font;
            m_size = size;
        }
};

// -------------------------------------------------------------  
// Function: Font()  
// Description: Implements font according the attributes.
// Parameters:
//      TTF_Font *font;         Font from file
//      const string& path;             
//      int size                Font size
// -------------------------------------------------------------   
Font::Font(TTF_Font *font, const string& path, int size)
    : m_impl(new Font::Impl(font, path, size)) {
}


// -------------------------------------------------------------  
// Function: ~Font()  
// Observations:
//      Funtion not implemented        
// -------------------------------------------------------------   
Font::~Font() {
}

// -------------------------------------------------------------  
// Function: from_file()  
// Description: Get the font from file.
// Parameters:
//      const string& path;     
// Return: Font *
// -------------------------------------------------------------   
Font * Font::from_file(const string& path) throw (Exception) {
    TTF_Font *font = TTF_OpenFont(path.c_str(), 20);

    if (not font) {
        throw Exception(TTF_GetError());
    } else {
        // Nothing to do
    }

    return new Font(font, path);
}

// -------------------------------------------------------------  
// Function: font()
// Description: Implements a font.
// Return: m_impl->font
// -------------------------------------------------------------   
TTF_Font * Font::font() const {
    return m_impl->font();
}

// -------------------------------------------------------------  
// Function: size()  
// Description: Returns the font size.
// Return: m_impl->size
// -------------------------------------------------------------   
int Font::size() const {
    return m_impl->size();
}

// -------------------------------------------------------------  
// Function: style()  
// Description: Returns the font style.
// Return: m_impl->style
// -------------------------------------------------------------   
Font::Style Font::style() const {
    return m_impl->style();
}

// -------------------------------------------------------------  
// Function: set_size()  
// Description: Set the font size.
// Parameters:
//      int size;     Font size
// Return: void
// -------------------------------------------------------------   
void Font::set_size(int size) {
    m_impl->set_size(size);
}

// -------------------------------------------------------------  
// Function: set_style()  
// Description: Set the font style.
//      Style style;         Type of font, like bold, italic or
//                           normal.    
// Return: void
// -------------------------------------------------------------   
void Font::set_style(Style style) {
    m_impl->set_style(style);
}   