/*! \file MenuNavigator.cpp
    \brief implementation of class MenuNavigator
    \author Sebastiano Valente
*/

#include "MenuNavigator.h"
#include "MenuContext.h"

using namespace std;

/* ----------------------------
   UTILITY FUNCTIONS
   ---------------------------- */

/// @brief clears terminal screen
static void ClearTerminal() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

/* ----------------------------
   CONSTRUCTORS
   ---------------------------- */

/// @brief constructor
/// @param root root menu node
/// @param context menu execution context
MenuNavigator::MenuNavigator(const shared_ptr<MenuNode>& root, MenuContext& context)
    : root(root), context(context), current(root) {
}

/* ----------------------------
   MENU VISUALIZATION
   ---------------------------- */

/// @brief prints current menu on terminal
void MenuNavigator::show() const {
    if (!current) return;

    auto& cur = *current;

    if (cur.IsInputNode()) {
        cout << endl << cur.GetText() << endl;
    }
    else {
        ClearTerminal();
        cout << "=== " << cur.GetTitle() << " ===" << endl;

        const auto& children = cur.GetChildren();
        for (size_t i = 0; i < children.size(); ++i) {
            cout << i + 1 << ". " << children[i]->GetText() << endl;
        }

        if (cur.HasBackOption()) {
            cout << "0. " << cur.GetBackText() << endl;
        }
    }
}

/* ----------------------------
   MENU EXECUTION
   ---------------------------- */

/// @brief executes current menu node
void MenuNavigator::Run() {
    if (!current) return;

    auto cur = current;

    EndActionBehaviour behv = EndActionBehaviour::ExecuteSelectedChild;
    bool inputNode = false;

    if (cur->GetChildren().size() == 1 && cur->GetChildren()[0]->IsInputNode()) {
        if (history.size() == 0) { history.push(current); }
        else if (current != history.top()) history.push(current);
        current = cur->GetChildren()[0];
        inputNode = true;
    }

    show();

    if (!inputNode) {
        int choice;
        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return Run();
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 0 && cur->HasBackOption()) {
            if (history.size() <= 1) return exit(0);

            history.pop();
            current = history.top();
            if (current->IsRuntimeGenerated()) {
                history.pop();
                current = history.top();
            }

            if (current->GetAction()) {
                behv = current->GetAction()(context, *this);
            }

            return Run();
        }

        if (choice < 1 || choice > cur->GetChildren().size()) { return Run();}

        current = cur->GetChildren()[choice - 1];
    }

    if (current->GetAction()) {
        behv = current->GetAction()(context, *this);
    }

    switch (behv) {
    case EndActionBehaviour::ExecuteSelectedChild:
        if (!current->GetChildren().empty()) {
            if (history.size() == 0) { history.push(current); }
            else if (current != history.top()) history.push(current);
        }
        else if (!history.empty()) {
            current = history.top();
            history.pop();
        }
        return Run();

    case EndActionBehaviour::JumpToStart:
        while (!history.empty()) history.pop();
        current = root;
        return Execute(root);

    case EndActionBehaviour::Repeat:
        if (!history.empty()) {
            current = history.top();
            history.pop();
        }
        return Run();

    case EndActionBehaviour::Nope:
        return;

    default:
        return;
    }
}

/// @brief executes navigation from a specified node
/// @param start starting node
void MenuNavigator::Execute(const shared_ptr<MenuNode>& start) {
    if (current) {
        if (history.size() == 0) { history.push(current); }
        else if (current != history.top()) { history.push(current); }
    }
    current = start;
    Run();
}