#include "scalator.h"

Scalator::Scalator(): x_factor(1.0), y_factor(1.0) {}

Scalator::Scalator(float factor): x_factor(factor), y_factor(factor) {}

Scalator::Scalator(float x_factor, float y_factor): x_factor(x_factor), y_factor(y_factor) {}

void Scalator::set_x_factor(float new_x_factor) {
    x_factor = new_x_factor;
}

void Scalator::set_y_factor(float new_y_factor) {
    y_factor = new_y_factor;
}

void Scalator::set_factor(float new_factor) {
    x_factor = new_factor;
    y_factor = new_factor;
}
