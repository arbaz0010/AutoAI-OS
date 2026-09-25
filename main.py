from src.hardware_discovery import HardwareScanner
from src.ai_agent import AutonomousAIAgent
from src.task_executor import AutonomousTaskExecutor
from src.hal import UniversalHAL
from src.self_healing import SelfHealingEngine
from src.code_generator import DynamicCodeGenerator
from src.cts_runner import HardwareCompatibilityTestSuite
from src.native_bridge import NativeMemoryBridge

def main():
    print("=" * 60)
    print(" 🚀 AutoAI-OS - Core Foundation + Low-Level Native Bridge Active")
    print("=" * 60)
    
    # Core Engine Components
    scanner = HardwareScanner()
    hardware_data = scanner.scan_system()
    
    agent = AutonomousAIAgent(hardware_data)
    action_plan, analysis = agent.generate_system_action_plan()
    
    hal = UniversalHAL()
    hal.auto_map_bus_device("Virtual-PCIe", "DEV_CPU_01", {"capabilities": ["compute", "threads"]})
    
    healer = SelfHealingEngine()
    codegen = DynamicCodeGenerator(ai_mode=analysis['suggested_mode'])
    cts = HardwareCompatibilityTestSuite(hal, healer)
    native_bridge = NativeMemoryBridge()
    
    print(f"\n[+] Operational Mode: {analysis['suggested_mode']}")
    print("[+] Low-Level C-Types Native Memory Bridge Online.")
    print("=" * 60)
    print("Commands: 'hal', 'heal', 'generate', 'cts', 'native' (Test Direct I/O), 'exit'")
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
                continue

            if cmd == 'generate':
                print("\n[Synthesizing Driver Code...]")
                result = codegen.synthesize_and_run("DEV_NEURAL_ACCELERATOR_01", "tensor_compute")
                print(result)
                continue

            if cmd == 'cts':
                cts.run_full_cts_diagnostics()
                continue

            if cmd == 'native':
                print("\n[Testing Low-Level Native Memory & Direct I/O Access...]")
                native_bridge.execute_direct_io_control("PCIe_BUS_0", b"\x00\xFF\xAA\x55_KERNEL_PACKET")
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
