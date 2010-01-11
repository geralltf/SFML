////////////////////////////////////////////////////////////
//
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
//
// This software is provided 'as-is', without any express or implied warranty.
// In no event will the authors be held liable for any damages arising from the use of this software.
//
// Permission is granted to anyone to use this software for any purpose,
// including commercial applications, and to alter it and redistribute it freely,
// subject to the following restrictions:
//
// 1. The origin of this software must not be misrepresented;
//    you must not claim that you wrote the original software.
//    If you use this software in a product, an acknowledgment
//    in the product documentation would be appreciated but is not required.
//
// 2. Altered source versions must be plainly marked as such,
//    and must not be misrepresented as being the original software.
//
// 3. This notice may not be removed or altered from any source distribution.
//
////////////////////////////////////////////////////////////

#ifndef SFML_WINDOWIMPL_HPP
#define SFML_WINDOWIMPL_HPP

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include <SFML/Config.hpp>
#include <SFML/System/NonCopyable.hpp>
#include <SFML/Window/Joystick.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/WindowHandle.hpp>
#include <set>
#include <string>


namespace sf
{
class Event;
class WindowListener;

namespace priv
{
////////////////////////////////////////////////////////////
/// \brief Abstract base class for OS-specific window implementation
///
////////////////////////////////////////////////////////////
class WindowImpl : NonCopyable
{
public :

    ////////////////////////////////////////////////////////////
    /// \brief Create a new window depending on the current OS
    ///
    /// \param mode  Video mode to use
    /// \param title Title of the window
    /// \param style Window style
    ///
    /// \return Pointer to the created window (don't forget to delete it)
    ///
    ////////////////////////////////////////////////////////////
    static WindowImpl* New(VideoMode mode, const std::string& title, unsigned long style);

    ////////////////////////////////////////////////////////////
    /// \brief Create a new window depending on to the current OS
    ///
    /// \param handle Platform-specific handle of the control
    ///
    /// \return Pointer to the created window (don't forget to delete it)
    ///
    ////////////////////////////////////////////////////////////
    static WindowImpl* New(WindowHandle handle);

public :

    ////////////////////////////////////////////////////////////
    /// \brief Destructor
    ///
    ////////////////////////////////////////////////////////////
    virtual ~WindowImpl();

    ////////////////////////////////////////////////////////////
    /// \brief Add a listener to the window
    ///
    /// \param listener Listener to add
    ///
    ////////////////////////////////////////////////////////////
    void AddListener(WindowListener* listener);

    ////////////////////////////////////////////////////////////
    /// \brief Remove a listener from the window
    ///
    /// \param listener Listener to remove
    ///
    ////////////////////////////////////////////////////////////
    void RemoveListener(WindowListener* listener);

    ////////////////////////////////////////////////////////////
    /// \brief Get the client width of the window
    ///
    /// \return Width of the window in pixels
    ///
    ////////////////////////////////////////////////////////////
    unsigned int GetWidth() const;

    ////////////////////////////////////////////////////////////
    /// \brief Get the client height of the window
    ///
    /// \return Height of the window in pixels
    ///
    ////////////////////////////////////////////////////////////
    unsigned int GetHeight() const;

    ////////////////////////////////////////////////////////////
    /// \brief Change the joystick threshold, ie. the value below which
    ///        no move event will be generated
    ///
    /// \param threshold : New threshold, in range [0, 100]
    ///
    ////////////////////////////////////////////////////////////
    void SetJoystickThreshold(float threshold);

    ////////////////////////////////////////////////////////////
    /// \brief Process incoming events from the operating system
    ///
    /// \param block Use true to block the thread until an event arrives
    ///
    ////////////////////////////////////////////////////////////
    void DoEvents(bool block);

    ////////////////////////////////////////////////////////////
    /// \brief Get the OS-specific handle of the window
    ///
    /// \return Handle of the window
    ///
    ////////////////////////////////////////////////////////////
    virtual WindowHandle GetHandle() const = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Show or hide the mouse cursor
    ///
    /// \param show True to show, false to hide
    ///
    ////////////////////////////////////////////////////////////
    virtual void ShowMouseCursor(bool show) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Change the position of the mouse cursor
    ///
    /// \param left Left coordinate of the cursor, relative to the window
    /// \param top  Top coordinate of the cursor, relative to the window
    ///
    ////////////////////////////////////////////////////////////
    virtual void SetCursorPosition(unsigned int left, unsigned int top) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Change the position of the window on screen
    ///
    /// \param left Left position
    /// \param top  Top position
    ///
    ////////////////////////////////////////////////////////////
    virtual void SetPosition(int left, int top) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Change the size of the rendering region of the window
    ///
    /// \param width  New width, in pixels
    /// \param height New height, in pixels
    ///
    ////////////////////////////////////////////////////////////
    virtual void SetSize(unsigned int width, unsigned int height) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Show or hide the window
    ///
    /// \param show True to show, false to hide
    ///
    ////////////////////////////////////////////////////////////
    virtual void Show(bool show) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Enable or disable automatic key-repeat
    ///
    /// \param enabled True to enable, false to disable
    ///
    ////////////////////////////////////////////////////////////
    virtual void EnableKeyRepeat(bool enabled) = 0;

    ////////////////////////////////////////////////////////////
    /// \brief Change the window's icon
    ///
    /// \param width  Icon's width, in pixels
    /// \param height Icon's height, in pixels
    /// \param pixels Pointer to the pixels in memory, format must be RGBA 32 bits
    ///
    ////////////////////////////////////////////////////////////
    virtual void SetIcon(unsigned int width, unsigned int height, const Uint8* pixels) = 0;

protected :

    ////////////////////////////////////////////////////////////
    /// \brief Default constructor
    ///
    ////////////////////////////////////////////////////////////
    WindowImpl();

    ////////////////////////////////////////////////////////////
    /// \brief Send an event to listeners (for derived classes only)
    ///
    /// \param event Event to send
    ///
    ////////////////////////////////////////////////////////////
    void SendEvent(const Event& event);

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    unsigned int myWidth;  ///< Internal width of the window
    unsigned int myHeight; ///< Internal height of the window

private :

    ////////////////////////////////////////////////////////////
    /// \brief Read the joysticks state and generate the appropriate events
    ///
    ////////////////////////////////////////////////////////////
    void ProcessJoystickEvents();

    ////////////////////////////////////////////////////////////
    /// \brief Process incoming events from the operating system
    ///
    /// \param block Use true to block the thread until an event arrives
    ///
    ////////////////////////////////////////////////////////////
    virtual void ProcessEvents(bool block) = 0;

    ////////////////////////////////////////////////////////////
    // Member data
    ////////////////////////////////////////////////////////////
    std::set<WindowListener*> myListeners;             ///< Array of listeners connected to the window
    Joystick                  myJoysticks[Joy::Count]; ///< Joysticks to observe
    JoystickState             myJoyStates[Joy::Count]; ///< Current states of the joysticks
    float                     myJoyThreshold;          ///< Joystick threshold (minimum motion for MOVE event to be generated)
};

} // namespace priv

} // namespace sf


#endif // SFML_WINDOWIMPL_HPP
