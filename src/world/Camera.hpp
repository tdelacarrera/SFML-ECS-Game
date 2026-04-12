#pragma once

class Camera
{
public:
    void move(const sf::Vector2f &delta)
    {
        target += delta;
    }
    void setTarget(const sf::Vector2f &pos)
    {
        target = pos;
    }

    void update(float dt)
    {
        sf::Vector2f current = view.getCenter();
        view.setCenter(current + (target - current) * 5.f * dt);
    }

    const sf::View &getView() const { return view; }

    void setSize(const sf::Vector2f &size)
    {
        baseSize = size;
        zoomLevel = 1.f;
        view.setSize(baseSize);
    }

    void addZoom(float delta)
    {
        zoomLevel -= delta * 0.1f;
        zoomLevel = std::clamp(zoomLevel, 0.5f, 3.0f);

        view.setSize(baseSize * zoomLevel);
    }

private:
    sf::View view;
    sf::Vector2f target;
    sf::Vector2f baseSize;
    float zoomLevel = 1.f;
};