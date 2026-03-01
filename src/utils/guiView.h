#pragma once
#include <TGUI/TGUI.hpp>
#include <TGUI/Backend/SFML-Graphics.hpp>

class GuiView
{
public:
    virtual ~GuiView() = default;

    virtual void build(tgui::SFML_GRAPHICS::Gui& gui) = 0;
    virtual void destroy(tgui::SFML_GRAPHICS::Gui& gui) = 0;
};