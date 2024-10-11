#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>

float CAPTURE_DISTANCE = 2.0;
float EVADER_VELOCITY = 5.0;


//// IMPLEMENTATION ////
// Implement the pure pursuit algorithm
std::vector<float> pure_pursuit_algorithm(std::vector<float> evader_position, 
    std::vector<float> pursuer_position, float dt)
{
    float heading_cmd = 0.0;
    float vel_cmd = 5.0;

    return {heading_cmd, vel_cmd};
}

// Compute the distance between two points and returns true if within CAPTURE_DISTANCE
bool is_captured(std::vector<float> evader_position, 
    std::vector<float> pursuer_position, float capture_distance)
{
    float distance = 100.0;
    return distance < capture_distance;
}


/// Helper functions ///    
float rad2deg(float rad)
{
    return rad * 180.0 / M_PI;
}

float deg2rad(float deg)
{
    return deg * M_PI / 180.0;
}

std::vector<float> move(std::vector<float> position, 
    float velocity, float heading_cmd, float dt)
{
    float x = position[0];
    float y = position[1];
    float theta = position[2];

    x += velocity * cos(deg2rad(theta)) * dt;
    y += velocity * sin(deg2rad(theta)) * dt;
    theta += heading_cmd * dt;

    return {x, y, theta};
}


// Main function
int main()
{
    float start_time = 0.0;
    float end_time = 10.0;
    float dt = 0.05;
    int num_steps = int((end_time - start_time) / dt);

    std::vector<float> evader_position = {
        0.0, // x    
        0.0, // y
        rad2deg(45.0) // theta
    };

    std::vector<float> pursuer_position = {
        0.0, // x
        0.0, // y
        rad2deg(0.0) // theta
    };

    for (int i = 0; i <= num_steps; i++)
    {
        // printf("Step %d\n", i);
        std::vector<float> control_cmd = pure_pursuit_algorithm(
            evader_position, pursuer_position, dt);

        pursuer_position = move(pursuer_position, 
            control_cmd[0], control_cmd[1], dt);

        evader_position = move(evader_position, 
            EVADER_VELOCITY, 0.0, dt);

        if (is_captured(evader_position, pursuer_position, CAPTURE_DISTANCE))
        {
            printf("Captured at step %d\n", i);
            break;
        }
        
    }
}
