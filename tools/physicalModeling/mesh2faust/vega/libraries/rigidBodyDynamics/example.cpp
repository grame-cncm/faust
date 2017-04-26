#include <stdio.h>
#include "rigidBody.h"

// This example demonstrates how to use the rigidBody.h class
// Example author: Jernej Barbic

// this function prints out the current simulation parameters of the rigid body
void PrintSimulationState(RigidBody * rigidBody)
{
  // query current rigid body parameters
  double x,y,z;
  double velx, vely, velz;
  rigidBody->GetPosition(&x, &y, &z);
  rigidBody->GetVelocity(&velx, &vely, &velz);
  double R[9];
  rigidBody->GetRotation(R);
  double angularVelocity[3];
  rigidBody->GetAngularVelocity(&angularVelocity[0], &angularVelocity[1], &angularVelocity[2]);
  double inertiaTensor[9];
  rigidBody->GetInertiaTensor(inertiaTensor);
    
  // print them out
  printf("Center of mass position: %G %G %G\n", x,y,z);
  printf("Center of mass velocity: %G %G %G\n", velx,vely,velz);
  printf("Current rotation:\n");
  printf("%G %G %G\n", R[0], R[1], R[2]);
  printf("%G %G %G\n", R[3], R[4], R[5]);
  printf("%G %G %G\n", R[6], R[7], R[8]);
  printf("Current angular velocity: %G %G %G\n", 
    angularVelocity[0], angularVelocity[1], angularVelocity[2]);
  printf("Current inertia tensor:\n");
  printf("%G %G %G\n", inertiaTensor[0], inertiaTensor[1], inertiaTensor[2]);
  printf("%G %G %G\n", inertiaTensor[3], inertiaTensor[4], inertiaTensor[5]);
  printf("%G %G %G\n", inertiaTensor[6], inertiaTensor[7], inertiaTensor[8]);
}

int main()
{
  // let's simulate a solid cylinder with a radius of 10 cm, 
  // height of 50 cm, and mass of 10 kg
  double radius = 0.1;
  double height = 0.5;
  double mass = 10.0; 

  // I looked up the inertia tensor formulas for the cylinder in an online reference:
  double inertiaTensorAtRestX = 1.0 / 12 * mass * height * height + 1.0 / 4 * mass * radius * radius;
  double inertiaTensorAtRestY = 0.5 * mass * radius * radius; // our cylinder is aligned with the y-axis direction
  double inertiaTensorAtRestZ = inertiaTensorAtRestX;

  // inertia tensor at rest for the cylinder is diagonal, so we can use the
  // basic (and fast) version of the class
  RigidBody cylinder(mass, 
    inertiaTensorAtRestX, inertiaTensorAtRestY, inertiaTensorAtRestZ);

  // Let's simulate ballistic motion of the cylinder, under Earth's gravity...

  // initial conditions
  cylinder.SetPosition(0,2,0); // set center of mass at (0,2m,0)
  // note: Rotation defaults to identity and we won't explicitly set it 
  cylinder.SetVelocity(1,0,0); // 1m/sec along the x-axis
  cylinder.SetAngularVelocity(1,0,1); // around the center of mass

  double timestep = 1.0 / 30;
  int numTimesteps = 60; // 2 seconds of motion

  // set gravity force
  // note: forces remains in place until explicity set to another value
  // note: the torque due to gravity is always zero; so no need to set it in this case
  cylinder.SetExternalForce(0, -mass * 9.81, 0); 

  for(int i=0; i<numTimesteps; i++)
  {
    printf("==== Timestep %d. Time = %f ======\n", i, i * timestep);
    PrintSimulationState(&cylinder);
    // advance the rigid object to the next timestep
    cylinder.EulerStep(timestep); 
  }

  // now, apply a vertical external force to the center of the top base of the cylinder
  // force magnitude: 10000 N; force duration: one timestep (1.0 / 30 of a second)
  // first, compute the current position of the center of the top base:
  double posx, posy, posz;
  cylinder.GetPointPosition(0,0.5*height,0, &posx, &posy, &posz);
  double forcex = 0;
  double forcey = 10000;
  double forcez = 0;
  cylinder.SetExternalForce(forcex, forcey, forcez);
  cylinder.AddExternalForce(0, -mass * 9.81, 0); // add gravity
  // compute the torque that needs to be applied:
  double torquex, torquey, torquez;
  cylinder.ComputeTorque(posx, posy, posz, forcex, forcey, forcez, &torquex, &torquey, &torquez);
  // don't forget to actually set the torque!!:    
  cylinder.SetExternalTorque(torquex, torquey, torquez); 

  printf("==== Timestep %d. Time = %f ======\n", numTimesteps, numTimesteps * timestep);
  PrintSimulationState(&cylinder);
  // do one simulation step during which the force/torque is applied
  cylinder.EulerStep(timestep); 

  // reset forces and torques
  cylinder.ResetWrenches();
  // add gravity again
  cylinder.SetExternalForce(0, -mass * 9.81, 0); 

  // simulate another 2 seconds of ballistic motion
  for(int i=numTimesteps+1; i<2*numTimesteps; i++)
  {
    printf("==== Timestep %d. Time = %f ======\n", i, i * timestep);
    PrintSimulationState(&cylinder);
    // advance the rigid object to the next timestep
    cylinder.EulerStep(timestep); 
  }

  return 0;
}

