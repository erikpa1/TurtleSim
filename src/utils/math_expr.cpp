#include "math_expr.h"

#include <string>
#include <regex>
#include <random>
#include <iostream>
#include <variant>

#include "../external/exprtk.hpp"

std::default_random_engine rng;

using namespace exprtk;

namespace simstudio
{

    Option<double> MathExpr::Execute(String &expr)
    {

        std::regex uniformRegex(R"(uniform\(([^,]+),\s*([^)]+)\))");
        std::regex standardRangeRegex(R"(standard\(([^,]+),\s*([^)]+)\))");
        std::regex standardMaxRegex(R"(standard\(([^,]+)\))");

        std::smatch match;

        if (std::regex_search(expr, match, uniformRegex))
        {
            String minStr = match[1];
            String maxStr = match[2];

            double min = std::stod(minStr);
            double max = std::stod(maxStr);

            std::uniform_real_distribution<double> distribution(min, max);
            return distribution(rng);
        }
        else if (std::regex_search(expr, match, standardRangeRegex))
        {
            String minStr = match[1];
            String maxStr = match[2];

            double min = std::stod(minStr);
            double max = std::stod(maxStr);

            std::normal_distribution<double> distribution(0.0, 1.0);
            double value = distribution(rng);

            return (value * (max - min)) + min;
        }
        else if (std::regex_search(expr, match, standardMaxRegex))
        {
            String maxStr = match[1];

            double max = std::stod(maxStr);

            std::normal_distribution<double> distribution(0.0, 1.0);
            double value = distribution(rng);

            return value * max;
        }
        else
        {

            symbol_table<double> symbol_table;
            expression<double> expression;
            parser<double> parser;

            expression.register_symbol_table(symbol_table);
            parser.compile(expr, expression);

            const double y = expression.value();

            if (std::isnan(y))
            {
                LogE << "Received: " << y;
                return {};
            }
            else
            {
                return y;
            }

            return y;
        }

        return {};
    }

}