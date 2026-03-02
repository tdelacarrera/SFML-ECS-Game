#pragma once

#include <TGUI/Backend/SFML-Graphics.hpp>
#include <SFML/Graphics.hpp>
#include "guiView.h"

class GuiManager
{
public:
    GuiManager(sf::RenderWindow& window);
    void render();
    void processEvent(const sf::Event& event);
    void setView(std::unique_ptr<GuiView> view);

private:
    sf::RenderWindow& window_;
    tgui::SFML_GRAPHICS::Gui gui_;
    std::unique_ptr<GuiView> currentView_;
};