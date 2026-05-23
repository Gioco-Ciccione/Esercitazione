#include "MenuNode.h"
#include "MenuContext.h"
#include "MenuNavigator.h"

using namespace std;

MenuNode::MenuNode(const string& text)
    : text(text), title(text)
{
    this->action = [](MenuContext&, MenuNavigator&) { return EndActionBehaviour::ExecuteSelectedChild; };
}

MenuNode::MenuNode(const string& text, const function<void()>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext&, MenuNavigator&) {
        action();
        return EndActionBehaviour::ExecuteSelectedChild;
        };
}

MenuNode::MenuNode(const string& text, const function<void(MenuNavigator&)>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext&, MenuNavigator& nav) {
        action(nav);
        return EndActionBehaviour::ExecuteSelectedChild;
        };
}

MenuNode::MenuNode(const string& text, const function<void(MenuContext&)>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext& ctx, MenuNavigator&) {
        action(ctx);
        return EndActionBehaviour::ExecuteSelectedChild;
        };
}

MenuNode::MenuNode(const string& text, const function<EndActionBehaviour()>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext&, MenuNavigator&) {
        return action();
        };
}

MenuNode::MenuNode(const string& text, const function<EndActionBehaviour(MenuNavigator&)>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext&, MenuNavigator& nav) {
        return action(nav);
        };
}

MenuNode::MenuNode(const string& text, const function<EndActionBehaviour(MenuContext&)>& action)
    : text(text), title(text)
{
    this->action = [action](MenuContext& ctx, MenuNavigator&) {
        return action(ctx);
        };
}

MenuNode::MenuNode(const string& text, const Action& action)
    : text(text), action(action), title(text)
{
}

const string& MenuNode::GetText() const
{
    return text;
}

const string& MenuNode::GetTitle() const
{
    return title;
}

const Action& MenuNode::GetAction() const
{
    return action;
}

vector<shared_ptr<MenuNode>>& MenuNode::GetChildren()
{
    return children;
}

const vector<shared_ptr<MenuNode>>& MenuNode::GetChildren() const
{
    return children;
}

bool MenuNode::IsInputNode() const
{
    return isInputNode;
}


const string& MenuNode::GetBackText() const
{
    return backText;
}

bool MenuNode::HasBackOption() const
{
    return hasBackOption;
}

bool MenuNode::IsRuntimeGenerated() const
{
    return isRuntimeGenerated;
}

shared_ptr<MenuNode> MenuNode::SetBackOptionVisibility(bool value)
{
    hasBackOption = value;
    return shared_from_this();
}

shared_ptr<MenuNode> MenuNode::SetBackText(const string& text)
{
    backText = text;
    return shared_from_this();
}

shared_ptr<MenuNode> MenuNode::SetTitle(const string& text)
{
    this->title = text;
    return shared_from_this();
}

shared_ptr<MenuNode> MenuNode::MarkAsInputNode()
{
    isInputNode = true;
    return shared_from_this();
}

shared_ptr<MenuNode> MenuNode::MarkAsRuntimeGenerated()
{
    isRuntimeGenerated = true;
    return shared_from_this();
}


shared_ptr<MenuNode> MenuNode::AddChild(const shared_ptr<MenuNode>& child)
{
    children.push_back(child);
    return shared_from_this();
}

void MenuNode::ClearChildren()
{
    children.clear();
}