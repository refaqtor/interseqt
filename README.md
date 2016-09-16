# interseqt
version control system backed self-balancing distributed configuration, process management and data aggregation system

This is achieved with identical clients on every device that contain the algorithms to determine, from the replicated whole system configuraton and status data, how to throttle and heal the system continually based on current processor/network/memory loads across all the nodes.  By nature of the distributed version control systems which underlies the distribution of information and backup of data, and exquisitely detailed record of system state transitions is kept, while also minimizing network traffic.

initial use cases for which algorithms and explorations have been developed, in other test code, include:
 - system configuration management and updates 
 - application configuration management and updates 
 - distributed execution of parallel jobs across multiple processor cores and machines
 - collection and aggregation of job results or sensor data
 
