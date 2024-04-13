#pragma once

#include "ImFx/ImFx.h"
#include "ImGui/DroidSans.hpp"
#include "ImGui/imgui_impl_dx11.h"
#include "ImGui/imgui_impl_win32.h"

#include <string>
#include <functional>

#undef min
#undef max
#include <algorithm>

class Renderer {
private:
    static bool initialized;
    static ImDrawList* drawList;
private:
    static IDXGISwapChain3* sc;
private:
    static ID3D11DeviceContext* context;
    static ID3D11Texture2D* backBuffer;
    static IDXGISurface* surfaceBuffer;
    static ID3D11RenderTargetView* tv;
public:
    static auto getSCVtable(void) -> unsigned long long*;
    static auto getWindow(void) -> HWND;
public:
    static auto init(IDXGISwapChain3*, ID3D11Device*) -> bool;
    static auto cleanup(bool) -> void;
public:
    static auto newFrame(void) -> void;
    static auto endFrame(void) -> void;
public:
    static auto setDrawList(ImDrawList*) -> void;
public:
    static auto getTextSize(std::string, float) -> ImVec2;
    static auto getTextW(std::string, float) -> float;
    static auto getTextH(std::string, float) -> float;
public:
    static auto drawText(ImVec2, std::string, float, ImColor) -> void;
public:
    static auto addRect(ImVec4, ImColor, float, float) -> void;
    static auto fillRect(ImVec4, ImColor, float) -> void;
};

class LiteRender {
public:
    class Element {
        public:
            class ElementStyle {
                private:
                    ImColor bg_color, outline_color;
                    ImColor hoverColor;
                public:
                    auto setBgColor(const ImColor& color) -> void { this->bg_color = color; };
                    auto setBgColor(float r, float g, float b, float a = 1.f) -> void { this->bg_color = ImColor(r, g, b, a); };
                    auto getBgColor(void) -> ImColor& { return this->bg_color; };
                public:
                    auto setOutlineColor(const ImColor& color) -> void { this->outline_color = color; };
                    auto setOutlineColor(float r, float g, float b, float a = 1.f) -> void { this->outline_color = ImColor(r, g, b, a); };
                    auto getOutlineColor(void) -> ImColor& { return this->outline_color; };
                public:
                    auto setHoverColor(const ImColor& color) -> void { this->hoverColor = color; };
                    auto setHoverColor(float r, float g, float b, float a = 1.f) -> void { this->hoverColor = ImColor(r, g, b, a); };
                    auto getHoverColor(void) -> ImColor& { return this->hoverColor; };
                public:
                    ElementStyle(ImColor bgColor, ImColor outlineColor = ImColor(0.f, 0.f, 0.f)) : bg_color(bgColor), outline_color(outlineColor) {};
            };
        private:
            ElementStyle elStyle;
        public:
            auto style(void) -> ElementStyle& { return this->elStyle; };
        public:
            class ElementDisplay {
                private:
                    std::string display_text;
                    ImColor text_color;
                    float font_size;
                public:
                    auto getColor(void) -> ImColor& { return this->text_color; };
                    auto setColor(const ImColor& color) -> void { this->text_color = color; };
                public:
                    auto getText(void) -> std::string& { return this->display_text; };
                    auto setText(std::string text) -> void { this->display_text = text.c_str(); };
                public:
                    auto getFontSize(void) -> float { return this->font_size; };
                    auto setFontSize(float fontSize) { this->font_size = fontSize; };
                public:
                    ElementDisplay(std::string text, ImColor color, float fontSize = 18.f) : display_text(text), text_color(color), font_size(fontSize) {};
                    ~ElementDisplay(void) { this->display_text.clear(); };
            };
        private:
            ElementDisplay elDisplay;
        public:
            auto display(void) -> ElementDisplay& { return this->elDisplay; };
        public:
            enum class ElementType {
                Unknown = 0,
                Base = 1,
                
                Text = 2,
                Button = 3
            };
        private:
            ElementType elType;
        public:
            auto getType(void) -> ElementType& { return this->elType; };
        public:
            Element(ElementDisplay display, ElementStyle style, ElementType type = ElementType::Base) : elDisplay(display), elStyle(style), elType(type) {};
            virtual ~Element() = default;
    };
public:
    class Container {
        private:
            ImVec4 boundsRect;
            ImVec2 tPos;
        private:
            Element* el = nullptr;
        public:
            Container(Element* element, ImVec2 pos = ImVec2(0.f, 0.f)) : el(element), tPos(pos) {};
            ~Container(void);
        public:
            auto get(void) -> Element* { return this->el; };
        public:
            auto style(void) -> Element::ElementStyle& { return this->el->style(); };
            auto display(void) -> Element::ElementDisplay& { return this->el->display(); };
        public:
            auto getType(void) -> Element::ElementType& { return this->el->getType(); };
        public:
            auto getSpace(void) -> float { return (this->display().getFontSize() / 10.f) + 4.f; };
            auto getSize(void) -> ImVec2 { auto& disp = this->display(); return Renderer::getTextSize(disp.getText(), disp.getFontSize()); };
        public:
            auto setPos(ImVec2 pos) -> void { this->tPos = pos; };
            auto setPos(float x = 0.f, float y = 0.f) -> void { this->tPos = ImVec2(x, y); };
        public:
            auto getBounds(void) -> ImVec4 { return this->boundsRect; };
            auto updateBounds(void) -> void;
        public:
            auto getRenderPos(void) -> ImVec2;
        public:
            auto render(void) -> void;
    };
public:
    class Frame {
        private:
            ImVec4 boundsRect;
            ImVec2 tPos;
        private:
            float font_size;
        public:
            std::vector<Container*> elements;
        public:
            Frame(std::vector<Container*> elements_list, float font_size = 18.f);
            ~Frame(void);
        public:
            auto setFontSize(float fontSize) -> void;
        public:
            auto setPos(ImVec2 pos) -> void { this->tPos = pos; };
            auto setPos(float x = 0.f, float y = 0.f) -> void { this->tPos = ImVec2(x, y); };
        public:
            auto getSpace(void) -> float { return (this->font_size / 10.f) + 4.f; };
        public:
            auto getBounds(void) -> ImVec4 { return this->boundsRect; };
            auto updateBounds(void) -> void;
        public:
            auto setStylesAll(LiteRender::Element::ElementStyle styles) -> void { for(auto el : this->elements) { auto& style = el->style(); style.setBgColor(styles.getBgColor()); style.setOutlineColor(styles.getOutlineColor()); }; };
            auto setStylesFor(LiteRender::Element::ElementType type, LiteRender::Element::ElementStyle styles) -> void { for(auto el : this->elements) { if(el->getType() == type) { auto& style = el->style(); style.setBgColor(styles.getBgColor()); style.setOutlineColor(styles.getOutlineColor()); }; }; };
        public:
            auto render(void) -> void;
    };
public:
    class Window {
        private:
            std::string title_text;
            float font_size;
        private:
            ImVec4 boundsRect;
            ImVec2 tPos;
        private:
            LiteRender::Element::ElementStyle styles = LiteRender::Element::ElementStyle(ImColor(), ImColor());
        public:
            std::vector<Frame*> frames;
        public:
            Window(std::string titleText, float fontSize = 18.f, std::vector<Frame*> framesList = {});
            ~Window(void);
        public:
            auto getWindowStyles(void) -> LiteRender::Element::ElementStyle& { return this->styles; };
            auto setWindowStyles(LiteRender::Element::ElementStyle style) -> void { this->styles = style; };
        public:
            auto setFontSize(float fontSize) -> void;
        public:
            auto setPos(ImVec2 pos) -> void { this->tPos = pos; };
            auto setPos(float x = 0.f, float y = 0.f) -> void { this->tPos = ImVec2(x, y); };
        public:
            auto getSpace(void) -> float { return (this->font_size / 10.f) + 4.f; };
        public:
            auto getBounds(void) -> ImVec4 { return this->boundsRect; };
            auto updateBounds(void) -> void;
        public:
            auto setStylesAll(LiteRender::Element::ElementStyle styles) -> void { for(auto frame : this->frames) { frame->setStylesAll(styles); }; };
            auto setStylesFor(LiteRender::Element::ElementType type, LiteRender::Element::ElementStyle styles) -> void { for(auto frame : this->frames) { frame->setStylesFor(type, styles); }; };
        public:
            auto render(void) -> void;
    };
public:
    class Text : public Element {
        public:
            Text(std::string text, ImColor textColor = ImColor(255.f, 255.f, 255.f)) : Element(ElementDisplay(text, textColor), ElementStyle(ImColor(0.f, 0.f, 0.f, 0.f), ImColor(0.f, 0.f, 0.f, 0.f)), ElementType::Text) {};
        public:
            auto getText(void) -> std::string& { return this->display().getText(); };
            auto getTextWidth(void) -> float { return Renderer::getTextW(this->getText(), display().getFontSize()); };
            auto getTextHeight(void) -> float { return Renderer::getTextH(this->getText(), display().getFontSize()); };
        public:
            auto getColor(void) -> ImColor& { return this->display().getColor(); };
    };
public:
    class Button : public Element {
        public:
            Button(std::string text, ImColor textColor, std::function<void(char, bool)> callback = [=](char, bool) -> void {}) : Element(ElementDisplay(text, textColor), ElementStyle(ImColor(24.f, 115.f, 201.f), ImColor(48.f, 67.f, 97.f)), ElementType::Button), onClick(callback) {};
        private:
            std::function<void(char, bool)> onClick;
    };
};