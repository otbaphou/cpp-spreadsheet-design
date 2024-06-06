#pragma once

#include "common.h"
#include "formula.h"

class Cell : public CellInterface {
public:
    Cell();
    ~Cell();

    void Set(std::string text);
    void Clear();

    Value GetValue() const override;
    std::string GetText() const override;

private:
//можете воспользоваться нашей подсказкой, но это необязательно.
    class Impl
    {
        public:
        
        virtual void SetValue(std::string& text)
        {
            value_ = std::move(text);
        }
        
        virtual Value GetValue() const
        {
            return "";
        }
        
        std::string GetText()
        {
            return value_;
        }
        
        protected:
        
        std::string value_;
    };
    
    class EmptyImpl : public Impl
    {
        public:
        
        EmptyImpl()
        {
            value_ = "";
        }
        
        Value GetValue() const override
        {
            return "";
        }
    };
    
    class TextImpl : public Impl
    {
        public:
        
        TextImpl() = default;
        
        TextImpl(std::string& text)
        {
            value_ = std::move(text);
        }
                
        void SetValue(std::string& text) override
        {
            value_ = std::move(text);
        }
        
        Value GetValue() const override
        {
            if(value_[0] == '\'')
            {
                std::string tmp(value_.begin() + 1, value_.end());
                return tmp;
            }
            
            return value_;
        }
    };
    
    class FormulaImpl : public Impl
    {
        public:
        
        FormulaImpl() = default;
        
        FormulaImpl(std::string& text)
        {
            value_ = std::move(text);
        }
                
        void SetValue(std::string& text) override
        {
            value_ = std::move(text);
        }
        
        Value GetValue() const override
        {
            std::string tmp(value_.begin() + 1, value_.end());
            
            if(tmp.size() == 0)
                return value_;
            
            std::unique_ptr<FormulaInterface> formula = ParseFormula(tmp);
            //std::cout << formula->GetExpression() << std::endl;
            std::variant<double, FormulaError> result = formula->Evaluate();
            
            if(std::holds_alternative<double>(result))
            {
                return std::get<double>(result);
            }
            else
            {
                return std::get<FormulaError>(result);
            }
        }
    };
    
    std::unique_ptr<Impl> impl_;

};
