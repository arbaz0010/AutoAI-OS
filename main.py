from src.hardware_discovery import HardwareScanner
from src.ai_agent import AutonomousAIAgent

def main():
    print("=" * 60)
    print(" 🚀 Autonomous AI OS - Booting System Engine")
    print("=" * 60)
    
    # Step 1: Scan Environment
    print("\n[Phase 1] Scanning Hardware Environment...")
    scanner = HardwareScanner()
    hardware_data = scanner.scan_system()
    
    print(f"    ✔ System: {hardware_data['platform']['system']} ({hardware_data['cpu']['architecture']})")
    print(f"    ✔ CPU Cores: {hardware_data['cpu']['cores_physical']} Physical / {hardware_data['cpu']['cores_total']} Logical")
    print(f"    ✔ RAM: {hardware_data['memory']['total_gb']} GB Total")
    
    # Step 2: Initialize AI Agent Analysis
    print("\n[Phase 2] Handing over control to Autonomous AI Agent...")
    agent = AutonomousAIAgent(hardware_data)
    action_plan, analysis = agent.generate_system_action_plan()
    
    print("\n--- AI Agent Analysis Report ---")
    print(f"Hardware Class: {analysis['hardware_rating']}")
    print(f"Recommended System Mode: {analysis['suggested_mode']}")
    print(f"Execution Strategy: {analysis['ai_execution_strategy']}")
    
    print("\n--- Execution Action Plan ---")
    for action in action_plan:
        print(f"  {action}")

    print("\n" + "=" * 60)
    print(" Autonomous AI OS Kernel Active & Ready.")
    print("=" * 60)

if __name__ == "__main__":
    main()
