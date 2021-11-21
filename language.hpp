
#define CHINESE

#ifdef CHINESE

#define TXT_NUMBER_OF_BLOCKS    "总方块数: "
#define TXT_INFO_FOR_BLOCK      "\n=== 方块 #%d 信息 ===\n"
#define TXT_INIT_STATE          "  初始点亮片数: "
#define TXT_ERR_ILLEGAL_STATE   "  \t错误: 非法的点亮片数数值!\n"
#define TXT_REENTER             "  \t请重新输入...\n"
#define TXT_NUM_RELATIVE        "  关联方块数: "
#define TXT_ERR_RELATIVE        "\t错误: 关联方块数不能多于方块总数!\n"
#define TXT_RELATIVE_NUMBER     "\t输入第 %d/%d 个关联方块编号: "
#define TXT_ERR_RELATIVE_LARGE  "\t\t错误: 关联方块编号不能多余方块总数!\n"
#define TXT_MUST_WITHIN         "\n 限定在多少步内完成: "
#define TXT_ERR_MAX_DEPTH       "\t错误: 最多不能超过 %d 步!\n"
#define TXT_ALREADY_SOLVED0     "\t这个问题此前已经解开了，无需再解\n"
#define TXT_ALREADY_SOLVED1     "\t看一下附近有无宝箱？\n"
#define TXT_FOUND_SOLUTIONS     "找到 %d 种解法。\n"
#define TXT_BEST_SOLUTION       "\n=== 最短解法 ===\n"
#define TXT_SHOW_OTHER_SOLUTION "要查看其它 %d 种解法吗? (Y/N): "
#define TXT_SOLUTION_NUM        "\n=== 解法 #%d ===\n"
#define TXT_UNABLE_SOLVE0       "\t未能在 %d 步内解开这道题，\n"
#define TXT_UNABLE_SOLVE1       "\t请检查输入的数据是否有误。"
#define TXT_SOLVED_IN           "共用 %d 步: \n"
#define TXT_HIT_BLOCK           "\t击打 %d 号方块\n"
#define TXT_SOLVING             "\n正在解题...\n"
#define TXT_GENSHIN_SOLVER      "|    Genshin Block Solver    |\n"

#else

#define TXT_NUMBER_OF_BLOCKS    "Number of blocks: "
#define TXT_INFO_FOR_BLOCK      "\n=== Info for Block #%d ===\n"
#define TXT_INIT_STATE          "  Init state: "
#define TXT_ERR_ILLEGAL_STATE   "  \tError: illegal state!\n"
#define TXT_REENTER             "  \tPlease re-enter...\n"
#define TXT_NUM_RELATIVE        "  Number of relative blocks: "
#define TXT_ERR_RELATIVE        "\tError: relatives must no more than blocks!\n"
#define TXT_RELATIVE_NUMBER     "\t(%d/%d) Relative block number: "
#define TXT_ERR_RELATIVE_LARGE  "\t\tError: relative number too large!\n"
#define TXT_MUST_WITHIN         "\n Must Within how many steps: "
#define TXT_ERR_MAX_DEPTH       "\tError: max depth no more than %d!\n"
#define TXT_ALREADY_SOLVED0     "\tThe problem seems to be already solved.\n"
#define TXT_ALREADY_SOLVED1     "\tCheck if teasure chests are around you.\n"
#define TXT_FOUND_SOLUTIONS     "Found %d solution(s).\n"
#define TXT_BEST_SOLUTION       "\n=== Best Solution ===\n"
#define TXT_SHOW_OTHER_SOLUTION "Show other %d solution(s)? (Y/N): "
#define TXT_SOLUTION_NUM        "\n=== Solution #%d ===\n"
#define TXT_UNABLE_SOLVE0       "\tUnable to solve this problem\n"
#define TXT_UNABLE_SOLVE1       "\tin a maximum %d steps."
#define TXT_SOLVED_IN           "Solved in %d steps:\n"
#define TXT_HIT_BLOCK           "\tHit block #%d\n"
#define TXT_SOLVING             "\nSolving...\n"
#define TXT_GENSHIN_SOLVER      "|    Genshin Block Solver    |\n"

#endif

// g++ block2d.cpp main.cpp -O3 -o genshin_block_solver.exe
