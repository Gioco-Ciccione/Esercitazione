/*! \file MenuNode.h
    \brief Declaration of the class MenuNode
    \author Sebastiano Valente
*/

#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

struct MenuContext;
class MenuNavigator;

/// @enum EndActionBehaviour
/// @brief Possible behaviours after executing a menu action
enum class EndActionBehaviour {
    ExecuteSelectedChild, ///< Execute the selected child node
    Repeat,               ///< Repeat the current node
    JumpToStart,          ///< Return to the root node
    Nope,                 ///< Do nothing
};

using namespace std;

/// @typedef Action
/// @brief Alias for a menu action callback
using Action = function<EndActionBehaviour(MenuContext&, MenuNavigator&)>;

/// @class MenuNode
/// @brief to manage a node inside a navigable menu structure
class MenuNode : public enable_shared_from_this<MenuNode> {
private:
    string text;
    string title;
    Action action{};
    vector<shared_ptr<MenuNode>> children;

    bool hasBackOption = false;
    string backText = "Indietro";

    bool isInputNode = false;
    bool isRuntimeGenerated = false;

public:
    /// @name CONSTRUCTORS / DESTRUCTOR
    /// @{
    MenuNode() = default;
    MenuNode(const string& text);

    MenuNode(const string& text, const function<void()>& action);
    MenuNode(const string& text, const function<void(MenuContext&)>& action);
    MenuNode(const string& text, const function<void(MenuNavigator&)>& action);
    MenuNode(const string& text, const function<EndActionBehaviour()>& action);
    MenuNode(const string& text, const function<EndActionBehaviour(MenuContext&)>& action);
    MenuNode(const string& text, const function<EndActionBehaviour(MenuNavigator&)>& action);
    MenuNode(const string& text, const Action& action);
    /// @}

    /// @name GETTERS
    /// @{
    const string& GetText() const;
    const string& GetTitle() const;
    const Action& GetAction() const;

    vector<shared_ptr<MenuNode>>& GetChildren();
    const vector<shared_ptr<MenuNode>>& GetChildren() const;

    bool IsInputNode() const;

    const string& GetBackText() const;
    bool HasBackOption() const;
    bool IsRuntimeGenerated() const;
    /// @}

    /// @name SETTERS
    /// @{
    shared_ptr<MenuNode> SetBackOptionVisibility(bool value);
    shared_ptr<MenuNode> SetBackText(const string& text);
    shared_ptr<MenuNode> SetTitle(const string& text);

    shared_ptr<MenuNode> MarkAsInputNode();
    shared_ptr<MenuNode> MarkAsRuntimeGenerated();
    /// @}

    /// @name CHILD MANAGEMENT
    /// @{
    shared_ptr<MenuNode> AddChild(const shared_ptr<MenuNode>& child);

    template<typename... Args>
    shared_ptr<MenuNode> AddChildren(Args... args);

    void ClearChildren();
    /// @}
};

#include "MenuNode.tpp"