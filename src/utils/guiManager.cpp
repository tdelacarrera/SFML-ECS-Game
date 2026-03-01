#include "guiManager.h"

GuiManager::GuiManager(sf::RenderWindow& window)
    : window_(window)
{
    gui_.setTarget(window_);
}

void GuiManager::setView(std::unique_ptr<GuiView> view)
{
    if (currentView_)
        currentView_->destroy(gui_);

    currentView_ = std::move(view);

    if (currentView_)
        currentView_->build(gui_);
}

void GuiManager::render()
{
    gui_.draw();
}

void GuiManager::processEvent(const sf::Event& event)
{
    gui_.handleEvent(event); 
}