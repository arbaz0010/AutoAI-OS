import psutil
import platform
import json

class HardwareScanner:
    def __init__(self):
        self.specs = {}

    def scan_system(self):
        # 1. CPU Specifications
        self.specs['cpu'] = {
            'architecture': platform.machine(),
            'processor': platform.processor(),
            'cores_physical': psutil.cpu_count(logical=False),
            'cores_total': psutil.cpu_count(logical=True),
            'frequency_mhz': psutil.cpu_freq().current if psutil.cpu_freq() else "N/A"
        }

        # 2. Memory Specifications
        virtual_mem = psutil.virtual_memory()
        self.specs['memory'] = {
            'total_gb': round(virtual_mem.total / (1024**3), 2),
            'available_gb': round(virtual_mem.available / (1024**3), 2),
            'usage_percent': virtual_mem.percent
        }

        # 3. Platform Details
        self.specs['platform'] = {
            'system': platform.system(),
            'release': platform.release(),
            'version': platform.version()
        }

        return self.specs

    def get_json_specs(self):
        return json.dumps(self.scan_system(), indent=4)

if __name__ == "__main__":
    scanner = HardwareScanner()
    print("=== AutoAI-OS: Hardware Discovery Matrix ===")
    print(scanner.get_json_specs())
