#pragma once

enum class ToolMode
{
    None,
    Chop,
    Mine,
    Harvest,
    Build,
    Cancel,
    ZoneStorage
};

struct ToolState
{
    ToolMode current = ToolMode::None;
};

struct ResourceData
{
    int wood = 0;
    int food = 0;
    int stone = 0;
};