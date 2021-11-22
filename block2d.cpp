#include "block2d.hpp"
#include <cassert>
#include <stdio.h>


Block2D::Block2D(int state, int n, int* toggle_list, int state_min, int state_max):
    m_state(state),
    m_toggle_list_size(n),
    m_toggle_list(toggle_list),
    m_state_min(state_min),
    m_state_max(state_max) {
    m_provided_list = true;
}


Block2D::~Block2D() {
    if (!m_provided_list && m_toggle_list) {
        delete[] m_toggle_list;
    }
}

int Block2D::enter_next_state() {
    if (++m_state > m_state_max) {
        m_state = m_state_min;
    }
    return m_state;
}

int Block2D::back_to_last_state() {
    if (--m_state < m_state_min) {
        m_state = m_state_max;
    }
    return m_state;
}

void Block2D::toggle(Block2D** p_blocks) {
    for (int i = 0; i < m_toggle_list_size; ++i) {
        p_blocks[m_toggle_list[i]]->enter_next_state();
    }
}

void Block2D::backward(Block2D** p_blocks) {
    for (int i = 0; i < m_toggle_list_size; ++i) {
        p_blocks[m_toggle_list[i]]->back_to_last_state();
    }
}

int Block2D::state() const {
    return m_state;
}

void Block2D::set_state_max(int state_max) {
    this->m_state_max = state_max;
}

void Block2D::set_state_min(int state_min) {
    this->m_state_min = state_min;
}

/*
Block2DSolver::Block2DSolver(std::vector<int>&& out_record, int n, ...):
    n(n),
    m_record(std::move(out_record)) {
    p_blocks = new Block2D*[n];
    m_solved = false;

    va_list vl;
    va_start(vl, n);
    for (int i = 0; i < n; ++i) {
        p_blocks[i] = va_arg(vl, Block2D*);
    }
}
*/

Block2DSolver::Block2DSolver(int n, Block2D** p_blocks, int target_state):
    n(n),
    p_blocks(p_blocks),
    m_target_state(target_state) { 
    
}

Block2DSolver::~Block2DSolver() {

}

bool Block2DSolver::is_solved() {
    for (int i = 0; i < n; ++i) {
        if (p_blocks[i]->state() != m_target_state) {
            return false;
        }
    }
    return true;
}

bool Block2DSolver::try_solve(int max_depth) {
    m_record.clear();
    m_solutions.clear();

    if (is_solved()) {
        return true;
    }

    for (int i = 0; i < n; ++i) {
        _solve(i, max_depth);
    }

    return m_solutions.size() > 0;
}

const std::vector<std::vector<int> >&
Block2DSolver::solutions() {
    return m_solutions;
}

void Block2DSolver::_solve(int index, int cnt) {
    if (cnt <= 0) {
        return;
    }

    p_blocks[index]->toggle(p_blocks);
    m_record.push_back(index);

    if (is_solved()) {
        // New solution.
        m_solutions.push_back(
            std::vector<int>(m_record)
        );
    }
    for (int i = 0; i < n; ++i) {
        _solve(i, cnt - 1);
    }

    p_blocks[index]->backward(p_blocks);
    m_record.pop_back();
}
