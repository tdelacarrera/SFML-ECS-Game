#pragma once

#include "../engine/gui/guiView.h"

class GameHUD : public GuiView
{
public:
    void build(tgui::SFML_GRAPHICS::Gui& gui) override;
    void destroy(tgui::SFML_GRAPHICS::Gui& gui) override;

private:
    tgui::Button::Ptr testButton_;
};