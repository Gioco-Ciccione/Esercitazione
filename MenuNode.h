#pragma once

#include <string>
#include <vector>
#include <memory>
#include <functional>

struct MenuContext;
class MenuNavigator;

enum class EndActionBehaviour {
    ExecuteSelectedChild,
    Repeat,
    JumpToStart,
    Nope,
};

using namespace std;

using Action = function<EndActionBehaviour(MenuContext&, MenuNavigator&)>;

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
    MenuNode() = default;
    MenuNode(const string& text);

    MenuNode(const string& text, const function<void()>& action);
    MenuNode(const string& text, const function<void(MenuContext&)>& action);
    MenuNode(const string& text, const function<void(MenuNavigator&)>& action);
    MenuNode(const string& text, const function<EndActionBehaviour()>& action);
    MenuNode(const string& text, const function<EndActionBehaviour(MenuContext&)>& action);
    MenuNode(const string& text, const function<EndActionBehaviour(MenuNavigator&)>& action);
    MenuNode(const string& text, const Action& action);

    const string& GetText() const;
    const string& GetTitle() const;
    const Action& GetAction() const;

    vector<shared_ptr<MenuNode>>& GetChildren();
    const vector<shared_ptr<MenuNode>>& GetChildren() const;

    bool IsInputNode() const;

    const string& GetBackText() const;
    bool HasBackOption() const;
    bool IsRuntimeGenerated() const;

    shared_ptr<MenuNode> SetBackOptionVisibility(bool value);
    shared_ptr<MenuNode> SetBackText(const string& text);
    shared_ptr<MenuNode> SetTitle(const string& text);

    shared_ptr<MenuNode> MarkAsInputNode();
    shared_ptr<MenuNode> MarkAsRuntimeGenerated();

    shared_ptr<MenuNode> AddChild(const shared_ptr<MenuNode>& child);

    template<typename... Args>
    shared_ptr<MenuNode> AddChildren(Args... args);

    void ClearChildren();
};

template<typename... Args>
shared_ptr<MenuNode> MenuNode::AddChildren(Args... args) {
    (AddChild(args), ...);
    return shared_from_this();
}