#include "colors.hpp"

const Color abyss  = { 11,  16,  38, 255 }; // Background
const Color red    = { 255,   0,   0, 255 };
const Color blue   = {   0,   0, 255, 255 };
const Color yellow = { 255, 255,   0, 255 };
const Color white  = { 255, 255, 255, 255 };
const Color green  = {   0, 255,   0, 255 };
const Color purple = { 128,   0, 128, 255 };
const Color orange = { 255, 165,   0, 255 };

std::vector<Color>getCellColors()
{
     return {
        {11, 16, 38, 255},    // Abyss color for back ground
        {255, 0, 0, 255},     // Red
        {0, 0, 255, 255},     // Blue
        {255, 255, 0, 255},   // Yellow
        {255, 255, 255, 255}, // White
        {0, 255, 0, 255},     // green
        {128, 0, 128, 255},   // Purple
        {255, 165, 0, 255}    // Orange
    };
}