## API 2022-2023
This is the final project for the Algorithms and Data Structures course at Politecnico di Milano for the academic year 2022/2023. The objective of the project was to design a solution that is efficient in terms of both time and space complexity. This solution was ultimately awarded a score of 30/30.
## Problem Description
This project addresses the challenge of planning the most efficient route between two service stations on a highway. It takes into consideration the unique distance of each station from the highway's start and the range of electric vehicles available for rent at these stations. The goal is to minimize the number of stops required, with a preference for routes that utilize stations closer to the highway's start in case of a non-unique solution.

## Features
<ul>
  <li><Strong>Station Management</Strong>: Add or remove service stations along the highway, each uniquely identified by its distance from the start.</li>
  <li><Strong>Vehicle Management</Strong>: Manage the fleet of electric vehicles at each station, including adding new vehicles or scrapping existing ones based on their range.</li>
  <li><Strong>Route Planning</Strong>: Plan the optimal route between two given stations, ensuring the least number of stops with a preference for earlier stations in case of ties.</li>
</ul>

## My Implementation
The proposed implementation utilizes a red-black tree, where each node stores the unique position of a station and all the vehicles at that station. The chosen policy dictates that the vehicle with the maximum range is placed in the first position to enhance performance during insertion and route planning. The planning algorithm is a customized version of Dijkstra's algorithm designed to better meet the requirement of having a unique solution.
