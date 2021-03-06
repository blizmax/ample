#pragma once

#include <SDL2/SDL.h>
#include <algorithm>
#include <memory>
#include <unordered_map>
#include <vector>

#include "EventHandler.h"
#include "EventManager.h"
#include "Noncopyable.h"
#include "Singleton.h"
#include "Vector2d.h"
#include "Window.h"

namespace ample::control
{
using Event = SDL_Event;

class KeyboardManager final : public EventHandler
{
public:
    enum scancodes
    {
        C_TAB = SDL_SCANCODE_TAB,
        C_LEFT = SDL_SCANCODE_LEFT,
        C_RIGHT = SDL_SCANCODE_RIGHT,
        C_UP = SDL_SCANCODE_UP,
        C_DOWN = SDL_SCANCODE_DOWN,
        C_PAGEUP = SDL_SCANCODE_PAGEUP,
        C_PAGEDOWN = SDL_SCANCODE_PAGEDOWN,
        C_HOME = SDL_SCANCODE_HOME,
        C_END = SDL_SCANCODE_END,
        C_INSERT = SDL_SCANCODE_INSERT,
        C_DELETE = SDL_SCANCODE_DELETE,
        C_BACKSPACE = SDL_SCANCODE_BACKSPACE,
        C_SPACE = SDL_SCANCODE_SPACE,
        C_ENTER = SDL_SCANCODE_RETURN,
        C_ESCAPE = SDL_SCANCODE_ESCAPE,
        C_KP_ENTER = SDL_SCANCODE_KP_ENTER,
        C_LSHIFT = SDL_SCANCODE_LSHIFT,
        C_RSHIFT = SDL_SCANCODE_RSHIFT,
        C_LCTRL = SDL_SCANCODE_LCTRL,
        C_RCTRL = SDL_SCANCODE_RCTRL,
        C_LALT = SDL_SCANCODE_LALT,
        C_RALT = SDL_SCANCODE_RALT,
        A = SDL_SCANCODE_A,
        B = SDL_SCANCODE_B,
        C = SDL_SCANCODE_C,
        D = SDL_SCANCODE_D,
        E = SDL_SCANCODE_E,
        F = SDL_SCANCODE_F,
        G = SDL_SCANCODE_G,
        H = SDL_SCANCODE_H,
        I = SDL_SCANCODE_I,
        J = SDL_SCANCODE_J,
        K = SDL_SCANCODE_K,
        L = SDL_SCANCODE_L,
        M = SDL_SCANCODE_M,
        N = SDL_SCANCODE_N,
        O = SDL_SCANCODE_O,
        P = SDL_SCANCODE_P,
        Q = SDL_SCANCODE_Q,
        R = SDL_SCANCODE_R,
        S = SDL_SCANCODE_S,
        T = SDL_SCANCODE_T,
        U = SDL_SCANCODE_U,
        V = SDL_SCANCODE_V,
        W = SDL_SCANCODE_W,
        X = SDL_SCANCODE_X,
        Y = SDL_SCANCODE_Y,
        Z = SDL_SCANCODE_Z,
    };

private:
    struct Modificators
    {
        bool leftShift() const noexcept;
        bool rightShift() const noexcept;
        bool shift() const noexcept;
        bool leftAlt() const noexcept;
        bool rightAlt() const noexcept;
        bool alt() const noexcept;
        bool leftCtrl() const noexcept;
        bool rightCtrl() const noexcept;
        bool ctrl() const noexcept;
        bool caps() const noexcept;
        void clear();

        bool _shift, _lShiftDown, _rShiftDown;
        bool _alt, _lAltDown, _rAltDown;
        bool _ctrl, _lCtrlDown, _rCtrlDown;
        bool _caps;
    };

public:
    void addKeyHandler(const keysym key, std::shared_ptr<KeyHandler> handler);
    void clearKey(const keysym key);
    void handleEvent(const SDL_Event &event) override;
    bool isKeyPressed(keysym key);
    bool isKeyReleased(keysym key);
    bool isKeyDown(keysym key);
    bool scancode(scancodes scancode);
    void clear();
    char getChar() const noexcept;
    const Modificators &modificators() const noexcept;
    bool getPressedScancode() const noexcept;

private:
    std::unordered_map<int32_t, std::vector<std::shared_ptr<KeyHandler>>> _handlers;
    std::unordered_map<int32_t, int32_t> _keymapWasUp;
    std::unordered_map<int32_t, int32_t> _keymapWasDown;
    std::unordered_map<int32_t, int32_t> _keymapPressed;
    std::unordered_map<int32_t, int32_t> _scancodePressed;
    Modificators _mods;

    char _char;
    uint32_t _scancode;
};

class EventManager : public utils::Singleton<EventManager>, public utils::Noncopyable
{
public:
    void update();

    void addEventHandler(const int eventType, std::shared_ptr<EventHandler> handler);
    void clearType(const int &eventType);

    KeyboardManager &keyboard();
    MouseHandler &mouse();

    std::vector<SDL_Event> &events() noexcept;

protected:
    EventManager();
    std::shared_ptr<KeyboardManager> _keyboard;
    std::shared_ptr<MouseHandler> _mouse;
    std::vector<SDL_Event> _events;

    std::unordered_map<int, std::vector<std::shared_ptr<EventHandler>>> _handlerByType;
};
} // namespace ample::control
