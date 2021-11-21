#include <cstdarg>
#include <vector>

#ifndef OUT
#define OUT
#endif

constexpr int STATE_MAX = 3;
constexpr int STATE_MIN = 1;

class Block2D {
protected:
    int m_state;
    int* m_toggle_list;
    int m_toggle_list_size;
    bool m_provided_list;

public:
    // explicit Block2D(int state, int n, ...);
    explicit Block2D(int state, int n, int* toggle_list);
    virtual ~Block2D();

    int enter_next_state();
    int back_to_last_state();
    void toggle(Block2D** p_blocks);
    void backward(Block2D** p_blocks);
    int state() const;
};

class Block2DSolver {
protected:
    Block2D** p_blocks;
    int n;

    std::vector<int> m_record;
    std::vector<std::vector<int> > m_solutions;

public:
    // explicit Block2DSolver(std::vector<int>&& out_record, int n, ...);
    explicit Block2DSolver(int n, Block2D** p_blocks);
    virtual ~Block2DSolver();

    bool is_solved();
    bool try_solve(int max_depth);
    const std::vector<std::vector<int> >& solutions();

protected:
    void _solve(int index, int cnt);
};
