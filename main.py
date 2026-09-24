from src.hardware_discovery import HardwareScanner
from src.ai_agent import AutonomousAIAgent
from src.task_executor import AutonomousTaskExecutor
from src.hal import UniversalHAL

def main():
    print("=" * 60)
    print(" 🚀 Autonomous AI OS - Interactive Engine & HAL Active")
    print("=" * 60)
    
    # Phase 1: Hardware Scan
    scanner = HardwareScanner()
    hardware_data = scanner.scan_system()
    
    # Phase 2: AI Agent Decision
    agent = AutonomousAIAgent(hardware_data)
    action_plan, analysis = agent.generate_system_action_plan()
    
    # Phase 4: Initialize HAL
    hal = UniversalHAL()
    hal.auto_map_bus_device("Virtual-PCIe", "DEV_CPU_01", {"capabilities": ["compute", "threads"]})
    hal.auto_map_bus_device("Virtual-USB", "DEV_INPUT_01", {"capabilities": ["stream_input"]})
    
    print(f"\n[+] Kernel Operational Mode: {analysis['suggested_mode']}")
    print("[+] Dynamic HAL Initialized. Bus Mapping Complete.")
    print("=" * 60)
    print("Type 'exit' or 'quit' to shut down. Type 'hal' to inspect mapped devices.")
    print("=" * 60)
    
    executor = AutonomousTaskExecutor(analysis)
    
    while True:
        try:
            user_input = input("\nAutoAI-OS Shell > ")
            if user_input.strip().lower() in ['exit', 'quit']:
                print("Shutting down AutoAI-OS Kernel safely...")
                break
                
            if user_input.strip().lower() == 'hal':
                print("\n[HAL Hardware Matrix]:")
                print(hal.get_hal_matrix())
                continue
                
            if not user_input.strip():
                continue
                
            response = executor.parse_and_execute(user_input)
            print(response)
            
        except KeyboardInterrupt:
            print("\nShutting down AutoAI-OS Kernel...")
            break

if __name__ == "__main__":
    main()
