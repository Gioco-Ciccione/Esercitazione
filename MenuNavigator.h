/*! \file MenuNavigator.h
    \brief Declaration of the class MenuNavigator
    \author Sebastiano Valente
*/

#pragma once

#include "MenuNode.h"
#include <functional>
#include <stack>
#include <memory>
#include <iostream>

/// @class MenuNavigator
/// @brief to manage the navigation and execution of menu nodes
class MenuNavigator {
private:
    std::shared_ptr<MenuNode> root;
    std::stack<std::shared_ptr<MenuNode>> history;
    MenuContext& context;
    std::shared_ptr<MenuNode> current;

public:
    /// @name CONSTRUCTORS
    /// @{
    MenuNavigator(const std::shared_ptr<MenuNode>& root, MenuContext& context);
    /// @}

    /// @name MENU VISUALIZATION
    /// @{
    void show() const;
    /// <summary>
    ///  @}
    
    /// <@name MENU EXECUTION
    /// @{
    void Run();
    void Execute(const std::shared_ptr<MenuNode>& start);
    /// @}
};