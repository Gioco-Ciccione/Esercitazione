#pragma once

#define NODE make_shared<MenuNode>
#define LAMBDA() [](MenuContext& context, MenuNavigator& nav)
#define LAMBDA_CAPTURE(...) [&__VA_ARGS__](MenuContext& context, MenuNavigator& nav)