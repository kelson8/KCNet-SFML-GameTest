#include "input_handler.h"

InputHandler::InputHandler() :
    m_MaxControllerButtons(16)
{

}

InputHandler::~InputHandler()
{

}

/**
 * @brief Handle controller input for the game
 *
 * TODO Fix this to work with the left/right sticks being moved.
 * Fix the DPad, and fix L2/R2, they don't work either.
 */
void InputHandler::HandleControllerInput() const
{
    // Loop through the amount of buttons
    for (unsigned int button = 0; button < m_MaxControllerButtons; ++button)
    {
        if (sf::Joystick::isButtonPressed(0, button)) // Check if button is pressed
        {
            switch (static_cast<JoystickButton>(button))
            {
            case JoystickButton::A:
                //fmt::println("A Button pressed");
                break;
            case JoystickButton::B:
                //fmt::println("B Button pressed");
                break;
            case JoystickButton::X:
                //fmt::println("X Button pressed");
                break;
            case JoystickButton::Y:
                //fmt::println("Y Button pressed");
                break;
            case JoystickButton::L1:
                //fmt::println("L1 Button pressed");
                break;
            case JoystickButton::R1:
                //fmt::println("R1 Button pressed");
                break;

            case JoystickButton::SELECT:
                //fmt::println("Select Button pressed");
                break;
            case JoystickButton::START:
                //fmt::println("Start Button pressed");
                break;

                // Pressing on left/right analog sticks
            case JoystickButton::LSTICK:
                fmt::println("Left stick button pressed");
                break;
            case JoystickButton::RSTICK:
                fmt::println("Right stick button pressed");
                break;

            default:
                fmt::println("Button #{} has been pressed", button);
                // Handle other buttons or do nothing
                break;
            }
        }
    }
}