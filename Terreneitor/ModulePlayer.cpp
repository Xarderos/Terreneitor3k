#include "Globals.h"
#include "Application.h"
#include "ModulePlayer.h"
#include "Primitive.h"
#include "PhysVehicle3D.h"
#include "PhysBody3D.h"

ModulePlayer::ModulePlayer(Application* app, bool start_enabled) : Module(app, start_enabled), vehicle(NULL)
{
	turn = acceleration = brake = 0.0f;
}

ModulePlayer::~ModulePlayer()
{}

// Load assets
bool ModulePlayer::Start()
{
	LOG("Loading player");

	VehicleInfo car;

	// Car properties ----------------------------------------
	car.chassis1_size.Set(3.5f, 3, 7);				//Collision box (1)

	car.chassis2_size.Set(2.5f, 0.5f, 6);			//Base 2  (Black)
	car.chassis3_size.Set(4, 0.5f, 4);				//Base 3  (Black)
	car.chassis4_size.Set(3.5f, 0.4f, 1);			//Base 4  (Black)
	car.chassis5_size.Set(1.5f, 0.5f, 11);			//Base 5  (Red)
	car.chassis6_size.Set(3.5f, 0.25f, 3.5f);		//Base 6  (Red)
	car.chassis7_size.Set(3.5f, 0.4f, 1);			//Base 7  (Black)
	car.chassis8_size.Set(1.75f, 0.3f, 10);			//Base 8  (Grey)
	car.chassis9_size.Set(1.25f, 0.4f, 9);			//Base 9  (Red)
	car.chassis10_size.Set(1.2f, 0.6f, 8);			//Base 10 (Grey)
	car.chassis11_size.Set(1.15f, 0.45f, 3);		//Base 11 (Red)
	car.chassis12_size.Set(0.75f, 0.5f, 0.25f);		//Chair   (Black)
	car.chassis13_size.Set(0.6f, 0.4f, 0.2f);		//Steering Wheel (Black)
	car.chassis14_size.Set(0.75f, 0.3f, 2);			//Base 12 (Orange)
	car.chassis15_size.Set(0.3f, 0.3f, 1.5f);		//Base Aileron 1 (Orange)
	car.chassis16_size.Set(0.3f, 0.3f, 1.5f);		//Base Aileron 2 (Orange)
	car.chassis17_size.Set(0.3f, 0.75f, 0.3f);		//Base Aileron 3 (Orange)
	car.chassis18_size.Set(0.3f, 0.75f, 0.3f);		//Base Aileron 4 (Orange)
	car.chassis19_size.Set(3, 0.1f, 1);				//Aileron 1 (Grey)
	car.chassis20_size.Set(0.1f, 0.4f, 1.1f);		//Aileron 2 (Black)
	car.chassis21_size.Set(0.1f, 0.4f, 1.1f);		//Aileron 3 (Black)

	car.chassis1_offset.Set(0, 1, 0);
	car.chassis2_offset.Set(0, 0, 0);
	car.chassis3_offset.Set(0, 0, 0);
	car.chassis4_offset.Set(0, 0, 4.1f);
	car.chassis5_offset.Set(0, 0.25f, 1);
	car.chassis6_offset.Set(0, 0.35f, 0);
	car.chassis7_offset.Set(0, 0, -4.25f);
	car.chassis8_offset.Set(0, 0.2f, 0.35f);
	car.chassis9_offset.Set(0, 0.5f, 0.5f);
	car.chassis10_offset.Set(0, 0.5f, -0.6f);
	car.chassis11_offset.Set(0, 0.75f, -2.5);
	car.chassis12_offset.Set(0, 1, -0.75f);
	car.chassis13_offset.Set(0, 0.75f, 0.5f);
	car.chassis14_offset.Set(0, 1, -2);
	car.chassis15_offset.Set(0.75f, 0.75f, -4.25f);
	car.chassis16_offset.Set(-0.75f, 0.75f, -4.25f);
	car.chassis17_offset.Set(0.75f, 1, -4.85);
	car.chassis18_offset.Set(-0.75f, 1, -4.85);
	car.chassis19_offset.Set(0, 1.4f, -4.85);
	car.chassis20_offset.Set(1.5f, 1.4f, -4.85);
	car.chassis21_offset.Set(-1.5f, 1.4f, -4.85);

	car.mass = 500.0f;
	car.suspensionStiffness = 15.88f;
	car.suspensionCompression = 0.83f;
	car.suspensionDamping = 0.88f;
	car.maxSuspensionTravelCm = 1000.0f;
	car.frictionSlip = 50.5;
	car.maxSuspensionForce = 6000.0f;

	// Wheel properties ---------------------------------------
	float connection_height = 1.2f;
	float wheel_radius = 0.6f;
	float wheel_width = 0.5f;
	float suspensionRestLength = 1.2f;

	// Don't change anything below this line ------------------

	float half_width = car.chassis1_size.x*0.5f;
	float half_length = car.chassis1_size.z*0.5f;
	
	vec3 direction(0,-1,0);
	vec3 axis(-1,0,0);
	
	car.num_wheels = 4;
	car.wheels = new Wheel[4];

	// FRONT-LEFT ------------------------
	car.wheels[0].connection.Set(half_width - 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[0].direction = direction;
	car.wheels[0].axis = axis;
	car.wheels[0].suspensionRestLength = suspensionRestLength;
	car.wheels[0].radius = wheel_radius;
	car.wheels[0].width = wheel_width;
	car.wheels[0].front = true;
	car.wheels[0].drive = true;
	car.wheels[0].brake = false;
	car.wheels[0].steering = true;

	// FRONT-RIGHT ------------------------
	car.wheels[1].connection.Set(-half_width + 0.3f * wheel_width, connection_height, half_length - wheel_radius);
	car.wheels[1].direction = direction;
	car.wheels[1].axis = axis;
	car.wheels[1].suspensionRestLength = suspensionRestLength;
	car.wheels[1].radius = wheel_radius;
	car.wheels[1].width = wheel_width;
	car.wheels[1].front = true;
	car.wheels[1].drive = true;
	car.wheels[1].brake = false;
	car.wheels[1].steering = true;

	// REAR-LEFT ------------------------
	car.wheels[2].connection.Set(half_width - 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[2].direction = direction;
	car.wheels[2].axis = axis;
	car.wheels[2].suspensionRestLength = suspensionRestLength;
	car.wheels[2].radius = wheel_radius;
	car.wheels[2].width = wheel_width;
	car.wheels[2].front = false;
	car.wheels[2].drive = false;
	car.wheels[2].brake = true;
	car.wheels[2].steering = false;

	// REAR-RIGHT ------------------------
	car.wheels[3].connection.Set(-half_width + 0.3f * wheel_width, connection_height, -half_length + wheel_radius);
	car.wheels[3].direction = direction;
	car.wheels[3].axis = axis;
	car.wheels[3].suspensionRestLength = suspensionRestLength;
	car.wheels[3].radius = wheel_radius;
	car.wheels[3].width = wheel_width;
	car.wheels[3].front = false;
	car.wheels[3].drive = false;
	car.wheels[3].brake = true;
	car.wheels[3].steering = false;

	vehicle = App->physics->AddVehicle(car);
	vehicle->SetPos(0, 20, 10);
	
	return true;
}

// Unload assets
bool ModulePlayer::CleanUp()
{
	LOG("Unloading player");

	return true;
}

// Update: draw background
update_status ModulePlayer::Update(float dt)
{
	turn = acceleration = brake = 0.0f;

	if(App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
	{
		acceleration = MAX_ACCELERATION;
	}

	if(App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
	{
		if(turn < TURN_DEGREES)
			turn +=  TURN_DEGREES;
	}

	if(App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
	{
		if(turn > -TURN_DEGREES)
			turn -= TURN_DEGREES;
	}
	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT) {
		if (vehicle->GetKmh() > 10) {
			acceleration = -MAX_ACCELERATION * 5;
		}
		else if (vehicle->GetKmh() > -MAX_SPEED_BACKWARDS) {
			acceleration = -MAX_ACCELERATION;
		}
	}

	if(App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_REPEAT)
	{
		brake = BRAKE_POWER;
	}

	vehicle->ApplyEngineForce(acceleration);
	vehicle->Turn(turn);
	vehicle->Brake(brake);

	vehicle->Render();

	char title[80];
	sprintf_s(title, "%.1f Km/h", vehicle->GetKmh());
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}



