#include "gameHUD.h"
#include <iostream>

void GameHUD::build(tgui::SFML_GRAPHICS::Gui& gui)
{
    testButton_ = tgui::Button::create("Click");
    testButton_->setSize(200, 50);
    testButton_->setPosition(50, 50);

    testButton_->onPress([]()
    {
        std::cout << "pressed\n";
    });

    gui.add(testButton_);
}

void GameHUD::destroy(tgui::SFML_GRAPHICS::Gui& gui)
{
    gui.remove(testButton_);
}
