from src.hardware_discovery import HardwareScanner

def main():
    print("Starting Autonomous AI OS Engine Boot Sequence...\n")
    
    # Initialize Hardware Scanner
    scanner = HardwareScanner()
    hardware_data = scanner.scan_system()
    
    print("[+] Hardware Detected Successfully!")
    print(f"    - System: {hardware_data['platform']['system']} ({hardware_data['cpu']['architecture']})")
    print(f"    - CPU Cores: {hardware_data['cpu']['cores_physical']} Physical / {hardware_data['cpu']['cores_total']} Logical")
    print(f"    - Memory: {hardware_data['memory']['total_gb']} GB Total ({hardware_data['memory']['available_gb']} GB Available)")
    
    print("\n[+] System matrix ready for Autonomous AI Agent analysis.")

if __name__ == "__main__":
    main()
