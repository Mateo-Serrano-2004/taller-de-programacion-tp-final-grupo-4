#include "aligner.h"

View::Aligner::Aligner(float alignment_y, float alignment_x):
        alignment_y(alignment_y), alignment_x(alignment_x) {}

float View::Aligner::get_vertical_alignment() const { return alignment_y; }

float View::Aligner::get_horizontal_alignment() const { return alignment_x; }

void View::Aligner::set_vertical_alignment(float new_alignment) { alignment_y = new_alignment; }

void View::Aligner::set_horizontal_alignment(float new_alignment) { alignment_x = new_alignment; }
