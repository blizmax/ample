#include <imgui.h>

#include "Utils.h"
#include "objects/GraphicalRotateActionGui.h"

namespace ample::gui
{
GraphicalRotateActionGui::GraphicalRotateActionGui(std::shared_ptr<filing::NamedObject> action,
                                                   std::shared_ptr<game::game2d::Game2dEditor> editor,
                                                   ObjectStorageGui *stor)
    : ObjectGroupActionGui<graphics::GraphicalObject>(action, editor, stor)
{
    _rotateAction = std::dynamic_pointer_cast<game::stateMachine::actions::GraphicalRotateAction>(action);
    angle = _rotateAction->getAngle();
    axis = _rotateAction->getAxis();
}

GraphicalRotateActionGui::GraphicalRotateActionGui(std::shared_ptr<game::game2d::Game2dEditor> editor, ObjectStorageGui *stor)
    : ObjectGroupActionGui<graphics::GraphicalObject>(editor, stor) {}

void GraphicalRotateActionGui::onCreate()
{
    ImGui::InputText("Name", nameBuffer, 255);
    gui_utils::InputScalar("Axis x", axis.x, 1.0f);
    gui_utils::InputScalar("Axis y", axis.y, 1.0f);
    gui_utils::InputScalar("Axis z", axis.z, 1.0f);
    gui_utils::InputScalar("Angle", angle, 1.0f);
}

void GraphicalRotateActionGui::onSubmitCreate()
{
    _rotateAction = std::make_shared<game::stateMachine::actions::GraphicalRotateAction>(nameBuffer,
                                                                                         std::vector<std::string>{},
                                                                                         axis,
                                                                                         angle);
    _baseActionPointer = _rotateAction; // !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    _groupAction = _rotateAction;
}

void GraphicalRotateActionGui::onEdit()
{
    ObjectGroupActionGui<graphics::GraphicalObject>::onEdit();
    gui_utils::InputScalar("Axis x", axis.x, 1.0f);
    gui_utils::InputScalar("Axis y", axis.y, 1.0f);
    gui_utils::InputScalar("Axis z", axis.z, 1.0f);
    gui_utils::InputScalar("Angle", angle, 1.0f);
}

void GraphicalRotateActionGui::onSubmitEdit()
{
    ObjectGroupActionGui<graphics::GraphicalObject>::onSubmitEdit();
    _rotateAction->setAngle(angle);
    _rotateAction->setAxis(axis);
}

void GraphicalRotateActionGui::onView() {}
void GraphicalRotateActionGui::onInspect()
{
    ObjectGroupActionGui<graphics::GraphicalObject>::onInspect();
}

void GraphicalRotateActionGui::onPreview()
{
    ImGui::Text("Axis: x %.2f y %.2f z %.2f", axis.x, axis.y, axis.z);
    ImGui::Text("Angle: %.2f", angle);
}

std::string GraphicalRotateActionGui::name() const
{
    return _rotateAction->name();
}

std::string GraphicalRotateActionGui::className() const
{
    return "GraphicalRotateAction";
}
} // namespace ample::gui
