#include "gapped.h"

View::Gapped::Gapped(int gap_y, int gap_x): gap_y(gap_y), gap_x(gap_x) {}

int View::Gapped::get_gap_y() const { return gap_y; }

int View::Gapped::get_gap_x() const { return gap_x; }

void View::Gapped::set_gap_y(int new_gap) { gap_y = new_gap; }

void View::Gapped::set_gap_x(int new_gap) { gap_x = new_gap; }
