//
//  Logging.cpp
//  MakeEngine
//
//  Created by Make100Games on 02.02.26.
//

#include "Logging.hpp"

std::ostream& operator<<(std::ostream& os, KeyInteraction interaction) {
    switch (interaction) {
    case KeyInteraction::KeyDown:    return os << "KeyDown";
    case KeyInteraction::KeyUp: return os << "KeyUp";
    default:             return os << "Unknown";
    }
}

std::ostream& operator<<(std::ostream& os, KeyCode keyCode) {
    switch (keyCode) {
    case KeyCode::LeftArrow:    return os << "LeftArrow";
    case KeyCode::RightArrow: return os << "RightArrow";
    case KeyCode::UpArrow: return os << "UpArrow";
    case KeyCode::DownArrow: return os << "DownArrow";
    case KeyCode::Space: return os << "Space";
    default:             return os << "Unknown";
    }
}

std::ostream& operator<<(std::ostream& os, const KeyInput& input) {
    return os << "Interaction: " << input.interaction << ", KeyCode: " << input.keyCode;
}
