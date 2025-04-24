#include "statistics.h"

#include "solver.h"
#include "BancroftSolver.h"
#include "BeckSolver.h"
#include "GradSolver.h"
#include "LinearSolver.h"
#include "LinearSolver_mul2.h"
#include "LSQSolver.h"
#include "RtkLibSolver.h"
#include "ZhilSolver.h"
#include "SimpleSolver.h"
#include "SimpleSolver_mul2.h"

#include <fstream>
#include <filesystem>

//using namespace PseudorangeMultilateration;

void PrintStatisticsPoints(const std::vector<StatisticsPoint>& stat_graph, std::ostream& ostream) {
    for (const auto& point : stat_graph) {
        ostream << point.deviation << ";";
        for (const auto& stat : point.stats) {
            ostream << stat.stat.avg / point.deviation << ";";
        }
        ostream << '\n';
    }
}

// Функция для инициализации вектора решателей
std::vector<Solver> initialize_solvers() {
    return {
        {BancroftSolver::locate_bancroft, "Bancroft" },
        {BeckSolver::locate_beck, "Beck" },
        {GradSolver::locate_grad, "Grad" },
        {LinearSolver::locate_linear, "Linear" },
        {LinearSolver_mul2::locate_linear, "Linear_mul2" },
        {LSQSolver::locate_LSQ, "LSQ" },
        {RtkLibSolver::locate_rtk_lsq, "RTK"},
        {SimpleSolver::locate_simple, "Simple"},
        {SimpleSolver_mul2::locate_simple, "Simple_mul2"},
        {ZhilSolver::locate_zhil, "Zhil"}
    };
}

int main(int argc, char* argv[]) {
    RandomSceneGenerator generator(666);

    std::vector<Solver> all_solvers = initialize_solvers();
    std::vector<Solver> selected_solvers;

    // Обработка аргументов командной строки
    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];
        for (const auto& solver : all_solvers) {
            if (arg == solver.GetDesignator()) {
                selected_solvers.push_back(solver);
                break;
            }
        }
    }

    //Если не указаны решатели, используем все
    if (selected_solvers.empty()) {
        selected_solvers = all_solvers;
    }

    std::string base_filename = "plot_data";
    std::string tail_filename = ".txt";
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
        const vector<StatisticsPoint> stat_graph = CompareDeviationErrorsInMethods(locators_count, selected_solvers, generator);
        
        file << "dev;";

        for (const auto& solver : selected_solvers) {
                const std::string solver_name = solver.GetDesignator();
                file << solver_name << ";";
        }
        file << "\n";
        
        PrintStatisticsPoints(stat_graph, file);
    }

    return 0;
}


