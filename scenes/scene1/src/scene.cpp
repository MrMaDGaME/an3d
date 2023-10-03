#include "scene.hpp"

using namespace cgp;

void AddPlane(std::vector<plane_structure *> &planes, const std::vector<vec3> &vertices, const vec3 &color) {
    auto *plane = new plane_structure();
    plane->x1 = vertices[0];
    plane->x2 = vertices[1];
    plane->x3 = vertices[2];
    plane->x4 = vertices[3];
    plane->c = color;
    planes.push_back(plane);
}

void scene_structure::initialize() {
    camera_control.initialize(inputs,
                              window); // Give access to the inputs and window global state to the camera controler
    camera_control.set_rotation_axis_z();
    camera_control.look_at({3.0f, 2.0f, 2.0f}, {0, 0, 0}, {0, 0, 1});
    global_frame.initialize_data_on_gpu(mesh_primitive_frame());
    timer.event_period = 0.5f;

    //image_structure image_skybox_template = image_load_file("../assets/skybox_01.jpg");
    image_structure image_skybox_template = image_load_file("../../assets/skybox_debug.png");
    std::vector<image_structure> image_grid = image_split_grid(image_skybox_template, 4, 3);
    skybox.initialize_data_on_gpu();
    skybox.texture.initialize_cubemap_on_gpu(image_grid[1], image_grid[7], image_grid[5], image_grid[3], image_grid[10],
                                             image_grid[4]);
    sphere.initialize_data_on_gpu(mesh_primitive_sphere());
    ball.p = {8, 24, 1};
    ball.r = 0.08f;
    ball.c = {1, 0, 0};
    ball.v = {0, 0, 0};
    ball.m = 1.0f;
    AddPlane(planes, {{-1, -1, 0.5},
                      {1,  -1, 0.5},
                      {1,  1,  0.5},
                      {-1, 1,  0.5}}, {0, 0, 1}); // Spawn plane
    AddPlane(planes, {{-1, -1, 0.75},
                      {-1, 1,  0.75},
                      {-1, 1,  0.5},
                      {-1, -1, 0.5}}, {0, 1, 0}); // Left wall
    AddPlane(planes, {{1, -1, 0.75},
                      {1, -1, 0.5},
                      {-1, -1, 0.5},
                      {-1, -1, 0.75}}, {0, 1, 0}); // Back wall
    AddPlane(planes, {{1, -1, 0.75},
                      {1, 1,  0.75},
                      {1, 1,  0.5},
                      {1, -1, 0.5}}, {0, 1, 0}); // Right wall
    AddPlane(planes, {{1,  1, 0.5},
                      {-1, 1, 0.5},
                      {-1, 2, 0},
                      {1,  2, 0}}, {0, 0, 1}); // Pente
    AddPlane(planes, {{-1, 2, 0},
                      {1,  2, 0},
                      {1,  8, 0},
                      {-1, 8, 0}}, {1, 0, 1}); // Floor
    AddPlane(planes, {{1,  8,  0},
                      {-9, 8,  0},
                      {-9, 10, 0},
                      {1,  10, 0}}, {1, 0.7, 0}); // Corner1_1
    AddPlane(planes, {{-7, 10, 0},
                      {-9, 10, 0},
                      {-9, 13, 0},
                      {-7, 13, 0}}, {1, 0.6, 0}); // Corner1_2
    AddPlane(planes, {{-8.25, 13, 0},
                      {-7.75, 13, 0},
                      {-7.75, 15, 0},
                      {-8.25, 15, 0}}, {1, 0.5, 0}); // Bridge
    AddPlane(planes, {{-7, 15, 0},
                      {-9, 15, 0},
                      {-9, 17, 0},
                      {-7, 17, 0}}, {1, 0.4, 0}); // Corner2_1
    AddPlane(planes, {{-9, 17, 0},
                      {-9, 19, 0},
                      {-3, 19, 0},
                      {-3, 17, 0}}, {1, 0.3, 0}); // Corner2_2

    AddPlane(planes, {{-3, 17, 0},
                      {-3, 19, 0},
                      {-1, 19, -0.5},
                      {-1, 17, -0.5}}, {0, 0, 1}); // Pente originale
    AddPlane(planes, {{-1, 17, -0.5},
                      {-1, 19, -0.5},
                      {1,  19, -0.5},
                      {1,  17, -0.5}}, {0, 0, 1}); // middle scene plane
    AddPlane(planes, {{1, 17, -0.5},
                      {1, 19, -0.5},
                      {3, 19, 0},
                      {3, 17, 0}}, {0, 0, 1}); // Pente

    AddPlane(planes, {{9, 17, 0},
                      {9, 19, 0},
                      {3, 19, 0},
                      {3, 17, 0}}, {1, 0.3, 0}); // Corner2_2 x = -x
    AddPlane(planes, {{7, 21, 0},
                      {9, 21, 0},
                      {9, 19, 0},
                      {7, 19, 0}}, {1, 0.4, 0}); // Corner2_1 y = 18 + (18 - y)
    AddPlane(planes, {{8.25, 23, 0},
                      {7.75, 23, 0},
                      {7.75, 21, 0},
                      {8.25, 21, 0}}, {1, 0.5, 0}); // Bridge
    AddPlane(planes, {{7, 23, 0},
                      {9, 23, 0},
                      {9, 26, 0},
                      {7, 26, 0}}, {1, 0.6, 0});
    AddPlane(planes, {{-1, 26, 0},
                      {9,  26, 0},
                      {9,  28, 0},
                      {-1, 28, 0}}, {1, 0.7, 0});
    AddPlane(planes, {{-1, 28, 0},
                      {1,  28, 0},
                      {1,  36, 0},
                      {-1, 36, 0}}, {1, 0.8, 0});
    AddPlane(planes, {{1,  36, 0},
                      {-1, 36, 0},
                      {-1, 37, 0.5},
                      {1,  37, 0.5}}, {0, 0, 1}); // Pente
    AddPlane(planes, {{1,  37, 0.5},
                      {-1, 37, 0.5},
                      {-1, 39, 0.5},
                      {1,  39, 0.5}}, {0, 0, 1}); // Pente
}

void scene_structure::display_frame() {
    // Set the light to the current position of the camera
    environment.light = camera_control.camera_model.position();
    //draw(skybox, environment);
    if (gui.display_frame)
        draw(global_frame, environment);
    timer.update();

    // Call the simulation of the particle system
    float const dt = 0.01f * timer.scale;
    simulate(ball, planes, spheres, moving_spheres, dt);
    sphere_display();
    plane_display();
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
    for (auto &sphere_struct: spheres) {
        sphere.material.color = sphere_struct->c;
        sphere.model.translation = sphere_struct->p;
        sphere.model.scaling = sphere_struct->r;
        draw(sphere, environment);
    }
    for (auto &moving_sphere_struct: moving_spheres) {
        sphere.material.color = moving_sphere_struct->c;
        sphere.model.translation = moving_sphere_struct->p;
        sphere.model.scaling = moving_sphere_struct->r;
        draw(sphere, environment);
    }
}

void scene_structure::plane_display() {
    for (auto &plane_struct: planes) {
        plane.initialize_data_on_gpu(
                mesh_primitive_quadrangle(plane_struct->x1, plane_struct->x2, plane_struct->x3, plane_struct->x4));
        plane.material.color = plane_struct->c;
        draw(plane, environment);
    }
}

void scene_structure::display_gui() {
    ImGui::Checkbox("Frame", &gui.display_frame);
    ImGui::SliderFloat("Time scale", &timer.scale, 0.05f, 2.0f, "%.2f s");
    ImGui::SliderFloat("Time to add new sphere", &timer.event_period, 0.05f, 2.0f, "%.2f s");
    ImGui::Checkbox("Add sphere", &gui.add_sphere);
}

void scene_structure::shotBall(particle_structure *ball, float force) {
    // Apply force depending on camera orientation
    // Pos = camera_control.camera_model.position();
    auto pos = camera_control.camera_model.position();
    auto orientation = camera_control.camera_model.orientation();

    // Calculte the angle between the camera and the ball
    //auto angle = std::acos(dot(normalize(ball->p - pos), normalize(ball->v)));

    ball->v = -force * orientation * vec3(0, 0, 1);
    ball->c = {1, 0, 0};
    ball->m = 1.0f;
    // Make the camera look at the ball
    std::cout << pos << std::endl;
}

void scene_structure::set_center_of_rotation(vec3 const &new_center) {
    camera_control.camera_model.center_of_rotation = new_center;
}

vec3 lerp(vec3 start, vec3 end, float factor) {
    return start + factor * (end - start);
}

const float desiredDistanceBehindBall = 5.0f;
const float timeAhead = 2.0f;
const float smoothFactor = 0.1f; // Ajustez cette valeur pour rendre la transition plus rapide ou plus lente

vec3 smooth_interpolate(vec3 current, vec3 target, float factor) {
    return current + factor * (target - current);
}

void scene_structure::follow_ball(vec3 const &ball_position) {

    // Calculez un point derrière la balle basé sur sa vitesse
    vec3 cameraOffset = -normalize(ball.v) * desiredDistanceBehindBall;
    vec3 targetCameraPosition = ball_position + cameraOffset;
    targetCameraPosition.z = camera_control.camera_model.position().z;

    // Interpolation lisse entre la position actuelle de la caméra et la position cible
    vec3 newCameraPosition = smooth_interpolate(ball_position, targetCameraPosition, smoothFactor);
    newCameraPosition += vec3{3, 3, 2}; // Ajoutez un peu de hauteur pour que la caméra ne soit pas dans le sol
    // Faites pointer la caméra vers la balle ou légèrement en avant
    vec3 lookAtPoint = ball_position + ball.v;
    camera_control.camera_model.look_at(newCameraPosition, lookAtPoint);
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
    if (inputs.keyboard.shift) {
        shotBall(&ball, 2.0f);
        follow_ball(ball.p);
    }
    // Créer un bouton space pour faire sauter la balle
    if (inputs.keyboard.ctrl) {
        shotBall(&ball, 15.0f);
    }
}

void scene_structure::idle_frame() {
    camera_control.idle_frame(environment.camera_view);
}
