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

	// Можете дополнить ваш класс нужными полями и методами

private:
	// Можете дополнить ваш класс нужными полями и методами
    //First int - height (row), second - width (col) 
    std::map<int, std::map<int, std::unique_ptr<Cell>>> data_;
    
    int width = 0, height = 0;
};
