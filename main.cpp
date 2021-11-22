#include <vector>
#include <iostream>
#include <cstdio>

#include "block2d.hpp"
#include "language.hpp"

#define PROMPT_FOR(obj, prompt, condition, fail_alert) \
    while (true) { \
        (prompt); \
        std::cin >> (obj); \
        if (!(condition)) { \
            (fail_alert); \
            printf(TXT_REENTER); \
        } \
        else { \
            break; \
        } \
    }

#define PROMPT_FOR_UNCHECK(obj, prompt) \
    PROMPT_FOR(obj, prompt, true, nullptr)


void print_solution(std::vector<int> solution);

int main(void) {
    constexpr int       MAX_DEPTH_LIMIT = 7;

    int                 state_min;
    int                 state_max;
    int                 state_target;
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

    PROMPT_FOR(
        nblocks, printf(TXT_NUMBER_OF_BLOCKS),
        nblocks > 0,
        printf(TXT_ERR_BLOCKS)
    );

    PROMPT_FOR_UNCHECK(
        state_min, printf(TXT_STATE_MIN)
    );

    PROMPT_FOR(
        state_max, printf(TXT_STATE_MAX),
        state_max >= state_min,
        printf(TXT_ERR_MAX_MIN)
    );

    PROMPT_FOR(
        state_target, printf(TXT_STATE_TARGET),
        state_target >= state_min && state_target <= state_max,
        printf(TXT_ERR_TARGET)
    );
    
    blocks = new Block2D*[nblocks];

    for (int i = 0; i < nblocks; ++i) {
        printf(TXT_INFO_FOR_BLOCK, i + 1);

        PROMPT_FOR(
            state, printf(TXT_INIT_STATE), 
            state >= state_min && state <= state_max,
            printf(TXT_ERR_ILLEGAL_STATE)
        );

        PROMPT_FOR(
            nrelatives, printf(TXT_NUM_RELATIVE), 
            nrelatives <= nblocks,
            printf(TXT_ERR_RELATIVE)
        );

        relatives = new int[nrelatives];

        for (int j = 0; j < nrelatives; ++j) {
            PROMPT_FOR(
                relatives[j], printf(TXT_RELATIVE_NUMBER, j + 1, nrelatives), 
                relatives[j] <= nblocks,
                printf(TXT_ERR_RELATIVE_LARGE)
            );
            --relatives[j];
        }

        blocks[i] = new Block2D(
            state, nrelatives, relatives,
            state_min, state_max
        );
    }

    PROMPT_FOR(
        max_depth, printf(TXT_MUST_WITHIN),
        max_depth <= MAX_DEPTH_LIMIT,
        printf(TXT_ERR_MAX_DEPTH, MAX_DEPTH_LIMIT)
    );
    
    printf(TXT_SOLVING);

    Block2DSolver solver(nblocks, blocks, state_target);

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

            // More solutions?
            if (nsolutions > 1) {
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
            } // endif
        } // else
    }
    else {
        printf(TXT_UNABLE_SOLVE0 TXT_UNABLE_SOLVE1, max_depth);
    }

    printf("\n");
    system("pause");

    printf(TXT_EXIT);
    system("pause");
    return 0;
}

void print_solution(std::vector<int> solution) {
    printf(TXT_SOLVED_IN, solution.size());
    for (int block_index : solution) {
        printf(TXT_HIT_BLOCK, block_index + 1);
    }
}
