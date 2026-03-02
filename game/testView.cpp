#include "testView.h"
#include <iostream>

void TestView::build(tgui::SFML_GRAPHICS::Gui& gui)
{
    testButton_ = tgui::Button::create("Click");
    testButton_->setSize(200, 50);
    testButton_->setPosition(50, 50);

    testButton_->onPress([]()
    {
        std::cout << "pressed\n";
    });

    gui.add(testButton_);


    testButton_ = tgui::Button::create("Click button 2");
    testButton_->setSize(200, 50);
    testButton_->setPosition(50, 250);

    testButton_->onPress([]()
    {
        std::cout << "pressed button 2\n";
    });

    gui.add(testButton_);
}

void TestView::destroy(tgui::SFML_GRAPHICS::Gui& gui)
{
    gui.remove(testButton_);
}
