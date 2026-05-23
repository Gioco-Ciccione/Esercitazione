/*! \file ShapeTester.h
    \brief Declaration of the class ShapeTester
    \author Valente Sebastiano
*/
#pragma once

#include <memory>
#include <array>
#include <iostream>

using namespace std;

class Shape;

/// @class ShapeTester
/// @brief to test the class Shape with polymorphism
class ShapeTester final
{
private:
    /// @name CONSTRUCTORS
    /// @{
    ShapeTester() = delete;
    /// @}

public:
    /// @name ROUTINE
    /// @{
    template <size_t N>
    static void ExecuteTestRoutine(const array<unique_ptr<Shape>, N>& figures);
    /// @}

    /// @name TESTS
    /// @{
    template <size_t N>
    static void DumpAll(const array<unique_ptr<Shape>, N>& figures);

    template <size_t N>
    static void TestEquality(const array<unique_ptr<Shape>, N>& figures);

    template <size_t N>
    static void TestScale(const array<unique_ptr<Shape>, N>& figures);
    /// @}

private:
    /// @name HELPERS
    /// @{
    template <size_t N>
    static void ShapesTablePrint(const array<array<bool, N>, N>& table);
    /// @}
};

#include "ShapeTester.tpp"

