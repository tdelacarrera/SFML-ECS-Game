#pragma once

#include "../engine/gui/guiView.h"

class TestView : public GuiView
{
public:
    void build(tgui::SFML_GRAPHICS::Gui& gui) override;
    void destroy(tgui::SFML_GRAPHICS::Gui& gui) override;

private:
    tgui::Button::Ptr testButton_;
    tgui::Button::Ptr testButton2_;
};