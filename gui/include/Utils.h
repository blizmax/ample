#pragma once

#include <imgui.h>

#include <imfilebrowser.h>
#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "ample/EventManager.h"

namespace ample::gui
{
enum class finalObjectClass;
struct ClassInfo
{
    finalObjectClass finalClass;
    bool drawInCreator = true;
    std::string parentClass = "";
};
} // namespace ample::gui

namespace ample::gui::gui_utils
{
template <typename T>
std::shared_ptr<T> SelectNamedObjectFromList(const std::string &selectionName,
                                             const std::vector<std::shared_ptr<T>> &list);

class MessagePopup
{
public:
    MessagePopup(const std::string &id, const std::string &message, bool opened = false)
        : id(id), message(message), opened(opened) {}

    MessagePopup() = default;

    std::string id;
    std::string message;
    bool opened = false;
    void drawInterface()
    {
        if (opened || !message.empty())
        {
            ImGui::OpenPopup(id.c_str());
            if (ImGui::BeginPopupModal(id.c_str(), NULL, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("%s", message.c_str());
                if (ImGui::Button("Close"))
                {
                    message.clear();
                    opened = false;
                    ImGui::CloseCurrentPopup();
                }
                ImGui::EndPopup();
            }
        }
    }
};

inline void TextDisabled(const char *text)
{
    ImGui::TextColored(ImVec4(0.7f, 0.7f, 0.7f, 0.7f), "%s", text);
}

inline void CloseCurrentPopupOnSuccessButton(bool &success)
{
    if (ImGui::Button("Close") || success)
    {
        success = false;
        ImGui::CloseCurrentPopup();
    }
}

void inputKeysym(const std::string &label, control::keysym &key);

template <typename T>
void InputScalar(const std::string &label, T &value, T step);

template <typename T>
void InputScalar(const std::string &label, T &value, T step, T min, T max);

template <typename T>
void InputCoordinates(const std::string &label, T &valueX, T &valueY, T step);

template <typename T>
void InputCoordinates(const std::string &label, T &valueX, T &valueY, T step, T min, T max);

template <typename T>
void NamedObjectSelector(const std::string &label, std::shared_ptr<T> &object, const std::vector<std::shared_ptr<T>> &list);

template <typename T>
void NamedObjectSelector(const std::string &label, std::shared_ptr<T> &object, const std::unordered_map<size_t, std::shared_ptr<T>> &list);

template <typename T>
void NamedObjectSelector(const std::string &label, std::shared_ptr<T> &object, const std::unordered_map<std::string, std::shared_ptr<T>> &list);

template <typename T>
void NamedObjectSelector(const std::string &label, std::string &objectName, const std::unordered_map<std::string, std::shared_ptr<T>> &list);

inline void StringSelector(const std::string &label, std::string &string, const std::vector<std::string> &list)
{
    if (ImGui::Button(label.c_str()))
    {
        ImGui::OpenPopup((label + ".popup").c_str());
    }
    ImGui::SameLine();
    if (!string.empty())
    {
        ImGui::Text("%s", string.c_str());
    }
    else
    {
        gui_utils::TextDisabled("[select]");
    }
    if (ImGui::BeginPopup((label + ".popup").c_str()))
    {
        if (list.empty())
        {
            gui_utils::TextDisabled("[empty]");
        }
        for (const auto &obj : list)
        {
            if (ImGui::Selectable(obj.c_str()))
            {
                string = obj;
            }
        }
        ImGui::EndPopup();
    }
}

inline void PathSelector(const std::string &label, std::string &path, ImGui::FileBrowser &filebrowser)
{
    if (ImGui::Button(label.c_str()))
    {
        filebrowser.Open();
    }
    ImGui::SameLine();
    ImGui::Text("%s", path.c_str());
    filebrowser.Display();
    if (filebrowser.HasSelected())
    {
        path = filebrowser.GetSelected();
    }
}

class ClassSelector
{
public:
    ClassSelector(const std::string &title, const std::string &parentClassName);
    void drawInterface();
    void open();
    bool hasResult();
    ClassInfo popResult();

private:
    std::string _title;
    std::string _parentClassName;
    bool _isOpened = false;
    bool _has = false;
    ClassInfo _result;
    int choosenId = 0;
};
} // namespace ample::gui::gui_utils

#include "templates/Utils.hpp"
