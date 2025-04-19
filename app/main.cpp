#include "statistics.h"

#include "solver.h"
#include "BancroftSolver.h"
#include "BeckSolver.h"
#include "LinearSolver.h"
#include "LSQSolver.h"
#include "RtkLibSolver.h"
#include "ZhilSolver.h"
#include "SimpleSolver.h"

#include <fstream>
#include <filesystem>

//using namespace PseudorangeMultilateration;

void PrintStatisticsPoints(const std::vector<StatisticsPoint>& stat_graph, std::ostream& ostream) {
    for (const auto& point : stat_graph) {
        ostream << point.deviation << " ";
        for (const auto& stat : point.stats) {
            ostream << stat.stat.avg / point.deviation << " ";
        }
        ostream << '\n';
    }
}

int main() {
    RandomSceneGenerator generator(666);
    const vector<Solver> solvers{
        {BancroftSolver::locate_bancroft, "Bancroft" },
        {BeckSolver::locate_beck, "Beck" },
        {LinearSolver::locate_linear, "Linear" },
        {LSQSolver::locate_LSQ, "LSQ" },
        {RtkLibSolver::locate_rtk_lsq, "RTK"},
        {SimpleSolver::locate_simple, "Simple"}
    };

    // TestMethodError(generator, eigen_solver);
    // TestNoiseError(generator, eigen_solver, 3, 0, 200, 100);

    //const Solver simple(LSQSolver::locate_rtk_lsq, "rtk_lsq");
    const Solver banckroft(BancroftSolver::locate_bancroft, "Bancroft");


    std::cout << SolveSimpleCase(solvers[0]) << '\n';

    std::string base_filename = "zhil_lin_simp_";
    std::string tail_filename = "loc_1200km_log100.txt";
    //for (int locators_count : {3, 4, 5, 6, 7, 10, 20, 100}) {
    for (int locators_count : { 3 }) {
        std::string dyn_filename = base_filename;
        dyn_filename += std::to_string(locators_count);
        dyn_filename += tail_filename;
        std::ofstream file(dyn_filename);
        if (!file.is_open()) {
            std::cout << "Unable to open file \"" << dyn_filename << "\" !\n";
            continue;
        }
        const vector<StatisticsPoint> stat_graph = CompareDeviationErrorsInMethods(locators_count, solvers, generator);
        PrintStatisticsPoints(stat_graph, file);
    }

    printf("THE END\n");

    return 0;
}


