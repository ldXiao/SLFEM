//
// Created by Lind Xiao on 5/14/19.
//

#include <iostream>
#include <polyfem/ExpressionValue.hpp>
#include "SturmLiouville.hpp"
#include <polyfem/Helmholtz.hpp>
#include <polyfem/Common.hpp>
#include <polyfem/AutodiffTypes.hpp>
#include <polyfem/ExpressionValue.hpp>
#include <polyfem/ElementAssemblyValues.hpp>
#include <Eigen/Dense>
using namespace polyfem;
int main(){
    ExpressionValue tt;
    json in_args = json({});
    std::string eval = "sin(x+y+z)";
    tt.init(eval);
    json initialization_params = R"({"pweight":"2+cos(x+y) ","qweight": "x-y"})"_json;
    SturmLiouville SL;
    in_args["SLparams"] = initialization_params;
    in_args["asd"] = 1;
    SL.set_parameters(in_args);
    return 0;
}