<div align="center">

## 2D Game Engine Wireframe

![C++](https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-064F8C?style=for-the-badge&logo=cmake&logoColor=white)
![Lua](https://img.shields.io/badge/Lua-2C2D72?style=for-the-badge&logo=lua&logoColor=white)
![GLM](https://img.shields.io/badge/GLM-4A4A4A?style=for-the-badge)
![Dear ImGui](https://img.shields.io/badge/Dear%20ImGui-1F6FEB?style=for-the-badge)
![sol2](https://img.shields.io/badge/sol2-6A1B9A?style=for-the-badge)
<img src="https://img.shields.io/badge/Version-1.0%20in%20progress-orange?logo=git&logoColor=white" alt="Version 1.0 in progress">

</div>

## ECS Structure

The engine uses an Entity-Component-System (ECS) design:

- **Entity**: a unique ID with no data or behaviour
- **Component**: plain data (Transform, RigidBody, Sprite, …), stored in one pool per type
- **System**: logic that runs on every entity whose components match its signature

```mermaid
flowchart TB
    E(["Entity<br/>unique ID only"])

    subgraph REG [Registry]
        direction LR
        CP[("componentPools<br/>component data,<br/>one pool per type")]
        ES[("entityComponentSignatures<br/>which components<br/>each entity has")]
        SYS[("systems<br/>each with a required<br/>componentSignature")]
    end

    E -- "ID indexes into" --> REG

    subgraph CHANGE [When a component is added or removed]
        direction TB
        C1["Write or clear data<br/>in componentPools"] --> C2["Set or clear bit<br/>in entity signature"]
        C2 --> C3{"Entity signature contains<br/>system signature?"}
        C3 -- Yes --> C4["System adds entity"]
        C3 -- No --> C5["System removes entity"]
    end

    subgraph FRAME [Every frame]
        direction TB
        F1["Each system loops over<br/>its matching entities"] --> F2["Reads and updates<br/>their component data"]
    end

    REG --> CHANGE
    CHANGE --> FRAME
    F2 -. "data lives in" .-> CP
```

</div>

## Example layout

| Entity | Signature (T R S) | Transform    | RigidBody  | Sprite     |
| ------ | ----------------- | ------------ | ---------- | ---------- |
| 0      | `111`             | pos (10, 20) | vel (2, 0) | player.png |
| 1      | `101`             | pos (50, 80) | —          | tree.png   |
| 2      | `110`             | pos (0, 0)   | vel (0, 5) | —          |

`MovementSystem` requires Transform + RigidBody (`110`), so it processes entities 0 and 2.

## Project Status

> Version 1.0 is currently in progress.

## Credits

Thanks to **Gustavo Pezzi** for his online 2D game engine course at [Pikuma](https://pikuma.com).
