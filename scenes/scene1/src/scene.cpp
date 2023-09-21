#include "scene.hpp"

using namespace cgp;

void scene_structure::initialize() {
    camera_control.initialize(inputs,
                              window); // Give access to the inputs and window global state to the camera controler
    camera_control.set_rotation_axis_z();
    camera_control.look_at({3.0f, 2.0f, 2.0f}, {0, 0, 0}, {0, 0, 1});
    global_frame.initialize_data_on_gpu(mesh_primitive_frame());
    timer.event_period = 0.5f;

    // Edges of the containing cube
    //  Note: this data structure is set for display purpose - don't use it to compute some information on the cube - it would be un-necessarily complex
    /*numarray<vec3> cube_wireframe_data = {{-1, -1, -1},
                                          {1,  -1, -1},
                                          {1,  -1, -1},
                                          {1,  1,  -1},
                                          {1,  1,  -1},
                                          {-1, 1,  -1},
                                          {-1, 1,  -1},
                                          {-1, -1, -1},
                                          {-1, -1, 1},
                                          {1,  -1, 1},
                                          {1,  -1, 1},
                                          {1,  1,  1},
                                          {1,  1,  1},
                                          {-1, 1,  1},
                                          {-1, 1,  1},
                                          {-1, -1, 1},
                                          {-1, -1, -1},
                                          {-1, -1, 1},
                                          {1,  -1, -1},
                                          {1,  -1, 1},
                                          {1,  1,  -1},
                                          {1,  1,  1},
                                          {-1, 1,  -1},
                                          {-1, 1,  1}};
    cube_wireframe.initialize_data_on_gpu(cube_wireframe_data);*/
    sphere.initialize_data_on_gpu(mesh_primitive_sphere());
    plane.initialize_data_on_gpu(mesh_primitive_quadrangle());
    ball.p = {0, 0, 1};
    ball.r = 0.08f;
    ball.c = {1, 0, 0};
    ball.v = {1, 0, 0};
    ball.m = 1.0f;
    auto *plane = new plane_structure();
    plane->p = {0, 0, 0};
    plane->n = {0, 0, 1};
    plane->c = {0, 0, 1};
    plane->s = 10.0f;
    ground.push_back(plane);
}

void scene_structure::display_frame() {
    // Set the light to the current position of the camera
    environment.light = camera_control.camera_model.position();
    if (gui.display_frame)
        draw(global_frame, environment);
    timer.update();

    // Create a new particle if needed
//    emit_particle();

    // Call the simulation of the particle system
    float const dt = 0.01f * timer.scale;
    simulate(ball, ground, dt);
    sphere_display();
    plane_display();
//    draw(plane, environment);
    // Display the result
    if (gui.display_frame)
        draw(global_frame, environment);
}

void scene_structure::sphere_display() {
    // Display the particles as spheres
    sphere.material.color = ball.c;
    sphere.model.translation = ball.p;
    sphere.model.scaling = ball.r;
    draw(sphere, environment);

    // Display the box in which the particles should stay
    draw(cube_wireframe, environment);
}

void scene_structure::plane_display() {
    for (auto &plane_struct: ground) {
        vec3 offset = {0.5f * plane_struct->s, 0.5f * plane_struct->s, 0.0f};
        plane.model.translation = plane_struct->p - offset;
        plane.model.scaling = plane_struct->s;
        plane.material.color = plane_struct->c;
        // rotation ???
        draw(plane, environment);
    }
}

/*void scene_structure::emit_particle() {
    // Emit particle with random velocity
    //  Assume first that all particles have the same radius and mass
    static numarray<vec3> const color_lut = {{1, 0, 0},
                                             {0, 1, 0},
                                             {0, 0, 1},
                                             {1, 1, 0},
                                             {1, 0, 1},
                                             {0, 1, 1}};
    if (timer.event && gui.add_sphere) {
        float const theta = rand_interval(0, 2 * Pi);
        vec3 const v = vec3(1.0f * std::cos(theta), 1.0f * std::sin(theta), 4.0f);
        particle_structure particle;
        particle.p = {0, 0, 0};
        particle.r = 0.08f;
        particle.c = color_lut[int(rand_interval() * color_lut.size())];
        particle.v = v;
        particle.m = 1.0f; //

        particles.push_back(particle);
    }
}*/

void scene_structure::display_gui() {
    ImGui::Checkbox("Frame", &gui.display_frame);
    ImGui::SliderFloat("Time scale", &timer.scale, 0.05f, 2.0f, "%.2f s");
    ImGui::SliderFloat("Time to add new sphere", &timer.event_period, 0.05f, 2.0f, "%.2f s");
    ImGui::Checkbox("Add sphere", &gui.add_sphere);
}

void scene_structure::mouse_move_event() {
    if (!inputs.keyboard.shift)
        camera_control.action_mouse_move(environment.camera_view);
}

void scene_structure::mouse_click_event() {
    camera_control.action_mouse_click(environment.camera_view);
}

void scene_structure::keyboard_event() {
    camera_control.action_keyboard(environment.camera_view);
}

void scene_structure::idle_frame() {
    camera_control.idle_frame(environment.camera_view);
}
