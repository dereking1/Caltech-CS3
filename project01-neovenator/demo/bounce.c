#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "sdl_wrapper.h"
#include "polygon.h"

const double SPEED = 1000;
const double ANGULAR_SPEED = M_PI;
const size_t POINTS = 5;
const double OUTER_RADIUS = 100;
const float R = 0.8;
const float G = 0.2;
const float B = 0.8;
const double WINDOW_WIDTH = 1000;
const double WINDOW_HEIGHT = 500;
const vector_t WINDOW_MAX = {.x = 1000, .y = 500};
const double EXTERIOR_ANGLE = (360 / 5) * M_PI / 180;
const double INTERIOR_ANGLE = (540 / 5) * M_PI / 180;

vector_t vec_rotate_about_point(vector_t vec, double angle, vector_t point) {
    vec = vec_subtract(vec, point);
    vec = vec_rotate(vec, angle);
    vec = vec_add(vec, point);
    return vec;
}

vec_list_t *make_star(vector_t star_center) {
    vec_list_t *star = vec_list_init(POINTS * 2);
    vector_t outer_vec = {.x = 0, .y = OUTER_RADIUS}; // making star from two pentagons (outer and inner).
    outer_vec = vec_add(outer_vec, star_center); // Move outer vector to start at center of star.
    double inner_radius = OUTER_RADIUS*sin(EXTERIOR_ANGLE)/(tan(EXTERIOR_ANGLE)*sin(INTERIOR_ANGLE / 2)); // Did geometry to find inner radius of star given outer radius
    vector_t inner_vec = {.x = 0, .y = inner_radius};
    inner_vec = vec_rotate(inner_vec,  M_PI/5); // First inner vector M_PI/5 radians counterclockwise with respect to first vector from center to outer vertex.
    inner_vec = vec_add(inner_vec, star_center); // Move inner vector to start at center of star.
    for (size_t i = 0; i < POINTS; i++) {
        vector_t *outer_point = malloc(sizeof(vector_t));
        vector_t *inner_point = malloc(sizeof(vector_t));
        *outer_point = vec_rotate_about_point(outer_vec, i*2*M_PI/POINTS, star_center); // pentagon has 5 vertices, rotate vectors by 2*M_PI/5 radians each iteration.
        *inner_point = vec_rotate_about_point(inner_vec, i*2*M_PI/POINTS, star_center);
        vec_list_add(star, outer_point);
        vec_list_add(star, inner_point);
    }
    return star;
}

double update_direction(double dt, double direction, vector_t star_center) {
    double dx = SPEED * dt * cos(direction);
    double dy = SPEED * dt * sin(direction);
    if (star_center.x + OUTER_RADIUS + dx >= WINDOW_WIDTH || star_center.x - OUTER_RADIUS + dx <= 0) {
        direction = M_PI - direction;
    }
    if (star_center.y + OUTER_RADIUS + dy >= WINDOW_HEIGHT || star_center.y - OUTER_RADIUS + dy <= 0) {
        direction *= -1;
    }
    return direction;
}

int main(int argv, char *argc[]) {
    sdl_init(VEC_ZERO, WINDOW_MAX);
    vector_t star_center = vec_multiply(0.5, WINDOW_MAX);
    double direction = 2 * M_PI * (rand() % 10) / 10; // Direction is a randomly chosen angle that is in the interval [0, 2pi].
    double dx;
    double dy;
    vec_list_t *star = make_star(star_center);
    while (!sdl_is_done()) {
        sdl_clear();
        sdl_draw_polygon(star, R, G, B);
        sdl_show();
        double dt = time_since_last_tick();
        direction = update_direction(dt, direction, star_center);
        dx = SPEED * dt * cos(direction);
        dy = SPEED * dt * sin(direction);
        vector_t displacement = {.x = dx, .y = dy};
        polygon_rotate(star, ANGULAR_SPEED * dt, star_center);
        polygon_translate(star, displacement);
        star_center = polygon_centroid(star);
    }
    vec_list_free(star);
    return 0;
}