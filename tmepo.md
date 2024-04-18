``` markdown
# Use Case Diagram
 
``` 
mermaid
usecase EnvironmentInterface {
  actor User
  User --> (Monitor Agents)
  User --> (Intervene)
  (Display Map) --> WorldMap
}

usecase ExternalAPIsIntegration {
  (Access External Data) --> ExternalAPIsIntegration
  (Perform Analytics) --> ExternalAPIsIntegration
  (Integrate with External Systems) --> ExternalAPIsIntegration
}

usecase Communication {
  (Send Message) --> Communication
  (Receive Message) --> Communication
  (Coordinate Agents) --> Communication
}

usecase ExplorationMapping {
  (Plan Path) --> ExplorationMapping
  (Perform SLAM) --> ExplorationMapping
  (Update Environmental Model) --> ExplorationMapping
}

usecase AIDecisionMaking {
  (Make Decision) --> AIDecisionMaking
  (Learn from Experience) --> AIDecisionMaking
  (Select Strategy) --> AIDecisionMaking
}

usecase FaultDetectionRecovery {
  (Detect Anomaly) --> FaultDetectionRecovery
  (Perform Maintenance) --> FaultDetectionRecovery
  (Initiate Recovery) --> FaultDetectionRecovery
}

usecase AgentArchitecture {
  (Process Sensor Data) --> AgentArchitecture
  (Perform Computation) --> AgentArchitecture
  (Learn from Data) --> AgentArchitecture
}

usecase HardwareInfrastructure {
  (Execute Process) --> HardwareInfrastructure
  (Store Data) --> HardwareInfrastructure
  (Transmit Data) --> HardwareInfrastructure
}

actor User
actor ExternalSystem

User --> EnvironmentInterface
User --> ExternalAPIsIntegration
User --> Communication
User --> ExplorationMapping
User --> AIDecisionMaking
User --> FaultDetectionRecovery
User --> AgentArchitecture
User --> HardwareInfrastructure

ExternalSystem --> ExternalAPIsIntegration
