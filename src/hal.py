import json

class UniversalHAL:
    def __init__(self):
        self.registered_interfaces = {}

    def auto_map_bus_device(self, bus_type, device_id, raw_descriptor):
        """
        یہ میتھڈ کسی بھی ہارڈویئر کے سگنل یا ڈسکرپٹر کو پکڑ کر 
        AI ایجنٹ کے لیے قابلِ فہم انٹرفیس میں بدلتا ہے۔
        """
        interface_spec = {
            "bus_type": bus_type,
            "device_id": device_id,
            "status": "Mapped",
            "driver_mode": "Zero-Driver AI Managed",
            "capabilities": raw_descriptor.get("capabilities", ["data_transfer"])
        }
        
        self.registered_interfaces[device_id] = interface_spec
        return interface_spec

    def get_hal_matrix(self):
        return json.dumps(self.registered_interfaces, indent=4)
