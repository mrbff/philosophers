# Philosophers
This project simulates the classic dining philosophers problem using POSIX threads in C.

The dining philosophers problem is an example used to illustrate synchronization issues in concurrent programming. It involves a group of philosophers sitting around a table, with each philosopher needing both a left and right chopstick to eat. However, there are only as many chopsticks as there are philosophers. This leads to potential deadlocks and starvation if not properly managed.

## Prerequisites
POSIX threads library (pthread), ```gcc``` compiler and ```make``` must be installed on your system.

## Usage
After running ```make``` inside the philo directory you can run the executable:

```./philo [number of philosophers] [time to starve] [time to eat] [time to sleep] [total meals]```.

Last parameter is optional.
