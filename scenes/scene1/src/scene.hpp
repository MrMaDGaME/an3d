#pragma once


#include "cgp/cgp.hpp"
#include "environment.hpp"

#include "simulation/simulation.hpp"

using cgp::mesh_drawable;


struct gui_parameters {
	bool display_frame = true;
	bool add_sphere = true;
};

// The structure of the custom scene
struct scene_structure : scene_inputs_generic {

	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //
	camera_controller_orbit_euler camera_control;
	camera_projection_perspective camera_projection;
	window_structure window;

	mesh_drawable global_frame;          // The standard global frame
	environment_structure environment;   // Standard environment controler
	input_devices inputs;                // Storage for inputs status (mouse, keyboard, window dimension)
	gui_parameters gui;                  // Standard GUI element storage

	// ****************************** //
	// Elements and shapes of the scene
	// ****************************** //
	cgp::timer_event_periodic timer;
	particle_structure ball;
	cgp::mesh_drawable sphere;
    cgp::mesh_drawable plane;
    cgp::mesh_drawable cylinder;
	cgp::curve_drawable cube_wireframe;
    std::vector<plane_structure*> planes;
    std::vector<sphere_structure*> spheres;
    std::vector<moving_sphere_structure*> moving_spheres;
    std::vector<cylinder_structure*> cylinders;
	cgp::skybox_drawable skybox;
	float force = 0.0f;


	// ****************************** //
	// Functions
	// ****************************** //

	void initialize();    // Standard initialization to be called before the animation loop
	void display_frame(); // The frame display to be called within the animation loop
	void display_gui();   // The display of the GUI, also called within the animation loop

	void shotBall(particle_structure* object, float force) const;
	void set_center_of_rotation(vec3 const& new_center);
	void follow_ball(vec3 const& ball_position);

	void mouse_move_event();
	void mouse_click_event();
	void keyboard_event();
	void idle_frame();

	void emit_particle();
	void simulation_step(float dt);
	void sphere_display();

    void plane_display();

    void cylinder_display();
};
