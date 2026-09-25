from src.hardware_discovery import HardwareScanner
from src.ai_agent import AutonomousAIAgent
from src.task_executor import AutonomousTaskExecutor
from src.hal import UniversalHAL
from src.self_healing import SelfHealingEngine
from src.code_generator import DynamicCodeGenerator
from src.cts_runner import HardwareCompatibilityTestSuite

def main():
    print("=" * 60)
    print(" 🚀 Autonomous AI OS - Core Foundation Complete (Phase 1-7)")
    print("=" * 60)
    
    # Phase 1: Hardware Scan
    scanner = HardwareScanner()
    hardware_data = scanner.scan_system()
    
    # Phase 2: AI Agent Decision
    agent = AutonomousAIAgent(hardware_data)
    action_plan, analysis = agent.generate_system_action_plan()
    
    # Phase 4: HAL
    hal = UniversalHAL()
    hal.auto_map_bus_device("Virtual-PCIe", "DEV_CPU_01", {"capabilities": ["compute", "threads"]})
    hal.auto_map_bus_device("Virtual-USB", "DEV_INPUT_01", {"capabilities": ["stream_input"]})
    
    # Phase 5, 6 & 7 Modules
    healer = SelfHealingEngine()
    codegen = DynamicCodeGenerator(ai_mode=analysis['suggested_mode'])
    cts = HardwareCompatibilityTestSuite(hal, healer)
    
    print(f"\n[+] Kernel Operational Mode: {analysis['suggested_mode']}")
    print("[+] Dynamic HAL & Self-Healing Engine Active.")
    print("[+] LLM Dynamic Code Synthesizer Ready.")
    print("[+] Hardware Compatibility Test Suite (CTS) Initialized.")
    print("=" * 60)
    print("Commands: 'hal', 'heal', 'generate', 'cts' (Run Tests), 'exit'")
    print("=" * 60)
    
    executor = AutonomousTaskExecutor(analysis)
    
    while True:
        try:
            user_input = input("\nAutoAI-OS Shell > ")
            cmd = user_input.strip().lower()
            
            if cmd in ['exit', 'quit']:
                print("Shutting down AutoAI-OS Kernel safely...")
                break
                
            if cmd == 'hal':
                print("\n[HAL Hardware Matrix]:")
                print(hal.get_hal_matrix())
                continue

            if cmd == 'heal':
                print("\n[Self-Healing Diagnostic Report]:")
                report = healer.inspect_system_health()
                print(f"Health Status: {report['health_status']}")
                print(f"Memory Load: {report['memory_usage_percent']}% | CPU Load: {report['cpu_usage_percent']}%")
                for action in report['corrective_actions']:
                    print(f"  {action}")
                continue

            if cmd == 'generate':
                print("\n[Synthesizing Driver Code for Unknown Peripheral...]")
                result = codegen.synthesize_and_run("DEV_NEURAL_ACCELERATOR_01", "tensor_compute")
                print(result)
                continue

            if cmd == 'cts':
                cts.run_full_cts_diagnostics()
                continue
                
            if not cmd:
                continue
                
            response = executor.parse_and_execute(user_input)
            print(response)
            
        except KeyboardInterrupt:
            print("\nShutting down AutoAI-OS Kernel...")
            break

if __name__ == "__main__":
    main()
