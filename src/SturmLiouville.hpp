#pragma once

#include <polyfem/Common.hpp>
#include <polyfem/AutodiffTypes.hpp>
#include <polyfem/ExpressionValue.hpp>
#include <polyfem/ElementAssemblyValues.hpp>
#include <Eigen/Dense>

namespace polyfem
{
    class SturmLiouville
    {
    public:
        Eigen::Matrix<double, 1, 1> assemble(const ElementAssemblyValues &vals, const int i, const int j, const QuadratureVector &da) const;
        Eigen::Matrix<double, 1, 1> compute_rhs(const AutodiffHessianPt &pt) const;

        Eigen::Matrix<AutodiffScalarGrad, Eigen::Dynamic, 1, 0, 3, 1> kernel(const int dim, const AutodiffScalarGrad &r) const;

        inline int size() const { return 1; }

        void set_parameters(const json &params);

    private:
        double k_ = 1;
        ExpressionValue pweight_;
        ExpressionValue qweight_;
    };
}

