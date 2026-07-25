#include <iostream>
#include <fstream>
#include <vector>
#include <chrono>

using namespace std;

int main() {

  auto t1 = std::chrono::high_resolution_clock::now();

  // declare variables
  double m, k, x, v, xplus1, vplus1, t_max, dt, t, a;
  vector<double> t_list, x_list, v_list;

  // mass, spring constant, initial position and velocity
  m = 1;
  k = 1;
  x = 0;
  v = 1;


  // simulation time and timestep
  t_max = 1000000;
  dt = 0.1;

  xplus1 = x + v * dt;
  vplus1 = v;

  // Euler integration
  for (t = 0; t <= t_max; t = t + dt) {

    if (x_list.empty()) {
        x_list.push_back(x);
        v_list.push_back(v);
        x_list.push_back(xplus1);
        v_list.push_back(vplus1);
    }
    else {
        // append current state to trajectories
        t_list.push_back(t);
        x_list.push_back(x);
        v_list.push_back(v);

        // calculate new position and velocity
        a = -k * x / m;
        x = 2 * x - x_list[t - 1] + std::pow(dt,2) * a;
        v = (1 / dt) * (x - x_list[t]);
    }


  }
  auto t2 = std::chrono::high_resolution_clock::now();



  std::cout << "f() took "
      << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count()
      << " milliseconds\n";

  // Write the trajectories to file
  ofstream fout;
  fout.open("trajectories.txt");
  if (fout) { // file opened successfully
    for (int i = 0; i < t_list.size(); i = i + 1) {
      fout << t_list[i] << ' ' << x_list[i] << ' ' << v_list[i] << endl;
    }
  } else { // file did not open successfully
    cout << "Could not open trajectory file for writing" << endl;
  }

  /* The file can be loaded and visualised in Python as follows:

  import numpy as np
  import matplotlib.pyplot as plt
  results = np.loadtxt('trajectories.txt')
  plt.figure(1)
  plt.clf()
  plt.xlabel('time (s)')
  plt.grid()
  plt.plot(results[:, 0], results[:, 1], label='x (m)')
  plt.plot(results[:, 0], results[:, 2], label='v (m/s)')
  plt.legend()
  plt.show()

  */
}
