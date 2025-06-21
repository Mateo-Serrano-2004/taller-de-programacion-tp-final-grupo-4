#include "line.h"

#include "controller/game_controller.h"

View::Line::Line(Weak<Controller::GameController> controller)
: View::HorizontalPane(controller), first_item(controller), second_item(controller) {
    set_width(400);
    set_height(20);
    add_child(&first_item);
    add_child(&second_item);
    first_item.set_width(200);
    first_item.set_background_color(31, 45, 31, 255);
    first_item.set_draw_background(true);
    second_item.set_width(200);
    second_item.set_background_color(31, 45, 31, 255);
    second_item.set_draw_background(true);
}
