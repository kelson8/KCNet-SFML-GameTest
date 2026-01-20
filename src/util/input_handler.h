#pragma once
#include "pch.h"

/**
 * @brief List of JoystickButtons for SFML
 *
 * The L2 and R2 buttons don't seem to work, some of them do, besides moving the sticks, DPAD, and pressing the sticks.
 */
enum class JoystickButton
{
    A = 0,
    B,
    X,
    Y,
    L1,
    R1,

    SELECT,
    START,

    LSTICK,
    RSTICK,
};

class InputHandler
{
public:
    static InputHandler& getInstance()
    {
        static InputHandler instance; // Guaranteed to be destroyed.
        return instance;
    }

    void HandleControllerInput() const;

private:
    InputHandler();
    ~InputHandler();

    InputHandler(const InputHandler&) = delete; // Prevent copying
    InputHandler& operator=(const InputHandler&) = delete; // Prevent assignments

    int m_MaxControllerButtons;
};

