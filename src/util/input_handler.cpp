#include "input_handler.h"

#ifdef _IMGUI_TEST
#include <imgui-SFML.h>
#include <imgui.h>
#include "util/imgui_setup.h"
#include "menus/debug/imgui_menu.h"
#endif // _IMGUI_TEST

#include "game.h"

#include "player.h"
#include "enemy.h"

InputHandler::InputHandler() :
    m_MaxControllerButtons(16)
{

}

InputHandler::~InputHandler()
{

}

/**
 * @brief Run the main loop for the input handler.
 */
void InputHandler::Run()
{
    HandleAllInput();
}

/**
 * @brief Handle mouse/keyboard input, and handle controller input.
 */
void InputHandler::HandleAllInput()
{
    WindowManager& windowManager = WindowManager::getInstance();

    Player& player = Player::getInstance();
#ifdef _IMGUI_TEST
    ImGuiMenu& imGuiMenu = ImGuiMenu::getInstance();
#endif // _IMGUI_TEST
    Game& game = Game::getInstance();
    Enemy& enemy = Enemy::getInstance();

    InputHandler& inputHandler = InputHandler::getInstance();

    while (const std::optional<sf::Event> event = windowManager.getWindow().pollEvent())
    {
#ifdef _IMGUI_TEST
        // Process ImGui events if enabled.
        ImGui::SFML::ProcessEvent(windowManager.getWindow(), *event);
#endif // _IMGUI_TEST

        // Close the window if the event type is set to closed.
        if (event->is<sf::Event::Closed>())
        {
            windowManager.close();
        }
        
        //------
        // Handle inputs
        //------

        //------
        // Controller input
        //------
        else if (const auto* controllerButtonPressed = event->getIf<sf::Event::JoystickButtonPressed>())
        {
            // This is disabled for now.
            // https://www.sfml-dev.org/tutorials/3.0/window/inputs/#joystick
            //if (sf::Joystick::isConnected(0))
            //{
                //inputHandler.HandleControllerInput();
            //}
        }

        //------
        // Keyboard input
        //------
        else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
        {
            // I figured out the switch statement for this! I had to change the settings
            // For my key handling, and switch from keyPressed->scancode to keyPressed-Code.
            switch (keyPressed->code)
            {
                //------
                // Pause the game
                //------

            case KeyCodes::Key_Escape:
                game.setPaused(!game.getPaused());
                break;

                //------
                // Move keys
                // These check if the game is paused, and if the end screen is shown.
                // Otherwise it doesn't update the values.
                //------

                // Move Up
            case KeyCodes::Key_W:
                if (game.getPaused() || game.getEndScreen()) return;
                player.Move(0.f, -player.GetMoveSpeed());
                break;

                // Move Down
            case KeyCodes::Key_S:
                if (game.getPaused() || game.getEndScreen()) return;
                player.Move(player.GetMoveSpeed(), 0.f); // Move down
                break;

                // Move Left
            case KeyCodes::Key_A:
                if (game.getPaused() || game.getEndScreen()) return;
                player.Move(-player.GetMoveSpeed(), 0.f); // Move left
                break;

                // Move right
            case KeyCodes::Key_D:
                if (game.getPaused() || game.getEndScreen()) return;
                player.Move(0.f, player.GetMoveSpeed());
                break;


                // If the player is on the end screen, respawn them.
            case KeyCodes::Key_Enter:
                if (game.getEndScreen())
                {
                    player.Respawn();
                }
                break;

                //------
                // Debug Keys
                //------

            case KeyCodes::Key_B:

                // Game::getInstance().setEndGame(true);
                // std::cout << "Game ended with 'B' key" << std::endl;
                break;

                // ImGui Key
#ifdef _IMGUI_TEST
            case KeyCodes::Key_F2:
                imGuiMenu.SetStatus(!imGuiMenu.GetStatus());
                break;
#endif // _IMGUI_TEST

                //------
                // Close the game
                //------

            case KeyCodes::Key_F4:
                windowManager.close();
                break;
            }
        }
    }
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