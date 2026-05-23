/// @brief Helper: executes the full test routine on the input figures
/// @tparam N number of elements in the array
/// @param figures array of unique_ptr<Shape>
template <size_t N>
void ShapeTester::ExecuteTestRoutine(const array<unique_ptr<Shape>, N>& figures)
{
    // Dump
    DumpAll(figures);

    // Equality
    TestEquality(figures);

    // Scale
    TestScale(figures);
}


/// @brief Helper: prints the truth table to the terminal.
/// @param table Matrix containing the truth table.
template <size_t N>
void ShapeTester::ShapesTablePrint(const array<array<bool, N>, N>& table)
{
    cout << "  ";

    for (size_t j = 0; j < N; ++j)
        cout << j << " ";

    cout << "\n";

    for (size_t i = 0; i < N; ++i)
    {
        cout << i << " ";

        for (size_t j = 0; j < N; ++j)
        {
            cout << (table[i][j] ? 'T' : 'F') << " ";
        }

        cout << "\n";
    }
}


/// @brief Prints all shapes in the array using polymorphic Dump()
/// @tparam N number of elements in the array
/// @param figures array of unique_ptr<Shape>
template <size_t N>
void ShapeTester::DumpAll(const array<unique_ptr<Shape>, N>& figures)
{
    cout << endl << "\n===== DUMP POLIMORFICO =====\n" << endl;

    for (const auto& fig : figures)
    {
        if (fig)
            fig->Dump();
    }
}

/// @brief Builds and prints a truth table for polymorphic operator== between shapes
/// @tparam N number of elements in the array
/// @param figures array of unique_ptr<Shape>
template <size_t N>
void ShapeTester::TestEquality(const array<unique_ptr<Shape>, N>& figures)
{
    cout << endl << "\n===== EQUALITY TEST =====\n" << endl;

    array<array<bool, N>, N> table{};

    for (size_t i = 0; i < N; ++i)
    {
        for (size_t j = 0; j < N; ++j)
        {
            table[i][j] =
                (figures[i] && figures[j]) &&
                (*figures[i] == *figures[j]);
        }
    }

    ShapesTablePrint(table);
}

/// @brief Tests the correctness of Shape::Scale() on all shapes
/// @tparam N number of elements in the array
/// @param figures array of unique_ptr<Shape>
template <size_t N>
void ShapeTester::TestScale(const array<unique_ptr<Shape>, N>& figures)
{
    cout << endl << "\n===== SCALE TEST =====\n" << endl;

    array<bool, N> table{};
    const float sf = 2.0f;

    for (size_t i = 0; i < N; ++i)
    {
        if (!figures[i])
        {
            table[i] = false;
            continue;
        }

        float oldW = figures[i]->GetWidth();
        float oldH = figures[i]->GetHeight();

        figures[i]->Scale(sf);

        float newW = figures[i]->GetWidth();
        float newH = figures[i]->GetHeight();

        table[i] =
            (newW == oldW * sf) &&
            (newH == oldH * sf);
    }

    for (size_t i = 0; i < N; ++i)
    {
        cout << "Figure " << i << ": "
            << (table[i] ? 'T' : 'F')
            << "\n";
    }
}