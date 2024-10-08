#pragma once

#include "cell.h"
#include "common.h"

#include <functional>
#include <map>

class Sheet : public SheetInterface 
{
public:
    ~Sheet();

    void SetCell(Position pos, std::string text) override;

    const CellInterface* GetCell(Position pos) const override;
    CellInterface* GetCell(Position pos) override;

    void ClearCell(Position pos) override;

    Size GetPrintableSize() const override;

    void PrintValues(std::ostream& output) const override;
    void PrintTexts(std::ostream& output) const override;

    const Cell* GetConcreteCell(Position pos) const;
    Cell* GetConcreteCell(Position pos);

private:
    void MaybeIncreaseSizeToIncludePosition(Position pos);
    void PrintCells(std::ostream& output, const std::function<void(const CellInterface&)>& printCell) const;
    Size GetActualSize() const;

    std::map<int, std::map<int, std::unique_ptr<Cell>>> data_;
    std::unordered_map<Position, std::string> cache_;
    std::unordered_map<Position, std::vector<Position>> dependencies_;
    
    int width = 0, height = 0;
};
