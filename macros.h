/*! \file MenuMacros.h
    \brief Declaration of utility macros for menu creation
    \author Sebastiano Valente
*/

#pragma once

/// @def NODE
/// @brief Shortcut macro for creating a shared MenuNode instance
#define NODE make_shared<MenuNode>

/// @def LAMBDA
/// @brief Shortcut macro for declaring a standard menu lambda
/// @details Expands to a lambda with MenuContext and MenuNavigator parameters
#define LAMBDA() [](MenuContext& context, MenuNavigator& nav)

/// @def LAMBDA_CAPTURE
/// @brief Shortcut macro for declaring a capturing menu lambda
/// @param ... Variables to capture by reference
/// @details Expands to a lambda with MenuContext and MenuNavigator parameters
#define LAMBDA_CAPTURE(...) [__VA_ARGS__](MenuContext& context, MenuNavigator& nav)