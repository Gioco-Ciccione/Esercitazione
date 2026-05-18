#pragma once

#include <memory>
#include <array>
#include <iostream>

using namespace std;

class Shape;

class ShapeTester final
{
private:
    ShapeTester() = delete;

public:
    template <size_t N>
    static void ExecuteTestRoutine(const array<unique_ptr<Shape>, N>& figures);

    template <size_t N>
    static void DumpAll(const array<unique_ptr<Shape>, N>& figures);

    template <size_t N>
    static void TestEquality(const array<unique_ptr<Shape>, N>& figures);

    template <size_t N>
    static void TestScale(const array<unique_ptr<Shape>, N>& figures);

private:

    template <size_t N>
    static void ShapesTablePrint(const array<array<bool, N>, N>& table);
};

#include "ShapeTester.tpp"

