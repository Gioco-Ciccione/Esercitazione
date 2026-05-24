/*! \file MenuNode.cpp
    \brief implementation of class MenuNode
    \author Sebastiano Valente
*/

#include "MenuNode.h"
#include "MenuContext.h"
#include "MenuNavigator.h"

using namespace std;

/* ----------------------------
   CONSTRUCTORS
   ---------------------------- */

/// @brief constructor with default action
/// @param text node text
MenuNode::MenuNode(const string& text)
    : text(text), title(text)
{
    this->action = [](MenuContext&, MenuNavigator&) {
        return EndActionBehaviour::ExecuteSelectedChild;
        };
}

/// @brief constructor with void action
/// @param text node text
/// @param action callback action
MenuNode::MenuNode(const string& text, const function<void()>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext&, MenuNavigator&) {
        action();
        return EndActionBehaviour::ExecuteSelectedChild;
        };
}

/// @brief constructor with navigator callback
/// @param text node text
/// @param action callback action
MenuNode::MenuNode(const string& text, const function<void(MenuNavigator&)>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext&, MenuNavigator& nav) {
        action(nav);
        return EndActionBehaviour::ExecuteSelectedChild;
        };
}

/// @brief constructor with context callback
/// @param text node text
/// @param action callback action
MenuNode::MenuNode(const string& text, const function<void(MenuContext&)>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext& ctx, MenuNavigator&) {
        action(ctx);
        return EndActionBehaviour::ExecuteSelectedChild;
        };
}

/// @brief constructor with behaviour callback
/// @param text node text
/// @param action callback action
MenuNode::MenuNode(const string& text, const function<EndActionBehaviour()>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext&, MenuNavigator&) {
        return action();
        };
}

/// @brief constructor with navigator behaviour callback
/// @param text node text
/// @param action callback action
MenuNode::MenuNode(const string& text, const function<EndActionBehaviour(MenuNavigator&)>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext&, MenuNavigator& nav) {
        return action(nav);
        };
}

/// @brief constructor with context behaviour callback
/// @param text node text
/// @param action callback action
MenuNode::MenuNode(const string& text, const function<EndActionBehaviour(MenuContext&)>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext& ctx, MenuNavigator&) {
        return action(ctx);
        };
}

/// @brief constructor with generic action
/// @param text node text
/// @param action callback action
MenuNode::MenuNode(const string& text, const Action& action)
    : text(text), action(action), title(text)
{
}

/* ----------------------------
   GETTERS
   ---------------------------- */

/// @brief getter for node text
/// @return node text
const string& MenuNode::GetText() const
{
    return text;
}

/// @brief getter for node title
/// @return node title
const string& MenuNode::GetTitle() const
{
    return title;
}

/// @brief getter for node action
/// @return node action
const Action& MenuNode::GetAction() const
{
    return action;
}

/// @brief getter for children nodes
/// @return vector of child nodes
vector<shared_ptr<MenuNode>>& MenuNode::GetChildren()
{
    return children;
}

/// @brief const getter for children nodes
/// @return vector of child nodes
const vector<shared_ptr<MenuNode>>& MenuNode::GetChildren() const
{
    return children;
}

/// @brief checks if node is an input node
/// @return true if node is input node
bool MenuNode::IsInputNode() const
{
    return isInputNode;
}

/// @brief getter for back option text
/// @return back option text
const string& MenuNode::GetBackText() const
{
    return backText;
}

/// @brief checks if node has back option
/// @return true if back option is enabled
bool MenuNode::HasBackOption() const
{
    return hasBackOption;
}

/// @brief checks if node is runtime generated
/// @return true if runtime generated
bool MenuNode::IsRuntimeGenerated() const
{
    return isRuntimeGenerated;
}

/* ----------------------------
   SETTERS
   ---------------------------- */

   /// @brief enables or disables back option
   /// @param value visibility state
   /// @return current node
shared_ptr<MenuNode> MenuNode::SetBackOptionVisibility(bool value)
{
    hasBackOption = value;
    return shared_from_this();
}

/// @brief sets back option text
/// @param text new text
/// @return current node
shared_ptr<MenuNode> MenuNode::SetBackText(const string& text)
{
    backText = text;
    return shared_from_this();
}

/// @brief sets node title
/// @param text new title
/// @return current node
shared_ptr<MenuNode> MenuNode::SetTitle(const string& text)
{
    this->title = text;
    return shared_from_this();
}

/// @brief marks node as input node
/// @return current node
shared_ptr<MenuNode> MenuNode::MarkAsInputNode()
{
    isInputNode = true;
    return shared_from_this();
}

/// @brief marks node as runtime generated
/// @return current node
shared_ptr<MenuNode> MenuNode::MarkAsRuntimeGenerated()
{
    isRuntimeGenerated = true;
    return shared_from_this();
}

/* ----------------------------
   CHILD MANAGEMENT
   ---------------------------- */

/// @brief adds a child node
/// @param child child node
/// @return current node
shared_ptr<MenuNode> MenuNode::AddChild(const shared_ptr<MenuNode>& child)
{
    children.push_back(child);
    return shared_from_this();
}

/// @brief removes all child nodes
void MenuNode::ClearChildren()
{
    children.clear();
}