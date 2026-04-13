#pragma once

enum class ToolMode
{
    None,
    Mine,
    Chop,
    Harvest,
    Cancel,
    PaintTile,
};

struct ToolState
{
    ToolMode current = ToolMode::None;
    int selectedTile = 0;
};
