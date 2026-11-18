# ROS 2 Architecture & Middleware - Checkpoint

## Q1: QoS (Quality of Service)
You have a Publisher node (e.g., telemetry at 100Hz) configured with a "Best Effort" QoS, and a Subscriber configured with a "Reliable" QoS. Will the two nodes be able to communicate? Why?

**Answer:**
No, they will not communicate. This is governed by the QoS Compatibility Matrix for the *Reliability* policy. A "Reliable" Subscriber strictly requires the Publisher to guarantee message delivery (which involves buffering and resending lost packets). A "Best Effort" Publisher cannot fulfill this contract, as it operates on a "fire and forget" mechanism. Consequently, the DDS middleware will refuse to establish the connection.

## Q2: Discovery & DDS
How do two ROS 2 nodes launched on two different PCs (connected to the same Wi-Fi router) physically "find" each other and exchange messages, considering there is no longer a central `roscore` like in ROS 1?

**Answer:**
They use the RTPS (Real-Time Publish Subscribe) protocol embedded in the DDS middleware. Node discovery relies on UDP Multicast. When a node starts, it broadcasts its presence to a standard multicast IP address (a phase known as Simple Participant Discovery Protocol, or SPDP). Other nodes on the network listen to this multicast address, acknowledge the new participant via Unicast, and seamlessly establish peer-to-peer data endpoints without any centralized broker.

## Q3: Network Isolation
What exactly is the `ROS_DOMAIN_ID` environment variable used for? What happens if two teams of engineers fly their drones in the same field and on the same network leaving the Domain ID to its default value?

**Answer:**
The `ROS_DOMAIN_ID` acts as a logical network isolation layer. Under the hood, DDS uses this ID as a mathematical offset to calculate the specific UDP ports for multicast and unicast traffic. If two teams share the same local network and leave the ID at its default (0), they will broadcast over the exact same ports. This causes dangerous "cross-talk," where Drone A might receive and execute flight commands published by Team B's ground station, leading to catastrophic crashes.

## Q4: Executors & Callbacks
You are using a `SingleThreadedExecutor`. Inside a subscription callback for a GPS topic, you insert a blocking operation that takes 2 seconds (e.g., a heavy synchronous write to a file). What is the impact on the rest of the node (for example, on safety timers or other callbacks)?

**Answer:**
The entire node will stall for 2 seconds. A `SingleThreadedExecutor` pulls and executes one callback at a time from its internal queue using a single thread. A blocking operation prevents the thread from returning to the queue. This causes "starvation": incoming sensor messages will be dropped (or queue up until memory is exhausted), safety failsafe timers will not trigger, and service requests will time out, fundamentally compromising the real-time constraints of the flight software.