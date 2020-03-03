#include "CameraBehavior.h"
#include "Debug.h"

CameraBehavior::CameraBehavior(ample::window::WindowActivity &game, ample::graphics::Camera &camera)
    : game(game), camera(camera) {}

void CameraBehavior::onActive()
{
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_a))
    {
        camera.translate(5, 0, 0);
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_d))
    {
        camera.translate(-5, 0, 0);
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_s))
    {
        camera.translate(0, 5, 0);
    }
    if (game.eventManager->keyboard()->isKeyDown(ample::control::keysym::KEY_w))
    {
        camera.translate(0, -5, 0);
    }
    if (game.eventManager->mouse()->getWheelY() < 0)
    {
        camera.setPerspective(camera.getLeft(), camera.getRight(), camera.getBottom(), camera.getTop(), camera.getNear() + 10, camera.getFar());
    }
    else if (game.eventManager->mouse()->getWheelY() > 0)
    {
        camera.setPerspective(camera.getLeft(), camera.getRight(), camera.getBottom(), camera.getTop(), camera.getNear() - 10, camera.getFar());
    }
}