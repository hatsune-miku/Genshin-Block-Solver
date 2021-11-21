#include <vector>
#include <iostream>
#include <cstdio>

#include "block2d.hpp"
#include "language.hpp"

void print_solution(std::vector<int> solution);

int main(void) {
    constexpr int       MAX_DEPTH_LIMIT = 7;

    int                 nblocks;
    int                 max_depth;
    int                 state;
    int                 nrelatives;
    int*                relatives;
    char                selection;
    Block2D**           blocks;

    setlocale(LC_ALL, "zh_CN.UTF-8");

    printf("+============================+\n");
    printf("|                            |\n");
    printf(TXT_GENSHIN_SOLVER);
    printf("|                            |\n");
    printf("+============================+\n\n");

    printf(TXT_NUMBER_OF_BLOCKS);
    std::cin >> nblocks;
    blocks = new Block2D*[nblocks];

    for (int i = 0; i < nblocks; ++i) {
        printf(TXT_INFO_FOR_BLOCK, i + 1);

        while (true) {
            printf(TXT_INIT_STATE);
            std::cin >> state;

            if (state < STATE_MIN || state > STATE_MAX) {
                printf(TXT_ERR_ILLEGAL_STATE);
                printf(TXT_REENTER);
            }
            else {
                break;
            }
        }

        while (true) {
            printf(TXT_NUM_RELATIVE);
            std::cin >> nrelatives;
            
            if (nrelatives > nblocks) {
                printf(TXT_ERR_RELATIVE);
                printf(TXT_REENTER);
            }
            else {
                break;
            }
        }

        relatives = new int[nrelatives];

        for (int j = 0; j < nrelatives; ++j) {
            while (true) {
                printf(TXT_RELATIVE_NUMBER, j + 1, nrelatives);
                std::cin >> relatives[j];

                if (relatives[j] > nblocks) {
                    printf(TXT_ERR_RELATIVE_LARGE);
                    printf(TXT_REENTER);
                }
                else {
                    --relatives[j];
                    break;
                }
            }
        }

        blocks[i] = new Block2D(state, nrelatives, relatives);
    }

    while (true) {
        printf(TXT_MUST_WITHIN);
        std::cin >> max_depth;

        if (max_depth > MAX_DEPTH_LIMIT) {
            printf(TXT_ERR_MAX_DEPTH, MAX_DEPTH_LIMIT);
            printf(TXT_REENTER);
        }
        else {
            break;
        }
    }

    printf(TXT_SOLVING);

    Block2DSolver solver(nblocks, blocks);

    if (solver.try_solve(max_depth)) {
        const auto& solutions = solver.solutions();
        int nsolutions = solutions.size();

        if (nsolutions == 0) {
            printf(TXT_ALREADY_SOLVED0);
            printf(TXT_ALREADY_SOLVED1);
        }
        else {
            printf(TXT_FOUND_SOLUTIONS, nsolutions);

            int best_index = 0;
            // Find best.
            for (int i = 1; i < nsolutions; ++i) {
                if (solutions[i].size() < solutions[best_index].size()) {
                    best_index = i;
                }
            }

            printf(TXT_BEST_SOLUTION);
            print_solution(solutions[best_index]);

            printf(TXT_SHOW_OTHER_SOLUTION, nsolutions - 1);
            std::cin >> selection;

            if (selection == 'y' || selection == 'Y') {
                for (int i = 0; i < nsolutions; ++i) {
                    if (i == best_index) {
                        continue;
                    }

                    const auto& solution = solutions[i];

                    // Another +1 to skip the best.
                    printf(TXT_SOLUTION_NUM, i + 1 + 1);
                    print_solution(solution);
                } // for
            }

        } // else
    }
    else {
        printf(TXT_UNABLE_SOLVE0 TXT_UNABLE_SOLVE1, max_depth);
    }

    system("pause");
    return 0;
}

void print_solution(std::vector<int> solution) {
    printf(TXT_SOLVED_IN, solution.size());
    for (int block_index : solution) {
        printf(TXT_HIT_BLOCK, block_index + 1);
    }
}
