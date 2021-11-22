#include <cstdarg>
#include <vector>

#ifndef OUT
#define OUT
#endif


class Block2D {
protected:
    int m_state;
    int* m_toggle_list;
    int m_toggle_list_size;
    bool m_provided_list;
    int m_state_max;
    int m_state_min;

public:
    explicit Block2D(
        int state, 
        int n, int* toggle_list, 
        int state_min, 
        int state_max
    );
    virtual ~Block2D();

    int enter_next_state();
    int back_to_last_state();
    void toggle(Block2D** p_blocks);
    void backward(Block2D** p_blocks);
    int state() const;

    void set_state_max(int state_max);
    void set_state_min(int state_min);
};

class Block2DSolver {
protected:
    Block2D** p_blocks;
    int n;
    int m_target_state;

    std::vector<int> m_record;
    std::vector<std::vector<int> > m_solutions;

public:
    explicit Block2DSolver(int n, Block2D** p_blocks, int target_state);
    virtual ~Block2DSolver();

    bool is_solved();
    bool try_solve(int max_depth);
    const std::vector<std::vector<int> >& solutions();

protected:
    void _solve(int index, int cnt);
};
