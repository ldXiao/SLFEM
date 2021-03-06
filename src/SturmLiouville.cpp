#include "SturmLiouville.hpp"
#include <polyfem/Bessel.hpp>

#include <iostream>
#include <polyfem/autodiff.h>

namespace polyfem
{

    Eigen::Matrix<double, 1, 1> SturmLiouville::assemble(const ElementAssemblyValues &vals, const int i, const int j, const QuadratureVector &da) const
    {
        const Eigen::MatrixXd &gradi = vals.basis_values[i].grad_t_m;
        const Eigen::MatrixXd &gradj = vals.basis_values[j].grad_t_m;
        const Eigen::MatrixXd &point = vals.val;
        int dim = point.cols();
        double res = 0;
        for (int k = 0; k < gradi.rows(); ++k) {
            if(dim==2) {
                res += gradi.row(k).dot(gradj.row(k)) * da(k) * pweight_(point(k, 0), point(k, 1));
                res -= (vals.basis_values[i].val.array() *
                        vals.basis_values[j].val.array() * da.array()).sum() * qweight_(point(k,0),point(k,1)) / gradi.rows();
            }
            else {
                res += gradi.row(k).dot(gradj.row(k)) * da(k) * pweight_(point(k, 0), point(k, 1), point(k, 2)) / gradi.rows();
            }
        }
//        if(dim==2) {
//            res -= (vals.basis_values[i].val.array() *
//                    vals.basis_values[j].val.array() * da.array()).sum() * k_ * k_;
//        }
//        else {
//            res += (vals.basis_values[i].val.array() *
//                    vals.basis_values[j].val.array() * da.array()).sum() * qweight_(point(0,0),point(0,1), point(0,2));
//        }

        return Eigen::Matrix<double, 1, 1>::Constant(res);
    }

    Eigen::Matrix<double, 1, 1> SturmLiouville::compute_rhs(const AutodiffHessianPt &pt, const Eigen::MatrixXd &cordinate) const
    {
        Eigen::Matrix<double, 1, 1> result;
        assert(pt.size() == 1);
        result(0) = pweight_(cordinate(0,0), cordinate(0,1))* pt(0).getHessian().trace()
                + pweightdiffx_(cordinate(0,0), cordinate(0,1)) * pt(0).getGradient()(0)
                + pweightdiffy_(cordinate(0,0), cordinate(0,1)) * pt(0).getGradient()(1)
                + qweight_(cordinate(0,0), cordinate(0,1)) * pt(0).getValue();
        return result;
    }

    void SturmLiouville::set_parameters(const json &params)
    {
        if(params.find("SLparams")!= params.end()) {
            auto weights = params["SLparams"];
            pweight_.init(weights["pweight"]);
            qweight_.init(weights["qweight"]);
            pweightdiffx_.init(weights["pweightdiffx"]);
            pweightdiffy_.init(weights["pweightdiffy"]);
        }
        else{
            pweight_.init(1);
            qweight_.init(0);
            pweightdiffx_.init(0);
            pweightdiffy_.init(0);
        }
    }

//    Eigen::Matrix<AutodiffScalarGrad, Eigen::Dynamic, 1, 0, 3, 1> SturmLiouville::kernel(const int dim, const AutodiffScalarGrad &r) const
//    {
//        Eigen::Matrix<AutodiffScalarGrad, Eigen::Dynamic, 1, 0, 3, 1> res(1);
//
//        if(dim == 2)
//            res(0) = -0.25*bessy0(k_*r);
//        else if(dim == 3)
//            res(0) = 0.25*cos(k_*r)/(M_PI*r);
//        else
//            assert(false);
//
//        return res;
//    }

}
