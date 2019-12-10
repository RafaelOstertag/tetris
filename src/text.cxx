#include "text.hh"

#include <cassert>
#include <stdexcept>

Text::Text(const std::string& ttfFilepath, int size, int x, int y,
           const Color& color, const std::string& text)
    : font{nullptr}, texture{nullptr}, color{color}, text{text}, rectangle{x, y,
                                                                           -1,
                                                                           -1} {
    font = TTF_OpenFont(ttfFilepath.c_str(), size);
    if (font == nullptr) {
        std::string errmsg{"Cannot load font: "};
        throw std::invalid_argument(errmsg + SDL_GetError());
    }
}

Text::Text(Text&& o)
    : font{o.font}, texture{o.texture}, color{o.color}, text{std::move(o.text)},
      rectangle{o.rectangle} {
    font = nullptr;
    texture = nullptr;
}

Text& Text::operator=(Text&& o) {
    font = o.font;
    o.font = nullptr;

    texture = o.texture;
    o.texture = nullptr;

    color = o.color;
    text = std::move(o.text);
    rectangle = o.rectangle;

    return *this;
}

Text::~Text() {
    if (font) {
        TTF_CloseFont(font);
    }

    freeTexture();
}

void Text::setText(const std::string& text) {
    if (this->text == text) {
        return;
    }
    this->text = text;

    freeTexture();
}

void Text::render(const Renderer& renderer) {
    if (texture == nullptr) {
        textToTexture(renderer);
    }

    assert(rectangle.w > 0);
    assert(rectangle.h > 0);
    SDL_RenderCopy(renderer, texture, nullptr, &rectangle);
}

void Text::freeTexture() {
    if (texture) {
        SDL_DestroyTexture(texture);
        texture = nullptr;
    }
}

void Text::textToTexture(const Renderer& renderer) {
    assert(texture == nullptr);
    SDL_Surface* textSurface =
        TTF_RenderText_Blended(font, text.c_str(), color);
    if (textSurface == nullptr) {
        std::string errorMsg{"Unable to render text surface: "};
        throw std::runtime_error(errorMsg + TTF_GetError());
    }

    rectangle.w = textSurface->w;
    rectangle.h = textSurface->h;

    texture = SDL_CreateTextureFromSurface(renderer, textSurface);
    if (texture == nullptr) {
        std::string errorMsg{"Unable to create texture from rendered text: "};
        throw std::runtime_error(errorMsg + SDL_GetError());
    }

    SDL_FreeSurface(textSurface);
}
