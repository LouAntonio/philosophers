# philosophers
The dining philosophers problem

<img src="https://github.com/LouAntonio/LouAntonio/blob/main/resources/philo.png" style="width: 100%"/>

According to [Wikipedia](https://en.wikipedia.org/wiki/Dining_philosophers_problem), in computer science, the dining philosophers problem is an example problem often used in concurrent algorithm design to illustrate synchronization issues and techniques for resolving them.

It was originally formulated in 1965 by Edsger Dijkstra as a student exam exercise, presented in terms of computers competing for access to tape drive peripherals. Soon after, Tony Hoare gave the problem its present form.

The problem was designed to illustrate the challenges of avoiding deadlock, a system state in which no progress is possible. To see that a proper solution to this problem is not obvious, consider a proposal in which each philosopher is instructed to behave as follows:

 - Think unless the left fork is available; when it is, pick it up;
 - Think unless the right fork is available; when it is, pick it up;
 - When both forks are held, eat for a fixed amount of time;
 - Put the left fork down;
 - Put the right fork down;
 - Repeat from the beginning.
   
With these instructions, the situation may arise where each philosopher holds the fork to their left; in that situation, they will all be stuck forever, waiting for the other fork to be available: it is a deadlock.

<a href="#">
    <img src="https://github.com/LouAntonio/LouAntonio/blob/main/resources/philo_eval.png"/>
</a>
