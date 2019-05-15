#include "UIState.hpp"
#include "CustomAssemblerUtils.hpp"
#include "CustomState.hpp"
#include "SturmLiouville.hpp"

#include <polyfem/State.hpp>
#include <polyfem/LinearSolver.hpp>
#include <polyfem/StringUtils.hpp>
#include <polyfem/Logger.hpp>

#include <polyfem/Problem.hpp>
//#include <polyfem/AssemblerUtils.hpp>
#include <polyfem/LinearSolver.hpp>
#include <polyfem/Assembler.hpp>

//#include <geogram/basic/command_line.h>
//#include <geogram/basic/command_line_args.h>

using namespace polyfem;
using namespace Eigen;

std::string data_path = "/Users/vector_cat/gits/polySLBVP/data/";





int main(int argc, char **argv)
{
#ifndef WIN32
    setenv("GEO_NO_SIGNAL_HANDLER", "1", 1);
#endif

    GEO::initialize();


//    // Import standard command line arguments, and custom ones
//    GEO::CmdLine::import_arg_group("standard");
//    GEO::CmdLine::import_arg_group("pre");
//    GEO::CmdLine::import_arg_group("algo");


//    CLI::App command_line{"polyfem"};


    std::string path = data_path+"plane_hole.obj";
    std::string output = "";
    std::string vtu = "";
    std::string screenshot = "";
    std::string problem_name = "GenericScalar";
//    std::string json_file = data_path+"run.json";
    json problemparam = R"({"dirichlet_boundary":[{"id": "all", "value": "sin(x+y) "}]})"_json;

//    json sturmliouville_param=R"";
    int n_refs = 0;

    std::string scalar_formulation = "SturmLiouville";
    std::string tensor_formulation = "LinearElasticity"; //"SaintVenant";
    // std::string mixed_formulation = "Stokes"; //"SaintVenant";
    std::string solver = "";

    int discr_order = 1;

    bool use_splines = false;
    bool skip_normalization = false;
    bool p_ref = false;
    bool force_linear = false;
    bool isoparametric = false;
    bool serendipity = false;


    std::string log_file = "";
    bool is_quiet = false;
    int log_level = 1;


    //for debugging
    const ProblemFactory &p_factory = ProblemFactory::factory();

    const AssemblerUtils &assembler = AssemblerUtils::instance();

    const std::vector<std::string> solvers = LinearSolver::availableSolvers();



    json in_args = json({});

    in_args["mesh"] = path;
    in_args["force_linear_geometry"] = force_linear;
    in_args["n_refs"] = n_refs;
    in_args["problem"] = problem_name;
    in_args["normalize_mesh"] = !skip_normalization;
    in_args["problem_params"] = problemparam;

    in_args["scalar_formulation"] = scalar_formulation;
    in_args["tensor_formulation"] = tensor_formulation;
    // in_args["mixed_formulation"] = mixed_formulation;
    in_args["discr_order"] = discr_order;
    in_args["use_spline"] = use_splines;
    in_args["output"] = output;
    in_args["use_p_ref"] = p_ref;
    in_args["iso_parametric"] = isoparametric;
    in_args["serendipity"] = serendipity;

    if (!vtu.empty()) {
        in_args["export"]["vis_mesh"] = vtu;
        in_args["export"]["wire_mesh"] = StringUtils::replace_ext(vtu, "obj");
    }
    if (!solver.empty())
        in_args["solver_type"] = solver;


    UIState::ui_state().launch(log_file, log_level, is_quiet, in_args);


    return EXIT_SUCCESS;
}

