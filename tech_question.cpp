#include <stdio.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <math.h>

float CAPTURE_DISTANCE = 2.0;
float EVADER_VELOCITY = 5.0;

//// -------------- IMPLEMENTATION -------------------------------- ////
// Implement the pure pursuit algorithm
std::vector<float> pure_pursuit_algorithm(
    std::vector<float> evader_position, 
    std::vector<float> pursuer_position, float dt)
{
    float vel_cmd = 10.0;
    float heading_cmd = 0.0;
    // Calculate the heading command keep velocity constant
    return {vel_cmd, heading_cmd};
}

// Compute the distance between two points and returns true if within CAPTURE_DISTANCE
bool is_close(std::vector<float> evader_position, 
    std::vector<float> pursuer_position, float capture_distance)
{
    float distance = 100.0;
    return false;
}


/// --------------Helper functions ----------------------------------- ///    
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

    position[0] += velocity * cos(position[2]) * dt;
    position[1] += velocity * sin(position[2]) * dt;
    position[2] += heading_cmd; //* dt;

    return position;
}

void save_to_csv(std::vector<std::vector<float>> evader_positions, 
    std::vector<std::vector<float>> pursuer_positions)
{
    FILE *f = fopen("pursuit.csv", "w");
    fprintf(f, "evader_x,evader_y,evader_theta,pursuer_x,pursuer_y,pursuer_theta\n");
    for (int i = 0; i < evader_positions.size(); i++)
    {
        fprintf(f, "%f,%f,%f,%f,%f,%f\n", 
            evader_positions[i][0], evader_positions[i][1], evader_positions[i][2],
            pursuer_positions[i][0], pursuer_positions[i][1], pursuer_positions[i][2]);
    }

    fclose(f);
}

// Main function
int main()
{
    float start_time = 0.0;
    float end_time = 10.0;
    float dt = 0.05;
    int num_steps = int((end_time - start_time) / dt);

    std::vector<float> pursuer_position = {
        -15.0, // x
        -15.0, // y
        deg2rad(45.0) // theta
    };

    std::vector<float> evader_position = {
        0.0, // x    
        0.0, // y
        deg2rad(0.0) // theta
    };


    // Used to store the positions of the evader and pursuer
    std::vector<std::vector<float>> evader_positions;
    std::vector<std::vector<float>> pursuer_positions;

    // Simulator loop
    for (int i = 0; i <= num_steps; i++)
    {
        // IMPLEMENT PURSUIT ALGORITHM
        std::vector<float> control_cmd = pure_pursuit_algorithm(
            evader_position, pursuer_position, dt);

        pursuer_position = move(pursuer_position, 
            control_cmd[0], control_cmd[1], dt);

        evader_position = move(evader_position, 
            EVADER_VELOCITY, 0.0, dt);

        evader_positions.push_back(evader_position);
        pursuer_positions.push_back(pursuer_position);

        // IMPLEMENT DISTANCE CHECK
        if (is_close(evader_position, pursuer_position, CAPTURE_DISTANCE))
        {
            printf("Captured at step %d\n", i);
            break;
        }
        
        
    }

    save_to_csv(evader_positions, pursuer_positions);

}
