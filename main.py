from src.hardware_discovery import HardwareScanner
from src.ai_agent import AutonomousAIAgent
from src.task_executor import AutonomousTaskExecutor

def main():
    print("=" * 60)
    print(" 🚀 Autonomous AI OS - Interactive Engine Active")
    print("=" * 60)
    
    # Phase 1: Hardware Scan
    scanner = HardwareScanner()
    hardware_data = scanner.scan_system()
    
    # Phase 2: AI Agent Decision
    agent = AutonomousAIAgent(hardware_data)
    action_plan, analysis = agent.generate_system_action_plan()
    
    print(f"\n[+] Kernel Operational Mode: {analysis['suggested_mode']}")
    print("[+] Zero-Driver Hardware Abstraction Layer Active.")
    print("=" * 60)
    print("Type 'exit' or 'quit' to shut down the Autonomous Shell.")
    print("=" * 60)
    
    # Phase 3: Autonomous AI Shell Loop
    executor = AutonomousTaskExecutor(analysis)
    
    while True:
        try:
            user_input = input("\nAutoAI-OS Shell > ")
            if user_input.strip().lower() in ['exit', 'quit']:
                print("Shutting down AutoAI-OS Kernel safely...")
                break
                
            if not user_input.strip():
                continue
                
            response = executor.parse_and_execute(user_input)
            print(response)
            
        except KeyboardInterrupt:
            print("\nShutting down AutoAI-OS Kernel...")
            break

if __name__ == "__main__":
    main()
