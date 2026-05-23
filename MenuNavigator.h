#pragma once

#include "MenuNode.h"
#include <functional>
#include <stack>
#include <memory>
#include <iostream>

class MenuNavigator {
private:
    std::shared_ptr<MenuNode> root;
    std::stack<std::shared_ptr<MenuNode>> history;
    MenuContext& context;
    std::shared_ptr<MenuNode> current;

public:
    MenuNavigator(const std::shared_ptr<MenuNode>& root, MenuContext& context);

    void show() const;
    void Run();
    void Execute(const std::shared_ptr<MenuNode>& start);
};