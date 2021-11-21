#include <vector>
#include <iostream>
#include <cstdio>

#include "block2d.hpp"

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

    printf("+============================+\n");
    printf("|                            |\n");
    printf("|    Genshin Block Solver    |\n");
    printf("|                            |\n");
    printf("+============================+\n\n");

    printf("Number of blocks: ");
    std::cin >> nblocks;
    blocks = new Block2D*[nblocks];

    for (int i = 0; i < nblocks; ++i) {
        printf("\n=== Info for Block #%d ===\n", i + 1);

        while (true) {
            printf("  Init state: ");
            std::cin >> state;

            if (state < STATE_MIN || state > STATE_MAX) {
                printf("\tError: illegal state!\n");
                printf("\tPlease re-enter...\n");
            }
            else {
                break;
            }
        }

        while (true) {
            printf("  Number of relative blocks: ");
            std::cin >> nrelatives;
            
            if (nrelatives > nblocks) {
                printf("\tError: relatives must no more than blocks!\n");
                printf("\tPlease re-enter...\n");
            }
            else {
                break;
            }
        }

        relatives = new int[nrelatives];

        for (int j = 0; j < nrelatives; ++j) {
            while (true) {
                printf("\t(%d/%d) Relative block number: ", j + 1, nrelatives);
                std::cin >> relatives[j];

                if (relatives[j] > nblocks) {
                    printf("\t\tError: relative number too large!\n");
                    printf("\t\tPlease re-enter...\n");
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
        printf("\n Must Within how many steps: ");
        std::cin >> max_depth;

        if (max_depth > MAX_DEPTH_LIMIT) {
            printf("\tError: max depth no more than %d!\n", MAX_DEPTH_LIMIT);
            printf("\t\tPlease re-enter...\n");
        }
        else {
            break;
        }
    }

    printf("\nSolving...\n");

    Block2DSolver solver(nblocks, blocks);

    if (solver.try_solve(max_depth)) {
        const auto& solutions = solver.solutions();
        int nsolutions = solutions.size();

        if (nsolutions == 0) {
            printf("\tThe problem seems to be already solved.\n");
            printf("\tCheck if teasure chests are around you.\n");
        }
        else {
            printf("Found %d solutions.\n", nsolutions);

            int best_index = 0;
            // Find best.
            for (int i = 1; i < nsolutions; ++i) {
                if (solutions[i].size() < solutions[best_index].size()) {
                    best_index = i;
                }
            }

            printf("\n=== Best Solution ===\n");
            print_solution(solutions[best_index]);

            printf("Show other %d solutions? (Y/N): ", nsolutions - 1);
            std::cin >> selection;

            if (selection == 'y' || selection == 'Y') {
                for (int i = 0; i < nsolutions; ++i) {
                    if (i == best_index) {
                        continue;
                    }

                    const auto& solution = solutions[i];

                    // Another +1 to skip the best.
                    printf("\n=== Solution #%d ===\n", i + 1 + 1);
                    print_solution(solution);
                } // for
            }

        } // else
    }
    else {
        printf("\tUnable to solve this problem\n" \
               "\tin a maximum %d steps.", max_depth);
    }

    system("pause");
    return 0;
}

void print_solution(std::vector<int> solution) {
    printf("Solved in %d steps:\n", solution.size());
    for (int block_index : solution) {
        printf("\tHit block #%d\n", block_index + 1);
    }
}
