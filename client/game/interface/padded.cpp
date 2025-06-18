#include "padded.h"

View::Padded::Padded(int padding): padding(padding) {}

int View::Padded::get_padding() const { return padding; }

void View::Padded::set_padding(int new_padding) { padding = new_padding; }
