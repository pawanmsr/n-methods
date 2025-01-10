Personal Guide to Testing APIs
==============================

Application interfaces are encountered by almost every engineer (regardless of their fields).  
I use this guide as a default unless stronger guidelines are enforced.

Here, total number of requests are number of users times requests per user.

Parameters for interfaces can be speed, reliability or a function of speed and reliability. Perform a million requests to interface (continuously or in salvos) and measure the time it takes for requests to be successful. The *mean time* for successful requests is the indicator of speed (in respective frameworks and programming languages). The number of contiguous unsuccessful request sequences, and the standard deviations (on both sides of the mean) of successful requests gives the reliability.

Note: It might seem that the distribution (of time it takes to complete requests successfully) will be a Gaussian, and that the standard deviations will be equal, but experiments reveal that the distribution will be Poisson.
