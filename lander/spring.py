# uncomment the next line if running in a notebook
# %matplotlib inline
import numpy as np
import matplotlib.pyplot as plt

g_m = 1
g_k = 1
g_x = 0
g_v = 1

# simulation time, timestep and time
g_t_max = 100
g_dt = 0.001
g_t_array = np.arange(0, g_t_max, g_dt)


def Euler():
    
    # mass, spring constant, initial position and velocity
    m = g_m
    k = g_k
    x = g_x
    v = g_v

    # simulation time, timestep and time
    t_max = g_t_max
    dt = g_dt
    t_array = np.arange(0, g_t_max, g_dt)

    # initialise empty lists to record trajectories
    x_list = []
    v_list = []

    # Euler integration
    for t in t_array:

        # append current state to trajectories
        x_list.append(x)
        v_list.append(v)

        # calculate new position and velocity
        a = -k * x / m
        x = x + dt * v
        v = v + dt * a
    # convert trajectory lists into arrays, so they can be sliced (useful for Assignment 2)
    x_array = np.array(x_list)
    v_array = np.array(v_list)
    return x_array, v_array

def Verlet():
    
    # mass, spring constant, initial position and velocity
    m = g_m
    k = g_k
    x = g_x
    v = g_v

    # simulation time, timestep and time
    t_max = g_t_max
    dt = g_dt
    t_array = np.arange(0, t_max, dt)


    xplus1 = g_x + v * dt

    # initialise empty lists to record trajectories
    x_list = []
    v_list = []
    
    for t in range(1,len(t_array)):
        if not x_list:
            x_list.append(x)
            x_list.append(xplus1)
            # v_list.append(v)
            continue
        x_list.append(x)
        
        a = -k * x / m
        x = 2 * x - x_list[t-1] + dt**2 * a
    
    return x_list
        

x_array, v_array = Euler()
vx_array = Verlet()

# plot the position-time graph
plt.figure(1)
plt.clf()
plt.xlabel('time (s)')
plt.grid()
plt.plot(g_t_array, x_array, label='x (m)')
plt.plot(g_t_array, v_array, label='v (m/s)')
plt.plot(g_t_array, vx_array, label='verlet x (m/s)')
plt.legend()
plt.show()
