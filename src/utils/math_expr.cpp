#include "math_expr.h"

#include <string>
#include <regex>
#include <random>
#include <iostream>
#include <variant>

namespace simstudio
{

    double MathExpr::Execute(String &expr)
    {
        std::default_random_engine rng;

        std::regex uniformRegex(R"(uniform\(([^,]+),\s*([^)]+)\))");
        std::regex standardRangeRegex(R"(standard\(([^,]+),\s*([^)]+)\))");
        std::regex standardMaxRegex(R"(standard\(([^,]+)\))");

        std::smatch match;

        if (std::regex_search(expr, match, uniformRegex))
        {
            std::string minStr = match[1];
            std::string maxStr = match[2];

            double min = std::stod(minStr);
            double max = std::stod(maxStr);

            std::uniform_real_distribution<double> distribution(min, max);
            return distribution(rng);
        }
        else if (std::regex_search(expr, match, standardRangeRegex))
        {
            std::string minStr = match[1];
            std::string maxStr = match[2];

            double min = std::stod(minStr);
            double max = std::stod(maxStr);

            std::normal_distribution<double> distribution(0.0, 1.0);
            double value = distribution(rng);

            return (value * (max - min)) + min;
        }
        else if (std::regex_search(expr, match, standardMaxRegex))
        {
            std::string maxStr = match[1];

            double max = std::stod(maxStr);

            std::normal_distribution<double> distribution(0.0, 1.0);
            double value = distribution(rng);

            return value * max;
        }
        else
        {
            // Evaluate the expression in another way if needed (not implemented here)
            std::cerr << "[Error][" << expr << "] Unknown expression" << std::endl;
            return 0.0;
        }
    }

}